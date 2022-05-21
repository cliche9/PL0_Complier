#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <iostream>
#include <exception>
using std::exception;
using std::string;

class LexerException: public exception {
public: 
    LexerException(string msg): message(msg) {}
    const char *what()const throw() {
        return message.c_str();
    }
protected:
    string message;
};

class SyntaxException: public exception {
public: 
    SyntaxException(string msg): message(msg) {}
    const char *what()const throw() {
        return message.c_str();
    }
protected:
    string message;
};

#endif