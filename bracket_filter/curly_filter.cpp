#include <bits/stdc++.h>
using namespace std;
int main()
{
    ifstream f1("input1.c");
    ofstream f2("output.txt");

    if(!f1.is_open()){
        cout<<"file can't be opened"<<endl;
        return 0;
    }

    char c;

    while(f1.get(c)){
        if(c=='{'||c=='}'){
            f2<<c;
        }
        
    }

    f1.close();
    f2.close();
    return 0;
}