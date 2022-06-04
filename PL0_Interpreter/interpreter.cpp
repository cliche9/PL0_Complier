#include "interpreter.h"

Interpreter::Interpreter(vector<Instruction> _code)
    : code(_code) {}

void Interpreter::interpretation() {
    for (Instruction &ir : code) {
        oneInstruction(ir);
    }
}

void Interpreter::oneInstruction(const Instruction &ir) {
    switch(ir.ins) {
        case LIT:
            stack.push(ir.offset);
            break;
        case LOD:
            stack.push(ir.offset);
            break;
        case STO:
            
        case CAL:
        case INT:
        case JMP:
        case JPC:
        case OPR:
        default:
            throw InterpreterException("OneInstruction: Invalid Instruction!");
    }
}