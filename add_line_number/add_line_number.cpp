#include <bits/stdc++.h>
using namespace std;
int main()
{
    ifstream f1("input.c");
    ofstream f2("output.txt");

    if(!f1.is_open()){
        cout<<"file cant be opened"<<endl;
        return 0;
    }

    string line;
    int i = 1;

    while(getline(f1,line)){
       f2<<i<<": "<<line<<endl;
       i++;
    }

    f1.close();
    f2.close();
    return 0;
}