#ifndef _PARSER_H_
#define _PARSER_H_

#define RECURSIVE_DEPTH 3

#include "../PL0_Lexer/lexer.h"
#include <vector>
#include <set>
#include <stack>
using std::set;
using std::stack;

/* ============ 符号表(标识符)相关定义 ============ */ 
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

/* ============ 目标代码(指令)相关定义 ============ */ 
enum INSTRUCTION {
    UDF,        // Undefined
    LIT,        // LIT offset, 将常数offset送到栈顶, level无效
    LOD,        // LOD(Load) level offset, 将变量送到栈顶, 使用level和offset标识变量位置
                // 其中level是调用层与说明层的插值
    STO,        // STO(Store) level offset, 将栈顶内容送至变量
    CAL,        // CAL(Call) level offset, 调用过程, 使用level和offset标识过程位置
    INT,        // INT offset, 初始化过程栈, offset为开辟数据个数
    JMP,        // JMP offset, 无条件跳转, offset为转移地址
    JPC,        // JPC offset, 条件跳转, 栈顶元素为真时, 跳转至offset地址
    OPR,        // OPR offset, 关系/算术运算, 次栈顶 = 栈顶 op 次栈顶
                // offset标识具体操作, =0时表示退出数据区
};

const vector<string> ins2str = {
    "UNDEFINED",
    "LIT",
    "LOD",
    "STO",
    "CAL",
    "INT",
    "JMP",
    "JPC",
    "OPR",
};

enum OPERATOR {
    NOP,
    ADD,
    SUB,
    MUL,
    DIV,
    LSS,
    LEQ,
    GTR,
    GEQ,
    EQL,
    NEQ,
    WRITE,
    READ,
    MINUS,
    ODD,
};

struct Instruction {
    Instruction(INSTRUCTION _ins = UDF, int _level = -1, int _offset = -1)
        : ins(_ins), level(_level), offset(_offset) {}
    
    void print(ostream &out) const {
        out << ins2str[ins] << "\t" << level << "\t" << offset << endl;
    }

    INSTRUCTION ins;
    int level;
    int offset;
};

/* ============ 四元式相关定义 ============ */ 
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
    void printCode(ostream &out) const;             // 输出代码表

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
    void backpatch(int lev, int index, int val);    // 回填符号表
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