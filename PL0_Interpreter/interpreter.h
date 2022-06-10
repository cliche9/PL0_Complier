#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include "../common/common.h"
#include "../common/instruction.h"

class Interpreter {
public:
    Interpreter(vector<Instruction> _code);
    void interpretation(ostream &logger = cout);

private:
    int pc;                         // PC寄存器
    int bp;                         // 指令所需数据区的基址寄存器
    Instruction ir;                 // 指令寄存器

    vector<Instruction> code;       // 目标代码
    vector<int> stack;              // 数据栈

    int base();                     // 获取变量所在层的基址bp
    void oneInstruction();          // 执行一条指令
    void opr();                     // 执行一次运算
    void monomialIns(OPERATOR opr); // 处理一元运算指令
    void binomialIns(OPERATOR opr); // 处理二元运算指令
    
    void pushStack(int n);          // 入栈
    int popStack();                 // 出栈
    void printIns(ostream &out) const;          // 输出当前指令
    void printReg(ostream &out) const;          // 输出寄存器值, pc和bp, 使用结构stack替代了sp
    void printStack(ostream &out) const;        // 输出栈内容
};

#endif