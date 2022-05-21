#include "symbol.h"

Symbol::Symbol(SymbolType type, string value)
    : type(type), value(value) {}

Symbol::~Symbol() {}

void Symbol::Print(ostream &out) const {
    string symbolName;
    switch (type) {
        case SymbolType::NUMBER:
            symbolName = "SYS_NUMBER";
            break;
        case SymbolType::WORD:
            if (keywordMapping.count(value))
                symbolName = keywordMapping.at(value);
            else
                symbolName = "SYS_IDENT";
            break;
        case SymbolType::OPT:
            symbolName = operatorMapping.at(value);
            break;
        case SymbolType::BOUND:
            symbolName = boundaryMapping.at(value);
            break;
        default:
            break;
    }
    out << "(" << value << ", " << symbolName << ")\n";
}
