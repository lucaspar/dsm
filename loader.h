/* PROJECT-LEVEL METHODS AND CONFIGURATION FILE LOADER */

#ifndef PROJECT_LOADER_H
#define PROJECT_LOADER_H

#include <vector>
#include <string>

using namespace std;

class Config {
public:
    int sharedBytes;                // bytes of available memory in each server
    unsigned int nServers;          // number of servers available
    vector<string> serverAddr;      // ip address of each server
};

void log (string logMessage);
void log (Config config);
int randomByte(int sharedBytes);
Config readConfig();

#endif //PROJECT_LOADER_H

