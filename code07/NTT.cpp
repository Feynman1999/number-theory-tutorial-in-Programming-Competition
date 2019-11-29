#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+10;
const int mod = 998244353;
const int groot = 3;//119 * 2^23 + 1 = mod
int gk = 119;
const int limit = 1<<23;
int omega[maxn<<2], omegaInverse[maxn<<2];//辅助
ll fast_exp(ll a,ll b,ll c){
    ll res=1;
    a=a%c;
    assert(b>=0);
    while(b>0)
    {
        if(b&1) res=(a*res)%c;
        b=b>>1;
        a=(a*a)%c;
    }
    return res;
}
inline int add(const int x, const int v){
    return x+v>=mod?x+v-mod: x+v;
}
inline int dec(const int x, const int v){
    return x-v<0?x-v+mod:x-v;
}
void init(const int n){
    omega[0] = 1;
    omegaInverse[0] = 1;
    assert(limit>=n);
    gk = gk* (limit / n);// 很关键 取到恰好用的2^m
    int g_n = fast_exp(groot, gk, mod);
    int g_n_ni = fast_exp(g_n, mod-2, mod);
    for(int i=1;i<n;++i) {
        omega[i] = 1LL*omega[i-1]*g_n%mod;
        omegaInverse[i] = 1LL*omegaInverse[i-1]*g_n_ni%mod;
    }
}
void trans(int *a,const int n,const int *omega){//a是系数  n是2的次幂  omega是要带入的点
    int k=0;
    while((1<<k)<n) k++; //看N是2的多少次幂
    for(int i=0;i<n;++i){
        int t=0;
        for(int j=0;j<k;++j) if(i&(1<<j)) t|=(1<<(k-j-1));
        if(i<t) swap(a[i],a[t]);//原地翻转
    }
    for(int l=2;l<=n;l*=2){//l=1不用求 就是系数
        int m=l/2;
        for(int *p=a;p!=a+n;p+=l){//l为一段要求 由两段l/2合并得到
            //当前处理[p,p+l)
            for(int i=0;i<m;++i){
                //蝴蝶操作  omega_{l}^{i}=omega_{N}^{N/l*i}
                int t=1LL*omega[n/l*i]*p[i+m]%mod;
                p[i+m]=dec(p[i], t);
                p[i]=add(p[i], t);
            }
        }
    }
}
void dft(int *a,const int n){
    trans(a,n,omega);
}
void idft(int *a,const int n){
    trans(a,n,omegaInverse);
    int n_ni = fast_exp(n, mod-2, mod);
    for(int i=0;i<n;++i) a[i] = 1LL*a[i]*n_ni%mod;
}
int a[maxn<<2], b[maxn<<2];
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    n++;m++;
    for(int i=0;i<n;++i) cin>>a[i];
    for(int i=0;i<m;++i) cin>>b[i];
    int N=1;
    while(N<m+n-1) N<<=1;
    init(N);
    dft(a,N);
    dft(b,N);
    for(int i=0;i<N;++i) a[i]=1LL*a[i]*b[i]%mod;
    idft(a,N);
    for(int i=0;i<n+m-1;++i) cout<<a[i]<<" ";
    return 0;
}
