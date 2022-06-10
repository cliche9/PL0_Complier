#include "interpreter.h"

Interpreter::Interpreter(vector<Instruction> _code)
    : pc(0), bp(0), code(_code) {
        // 初始化主程序栈
        for (int i = 0; i < 3; i++)
            stack.push_back(0);        
    }

void Interpreter::interpretation(ostream &logger) {
    int n = code.size();
    while (pc < n - 1) {
        printReg(logger);
        ir = code[pc++];
        printIns(logger);
        oneInstruction();
        printStack(logger);
    }
}

int Interpreter::base() {
    int gap = ir.level;
    int SL = bp;

    while (gap > 0) {
        SL = stack[SL + 2];
        --gap;
    }

    return SL;
}

void Interpreter::oneInstruction() {
    int temp = 0;
    switch(ir.ins) {
        case LIT:
            stack.push_back(ir.offset);
            break;
        case LOD:
            stack.push_back(stack[base() + ir.offset]);
            break;
        case STO:
            temp = stack.back();
            stack.pop_back();
            stack[base() + ir.offset] = temp;
            break;
        case CAL:
            temp = stack.size();
            stack.push_back(pc);                // RA
            stack.push_back(bp);                // DL
            stack.push_back(base());            // SL
            bp = temp;
            pc = ir.offset;
            break;
        case INT:
            for (int i = 3; i < ir.offset; i++)
                stack.push_back(0);
            break;
        case JMP:
            pc = ir.offset;
            break;
        case JPC:
            temp = stack.back();
            stack.pop_back();
            if (!temp)
                pc = ir.offset;
            break;
        case OPR:
            opr();
            break;
        default:
            throw InterpreterException("OneInstruction: Invalid Instruction!");
    }
}

void Interpreter::opr() {
    int temp = 0;
    int t1 = 0, t2 = 0;
    switch (ir.offset) {
        case END:
            pc = stack[bp];
            temp = stack[bp + 1];
            while (stack.size() > bp)
                stack.pop_back();
            bp = temp;
            break;
        case ADD:
        case SUB:
        case MUL:
        case DIV:
        case LSS:
        case LEQ:
        case GTR:
        case GEQ:
        case EQL:
        case NEQ:
            binomialIns(OPERATOR(ir.offset));
            break;
        case WRITE:
            t1 = stack.back();
            stack.pop_back();
            cout << t1 << endl;
            break;
        case READ:
            cin >> t1;
            stack.push_back(t1);
            break;
        case MINUS:
        case ODD:
            monomialIns(OPERATOR(ir.offset));
            break;
        default:
            throw InterpreterException("OPR: Invalid Operator!");
    }
}

void Interpreter::monomialIns(OPERATOR opr) {
    int t1 = stack.back();
    stack.pop_back();
    int res = 0;
    switch (opr) {
        case MINUS:
            res = -t1;
            break;
        case ODD:
            res = t1 % 2;
            break;
        default:
            throw InterpreterException("OPR: Invalid Operator!");
    }
    stack.push_back(res);
}

void Interpreter::binomialIns(OPERATOR opr) {
    int t2 = stack.back();
    stack.pop_back();
    int t1 = stack.back();
    stack.pop_back();
    int res = 0;
    switch (opr) {
        case ADD:
            res = t1 + t2;
            break;
        case SUB:
            res = t1 - t2;
            break;
        case MUL:
            res = t1 * t2;
            break;
        case DIV:
            res = t1 / t2;
            break;
        case LSS:
            res = t1 < t2;
            break;
        case LEQ:
            res = t1 <= t2;
            break;
        case GTR:
            res = t1 > t2;
            break;
        case GEQ:
            res = t1 >= t2;
            break;
        case EQL:
            res = t1 == t2;
            break;
        case NEQ:
            res = t1 != t2;
            break;
        default:
            throw InterpreterException("OPR: Invalid Operator!");
    }
    stack.push_back(res);
}

void Interpreter::pushStack(int n) {
    stack.push_back(n);
}

int Interpreter::popStack() {
    int t = stack.back();
    stack.pop_back();
    return t;
}

void Interpreter::printIns(ostream &out) const {
    out << "Instruction: ( " << ins2str[ir.ins] << ", " << ir.level << ", ";
    if (ir.ins == OPR)
        out << opr2str[ir.offset];
    else
        out << ir.offset;
    out << " )\n";
}

void Interpreter::printReg(ostream &out) const {
    out << "PC: " << pc
         << "\nBP: " << bp << endl;
}

void Interpreter::printStack(ostream &out) const {
    if (stack.empty())
        return;
    else {
        out << "=== Stack ===\n";

        for (int i = 0; i < stack.size(); i++)
            out << "\t" << i << ": " << stack[i] << "\n";
    }
    out << endl;
}