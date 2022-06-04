#include "interpreter.h"
#include "../PL0_Lexer/lexer.h"
#include "../PL0_Parser/parser.h"

int main() {
    ifstream fin[5] = {
        ifstream("PL0_code2022/input/PL0_code.in"),
        ifstream("PL0_code2022/input/PL0_code0.in"),
        ifstream("PL0_code2022/input/PL0_code1.in"),
        ifstream("PL0_code2022/input/PL0_code2.in"),
        ifstream("PL0_code2022/input/PL0_code3.in"),
    };

    ofstream logger[5] = {
        ofstream("PL0_code2022/interpreter_output/PL0_log.out"),
        ofstream("PL0_code2022/interpreter_output/PL0_log0.out"),
        ofstream("PL0_code2022/interpreter_output/PL0_log1.out"),
        ofstream("PL0_code2022/interpreter_output/PL0_log2.out"),
        ofstream("PL0_code2022/interpreter_output/PL0_log3.out"),
    };

    for (int i = 3; i < 5; i++) {
        Lexer lexer(fin[i]);
        try {
            lexer.symbolization();
        } catch (exception &e) {
            cout << e.what() << endl;
            continue;
        }
        fin[i].close();

        Parser parser(&lexer);
        try {
            parser.program();
        } catch (exception &e) {
            cout << e.what() << endl;
            continue;
        }

        Interpreter interpreter(parser.getCode());
        try {
            interpreter.interpretation(logger[i]);
        } catch (exception &e) {
            cout << e.what() << endl;
            continue;
        }
    }
    
    return 0;
}