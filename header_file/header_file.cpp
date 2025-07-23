#include<bits/stdc++.h>
using namespace std;
int main()
{
    ifstream file1("input3.c");
    ofstream file2("output.txt");

    if(!file1.is_open()){
        cout << "File can not be opened"<<endl;
        return 0;
    }

    string line;
    int ok = 0;
    while(getline(file1,line))
    {
        if(line.find("#include")!=-1){
            size_t start = line.find('<');
            size_t end = line.find('>');

            string hf =line.substr(start+1,end-start-1);
            file2<<hf;
        }
    }
    file1.close();
    file2.close();
    return 0;
}