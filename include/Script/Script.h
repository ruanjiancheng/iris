#pragma once
#include <bits/stdc++.h>
#include "../AST/ASTNode.h"
#include "../Parser/Parser.h"
#include "../Lexer/Lexer.h"

class Script {
public:
    int evaluate(ASTNode *node);
private:
    std::unordered_map<std::string, int> variables;
    bool v;
};