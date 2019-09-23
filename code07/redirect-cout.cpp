#include<bits/stdc++.h>
using namespace std;
int main()
{
    stringstream ss;
    streambuf* buffer = cout.rdbuf(); //oldbuffer,STDOUT的缓冲区
    cout.rdbuf(ss.rdbuf());//redirect

    cout<<"number theory"<<endl;
    cout<<"ok";

    string out(ss.str());
    cout.rdbuf(buffer); //重新载入STDOUT的缓冲区

    cout<<out<<endl;
    return 0;
}
