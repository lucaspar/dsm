/* CLIENT CODE */

#include <iostream>
#include <cstring>
#include "loader.h"     // project-level methods and config loader
#include "sma.h"        // Shared Memory API

void printUsage();
void serverSolver(Config, SHMessage);

using namespace std;

int main (int argc, char **argv) {

    if (argc != 1 && argc != 4) {           // invalid arguments
        printUsage();
        exit(-1);
    }

    // Read configuration file
    Config config = readConfig();
    log(config);

    // Build message to send and pick a random position in memory
    string msg;
    int start, length;
    SHMessage message;

    if(argc == 4) {
        if(argv[1][0] == 'r'){
            start   = stoi(argv[2]);
            length  = stoi(argv[3]);
            message = SHMessage(start, length);
        }
        else if(argv[1][0] == 'w'){
            msg     = string(argv[2]);
            start   = stoi(argv[3]);
            message = SHMessage(msg, start);
        }
        else {
            printUsage();
            exit(-1);
        }
    }
    else {                                                  // no arguments, write to random position"
        int totalShared = config.sharedBytes * config.nServers;
        start = randomByte((int) (totalShared - msg.size() - 2));   // pick a random possible start position
        msg = "Dormammu i've come to bargain";
        message = SHMessage(msg, start);                    // create message to send over network
    }

    serverSolver(config, message);

    log("-- CLIENT FINISHED --");
    exit(0);

}

// Choose the servers to send data
void serverSolver(Config config, SHMessage message) {

    // Select servers (by index) to send data
    int begServerIndex = message.begPos / (config.sharedBytes - 1);
    int effectiveLength = (int) ((message.begPos % config.sharedBytes) + message.getMessage().size());
    int endServerIndex = begServerIndex + ( effectiveLength / config.sharedBytes );

    log("Start server: " + config.serverAddr[begServerIndex] + "\t End server: " + config.serverAddr[endServerIndex] );
    SMA interface;
    SHMessage partial;

    int partial_start, partial_length, partial_capacity, remaining_bytes;

    if(message.operation == 'r') remaining_bytes = message.readLen;
    else if(message.operation == 'w') remaining_bytes = (int) message.getMessage().size();
    else {
        log("ERROR serverSolver(): Invalid operation ('r'|'w')");
        exit(-1);
    }

    for(int s=begServerIndex; s<=endServerIndex; s++) {

        if(s==begServerIndex) {
            partial_capacity = config.sharedBytes - message.begPos;
            partial_start = message.begPos;
            partial_length = (remaining_bytes > partial_capacity) ? partial_capacity : remaining_bytes;
        }
        else if (s==endServerIndex) {
            partial_start = 0;
            partial_length = remaining_bytes % config.sharedBytes;
        }
        else {
            partial_start = 0;
            partial_length = config.sharedBytes;
        }
        
        string address(config.serverAddr[s]);
        remaining_bytes -= partial_length;

        /*
        ostringstream ss;
        ss << "remaining_bytes: " << to_string(remaining_bytes) << endl;
        ss << "partial_start: " << to_string(partial_start) << endl;
        ss << "partial_length: " << to_string(partial_length) << endl;
        log(ss.str());
         */

        if(message.operation == 'r') {
            // create object to send over network
            partial = SHMessage(partial_start, partial_length);
            //log("READ " + address + " -> " + to_string(partial_start) + " to " + to_string(partial_start + partial_length));
        }

        else if(message.operation == 'w') {

            // trim the message to fit server border
            char *pmsg =            (char *) malloc(message.getMessage().size() * sizeof(char));
            char *partial_message = (char *) malloc(sizeof(char) * partial_length);
            strcpy(pmsg, message.getMessage().c_str());
            for (int k=0; k<partial_length; k++){
                partial_message[k] = pmsg[k];
            }
            partial_message[partial_length] = '\0';

            // update message with the remaining substring only
            string remaining_string = message.getMessage().substr((unsigned long) (partial_length));
            //log("Remaining string: " + remaining_string);
            message.setMessage( remaining_string );

            // create object to send over network
            partial = SHMessage(string(partial_message), partial_start);
            //log("WRITE " + string(partial_message) + " to " + address + " -> " + to_string(partial_start) + " to " + to_string(partial_start + partial_length));
        }

        interface.send(address, partial);
    }

}

void printUsage() {
    log("Usage:\n\tTo retrieve from shared memory:\n\t\t./client r [start] [length]\n\n\tTo write to shared memory:\n\t\t./client w [message] [start]\n");
}