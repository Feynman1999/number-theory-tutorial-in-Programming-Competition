//SPOJ - MOD
//sqrt(m)*常数
//用二分常数比map小一点
////a^x = b (mod m)  solve x     1<=a,b,m<=10^9
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll fast_exp(ll a,ll b,ll c){
    ll res=1;a=a%c;assert(b>=0);
    while(b>0)
    {
        if(b&1) res=(a*res)%c;
        b=b>>1;a=(a*a)%c;
    }
    return res;
}
ll gcd(ll a,ll b){if(b==0) return a;return gcd(b,a%b);}
struct pli{
    ll first;
    int second;
    pli(){}
    pli (ll x_,int y_){
        first=x_;
        second=y_;
    }
    bool operator < (const pli &b) const {
        if(first==b.first) return second>b.second;//因为second更大的解更小，所以>
        return first<b.first;
    }
};
ll bsgs(ll a,ll b,ll m)
{
    a%=m,b%=m;
    if(b==1) return 0;
    int cnt=0;
    ll t=1;
    for(ll g=gcd(a,m);g!=1;g=gcd(a,m)){
        if(b % g) return -1;//no solution
        m/=g , b/=g , t = t * (a / g) % m;//记录下要算逆元的值
        ++cnt;
        if(b==t) return cnt;
    }
    int M=int(sqrt(m)+1);//这里的m不等于形式参数中的值了
    ll base=b;
//    std::unordered_map<ll,int> hash;
//    for(int i=0;i!=M;++i){
//        hash[base]=i;//存的是大的编号，所以可以保证最小解
//        base=base*a%m;
//    }
//    base=fast_exp(a,M,m);//必要时要用快速乘
//    ll now=t;
//    for(int i=1;i<=M+1;++i){
//        now=now*base%m;//这里乘在左边了 相当于右边乘逆元
//        if(hash.count(now)) return i*M-hash[now]+cnt;
//    }
    pli hash[int(1e5)];//注意再大可能会爆内存
    for(int i=0;i!=M;++i){
        hash[i]=pli(base,i);
        base=base*a%m;
    }
    sort(hash,hash+M);//默认以first
    base=fast_exp(a,M,m);
    ll now=t;
    for(int i=1;i<=M+1;++i){
        now=now*base%m;
        //注意下面M+10  这样可以保证解最小
        int id=lower_bound(hash, hash+M, pli(now,M+10))-hash;//默认是first
        assert(id>=0 &&id<=M);
        if(id!=M && hash[id].first==now) return i*M-hash[id].second+cnt;//减去的编号second越大越好
    }
    return -1;
}
int main()
{
    ll a,b,m;
    while(cin>>a>>m>>b,m)
    {
        if(m==1) assert(b==0);
        ll ans=bsgs(a,b,m);
        if(ans==-1) cout<<"No Solution"<<endl;
        else{
            cout<<ans<<endl;
            assert(fast_exp(a,ans,m)==b%m);
        }
    }
    return 0;
}
