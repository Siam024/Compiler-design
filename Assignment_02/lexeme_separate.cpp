#include <bits/stdc++.h>
using namespace std;

string keywords[] = {"int", "float", "char", "if", "else", "while", "return", "for"};
string doubleOps[] = {"<=", ">=", "==", "!="};
char singleOps[] = {'+', '-', '*', '/', '=', '<', '>'};
char separators[] = {';', ',', '\''};
char parentheses[] = {'(', ')'};

bool isKeyword(string s) {
    for (int i = 0; i < 8; i++) {
        if (keywords[i] == s)
            return true;
    }
    return false;
}

bool isDoubleOperator(string s) {
    for (int i = 0; i < 4; i++) {
        if (doubleOps[i] == s)
            return true;
    }
    return false;
}

bool isSingleOperator(char c) {
    for (int i = 0; i < 7; i++) {
        if (singleOps[i] == c)
            return true;
    }
    return false;
}

bool isSeparator(char c) {
    for (int i = 0; i < 3; i++) {
        if (separators[i] == c)
            return true;
    }
    return false;
}

bool isParenthesis(char c) {
    for (int i = 0; i < 2; i++) {
        if (parentheses[i] == c)
            return true;
    }
    return false;
}

bool isIdentifier(string s) {
    if (!isalpha(s[0]) && s[0] != '_')
        return false;
    for (int i = 1; i < s.size(); i++) {
        if (!isalnum(s[i]) && s[i] != '_')
            return false;
    }
    return true;
}

bool isNumber(string s) {
    int dotCount = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '.') {
            dotCount++;
            if (dotCount > 1) return false;  // only one dot allowed
        }
        else if (!isdigit(s[i])) {
            return false;
        }
    }
    return !s.empty() && (isdigit(s[0]) || s[0] == '.');
}


vector<string> tokenize(string line) {
    vector<string> tokens;
    string temp;

    for (int i = 0; i < line.size(); i++) {
        char c = line[i];
        if (i + 1 < line.size()) {
            string two = line.substr(i, 2);
            if (isDoubleOperator(two)) {
                if (!temp.empty()) {
                    tokens.push_back(temp);
                    temp.clear();
                }
                tokens.push_back(two);
                i++;
                continue;
            }
        }
        if (isspace(c)) {
            if (!temp.empty()) {
                tokens.push_back(temp);
                temp.clear();
            }
        }
        else if (isSingleOperator(c) || isSeparator(c) || isParenthesis(c)) {
            if (!temp.empty()) {
                tokens.push_back(temp);
                temp.clear();
            }
            tokens.push_back(string(1, c));
        }
        else {
            temp += c;
        }
    }
    if (!temp.empty())
        tokens.push_back(temp);

    return tokens;
}

void classifyTokens(vector<string> tokens, ofstream &out) {
    for (int i = 0; i < tokens.size(); i++) {
        string t = tokens[i];

        if (isKeyword(t)) {
            out << "[kw " << t << "] ";
        }
        else if (isDoubleOperator(t)) {
            out << "[op " << t << "] ";
        }
        else if (t.size() == 1 && isSingleOperator(t[0])) {
            out << "[op " << t << "] ";
        }
        else if (t.size() == 1 && isSeparator(t[0])) {
            out << "[sep " << t << "] ";
        }
        else if (t.size() == 1 && isParenthesis(t[0])) {
            out << "[par " << t << "] ";
        }
        else if (isNumber(t)) {
            out << "[num " << t << "] ";
        }
        else if (isIdentifier(t)) {
            out << "[id " << t << "] ";
        }
        else {
            out << "[unkn " << t << "] ";
            cout << "Error: unrecognized token [" << t << "]\n";
        }
    }
    out << "\n";
}

int main() {
    ifstream in("input5.c");
    ofstream out("output.txt");

    if (!in.is_open()) {
        cout << "Failed to open input file.\n";
        return 1;
    }

    string line;
    while (getline(in, line)) {
        vector<string> tokens = tokenize(line);
        classifyTokens(tokens, out);
    }

    in.close();
    out.close();

    cout << "Lexical analysis complete. See 'output.txt'.\n";
    return 0;
}
