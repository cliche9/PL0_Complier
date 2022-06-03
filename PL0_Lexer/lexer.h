#ifndef _LEXER_H_
#define _LEXER_H_

#include "../common/symbol.h"
#include <iostream>
#include <list>
using std::list;

class Lexer {
public:
    Lexer(istream &in=cin);
    ~Lexer();

    void symbolization();
    void printAll(ostream &out);
    Symbol *getSymbol();
    void prependSymbol(Symbol *symbol);

private:
    istream &inFile;
    int line;
    int offset;

    list<Symbol *> symbolTable;

    char nextChar();                // 读取下一个字符
    void putCharBack(char c);       // 超前搜索 --- 写回输入串
    void nextLine();

    bool isLegal(char c);
};

#endif