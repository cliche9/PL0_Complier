#include "lexer.h"

Lexer::Lexer(istream &in)
    : inFile(in), line(0), offset(0) {}

Lexer::~Lexer() {
    for (Symbol *cur : symbolTable) {
        if (cur)
            delete cur;
        cur = NULL;
    }
    symbolTable.clear();
}

void Lexer::Symbolization() {
    char cur = EOF;
    string input;
    Symbol *symbol = NULL;
    bool eofReached = false;
    // 循环读取字符
    while ((cur = nextChar()) != EOF) {
        /* ========== 处理\n和空格 ========== */
        if (cur == '\n') {
            nextLine();
            continue;
        }
        if (isspace(cur))
            continue;

        input.clear();
        eofReached = false;
        if (isdigit(cur)) {
            /* ========== 数字 ========= */
            do {
                input += cur;
                if ((cur = nextChar()) == EOF) {
                    eofReached = true;
                    break;
                }
            } while (isdigit(cur));
            if (!eofReached)
                putCharBack(cur);
            symbol = new Symbol(SymbolType::NUMBER, input);
        } else if (isalpha(cur)) {
            /* ========== 变量/关键词 ========= */
            do {
                input += cur;
                if ((cur = nextChar()) == EOF) {
                    eofReached = true;
                    break;
                }
            } while (isalnum(cur));
            if (!eofReached)
                putCharBack(cur);
            symbol = new Symbol(SymbolType::WORD, input);
        } else if (isBoundary(cur)) {
            /* ========== 界符 ========= */
            input += cur;
            symbol = new Symbol(SymbolType::BOUND, input);
        } else {
            /* ========== 运算符 ========= */
            input += cur;
            if (!inFile.eof() && (cur == ':' || cur == '>' || cur == '<')) {
                if ((cur = nextChar()) == '=')
                    input += cur;
                else
                    putCharBack(cur);
            }
            symbol = new Symbol(SymbolType::OPT, input);
        }
        symbolTable.push_back(symbol);
    }
}

void Lexer::PrintAll(ostream &out) {
    for (Symbol *cur : symbolTable)
        cur->Print(out);
}

Symbol *Lexer::getSymbol() {
    Symbol *ret = NULL;
    if (!symbolTable.empty()) {
        ret = symbolTable.front();
        symbolTable.pop_front();
    }
    return ret;
}

void Lexer::nextLine() {
    ++line;
    offset = 0;
}

char Lexer::nextChar() {
    char ret = EOF;
    if (!inFile.eof()) {
        ret = inFile.get();
        ++offset;
    }
    return ret;
}

void Lexer::putCharBack(char c) {
    --offset;
    inFile.putback(c);   
}

bool Lexer::isBoundary(char c) {
    return boundaryMapping.count(string(1, c));
}