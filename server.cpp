#include "sma.h"        // Shared Memory API

int main() {

    SMA interface;

    // Read configuration file
    Config config = readConfig();
    log(config);

    // Allocate shared memory
    interface.byteMe((size_t) config.sharedBytes);

    // Clear and log memory
    interface.clearMemory();
    interface.logMemory();

    // Wait for new connections:
    interface.recv();

}