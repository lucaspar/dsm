#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "loader.h"

#define CONFIG_FILE "mcomp.cfg"

using namespace std;

// Return Config object by reading CONFIG_FILE
Config readConfig() {

    ifstream cfgStream;
    cfgStream.open(CONFIG_FILE);
    if(!cfgStream.is_open()) log(string("Error opening ")+CONFIG_FILE);

    // Read and cleanup
    string line;
    vector<string> lines;
    while (!cfgStream.eof()) {
        getline(cfgStream, line);

        // Remove whitespaces and comments (#)
        line.erase( remove_if(line.begin(), line.end(), ::isspace), line.end() );
        if(line[0] == '#' || line.size() == 0) continue;

        lines.push_back(line);
    }
    cfgStream.close();

    // Build object
    Config config;
    config.sharedBytes = stoi(lines[0]);
    config.nServers = (unsigned int) stoi(lines[1]);
    for(vector<string>::size_type k=2; k!=2+config.nServers; k++){
        config.serverAddr.push_back( lines[k] );
    }

    // sort addresses to determine primary server to snapshot
    sort(config.serverAddr.begin(), config.serverAddr.end());

    return config;
}

// Prints log messages to stdout
void log (Config config) {
    ostringstream ss;
    ss << "_________________________________\nConfig file:" << endl;
    ss << "\tMemory size (bytes):\t" << config.sharedBytes << endl;
    ss << "\tNumber of servers:\t\t" << config.nServers << endl;
    ss << "\tServers' addresses:" << endl;
    for(auto& v : config.serverAddr) {
        ss << "\t\t" << v << endl;
    }
    ss << "_________________________________\n";
    log(ss.str());
}

void log (string logMessage) {
    cout << logMessage << endl;
}

int randomByte (int sharedBytes) {

    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(0,sharedBytes); // guaranteed unbiased

    return uni(rng);
};
