#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include "common.h"

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

#endif