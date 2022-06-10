#ifndef _QUADIFIER_H_
#define _QUADIFIER_H_

#include "common.h"

/* ============ 四元式相关定义 ============ */ 
struct Quadifier {
    Quadifier(string _op = "", string _arg1 = "", string _arg2 = "", string _result = "")
        : op(_op), arg1(_arg1), arg2(_arg2), result(_result) {}
    
    void print(ostream &out) const {
        out << "(" << op << ", " << arg1 << ", " << arg2 << ", " << result << ")" << endl;
    }
    
    string op, arg1, arg2, result;
};

#endif