#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_

#include "../common/common.h"
#include "../common/instruction.h"

class Interpreter {
public:
    Interpreter(vector<Instruction> _code);
    void interpretation();

private:
    // int pc;                         // PC寄存器
    // Instruction ir;                 // 指令寄存器

    vector<Instruction> code;       // 目标代码
    stack<int> stack;               // 数据栈

    void oneInstruction(const Instruction &ir);
};

#endif