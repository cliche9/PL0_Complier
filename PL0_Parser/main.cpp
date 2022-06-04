#include "parser.h"
#include <fstream>

int main() {
    ifstream fin[5] = {
        ifstream("PL0_code2022/input/PL0_code.in"),
        ifstream("PL0_code2022/input/PL0_code0.in"),
        ifstream("PL0_code2022/input/PL0_code1.in"),
        ifstream("PL0_code2022/input/PL0_code2.in"),
        ifstream("PL0_code2022/input/PL0_code3.in"),
    };
    ofstream lex_out[5] = {
        ofstream("PL0_code2022/lexer_output/PL0_code.out"),
        ofstream("PL0_code2022/lexer_output/PL0_code0.out"),
        ofstream("PL0_code2022/lexer_output/PL0_code1.out"),
        ofstream("PL0_code2022/lexer_output/PL0_code2.out"),
        ofstream("PL0_code2022/lexer_output/PL0_code3.out"),
    };
    ofstream symbol_out[5] = {
        ofstream("PL0_code2022/parser_output/PL0_code_symbol.out"),
        ofstream("PL0_code2022/parser_output/PL0_code0_symbol.out"),
        ofstream("PL0_code2022/parser_output/PL0_code1_symbol.out"),
        ofstream("PL0_code2022/parser_output/PL0_code2_symbol.out"),
        ofstream("PL0_code2022/parser_output/PL0_code3_symbol.out"),
    };
    ofstream code_out[5] = {
        ofstream("PL0_code2022/parser_output/PL0_code_code.out"),
        ofstream("PL0_code2022/parser_output/PL0_code0_code.out"),
        ofstream("PL0_code2022/parser_output/PL0_code1_code.out"),
        ofstream("PL0_code2022/parser_output/PL0_code2_code.out"),
        ofstream("PL0_code2022/parser_output/PL0_code3_code.out"),
    };

    for (int i = 0; i < 5; i++) {
        Lexer lexer(fin[i]);
        try {
            lexer.symbolization();
            lexer.printAll(lex_out[i]);
        } catch (exception &e) {
            cout << e.what() << endl;
        }

        Parser parser(&lexer);
        try {
            parser.program();
        } catch (exception &e) {
            cout << e.what() << endl;
        }
        parser.printTable(symbol_out[i]);
        parser.printCode(code_out[i]);
    }
    
    return 0;
}