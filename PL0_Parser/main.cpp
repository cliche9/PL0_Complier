#include "parser.h"
#include <fstream>

int main() {
    ifstream fin("PL0_code2022/input/PL0_code1.in");
    ofstream lout("PL0_code2022/lexer_output/PL0_code.out");
    ofstream pout("PL0_code2022/parser_output/PL0_table_symbol.out");
    ofstream codeout("PL0_code2022/parser_output/PL0_table_code.out");
    Lexer lexer(fin);
    try {
        lexer.symbolization();
        lexer.printAll(lout);
    } catch (exception &e) {
        cout << e.what() << endl;
    }

    Parser parser(&lexer);
    try {
        parser.program();
    } catch (exception &e) {
        cout << e.what() << endl;
    }
    parser.printTable(pout);
    parser.printCode(codeout);
    
    return 0;
}