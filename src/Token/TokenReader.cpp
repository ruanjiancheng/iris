#include "../../include/Token/TokenReader.h"
#include <iostream>

Token TokenReader::read() {
    if (pos < (int)tokens.size()) {
        return tokens[pos++];
    }
    std::cerr << "no token\n";
    return Token();
}

Token TokenReader::peek() {
    if (pos < (int)tokens.size()) {
        return tokens[pos];
    }
    return Token();
}

void TokenReader::unread() {
    if (pos > 0) {
        pos--;
    }
}

int TokenReader::getPosition() {
    return pos;
}

void TokenReader::setPosition(int position) {
    if (position >= 0 && position < (int)tokens.size()) {
        pos = position;
    }
}

void TokenReader::dump() {
    std::cout << "text\t\ttype\n";
    for (Token &token : tokens) {
        std::cout << token.getText() << "\t\t" << (int)token.getType() << '\n';
    }
}