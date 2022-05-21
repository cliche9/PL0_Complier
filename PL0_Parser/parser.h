#ifndef _PARSER_H_
#define _PARSER_H_

#define RECURSIVE_DEPTH 3

#include "../PL0_Lexer/lexer.h"
#include <vector>

enum KIND {
    NIL,
    CONST,
    VAR,
    PROC,
};

struct Token {
    string name;
    KIND kind;
    int value;
    int level;
    int addr;
};


class Parser {
public:
    Parser(Lexer *lexer);

    void program();

private:
    Lexer *lexer;
    Symbol *symbol;
    int level;
    int addr[RECURSIVE_DEPTH];
    vector<Token> table;

    void getSymbol();
    void block();
    void declears();
};

#endif