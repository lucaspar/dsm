
#include <cstdio>
#include <cstdlib>
#include <zconf.h>

// Local
#include "loader.h"

// Sockets
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// IPC shared memory
#include <sys/shm.h>
#include <ifaddrs.h>
#include <cstring>
#include <thread>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

#define SHMSZ   27
#define SHMKEY  3403607790              //  0xCADEEEEE
#define clear() printf("\033[H\033[J")  // clear console
#define LOG     true                    // logging enabled/disabled

bool    isMaster        (const char *addr);
char*   locateSHM       (char *shm);
char*   getLocalIP      (char *resultIP);
int     setSlaveSocket  (string address);
int     setMasterSocket ();
void    logMemory       (char *, int);
void    logTime         ();
void    snapMaster      (Config config, char * shm);
void    snapSlave       (Config config, char * shm, unsigned int interval);
void    receiver        (int client_sockfd, int length, string client_address);
void    saveToFile      (char *data, int length, string basic_string);
void    appendToFile    (string basic_string, string basicString, int length);

int main(int argc, char **argv) {

    // Read configuration file
    Config config = readConfig();

    // Locate shared memory segment
    char *shm = nullptr;
    shm = locateSHM(shm);

    // Call master or slave thread
    thread th;
    bool master;
    unsigned int interval = 60;                         // Interval between snaps slaves send to master
    if (argc>1) {
        master = ( argv[1][0] == 'm' );
        if(argc>2) {
            interval = (unsigned int) atoi(argv[2]);
        }
    }
    else master = isMaster( config.serverAddr[0].c_str() );

    if ( master ) {                                     // Snapshot master process
        th = thread(snapMaster, config, shm);
    }
    else {                                              // Snapshot slave process
        th = thread(snapSlave, config, shm, interval);
    }

    th.detach();

    // Log snap forever to stdout
    while (LOG) {
        log(config);
        logTime();
        logMemory(shm, config.sharedBytes);

        sleep(3);
        clear();
    }
}

// Thread do snapshot slave
void snapSlave(Config config, char * shm, unsigned int interval) {
    log("Slave thread running");

    int sockfd;
    //logMemory(shm, config.sharedBytes);

    while (true) {
        sockfd = setSlaveSocket(config.serverAddr[0]);
        write(sockfd, shm, (size_t) config.sharedBytes);
        close(sockfd);
        sleep(interval);
    }

}

// Thread do snapshot master
void snapMaster(Config config, char * shm) {
    log("Master thread running");
    logMemory(shm, config.sharedBytes);

    int client_sockfd, server_sockfd = setMasterSocket();
    struct sockaddr_in client_address;
    socklen_t client_len;

    // Accept connections from snapshot processes
    thread th_array[config.nServers];
    while (true) {
        for(int i=0; i<config.nServers; i++) {

            log("[Snapshot master] Waiting for connection");
            client_len = sizeof(client_address);
            client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);

            // Logging
            char client_address_string[] = "";
            inet_ntop(AF_INET, &(client_address.sin_addr), client_address_string, INET_ADDRSTRLEN);
            log("[Snapshot master] Connected to " + string(client_address_string) + "\tNew thread incoming..." );

            // FIRING THREAD
            th_array[i] = thread(receiver, client_sockfd, config.sharedBytes, string(client_address_string));
        }

        // Joining threads
        for(int i=0; i<config.nServers; i++){
            th_array[i].join();
        }

        // Save local memory to file
        saveToFile(shm, config.sharedBytes, "snap/" + config.serverAddr[0]+".snap");

        // Join all files
        unsigned long epoch = (unsigned long) time(NULL);
        for(int i=0; i<config.nServers; i++){
            string outputFilename = "snap/" + to_string(epoch) + ".snapshot";
            string inputFilename = "snap/" + config.serverAddr[i] + ".snap";
            appendToFile(inputFilename, outputFilename, config.sharedBytes);
        }
    }

}

