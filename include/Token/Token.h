#pragma once

#include <string>
#include "TokenType.h"

/**
 * @brief def Token
 * 
 */

class Token {
public: 
    TokenType getType();
    std::string getText();
    void setText(std::string text) {this -> text = text;}
    void setType(TokenType type) {this -> type = type;}
    Token() {text = "";}
private:
    TokenType type;
    std::string text;
};