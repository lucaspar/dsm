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

using namespace std;

// SEND MESSAGE TO SERVERS
void SMA::send(string address, long begPos, string message) {

    // log message
    ostringstream ss;
    ss << "Writing message to " << address << " at position " << begPos << endl;
    log(ss.str());


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

    // send to server
    log("Message from server = " + msg.getMessage());
    write(sockfd, &msg, 1);
    read(sockfd, &msg, 1);

    // close socket and return
    close(sockfd);
    return;

};

void tasker(int client_sockfd, char ch) {

    log("Thread is stable, resuming process");

    sleep(1);

    read(client_sockfd, &ch, 1);
    ch++;
    write(client_sockfd, &ch, 1);
    close(client_sockfd);

    log("Successfully finished communication\nThis thread will be terminated.");
}

// READ FROM CLIENTS
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
    char ch;

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
    vector<thread> th_taskers;
    while(th_taskers.size() < 3) {
        log("Server waiting");
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);

        // Logging
        char client_address_string[] = "";
        inet_ntop(AF_INET, &(client_address.sin_addr), client_address_string, INET_ADDRSTRLEN);
        log("Connected to " + string(client_address_string) + "\t:: FIRING NEW THREAD, PLEASE STAND BACK ::" );

        // FIRING THREAD
        thread th_tasker(tasker, client_sockfd, ch);
        th_taskers.push_back(move(th_tasker));

    }

    // Joining threads -- yielding stack smashing detection (like buffer overflow or smthg)
    auto currentThread = th_taskers.begin();
    while (currentThread != th_taskers.end()) {
        currentThread->join();
        currentThread++;
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
        exit(1);
    }

    this->allocated = true;
    log("Allocated " + to_string(shmsz) + " bytes.");

};

// Clear allocated memory
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
    }
}