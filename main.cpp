#include "./include/Lexer/Lexer.h"
#include "./include/Parser/Parser.h"
#include "./include/utils/utils.h"
#include <bits/stdc++.h>
using namespace std;

string code = "";
string filePath = "./test/parseTest03.in";

void test01() {
    Lexer lexer;
    TokenReader tokenReader = lexer.tokenize(code);
    tokenReader.dump();
}

void test02() {
    Parser parser;
    ASTNode *root = parser.parse(code);
    root -> dump(root, "");
    root -> des(root);
}

int main() {
    code = readFileIntoString(filePath);
    freopen("../error.out", "w", stderr);
    freopen("../out.out", "w", stdout);
    test01();
    test02();
    return 0;
}