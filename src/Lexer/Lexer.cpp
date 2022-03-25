#include "../../include/Lexer/Lexer.h"
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 保存之前的 Token，并且使用 ch 初始化下一个 Token
 * 
 * @param ch 
 * @return DFAStatus 
 */
DFAStatus Lexer::initToken(char ch) {
    if (tokenText.length() > 0) {
        token.setText(tokenText);
        tokens.push_back(token);
        token = Token();
        tokenText = "";
    }
    DFAStatus newState = DFAStatus::Initial;
    if (isAlpha(ch)) {
        if (ch == 'i') {
            newState = DFAStatus::Id_int1;
        } else {
            newState = DFAStatus::Id;
        }
        token.setType(TokenType::Identifier);
        tokenText.push_back(ch);
    } else if (isDigit(ch)) {
        newState = DFAStatus::IntLiteral;
        token.setType(TokenType::IntLiteral);
        tokenText.push_back(ch);
    } else if (ch == '>') {
        newState = DFAStatus::GT;
        token.setType(TokenType::GT);
        tokenText.push_back(ch);
    } else if (ch == '+') {
            newState = DFAStatus::Plus;
            token.setType(TokenType::Plus);
            tokenText.push_back(ch);
        } else if (ch == '-') {
            newState = DFAStatus::Minus;
            token.setType(TokenType::Minus);
            tokenText.push_back(ch);
        } else if (ch == '*') {
            newState = DFAStatus::Star;
            token.setType(TokenType::Star);
            tokenText.push_back(ch);
        } else if (ch == '/') {
            newState = DFAStatus::Slash;
            token.setType(TokenType::Slash);
            tokenText.push_back(ch);
        } else if (ch == ';') {
            newState = DFAStatus::SemiColon;
            token.setType(TokenType::SemiColon);
            tokenText.push_back(ch);
        } else if (ch == '(') {
            newState = DFAStatus::LeftParen;
            token.setType(TokenType::LeftParen);
            tokenText.push_back(ch);
        } else if (ch == ')') {
            newState = DFAStatus::RightParen;
            token.setType(TokenType::RightParen);
            tokenText.push_back(ch);
        } else if (ch == '=') {
            newState = DFAStatus::Assignment;
            token.setType(TokenType::Assignment);
            tokenText.push_back(ch);
        } else {
            newState = DFAStatus::Initial;
        }
        return newState;
}


TokenReader Lexer::tokenize(std::string code) {
    tokens.clear();
    tokenText.clear();
    token = Token();
    int ptr = 0, len = code.size();
    char ch = 0;
    DFAStatus state = DFAStatus::Initial;
    while (ptr < len) {
        ch = code[ptr++];
        switch (state){
        case DFAStatus::Initial:
            state = initToken(ch);          //重新确定后续状态
            break;
        case DFAStatus::Id:
            if (isAlpha(ch) || isDigit(ch)) {
                tokenText.push_back(ch);       //保持标识符状态
            } else {
                state = initToken(ch);      //退出标识符状态，并保存Token
            }
            break;
        case DFAStatus::GT:
            if (ch == '=') {
                token.setType(TokenType::GE);  //转换成GE
                state = DFAStatus::GE;
                tokenText.push_back(ch);
            } else {
                state = initToken(ch);      //退出GT状态，并保存Token
            }
            break;
        case DFAStatus::GE:
        case DFAStatus::Assignment:
        case DFAStatus::Plus:
        case DFAStatus::Minus:
        case DFAStatus::Star:
        case DFAStatus::Slash:
        case DFAStatus::SemiColon:
        case DFAStatus::LeftParen:
        case DFAStatus::RightParen:
            state = initToken(ch);          //退出当前状态，并保存Token
            break;
        case DFAStatus::IntLiteral:
            if (isDigit(ch)) {
                tokenText.push_back(ch);       //继续保持在数字字面量状态
            } else {
                state = initToken(ch);      //退出当前状态，并保存Token
            }
            break;
        case DFAStatus::Id_int1:
            if (ch == 'n') {
                state = DFAStatus::Id_int2;
                tokenText.push_back(ch);
            }
            else if (isDigit(ch) || isAlpha(ch)){
                state = DFAStatus::Id;    //切换回Id状态
                tokenText.push_back(ch);
            }
            else {
                state = initToken(ch);
            }
            break;
        case DFAStatus::Id_int2:
            if (ch == 't') {
                state = DFAStatus::Id_int3;
                tokenText.push_back(ch);
            }
            else if (isDigit(ch) || isAlpha(ch)){
                state = DFAStatus::Id;    //切换回id状态
                tokenText.push_back(ch);
            }
            else {
                state = initToken(ch);
            }
            break;
        case DFAStatus::Id_int3:
            if (isBlank(ch)) {
                token.setType(TokenType::Int);
                state = initToken(ch);
            }
            else{
                state = DFAStatus::Id;    //切换回Id状态
                tokenText.push_back(ch);
            }
            break;
        default:
            break;
        }
    }
    if (tokenText.size() > 0) {
        initToken(ch);
    }
    return TokenReader(tokens);
}