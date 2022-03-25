#pragma once
#include <string>
#include "../AST/ASTNode.h"
#include "../Lexer/Lexer.h"


class Parser {
public:
    ASTNode* parse(std::string &script);
private:
    ASTNode* prog(TokenReader &tokens);
    ASTNode* intDeclare(TokenReader &tokens);
    ASTNode* additive(TokenReader &tokens);
    ASTNode* multiplicative(TokenReader &tokens);
    ASTNode* primary(TokenReader &tokens);
    ASTNode* expressionStatement(TokenReader &tokens);
    ASTNode* assignmentStatement(TokenReader &tokens);
};