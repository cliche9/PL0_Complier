#include "lexer.h"
#include <fstream>

int main() {
    ifstream fin("../PL0_code2022/input/PL0_code.in");
    ofstream fout("../PL0_Lexer/lexer_cpp.out");
    Lexer lexer(fin);
    lexer.Symbolization();
    lexer.PrintAll(fout);
    fin.close();
    fout.close();
    return 0;
}