#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "common.h"
#include <iostream>
using std::string;
using std::ostream;

class Symbol {
public:
    Symbol(SymbolTag tag, string value);
    ~Symbol();

    void print(ostream &out) const;
    SymbolTag getSymbolTag() const;
    string getValue() const;

private:
    SymbolTag tag;
    string value;
};

#endif