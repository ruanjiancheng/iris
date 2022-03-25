#include "../../include/Parser/Parser.h"
#include <iostream>

/*
    优先级越低的运算在越上层。
    通常的运算左结合，说明左边的节点在下层。导致编译器左递归。
    add ::= add + mul | mul
    如何消除左递归？
        通过改写语法规则来实现
        add ::= mul (+ mul)*
*/

ASTNode* Parser::parse(std::string &script) {
    Lexer lexer;
    TokenReader tokens = lexer.tokenize(script);
    ASTNode *rootNode = prog(tokens);
    return rootNode;
}

ASTNode* Parser::prog(TokenReader &tokens) {
    ASTNode *node = new ASTNode(ASTNodeType::Programm, "pwc");
    while (!tokens.empty()) {
        ASTNode *child = intDeclare(tokens);

        if (child == nullptr) {
            child = expressionStatement(tokens);
        }

        if (child == nullptr) {
            child = assignmentStatement(tokens);
        }

        if (child != nullptr) {
            node -> addChild(child);
        } else {
            std::cerr << "unknown statement" << std::endl;
        }
    }
    return node;
}
/**
 * @brief 表达式
 * 
 * @param tokens 
 * @return ASTNode* 
 */
ASTNode* Parser::expressionStatement(TokenReader &tokens) {
    int pos = tokens.getPosition();
    ASTNode *node = additive(tokens);
    if (node != nullptr) {
        Token token = tokens.peek();
        if (tokens.empty() == false && token.getType() == TokenType::SemiColon) {
            tokens.read();
        } else {
            node = nullptr;
            tokens.setPosition(pos);
        }
    } 
    return node;
}
/**
 * @brief 赋值
 * 
 * @param tokens 
 * @return ASTNode* 
 */
ASTNode* Parser::assignmentStatement(TokenReader &tokens) {
    ASTNode *node = nullptr;
    Token token = tokens.peek();
    // 读取标识符
    if (tokens.empty() == false && token.getType() == TokenType::Identifier) {
        token = tokens.read();
        node = new ASTNode(ASTNodeType::AssignmentStmt, token.getText());
        token = tokens.peek();
        // =
        if (tokens.empty() == false && token.getType() == TokenType::Assignment) {
            tokens.read();
            ASTNode *child = additive(tokens);
            if (child == nullptr) {
                std::cerr << "invalide assignment statement, expecting an expression" << std::endl;
            } else {
                node -> addChild(child);
                token = tokens.peek();
                // ;
                if (tokens.empty() == false && token.getType() == TokenType::SemiColon) {
                    tokens.read();
                } else {
                    std::cerr << "invalid statement, expecting semicolon" << std::endl;
                }
            }
        } else {
            tokens.unread();
            node = nullptr;
        }
    }
    return node;
}

/**
 * @brief int 变量申明
 * 
 * @param tokens 
 * @return ASTNode* 
 */
ASTNode* Parser::intDeclare(TokenReader &tokens) {
    ASTNode *node = nullptr;
    Token token = tokens.peek();
    // 识别标识符 Int
    if (!tokens.empty() && token.getType() == TokenType::Int) {
        token = tokens.read();
        // 获取字面量
        if (tokens.peek().getType() == TokenType::Identifier) {
            token = tokens.read();
            node = new ASTNode(ASTNodeType::IntDeclaration, token.getText());
            token = tokens.peek();
            // 是否有等号
            if (!tokens.empty() && token.getType() == TokenType::Assignment) {
                tokens.read();
                // 解析算数表达式
                ASTNode *child = additive(tokens);
                if (child == nullptr) {
                    std::cerr << "invalide variable initialization, expecting an expression" << std::endl;
                } else {
                    node -> addChild(child);
                }
            }
        }
        else {
            std::cerr << "variable name expected" << std::endl;
        }
        if (node != nullptr) {
            token = tokens.peek();
            // 获取分号;
            if (!tokens.empty() && token.getType() == TokenType::SemiColon) {
                tokens.read();
            } else {
                std::cerr << "invalid statement, expecting semicolon" << std::endl;
            }
        }
    }
    return node;
}

/**
 * @brief 加法表达式
 * 
 * @param tokens 
 * @return ASTNode* 
 */
ASTNode* Parser::additive(TokenReader &tokens) {
    ASTNode *child1 = multiplicative(tokens);
    ASTNode *root = child1;
    if (child1 != nullptr) {
        while (true) {
            Token token = tokens.peek();
            // +, -
            if (!tokens.empty() && (token.getType() == TokenType::Plus || token.getType() == TokenType::Minus)) {
                token = tokens.read();
                ASTNode *child2 = multiplicative(tokens);
                if (child2 != nullptr) {
                    root = new ASTNode(ASTNodeType::Additive, token.getText());
                    root -> addChild(child1);
                    root -> addChild(child2);
                    child1 = root;
                }
            } else {
                break;
            }
        }
    }
    return root;
}


/**
 * @brief 乘法表达式
 * 
 * @param tokens 
 * @return ASTNode* 
 */
ASTNode* Parser::multiplicative(TokenReader &tokens) {
    ASTNode *child1 = primary(tokens);
    ASTNode *root = child1;
    while (true) {
        Token token = tokens.peek();
        if (tokens.empty() == false && (token.getType() == TokenType::Star || token.getType() == TokenType::Slash)) {
            token = tokens.read();
            ASTNode *child2 = primary(tokens);
            if (child2 != nullptr) {
                root = new ASTNode(ASTNodeType::Multiplicative, token.getText());
                root -> addChild(child1);
                root -> addChild(child2);
                child1 = root;
            } else {
                std::cerr << "invalid multiplicative expression, expecting the right part." << std::endl;
            }
        } else {
            break;
        }
    }
    return root;
}

/**
 * @brief 基础表达式
 * 
 * @param tokens 
 * @return ASTNode* 
 */
ASTNode* Parser::primary(TokenReader &tokens) {
    ASTNode *node = nullptr;
    Token token = tokens.peek();
    if (tokens.empty() == false) {
        if (token.getType() == TokenType::IntLiteral) {
            // 整型字面量
            token = tokens.read();
            node = new ASTNode(ASTNodeType::IntLiteral, token.getText());
        } else if (token.getType() == TokenType::Identifier) {
            // 标识符
            token = tokens.read();
            node = new ASTNode(ASTNodeType::Identifier, token.getText());
        } else if (token.getType() == TokenType::LeftParen) {
            // (
            tokens.read();
            node = additive(tokens);
            if (node != nullptr) {
                token = tokens.peek();
                // )
                if (tokens.empty() == false && token.getType() == TokenType::RightParen) {
                    tokens.read();
                } else {
                    std::cerr << "expecting right parenthesis" << std::endl;
                }
            } else {
                std::cerr << "expecting an additive expression inside parenthesis" << std::endl;
            }
        }
    }
    return node;
}