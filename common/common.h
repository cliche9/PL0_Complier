#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <map>
using namespace std;

// 关键词
const map<string, string> keywordMapping = {
    {"const", "SYM_CONST"},
    {"var", "SYM_VAR"},
    {"procedure", "SYM_PROC"},
    {"begin", "SYM_BEGIN"},
    {"end", "SYM_END"},
    {"odd", "SYM_ODD"},
    {"if", "SYM_IF"},
    {"then", "SYM_THEN"},
    {"call", "SYM_CALL"},
    {"while", "SYM_WHILE"},
    {"do", "SYM_DO"},
    {"read", "SYM_READ"},
    {"write", "SYM_WRITE"}
};

// 运算符
const map<string, string> operatorMapping = {
    {"+", "SYM_PLUS"},
    {"-", "SYM_MINUS"},
    {"*", "SYM_MUL"},
    {"/", "SYM_DIV"},
    {"=", "SYM_EQL"},
    {"<", "SYM_LSS"},
    {"<=", "SYM_LEQ"},
    {">", "SYM_GTR"},
    {">=", "SYM_GEQ"},
    {"#", "SYM_NEQ"},
    {":=", "SYM_ASSIGN"}
};

// 界符
const map<string, string> boundaryMapping = {
    {"(", "SYM_LPAREN"},
    {")", "SYM_RPAREN"},
    {";", "SYM_SEMICOLON"},
    {",", "SYM_COMMA"},
    {".", "SYM_PERIOD"}
};

#endif //_COMMON_H_