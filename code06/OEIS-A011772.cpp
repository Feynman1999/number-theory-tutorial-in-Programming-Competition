#include<bits/stdc++.h>
using namespace std;
#define ll __int128
const int maxn=100;
const int maxm =2e6+10;
ll a[maxn];//质因子
int b[maxn];//质因子的指数
int tot;//1~tot
bool valid[maxm];
int prime[maxm];
void getprime(int n,int &tot,int ans[])
{
    tot=0;
    memset(valid,true,sizeof(valid));
    for(int i=2;i<=n;++i){
        if(valid[i]){
            tot++;
            ans[tot]=i;
        }
        //下面的主角是小于等于i的每个质数
        for(int j=1;(j<=tot) && (i*ans[j]<=n);++j){
            valid[i*ans[j]]=false;
            if(i%ans[j]==0) break;//如果整除就break;
        }
    }
}
void factor(ll n)
{
    ll now=n;
    tot=0;
    for(int i=1;1LL*prime[i]*prime[i]<=now;++i) if(now%prime[i]==0){
        a[++tot]=prime[i];b[tot]=0;
        while(now%prime[i]==0){++b[tot];now/=prime[i];}
    }
    if(now>1){
        a[++tot]=now;b[tot]=1;
    }
}
ll e_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0){x=1;y=0;return a;}
    ll ans=e_gcd(b,a%b,x,y);
    ll temp=x; x=y; y=temp-a/b*y;
    return ans;
}
ll newinv(ll a,ll mod)
{
    ll ans,tmp;
    e_gcd(a,mod,ans,tmp);
    //gcd(a,mod) = 1
    ll c = mod-1;
    ans = (c*ans%mod+mod)%mod;
    return ans;
}
int main()
{
    int Count;
    getprime(2e6,Count, prime);
    int t;
    cin>>t;
    while(t--)
    {
        long long n;
        cin>>n;
        if(n==1){cout<<1<<endl;continue;}
        factor(2*n);//n>1
        assert(tot<15);
        ll ans=1e18;
        for(int i=0;i<(1<<tot);++i){
            int tp = i;
            int id = 0;
            ll A=1,B;
            while(tp){
                ++id;
                if(tp&1){
                    A=A*(ll)pow((long long)(a[id]),(long long)((b[id])));
                }
                tp>>=1;
            }
            B = 2*n/A;
            ll ni = newinv(A,B);
            ll ans1 = A*ni;
            if(ans1 == 0) ans1 = 1e18;
            ans = min(ans1,ans);
        }
        cout<<(long long)ans<<endl;
    }
    return 0;
}
