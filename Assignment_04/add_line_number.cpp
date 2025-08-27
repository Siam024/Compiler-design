#include <bits/stdc++.h>
using namespace std;
int main()
{
    ifstream f1("input.c");
    ofstream f2("input1.txt");

    if(!f1.is_open()){
        cout<<"file can't be opened"<<endl;
        return 0;
    }

    string line;
    int i = 1;

    while(getline(f1,line)){
        if(line[0] == '/') continue;
        else{
            f2<<i<<": "<<line<<endl;
            i++;
        }
    }

    f1.close();
    f2.close();
    return 0;
}