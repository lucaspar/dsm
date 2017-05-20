/* SHARED MEMORY API */

#ifndef PROJECT_SMA_H
#define PROJECT_SMA_H
#define SHMKEY 3403607790       //  0xCADEEEEE

#include <iostream>
#include <sstream>
#include "loader.h"
#include "sma.h"

using namespace std;

class SMA {

public:
    void send(string address, int begPos, string message);      // SEND @message to @address to write at position @begPos
    void recv();                                                // RECEIVE a message from a client that used send()
    void byteMe(size_t SHMSZ);                                  // ALLOCATE local @SHMSZ bytes of inter-process memory
    void save(const char *ptr, int localStartPos, int nbytes);  // SAVE @nbytes at @localStartPos pointed by @ptr
    void clearMemory();                                         // CLEAR local shared memory
    void logMemory();                                           // PRINT local shared memory

private:

    bool allocated = false;     // whether inter-process memory was allocated or not
    char *shm;                  // pointer to inter-process memory
    size_t shmsz;               // size of inter-process memory

};

#endif //PROJECT_SMA_H
