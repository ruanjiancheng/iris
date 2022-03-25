#include <bits/stdc++.h>
#include "./include/Token/TokenReader.h"
#include "./include/Parser/Parser.h"
#include "./include/Lexer/Lexer.h"
#include "./include/Script/Script.h"
using namespace std;

bool v = false;
Script script;
Parser parser;
ASTNode *root = nullptr;


int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp("-v", argv[1]) == 0) {
        v = true;
        cout << "verbose mode" << endl;
    }
    cout << "Welcome to iris!" << endl;
    string scriptText = "";
    string code = "";
    cout << "\n>>> ";

    while (true) {
        getline(cin, code);
        if (code == "exit();") {
            cout << "good bye!" << endl;
            break;
        }
        scriptText += code + '\n';
        if (code.back() == ';') {
            root = parser.parse(scriptText);
            if (v) {
                root -> dump(root, "");
            }
            cout << "--- output ---\n";
            script.evaluate(root);
            cout << "\n>>> ";
            scriptText = "";
            root -> des(root);
        }
    }
    return 0;
}