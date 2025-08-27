#include <bits/stdc++.h>
using namespace std;

struct Entry {
    int SlNo;
    string Name, Id, Type, Scope, Value;
};

class SymbolTable {
    vector<Entry> rows;
    int auto_id = 0;

public:
    void insert(string name, string id, string type, string scope, string value = "") {
        rows.push_back({++auto_id, name, id, type, scope, value});
    }

    void update(string name, string value, string scope = "") {
        for (int i = 0; i < rows.size(); i++) {
            if (rows[i].Name == name && (scope == "" || rows[i].Scope == scope)) {
                rows[i].Value = value;
                return;
            }
        }
    }

    void display() {
        cout << "SlNo  Name   Id   Type   Scope   Value\n";
        for (int i = 0; i < rows.size(); i++) {
            cout << rows[i].SlNo << " "
                 << rows[i].Name << " "
                 << rows[i].Id << " "
                 << rows[i].Type << " "
                 << rows[i].Scope << " "
                 << rows[i].Value << "\n";
        }
    }
};

vector<string> read_tokens(string filename) {
    ifstream fin(filename);
    vector<string> tokens;
    string token;
    bool inside = false;
    char ch;

    while (fin.get(ch)) {
        if (ch == '[') { inside = true; token = ""; }
        else if (ch == ']') { inside = false; tokens.push_back(token); }
        else if (inside) token += ch;
    }
    return tokens;
}

SymbolTable parse_tokens(vector<string> tokens) {
    SymbolTable st;
    vector<string> scope = {"global"};
    string current_func = "";

    for (int i = 0; i < tokens.size();) {
        string tok = tokens[i];

        if (tok == "{") { 
            scope.push_back(current_func == "" ? scope.back() : current_func); 
            i++; 
            continue; 
        }
        if (tok == "}") { 
            scope.pop_back(); 
            if (scope.empty()) scope.push_back("global"); 
            if (current_func != "" && scope.back() == "global") current_func = ""; 
            i++; 
            continue; 
        }

        if (tok=="int"||tok=="float"||tok=="double"||tok=="char"||tok=="void") {
            string dtype = tok;
            if (i+1 < tokens.size() && tokens[i+1].rfind("id ",0)==0) {
                string name = tokens[i+1].substr(3);

                if (i+2 < tokens.size() && tokens[i+2]=="(") { 
                    st.insert(name,"func",dtype,"global");
                    current_func = name;
                } else { 
                    string val="";
                    if (i+2 < tokens.size() && tokens[i+2]=="=" && i+3 < tokens.size()) val = tokens[i+3];
                    st.insert(name,"var",dtype,scope.back(),val);
                }
                i+=2;
            } else i++;
            continue;
        }

        if (tok.rfind("id ",0)==0) {
            string name = tok.substr(3);
            if (i+1 < tokens.size() && tokens[i+1]=="=" && i+2 < tokens.size()) {
                string val = tokens[i+2];
                if (val.rfind("id",0)!=0) st.update(name,val,scope.back());
            }
            i++;
            continue;
        }

        i++;
    }
    return st;
}

int main() {
    vector<string> tokens = read_tokens("input3.txt");
    SymbolTable st = parse_tokens(tokens);

    st.display(); 
    return 0;
}
