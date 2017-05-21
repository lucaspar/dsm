#ifndef PROJECT_SHMESSAGE_H
#define PROJECT_SHMESSAGE_H

#include <string>

using namespace std;

class SHMessage {
public:
    SHMessage();
    SHMessage (string, int);    // writing to memory purposes (message, position)
    SHMessage (int, int);       // reading from memory purposes (start, length)

    string getMessage();
    void setMessage(string);

    const char * serialize();               // serialize to send over the network
    void deserialize(const char *serial);   // deserialize to retrieve data and save

    int begPos;                 // starting position (used to retrieve and write)
    int readLen;                // number of bytes to retrieve
    char operation;             // 'r' for retrieve, 'w' for write: set using the constructors above

private:
    string message;

};


#endif //PROJECT_SHMESSAGE_H
