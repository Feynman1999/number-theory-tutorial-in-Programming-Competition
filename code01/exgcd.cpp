/*
拓展欧几里得算法 (a,b非零)
求解ax+by=gcd(a,b)的一个解(x1,y1)
则通解为(x1+k*b/g,y1-k*a/g)

如果求解ax+by=c 
输入a,b后 下面模板会求出
ax+by=+\-gcd(a,b)的一个解(x1,y1) 
正负号虽然不确定（和扩欧写法有关） 但等式是成立的
ax+by=c 的一个解为(x2,y2)=c/g*(x1,y1)
则通解为(x2+k*b/g,y2-k*a/g)
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll e_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    ll ans=e_gcd(b,a%b,x,y);
    ll temp=x;
    x=y;
    y=temp-a/b*y;
    return ans;
}
int main()
{
    ll a,b,x,y;
    cin>>a>>b;
    ll gcd=e_gcd(a,b,x,y);
    cout<<"gcd:"<<gcd<<' '<<"x1:"<<x<<' '<<"y1:"<<y<<endl;
    cout<<"x的最小正整数解"<<(x%(b/gcd)+b/gcd)%(b/gcd)<<endl;
    return 0;
}
