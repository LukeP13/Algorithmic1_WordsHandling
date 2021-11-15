#include "myexception.hpp"

myexception::myexception(const std::string message): _message(message) { }

myexception::~myexception() throw() {
}

const char* myexception::what() const throw() {
        return _message.c_str();
}

