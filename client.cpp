/* CLIENT CODE */

#include <iostream>
#include "loader.h"     // project-level methods and config loader
#include "sma.h"        // Shared Memory API

using namespace std;

int main () {

    // Read configuration file
    Config config = readConfig();
    log(config);

    // Prepare message to send
    string message = "I'm sorry, Dave";
    int msgSize = (int) message.size();
    int totalShared = config.sharedBytes * config.nServers;
    int maxBeg = totalShared - msgSize - 2;     // max beginning position for writing
    int begPos = randomByte( maxBeg );          // pick a random beginning position
    int endPos = begPos + msgSize + 1;          // position of last byte to send

    // Select servers (by index) to send data
    int begServer = (int) ( begPos / (config.sharedBytes - 1) );
    int endServer = (int) ( begServer + (msgSize / (config.sharedBytes - 1)) );

    // Write data using the API in sma.h
    SMA interface;
    for (int s=begServer; s<=endServer; s++){
        string address = config.serverAddr[s];
        interface.send(address, begPos, message);
    }

    log("-- CLIENT FINISHED --");
    exit(0);

}