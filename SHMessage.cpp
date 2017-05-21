
#include <iostream>
#include <cstring>
#include "SHMessage.h"
#include "loader.h"

using namespace std;

//______ CONSTRUCTORS _______
// Save in memory constructor
SHMessage::SHMessage (string message, int begPos) {
    this->operation = 'w';
    this->message   = message;
    this->begPos    = begPos;
}

// Read from memory constructor
SHMessage::SHMessage(int start, int length) {
    this->operation = 'r';
    this->message   = "";
    this->begPos    = start;
    this->readLen   = length;
}

SHMessage::SHMessage () {}
//============================


string SHMessage::getMessage() {
    return this->message;
}
/*
void SHMessage::setMessage(string content) {
    this->message = content;
}
*/
// serialize SHMessage object returning byte array
// format: operation (1 byte) + readLen (4 bytes) + begPos (4 bytes) + msgLen (4 bytes) + msg (msgLen bytes)
const char * SHMessage::serialize() {
    int msgLen = (int) this->message.size();
    char * serial = (char *) malloc( sizeof(char) + (3 * sizeof(int)) + (msgLen * sizeof(char)) );

    memcpy( serial,                            &operation,            sizeof( char ) );
    memcpy( serial+sizeof(char),               &readLen,              sizeof( int ) );
    memcpy( serial+sizeof(char)+sizeof(int),   &begPos,               sizeof( int ) );
    memcpy( serial+sizeof(char)+2*sizeof(int), &msgLen,               sizeof( int ) );
    memcpy( serial+sizeof(char)+3*sizeof(int), this->message.c_str(), msgLen * sizeof(char) );

    return serial;
}

// deserialize byte array setting this SHMessage object
// format: operation (1 byte) + readLen (4 bytes) + begPos (4 bytes) + msgLen (4 bytes) + msg (msgLen bytes)
void SHMessage::deserialize(const char * serial) {

    int msgLen;

    memcpy( &(this->operation),  serial,                            sizeof( char ) );
    memcpy( &(this->readLen),    serial+sizeof(char),               sizeof( int ) );
    memcpy( &(this->begPos),     serial+sizeof(char)+sizeof(int),   sizeof( int ) );
    memcpy( &msgLen,             serial+sizeof(char)+2*sizeof(int), sizeof( int ) );

    char *message = (char *) malloc(sizeof(char) * (msgLen+1));
    memcpy(message, serial+(3*sizeof(int) + sizeof(char)), (size_t) msgLen * sizeof(char));
    message[msgLen] = '\0';
    this->message = string(message);

    log("\tSHMessage: deserialized message: '" + this->message + "'");

}

