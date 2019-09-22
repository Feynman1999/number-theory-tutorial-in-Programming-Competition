//求一个素数的原根
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> a;//p-1的所有质因子
ll fast_pow(ll a,ll b,ll c){
    ll res=1;
    a=a%c;
    while(b)
    {
        if(b&1) res=(res*a)%c;
        b=b>>1;
        a=(a*a)%c;
    }
    return res;
}
bool g_test(ll g,ll p){
    for(ll i=0;i<a.size();++i)
        if(fast_pow(g,(p-1)/a[i],p)==1)
            return 0;
    return 1;
}
ll primitive_root(ll p)
{
    a.clear();
    ll tmp=p-1;
    for(ll i=2;i<=tmp/i;++i)
        if(tmp%i==0){
            a.push_back(i);
            while(tmp%i==0) tmp/=i;
        }
    if(tmp!=1) a.push_back(tmp);
    long long g=1;
    while(1)
    {
        if(g_test(g,p)) return g;
        ++g;
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cout<<primitive_root(1e9+9)<<endl;
    return 0;
}