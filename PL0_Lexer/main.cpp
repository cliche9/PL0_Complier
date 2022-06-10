#include "lexer.h"

int main() {
    ifstream fin[5] = {
        ifstream("PL0_code2022/input/PL0_code.in"),
        ifstream("PL0_code2022/input/PL0_code0.in"),
        ifstream("PL0_code2022/input/PL0_code1.in"),
        ifstream("PL0_code2022/input/PL0_code2.in"),
        ifstream("PL0_code2022/input/PL0_code3.in"),
    };
    ofstream fout[5] = {
        ofstream("PL0_code2022/lexer_output/PL0_code.out"),
        ofstream("PL0_code2022/lexer_output/PL0_code0.out"),
        ofstream("PL0_code2022/lexer_output/PL0_code1.out"),
        ofstream("PL0_code2022/lexer_output/PL0_code2.out"),
        ofstream("PL0_code2022/lexer_output/PL0_code3.out"),
    };
    
    for (int i = 0; i < 5; i++) {
        Lexer lexer(fin[i]);
        try {
            lexer.symbolization();
            lexer.printAll(fout[i]);
        } catch (exception e) {
            cout << e.what();
        }
        fin[i].close();
        fout[i].close();
    }
    return 0;
}