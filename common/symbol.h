#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "common.h"
#include <iostream>
using std::string;
using std::ostream;

enum SymbolType {
    NONE,
    NUMBER,
    WORD,
    OPT,
    BOUND
};

class Symbol {
public:
    Symbol(SymbolType type, string value);
    ~Symbol();

    void Print(ostream &out) const;

private:
    SymbolType type;
    string value;
};

#endif