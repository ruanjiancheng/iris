#pragma once

#include "../Token/Token.h"
#include "../Token/TokenReader.h"
#include "../DFA/DFAStatus.h"
#include <string>
#include <vector>

class Lexer {
public:
    // 解析字符串，形成 Token
    TokenReader tokenize(std::string code);
private:
    DFAStatus initToken(char ch);
    bool isAlpha(int ch) {return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');}
    bool isDigit(int ch) {return ch >= '0' && ch <= '9';}
    bool isBlank(int ch) {return ch == ' ' || ch == '\t' || ch == '\n';}
    std::string tokenText;
    std::vector<Token> tokens;
    Token token;
};