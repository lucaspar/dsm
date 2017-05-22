// SHARED MEMORY API

// C/C++
#include <iostream>
#include <sstream>
#include <thread>
#include <unistd.h>

// Local
#include "loader.h"
#include "sma.h"

// Sockets
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// IPC shared memory
#include <sys/ipc.h>
#include <sys/shm.h>

// Semaphore
#include <sys/sem.h>
#include "semun.h"

// Suppressing a few warnings
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

using namespace std;

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);   // para esperar pelo acesso
static int semaphore_v(void);   // para liberar o acesso

static int sem_id;

// SEND MESSAGE TO SERVERS
void SMA::send(string address, SHMessage msg) {

    // configure socket
    struct sockaddr_in addr;
    socklen_t len;
    //printf("ADDR: %s", address.c_str());
    inet_pton(AF_INET, address.c_str(), &(addr.sin_addr));

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = 9734;
    len = sizeof(addr);

    // connect
    int result = connect(sockfd, (struct sockaddr *)&addr, len);

    // error handling
    log(string(inet_ntoa(addr.sin_addr)));
    if(result == -1) {
        perror(string("ERROR @SMA::send() >>> Failed sending to " + address).c_str());
        exit(1);
    }

    // log message
    ostringstream ss;
    if(msg.operation == 'r'){
        ss << "Reading "+ to_string(msg.readLen) + " bytes from server " << address << " at position #" << msg.begPos << endl;
    }
    else if(msg.operation == 'w'){
        ss << "Writing '"+ msg.getMessage() + "' to server " << address << " at position #" << msg.begPos << endl;
    }
    else {
        ss << "ERROR @SMA::send() >>> Invalid operation '" << msg.operation << "'" << endl;
        exit(2);
    }
    log(ss.str());

    size_t totalLength = sizeof(char) + 3*sizeof(int) + msg.getMessage().size()*sizeof(char);
    // size of totalLength: operation + readLen+begPos+msgLen + message.size()

    const char *serial = msg.serialize();
    write(sockfd, &totalLength, sizeof(size_t));            // send length of total message
    write(sockfd, serial, totalLength * sizeof(char));      // send message

    if(msg.operation == 'r') {
        char *content = (char *) malloc(msg.readLen * sizeof(char));
        read(sockfd, content, msg.readLen * sizeof(char));
        log("Content read: '" + string(content) + "'");
    }

    // close socket and return
    close(sockfd);
    return;

};

void tasker(int client_sockfd, SHMessage msg, SMA * interface) {

    log("\tThread created");
    sleep(1);

    // retrieve size
    size_t totalLength = 0;
    read(client_sockfd, &totalLength, sizeof(size_t));

    // retrieve snap
    char *serial = (char *) malloc(totalLength * sizeof(char));
    read(client_sockfd, serial, totalLength);
    log("\tRead message of " + to_string(totalLength) + " bytes from client");

    // deserialize
    msg.deserialize((const char *) serial);
    string read_msg = "Message retrieved by server.";

    // identify type of operation
    switch (msg.operation) {
        case 'r':           // retrieve content from shared memory
        {
            log("\tClient reading from memory");
            char *content = (char *) malloc(msg.readLen * sizeof(char));
            interface->retrieve(msg.begPos, msg.readLen, content);          // retrieve from memory
            write(client_sockfd, content, msg.readLen * sizeof(char));      // send back to client
            break;
        }
        case 'w':           // save message to shared memory
            log("\tClient writing to memory");
            interface->save(msg.getMessage().c_str(), msg.begPos, (int) msg.getMessage().size());
            break;
        default:
            log("\tClient requested invalid operation.");
    }

    close(client_sockfd);       // close connection
    log("\tThread finished");

}

// Receive requests from clients and start new threads
void SMA::recv() {

    // Checks if memory was allocated
    if(!this->allocated){
        log(">>> Allocate memory before usage by calling SMA::byteMe(size_t).");
        return;
    }

    int server_sockfd, client_sockfd;
    socklen_t server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    // Set socket params
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = 9734;
    server_len = sizeof(server_address);

    // Bind socket
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(server_sockfd, 5);

    // Log server address
    char server_address_string[] = "";
    inet_ntop(AF_INET, &(server_address.sin_addr), server_address_string, INET_ADDRSTRLEN);
    log("NEW SERVER");

    // Receive from clients
    thread th_array[1000];
    for(int i=0; i<1000; i++) {

        log("[Server] Waiting for connection");
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);

        // Logging
        char client_address_string[] = "";
        inet_ntop(AF_INET, &(client_address.sin_addr), client_address_string, INET_ADDRSTRLEN);
        log("[Server] Connected to " + string(client_address_string) + "\tNew thread incoming..." );

        // FIRING THREAD
        SHMessage msg = SHMessage();
        th_array[i] = thread(tasker, client_sockfd, msg, this);
        th_array[i].detach();
    }
}

