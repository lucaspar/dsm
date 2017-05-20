// SHARED MEMORY API

// C/C++
#include <iostream>
#include <sstream>
#include <thread>
#include <unistd.h>

// Local
#include "loader.h"
#include "sma.h"
#include "SHMessage.h"

// Sockets
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// IPC shared memory
#include <sys/ipc.h>
#include <sys/shm.h>

// Suppressing a few warnings
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

using namespace std;

// SEND MESSAGE TO SERVERS
void SMA::send(string address, int begPos, string message) {

    // configure socket
    struct sockaddr_in addr;
    socklen_t len;
    inet_pton(AF_INET, address.c_str(), &(addr.sin_addr));
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = 9734;
    len = sizeof(addr);

    // connect
    int result = connect(sockfd, (struct sockaddr *)&addr, len);

    // error handling
    if(result == -1) {
        perror(string("ERROR @SMA::send() >>> Failed sending to " + address).c_str());
        exit(1);
    }

    // build message
    SHMessage msg = SHMessage(message, begPos);

    const char *serial = msg.serialize();

    // log message
    ostringstream ss;
    ss << "Writing '"+ msg.getMessage() + "' to server " << address << " at position #" << begPos << endl;
    log(ss.str());

    size_t totalLength = 2*sizeof(int) + msg.getMessage().size();       // totalLength = begPos + msgLen + message.size()

    write(sockfd, &totalLength, sizeof(size_t));            // send length of total message
    write(sockfd, serial, totalLength * sizeof(char));      // send message

    // close socket and return
    close(sockfd);
    return;

};

void tasker(int client_sockfd, SHMessage msg, SMA * interface) {

    log("\tThread created");
    sleep(1);

    // read size
    size_t totalLength = 0;
    read(client_sockfd, &totalLength, sizeof(size_t));

    // read data
    char *serial = (char *) malloc(totalLength * sizeof(char));
    read(client_sockfd, serial, totalLength);
    log("\tRead message of " + to_string(totalLength) + " bytes from client");

    // deserialize
    msg.deserialize((const char *) serial);
    string read_msg = "Message read by server.";

    // save message to shared memory
    interface->save(msg.getMessage().c_str(), msg.begPos, (int) msg.getMessage().size());

    // send status to client
    //write(client_sockfd, &read_msg, read_msg.length());

    close(client_sockfd);

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
    log("NEW SERVER: " + string(server_address_string));

    // Receive from clients
    thread th_array[300];
    for(int i=0; true; i++){         // intentional endless loop

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
    }

    // Joining threads
    for(int i=0; i<300; i++){
        th_array[i].join();
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

    // Attach the segment to our data space
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
    if(shmsz < localStartPos+nbytes){
        log("ERROR @SMA::write() >>> Trying to fit "+to_string(localStartPos+nbytes)+"b in "+to_string(shmsz)+"b space.");
        exit(3);
    }
    char * realStartPos = (this->shm)+localStartPos;
    for (s = realStartPos; s - realStartPos < nbytes; s++){
        *s = *ptr;
        ptr++;
    }
    *s = '\0';                      // null termination
    logMemory();
}

// Clear allocated memory with null characters
void SMA::clearMemory() {
    char *s;
    for (s = this->shm; s - shm < shmsz; s++){
        *s = '\0';
    }
    log("Memory cleared");
}

// Prints memory to stdout for debugging
void SMA::logMemory() {
    char *s;
    for (s = shm; s - shm < shmsz; s++){
        printf("%c", *s);
        if ((s-shm) % 128 == 0) printf("\n");
        if(*s == '\0') printf(".");
    }
    printf("\n");
}
#pragma clang diagnostic pop