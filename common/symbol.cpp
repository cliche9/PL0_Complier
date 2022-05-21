#include "symbol.h"

Symbol::Symbol(SymbolTag tag, string value)
    : tag(tag), value(value) {}

Symbol::~Symbol() {}

void Symbol::print(ostream &out) const {
    out << "(" << value << ", " << tag2str[tag] << ")\n";
}

SymbolTag Symbol::getSymbolTag() const {
    return this->tag;
}