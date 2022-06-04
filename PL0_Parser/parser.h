#ifndef _PARSER_H_
#define _PARSER_H_

#define RECURSIVE_DEPTH 3

#include "../common/common.h"
#include "../common/identifier.h"
#include "../common/instruction.h"
#include "../PL0_Lexer/lexer.h"

class Parser {
public:
    Parser(Lexer *lexer);
    
    void program();
    void printTable(ostream &out) const;            // 输出符号表
    void printCode(ostream &out) const;             // 输出代码表
    vector<Instruction> getCode() const;            // 输出目标代码

private:
    Lexer *lexer;
    Symbol *symbol;
    int level;
    int addr[RECURSIVE_DEPTH];
    int dx;                                         // 符号表/四元式表/目标代码表每一层的相对地址, 一般初始化为3
    /* ========= 符号表 ========== */
    vector<Identifier> table[RECURSIVE_DEPTH];      // 符号表
    set<string> nameSet;                            // 变量名表, 用于查重
    void enter(string, KIND, int, int, int);        // 填入符号表
    /* ========= 目标代码 ========== */
    vector<Instruction> code;
    int mainCode;                                   // 用于反填代码表
    void emit(INSTRUCTION ins, int lev, int offset);// 生成目标代码

#ifdef QUAD
    vector<Quadifier> quads;                        // 四元式表
    stack<string> qStack;                           // 四元式用辅助栈
    int tempNumber;                                 // 临时变量T的个数
    string newTemp();                               // 新建临时变量T_i
    void pushStack(string s);                       // 四元式栈入栈
    string popStack();                              // 四元式栈出栈
    void generate(string, string, string, string);  // 生成四元式
#endif
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