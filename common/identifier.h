#ifndef _IDENTIFIER_H_
#define _IDENTIFIER_H_

#include "common.h"
#include <iomanip>
using std::setiosflags;
using std::setw;

/* ============ 符号表(标识符)相关定义 ============ */ 
enum KIND {
    NIL,
    CONST,
    VAR,
    PROC,
};

const vector<string> kind2str = {
    "NONE",
    "CONSTANT",
    "VARIABLE",
    "PROCEDURE",
};

struct Identifier {
    Identifier(string _name = "", KIND _kind = NIL, int _val = 0, int _lev = -1, int _addr = -1, int _quadAddr = -1):
        name(_name), kind(_kind), value(_val), level(_lev), addr(_addr), quadAddr(_quadAddr) {}
    
    void print(ostream &out) const {
        out << "NAME: " << setiosflags(std::ios::left) << setw(10) << name
            << "KIND: " << setiosflags(std::ios::left) << setw(10) << kind2str[kind] 
            << "VAL: " << setiosflags(std::ios::left) << setw(10) << value 
            << "LEVEL: " << setiosflags(std::ios::left) << setw(10) << level 
            << "ADR: " << setiosflags(std::ios::left) << setw(10) << addr 
            << endl;
    }

    string name;
    KIND kind;
    int value, level, addr, quadAddr;
};

#endif