// Allocates shared memory using IPC
void SMA::byteMe(size_t sharedSize) {

    int shmid;
    this->shmsz = sharedSize;

    // Create the memory segment
    if ((shmid = shmget((key_t) SHMKEY, shmsz, IPC_CREAT | 0666)) < 0) {
        perror("ERROR @SMA::byteMe() >>> SHMGET");
        exit(1);
    }

    // Attach the segment to our snap space
    if ((shm = (char *) shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("ERROR @SMA::byteMe() >>> SHMAT");
        exit(2);
    }

    this->allocated = true;
    log("Allocated " + to_string(shmsz) + " bytes.");

};

// Save nbytes [1,k] bytes from ptr to shared memory starting at localStartPos [0,k-1]
void SMA::save(const char * ptr, int localStartPos, int nbytes) {
    char *s;
    sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);

    // LOCK
    if (!set_semvalue()) {
        fprintf(stderr, "Falha ao inicializar o semaforo\n");
        exit(EXIT_FAILURE);
    }

    if (!semaphore_p()) {
        exit(EXIT_FAILURE);
    }
    log("\tLocked");

    if(shmsz < localStartPos+nbytes){
        log("ERROR @SMA::save() >>> Trying to fit "+to_string(localStartPos+nbytes)+"b in "+to_string(shmsz)+"b space.");
        exit(3);
    }
    char * realStartPos = (this->shm)+localStartPos;
    for (s = realStartPos; s - realStartPos < nbytes; s++){
        *s = *ptr;
        ptr++;
    }

    *s = '\0';                  // force null termination

    // UNLOCK
    if (!semaphore_v())
        exit(EXIT_FAILURE);
    log("\tUnlocked");
    del_semvalue();

    logMemory();
}

// Retrieve @length bytes of shared memory starting at @start
void SMA::retrieve(int start, int length, char * content) {
    if(start + length > shmsz) {
        log("ERROR @SMA::read() >>> Trying to retrieve until position "+to_string(start+length-1)+" in "+to_string(shmsz)+"b memory.");
    }
    char *s;
    printf(string("\t\tRETRIEVING from memory (" + to_string(start) + " to " + to_string(start+length) + "):\n\t\t").c_str());
    for (s = shm+start; s-shm < start+length; s++) {
        *content = *s;
        printf("%c", *content);
        content++;
    }
    *content = '\0';        // force null termination
}

// Clear allocated memory with null characters
void SMA::clearMemory() {
    char *s;
    for (s = this->shm; s - shm < shmsz; s++){
        *s = '\0';
    }
    log("Memory cleared");
}

// Print memory to stdout for debugging
void SMA::logMemory() {
    char *s;
    for (s = shm; s - shm < shmsz; s++){
        printf("%c", *s);
        if ((s-shm) % 128 == 0) printf("\n");
        if(*s == '\0') printf(".");
    }
    printf("\n");
}

/*
set_semvalue inicializa o semaforo usando o comando SETVAL em uma chamada semctl.
*/

static int set_semvalue(void)  {
    union semun sem_union;
    sem_union.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
        return(0);
    return(1);
}

/* del_semvalue remove o semaforo com identificador ID. Tambem usa semctl, mas
   o comando IPC_RMID remove o semaforo. */

static void del_semvalue(void) {
    union semun sem_union;

    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
        fprintf(stderr, "Falha ao remover o semaforo\n");
}

/* semaphore_p muda o semaforo para -1 (esperando). */

static int semaphore_p(void)
{
    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op = -1; /* P() */
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "semaphore_p falhou\n");
        return(0);
    }
    return(1);
}

/* semaphore_v torna o semaforo disponivel, atribuindo 1 para a parte sem_op do buffer
   (estrutura sembuf),
*/

static int semaphore_v(void)
{
    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op = 1; /* V() */
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "semaphore_v falhou\n");
        return(0);
    }
    return(1);
}

#pragma clang diagnostic pop