#include "parser.h"

Parser::Parser(Lexer *lexer): lexer(lexer), symbol(NULL), level(0) {
    for (int i = 0; i < RECURSIVE_DEPTH; i++)
        addr[i] = 0;
}

void Parser::program() {

}

void Parser::getSymbol() {
    if (symbol) {
        delete symbol;
        symbol = NULL;
    }
    symbol = lexer->getSymbol();
}

void Parser::block() {
    declears();

}

void Parser::declears() {
    while (true) {
        getSymbol();
        if (symbol->)
    }
}