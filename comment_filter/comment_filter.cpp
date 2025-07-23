#include<bits/stdc++.h>
using namespace std;
int main()
{
    ifstream file1("input2.c");
    ofstream file2("output.txt");

    if(!file1.is_open()){
        cout << "File can not be opened"<<endl;
        return 0;
    }

    string line;
    int ok = 0;
    while(getline(file1,line))
    {
        size_t flag1 = line.find("/*");
        size_t flag2 = line.find("*/");
        if(flag1 != -1) ok = 1;
        if(flag2 != -1) {
            ok = 0;
            continue;
        }
        if(ok) continue;
        
        size_t start = line.find("//");
        if(start != -1)
        {
            string line2 = line.substr(0, start);
            file2 << line2;
        }
        else{
            int flag = 0;
            for(char c : line)
            {
                if(c != ' ' && flag == 0)
                {
                    flag = 1;
                }
                if(flag) file2 << c;
            }
        }
    }
    file1.close();
    file2.close();
    return 0;
}