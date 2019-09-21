#include<bits/stdc++.h>
using namespace std;
typedef __int128 lll;
typedef long long ll;
ll f(lll x, ll c, ll n){ return (x*x+c)%n; }
ll gcd(ll a, ll b){
    if(b==0) return a;
    return gcd(b, a%b);
}
ll pollard_rho(ll N){
    if(N<=1) return -1;
    ll s=0,t=0,c=1LL*rand()*rand()%(N-1)+1;
    int goal, stp;
    lll val = 1;
    int up = (1<<6)-1;
    for(goal = 1;;goal<<=1,s=t,val=1)//维护区间
    {
        for(stp=1;stp<=goal;++stp){
            t = f(t,c,N);
            val = val * abs(t-s) % N;//int 128 或者快读乘
            if(!(stp&up))
            {
                ll d = gcd(val, N);
                if(d>1) return d;
            }
        }
        ll d = gcd(val, N);
        if(d>1) return d;
    }
}
int main(){
    cout<<pollard_rho(91)<<endl;
    return 0;
}
