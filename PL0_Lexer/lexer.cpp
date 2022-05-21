#include "lexer.h"
#include "../common/exception.h"

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

void Lexer::symbolization() {
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
            symbol = new Symbol(SymbolTag::SYM_NUMBER, input);

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
            // 关键词
            if (str2tag.count(input))
                symbol = new Symbol(str2tag.at(input), input);
            // 变量
            else 
                symbol = new Symbol(SymbolTag::SYM_IDENT, input);
            
        } else if (isLegal(cur)) {
            /* ========== 界符/运算符 ========= */
            input += cur;
            if (!inFile.eof() && (cur == ':' || cur == '>' || cur == '<')) {
                if ((cur = nextChar()) == '=')
                    input += cur;
                else
                    putCharBack(cur);
            }
            symbol = new Symbol(str2tag.at(input), input);
            
        } else 
            /* == 非法字符 == */
            throw LexerException("Unexpected Character!");
        // 加入符号表
        symbolTable.push_back(symbol);
    }
}

void Lexer::printAll(ostream &out) {
    for (Symbol *cur : symbolTable)
        cur->print(out);
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

bool Lexer::isLegal(char c) {
    return c == ':' || str2tag.count(string(1, c));
}