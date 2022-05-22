#include "parser.h"
#include <fstream>
#include <exception>

int main() {
    ifstream fin("PL0_code2022/input/PL0_code.in");
    ofstream fout("PL0_code2022/lexer_output/PL0_code.out");
    Lexer lexer(fin);
    try {
        lexer.symbolization();
        lexer.printAll(fout);
    } catch (exception &e) {
        cout << e.what() << endl;
    }

    Parser parser(&lexer);
    try {
        parser.program();
    } catch (exception &e) {
        cout << e.what() << endl;
    }
    
    return 0;
}