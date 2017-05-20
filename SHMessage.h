//
// Created by lucas on 18/05/17.
//

#ifndef PROJECT_SHMESSAGE_H
#define PROJECT_SHMESSAGE_H

#include <string>

using namespace std;

class SHMessage {
public:
    SHMessage();
    SHMessage (string, int);

    string getMessage();
    const char * serialize();
    void deserialize(const char *serial);

    int begPos;
private:
    string message;

};


#endif //PROJECT_SHMESSAGE_H
