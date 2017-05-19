//
// Created by lucas on 18/05/17.
//

#ifndef PROJECT_SHMESSAGE_H
#define PROJECT_SHMESSAGE_H

#include <string>

using namespace std;

class SHMessage {
public:
    SHMessage (string, int);
    string getMessage();

private:
    string message;
    int begPos;
};


#endif //PROJECT_SHMESSAGE_H
