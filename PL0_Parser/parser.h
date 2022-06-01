#ifndef _PARSER_H_
#define _PARSER_H_

#define RECURSIVE_DEPTH 3

#include "../PL0_Lexer/lexer.h"
#include <vector>
#include <set>
#include <stack>
using std::set;
using std::stack;

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
    Identifier(string _name = "", KIND _kind = NIL, int _val = 0, int _lev = -1, int _addr = -1):
        name(_name), kind(_kind), value(_val), level(_lev), addr(_addr) {}
    
    void print(ostream &out) const {
        out << "NAME: " << name << "\tKIND: " << kind2str[kind] << "\tVAL: " << value << "\tLEVEL: " << level << "\tADR: " << addr << endl;
    }

    string name;
    KIND kind;
    int value, level, addr;
};

struct Quadifier {
    Quadifier(string _op = "", string _arg1 = "", string _arg2 = "", string _result = "")
        : op(_op), arg1(_arg1), arg2(_arg2), result(_result) {}
    
    void print(ostream &out) const {
        out << "(" << op << ", " << arg1 << ", " << arg2 << ", " << result << ")";
    }
    
    string op, arg1, arg2, result;
};

class Parser {
public:
    Parser(Lexer *lexer);
    
    void program();
    void printTable(ostream &out) const;            // 输出符号表

private:
    Lexer *lexer;
    Symbol *symbol;
    int level;
    int addr[RECURSIVE_DEPTH];

    vector<Identifier> table[RECURSIVE_DEPTH];      // 符号表
    set<string> nameSet;                            // 变量名表, 用于查重
    void enter(string, KIND, int, int, int);        // 填入符号表

    vector<Quadifier> quads;                        // 四元式表
    stack<Quadifier> qStack;                        // 四元式用栈
    void generate(string, string, string, string);  // 生成四元式
    
    void getSymbol();                               // 读取一个符号
    void revoke();                                  // 撤回一个字符
    Identifier *findIdentifier(string name);        // 根据Name在Table中找到对应的表项
    
    void block();       // 完整程序块
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