
#include <iostream>
#include "SHMessage.h"

using namespace std;

SHMessage::SHMessage (string message, int begPos) {
    this->message    = message;
    this->begPos     = begPos;
}

string SHMessage::getMessage() {
    return this->message;
}