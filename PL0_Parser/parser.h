#ifndef _PARSER_H_
#define _PARSER_H_

#define RECURSIVE_DEPTH 3

#include "../PL0_Lexer/lexer.h"
#include <vector>
#include <set>

enum KIND {
    NIL,
    CONST,
    VAR,
    PROC,
};

struct Token {
    Token(string _name = "", KIND _kind = NIL, int _val = 0, int _lev = -1, int _addr = -1):
        name(_name), kind(_kind), value(_val), level(_lev), addr(_addr) {}
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
    vector<Token> table[RECURSIVE_DEPTH];
    set<string> nameSet;
    
    void getSymbol();               // 读取一个符号
    void revoke();                  // 撤回一个字符
    int findToken(string name);     // 根据Name在Table中找到对应的表项
    
    void block();                   // 完整程序块
    // Declaration 声明
    void declares();
    void constDeclare();
    void varDeclare();
    void procDeclare();
    // Statement 执行语句
    void statements();
    void assign();
    void compound();
    void condition();
    void call();
    void whiledo();
    void read();
    void write();
    // 辅助函数
    void cond();        // 条件
    void expr();        // 完整的表达式
    void term();        // 单独项
    void factor();      // 单个因子
};

#endif