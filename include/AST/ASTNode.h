#pragma once
#include <vector>
#include <string>
#include "./ASTNodeType.h"
#include <iostream>

class ASTNode {
public:
    ASTNode(ASTNodeType nodeType = ASTNodeType::Programm, std::string text = "") {this -> nodeType = nodeType; this -> text = text;}
    ASTNode* getParent() {return parent;}
    std::vector<ASTNode*> getChildren() {return children;}
    ASTNodeType getType() {return nodeType;}
    std::string getText() {return text;}
    void addChild(ASTNode *child) {child -> parent = this; children.push_back(child);}
    void des(ASTNode *now) {for(auto &it : now -> children) des(it); delete now;}
    void dump(ASTNode *now, std::string indent) {std::cout << indent << " " << now -> text << std::endl; for(auto &it : now -> children) dump(it, indent + '\t');}
    ~ASTNode();
private:
    ASTNode *parent = nullptr;
    std::vector<ASTNode*> children;
    ASTNodeType nodeType;
    std::string text;
};