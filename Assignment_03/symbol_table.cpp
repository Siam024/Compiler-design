#include <bits/stdc++.h>
using namespace std;

struct Symbol {
    string name;
    string type;
    string scope;
    string value;
};

bool isKeyword(const string &s) {
    string keywords[] = {"int","float","double","char","void","return","main"};
    for(string kw : keywords)
        if(s == kw) return true;
    return false;
}

bool isSeparator(char c) {
    string sep = ";,{}()[]";
    return sep.find(c) != string::npos;
}

bool isOperator(char c) {
    string ops = "+-*/=%";
    return ops.find(c) != string::npos;
}

int main() {
    ifstream in("input.c");   // input program file
    ofstream tokenOut("tokens.txt");
    ofstream symOut("symbol_table.txt");

    vector<Symbol> symbolTable;
    string word;
    char ch;

    string currentScope = "global";

    while(in.get(ch)) {
        if(isalnum(ch) || ch == '_') {
            word += ch;
        } else {
            if(!word.empty()) {
                if(isKeyword(word)) {
                    tokenOut << "[kw " << word << "] ";
                } else if(isdigit(word[0])) {
                    tokenOut << "[num " << word << "] ";
                } else {
                    tokenOut << "[id " << word << "] ";
                    // insert into symbol table if not exists
                    bool exists = false;
                    for(auto &s : symbolTable)
                        if(s.name == word) exists = true;
                    if(!exists) {
                        Symbol sym;
                        sym.name = word;
                        sym.type = "unknown"; // we can refine by parsing
                        sym.scope = currentScope;
                        sym.value = "";
                        symbolTable.push_back(sym);
                    }
                }
                word.clear();
            }

            if(isSeparator(ch)) {
                tokenOut << "[sep " << ch << "] ";
                if(ch == '{') currentScope = "local";
                if(ch == '}') currentScope = "global";
            } else if(isOperator(ch)) {
                tokenOut << "[op " << ch << "] ";
            } else if(isspace(ch)) {
                continue;
            } else if(ch == '(' || ch == ')') {
                tokenOut << "[par " << ch << "] ";
            }
        }
    }

    // write symbol table
    symOut << "SlNo\tName\tType\tScope\tValue\n";
    int i = 1;
    for(auto &s : symbolTable) {
        symOut << i++ << "\t" << s.name << "\t" 
               << s.type << "\t" 
               << s.scope << "\t" 
               << s.value << "\n";
    }

    cout << "Lexical analysis complete.\nCheck tokens.txt and symbol_table.txt\n";
    return 0;
}
