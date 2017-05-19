/* SHARED MEMORY API */

#ifndef PROJECT_SMA_H
#define PROJECT_SMA_H
#define SHMKEY 3403607790       //  0xcadeeeee

#include <iostream>
#include <sstream>
#include "loader.h"
#include "sma.h"

using namespace std;

class SMA {

public:
    void send(string address, long begPos, string message);     // send @message to server at @address start writing at position @begPos
    void recv();                                                // receive a message from a client
    void byteMe(size_t SHMSZ);                                  // locally allocate @shmsz bytes of interprocess memory

private:
    void clearMemory();             // Clear local shared memory
    void logMemory();               // Print local shared memory

    bool allocated = false;
    char *shm;
    size_t shmsz;

};

#endif //PROJECT_SMA_H
