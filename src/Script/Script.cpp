#include "../../include/Script/Script.h"
/**
 * @brief 解析
 * 
 * @param node 
 * @return int 
 */
int Script::evaluate(ASTNode *node) {
    int res = 0;
    ASTNode *child1 = nullptr, *child2 = nullptr;
    int res1 = 0, res2 = 0;
    std::string varName = "";
    int varVal = 0;
    switch ((node -> getType()))
    {
    case ASTNodeType::Programm:
        for (auto &it : node -> getChildren()) {
            res = evaluate(it);
        }
        break;
    case ASTNodeType::Additive:
        child1 = node -> getChildren()[0];
        res1 = evaluate(child1);
        child2 = node -> getChildren()[1];
        res2 = evaluate(child2);
        if (node -> getText() == "+") {
            res = res1 + res2;
        } else {
            res = res1 - res2;
        }
        break;
    case ASTNodeType::Multiplicative:
        child1 = node -> getChildren()[0];
        res1 = evaluate(child1);
        child2 = node -> getChildren()[1];
        res2 = evaluate(child2);
        if (node -> getText() == "*") {
            res = res1 * res2;
        } else {
            res = res1 / res2;
        }
        break;
    case ASTNodeType::IntLiteral:
        res = std::stoi(node -> getText());
        break;
    case ASTNodeType::Identifier:
        varName = node -> getText();
        if (variables.count(varName)) {
            res = variables[varName];
        } else {
            std::cerr << "unknown variable: " + varName << std::endl;
        }
        break;
    case ASTNodeType::AssignmentStmt:
        varName = node -> getText();
        if (variables.count(varName) == 0) {
            std::cerr << "unknown variable: " + varName << std::endl;
            break;
        } 
    case ASTNodeType::IntDeclaration:
        varName = node -> getText();
        if ((node -> getChildren()).size() > 0) {
            ASTNode *child = (node->getChildren())[0];
            res = evaluate(child);
            varVal = res;
        }
        variables[varName] = varVal;
        break;
    default:
        std::cerr << "unknown error" << std::endl;
        break;
    }
    if (node -> getType() == ASTNodeType::Programm) {
        std::cout << "<- " << res << std::endl;
    }
    return res;
}