// Appends @length bytes of input file to output;
void appendToFile(string inputFilename, string outputFilename, int length) {
    FILE *input, *output;

    // open input file
    input = fopen(inputFilename.c_str(), "r");
    if (input == NULL) {
        printf("ERROR @snapshot::appendToFile() could not open the input file %s\n", inputFilename.c_str());
        exit(5);
    }

    char * buffer = (char *) malloc(length * sizeof(char));
    fread(buffer, (size_t) length, sizeof(char), input);
    fclose(input);

    // open output file
    output = fopen(outputFilename.c_str(), "a");
    if (output == NULL) {
        printf("ERROR @snapshot::appendToFile() could not open the input file %s\n", outputFilename.c_str());
        exit(5);
    }

    fwrite(buffer, (size_t) length, sizeof(char), output);
    fclose(output);
}

// receive snap from client
void receiver(int client_sockfd, int length, string client_address) {

    log("IN THREAD");

    char *data = (char *) malloc(length * sizeof(char));
    read(client_sockfd, data, (size_t) length);

    log("Data received: ");
    logMemory(data, length);

    string filename = "snap/" + client_address + ".snap";
    log(filename);
    saveToFile(data, length, filename);

    close(client_sockfd);
}

// Save @snap to file named @filename
void saveToFile(char *data, int length, string filename) {

    // open file
    FILE *file = fopen(filename.c_str(), "w");
    if (file == NULL) {
        printf("ERROR @snapshot::saveToFile() could not open the file!\n");
        exit(5);
    }

    // write to file
    fwrite(data, (size_t) length, sizeof(char), file);

    fclose(file);
}

int setMasterSocket() {
    int server_sockfd;
    socklen_t server_len;
    struct sockaddr_in server_address;

    // Set socket params
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = 9700;
    server_len = sizeof(server_address);

    // Bind socket
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(server_sockfd, 5);

    // Log server address
    char server_address_string[] = "";
    inet_ntop(AF_INET, &(server_address.sin_addr), server_address_string, INET_ADDRSTRLEN);

    return server_sockfd;
}

// Setup a socket to address @address:9700
int setSlaveSocket(string address) {

    // Configure socket
    struct sockaddr_in addr;
    socklen_t len;
    inet_pton(AF_INET, address.c_str(), &(addr.sin_addr));
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = 9700;
    len = sizeof(addr);

    // Connect
    int result = connect(sockfd, (struct sockaddr *)&addr, len);

    // Error handling
    if(result == -1) {
        perror(string("ERROR @main() >>> Failed connecting to " + address).c_str());
    }

    return sockfd;
}

// Locate shared memory in this server
char * locateSHM(char *shm) {
    int shmid;

    // Locate the segment.
    if ((shmid = shmget((key_t) SHMKEY, SHMSZ, 0666)) < 0) {
        perror("ERROR @snapshot::locateSHM() >>> shmget");
        exit(1);
    }
    // Attach the segment to this snap space.
    if ((shm = (char *) shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("ERROR @snapshot::locateSHM() >>> shmat");
        exit(1);
    }

    return shm;
}

bool isMaster(const char *masterAddr) {
    char *thisIP = nullptr;
    thisIP = getLocalIP(thisIP);
    log("\nLocal IP: " + string(thisIP) + " \tMaster IP: " + masterAddr);
    return strcmp(masterAddr, thisIP) == 0;
}

// Get local IP address of this machine
char * getLocalIP(char *resultIP) {

    struct ifaddrs *ifaptr, *ifa;
    getifaddrs(&ifaptr);
    ifa = ifaptr;

    while (ifa)
    {
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) {
            struct sockaddr_in *pAddr = (struct sockaddr_in *)ifa->ifa_addr;
            resultIP = inet_ntoa(pAddr->sin_addr);
            //printf("%s: %s\n", ifa->ifa_name, resultIP);
            if (strstr(resultIP, "10.") != NULL || strstr(resultIP, "192.") != NULL) {       // probably local ip address
                return resultIP;
            }
        }
        ifa = ifa->ifa_next;
    }
    freeifaddrs(ifaptr);

    return resultIP;
}

// Print current time to stdout
void logTime() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\t\t%d-%d-%d %d:%d:%d\n\n", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

// Print shared memory content to stdout
void logMemory(char *shm, int length) {
    char *s;

    log("MEMORY SNAPSHOT:\n|");
    for (s = shm; s-shm < length; s++) {
        if(*s == '\0') putchar(' ');        // print space for null characters
        else putchar(*s);
    }
    log("|\n\n____________________________________\n");
}

#pragma clang diagnostic pop