#pragma once
#include "Token.h"
#include <vector>

/**
 * @brief Token 流的处理
 * 
 */

class TokenReader {
public:
    // 读取一个 Token
    Token read();
    // 预读取一个 Token
    Token peek();
    // 恢复 Token
    void unread();
    // 获取当前 Token 的位置
    int getPosition();
    // 设置当前读取的位置
    void setPosition(int position);
    void dump();
    bool empty() {return pos == (int)tokens.size();}
    TokenReader() {pos = 0, tokens.clear();}
    TokenReader(std::vector<Token> tokens) {pos = 0, this -> tokens = tokens;}
private:
    std::vector<Token> tokens;
    int pos;
};