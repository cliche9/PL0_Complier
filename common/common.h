#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <vector>
#include <map>
using namespace std;

enum SymbolTag {
    SYM_NONE,
    // 符号/标识符
    SYM_NUMBER,
    SYM_IDENT,
    // 关键词
    SYM_CONST,
    SYM_VAR,
    SYM_PROC,
    SYM_BEGIN,
    SYM_END,
    SYM_ODD,
    SYM_IF,
    SYM_THEN,
    SYM_CALL,
    SYM_WHILE,
    SYM_DO,
    SYM_READ,
    SYM_WRITE,
    // 运算符
    SYM_PLUS,
    SYM_MINUS,
    SYM_MUL,
    SYM_DIV,
    SYM_EQL,
    SYM_LSS,
    SYM_LEQ,
    SYM_GTR,
    SYM_GEQ,
    SYM_NEQ,
    SYM_ASSIGN,
    // 界符
    SYM_LPAREN,
    SYM_RPAREN,
    SYM_SEMICOLON,
    SYM_COMMA,
    SYM_PERIOD,
};

// 符号表
const vector<string> tag2str = {
    "SYM_NONE",
    "SYM_NUMBER",
    "SYM_IDENT",
    "SYM_CONST",
    "SYM_VAR",
    "SYM_PROC",
    "SYM_BEGIN",
    "SYM_END",
    "SYM_ODD",
    "SYM_IF",
    "SYM_THEN",
    "SYM_CALL",
    "SYM_WHILE",
    "SYM_DO",
    "SYM_READ",
    "SYM_WRITE",
    "SYM_PLUS",
    "SYM_MINUS",
    "SYM_MUL",
    "SYM_DIV",
    "SYM_EQL",
    "SYM_LSS",
    "SYM_LEQ",
    "SYM_GTR",
    "SYM_GEQ",
    "SYM_NEQ",
    "SYM_ASSIGN",
    "SYM_LPAREN",
    "SYM_RPAREN",
    "SYM_SEMICOLON",
    "SYM_COMMA",
    "SYM_PERIOD",
};

const map<string, SymbolTag> str2tag = {
    // 关键词
    {"const", SYM_CONST},
    {"var", SYM_VAR},
    {"procedure", SYM_PROC},
    {"begin", SYM_BEGIN},
    {"end", SYM_END},
    {"odd", SYM_ODD},
    {"if", SYM_IF},
    {"then", SYM_THEN},
    {"call", SYM_CALL},
    {"while", SYM_WHILE},
    {"do", SYM_DO},
    {"read", SYM_READ},
    {"write", SYM_WRITE},
    // 运算符
    {"+", SYM_PLUS},
    {"-", SYM_MINUS},
    {"*", SYM_MUL},
    {"/", SYM_DIV},
    {"=", SYM_EQL},
    {"<", SYM_LSS},
    {"<=", SYM_LEQ},
    {">", SYM_GTR},
    {">=", SYM_GEQ},
    {"#", SYM_NEQ},
    {":=", SYM_ASSIGN},
    // 界符
    {"(", SYM_LPAREN},
    {")", SYM_RPAREN},
    {";", SYM_SEMICOLON},
    {",", SYM_COMMA},
    {".", SYM_PERIOD},
};

#endif //_COMMON_H_