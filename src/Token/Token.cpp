#include "../../include/Token/Token.h"
#include <string>

TokenType Token::getType() {
    return type;    
}

std::string Token::getText() {
    return text;
}