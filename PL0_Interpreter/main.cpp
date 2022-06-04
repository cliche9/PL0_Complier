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

    for (int i = 0; i < 5; i++) {
        Lexer lexer(fin[i]);
        try {
            lexer.symbolization();
        } catch (exception &e) {
            cout << e.what() << endl;
        }
        fin[i].close();

        Parser parser(&lexer);
        try {
            parser.program();
        } catch (exception &e) {
            cout << e.what() << endl;
        }

        Interpreter interpreter(parser.getCode());
        try {
            interpreter.interpretation();
        } catch (exception &e) {
            cout << e.what() << endl;
        }
    }
    
    return 0;
}