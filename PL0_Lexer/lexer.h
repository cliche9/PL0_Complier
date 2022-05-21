#include "../common/symbol.h"
#include <iostream>
#include <list>
using namespace std;

class Lexer {
public:
    Lexer(istream &in=cin);
    ~Lexer();

    void Symbolization();
    void PrintAll(ostream &out);
    Symbol *getSymbol();

private:
    istream &inFile;
    int line;
    int offset;

    list<Symbol *> symbolTable;

    char nextChar();                // 读取下一个字符
    void putCharBack(char c);       // 超前搜索 --- 写回输入串
    void nextLine();

    bool isBoundary(char c);
    bool isOperator(char c);
};