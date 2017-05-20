
#include <iostream>
#include <cstring>
#include "SHMessage.h"
#include "loader.h"

using namespace std;

SHMessage::SHMessage (string message, int begPos) {
    this->message   = message;
    this->begPos    = begPos;
}

SHMessage::SHMessage () {}

string SHMessage::getMessage() {
    return this->message;
}

// serialize SHMessage object returning byte array
// format: begPos (4 bytes) + msgLen (4 bytes) + msg (msgLen bytes)
const char * SHMessage::serialize() {
    int msgLen = (int) this->message.size();
    char * serial = (char *) malloc( (2 * sizeof(int)) + (msgLen * sizeof(char)) );

    memcpy( serial, &begPos, sizeof( int ) );
    memcpy( serial+sizeof(int), &msgLen, sizeof( int ) );
    memcpy( serial+(2*sizeof(int)), this->message.c_str(), msgLen * sizeof(char) );

    return serial;
}

// deserialize byte array creating SHMessage object
// format: begPos (1byte) + msgLen (1byte) + msg (msgLen bytes)
void SHMessage::deserialize(const char * serial) {

    int msgLen;

    memcpy( &(this->begPos), serial, sizeof( int ) );
    memcpy( &msgLen, serial+sizeof(int), sizeof( int ) );

    char *message = (char *) malloc(sizeof(char) * (msgLen+1));
    memcpy(message, serial+(2*sizeof(int)), (size_t) msgLen);
    message[msgLen] = '\0';
    this->message = string(message);

    log("\tSHMessage: deserialized message: " + this->message);

}
