#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const double pi=acos(-1.0);
const int maxn=1e5;
typedef complex<double> xu;
xu omega[maxn<<2],omegaInverse[maxn<<2];//辅助
void init(const int n){
    for(int i=0;i<n;++i){
        omega[i]=xu(cos(2*pi/n*i),sin(2*pi/n*i));
        omegaInverse[i]=conj(omega[i]);
    }
}
void trans(xu *a,const int n,const xu *omega){//a是系数  n是2的次幂  omega是要带入的点
    int k=0;
    while((1<<k)<n) k++;
    //看N是2的多少次幂
    for(int i=0;i<n;++i){
        int t=0;
        for(int j=0;j<k;++j) if(i&(1<<j)) t|=(1<<(k-j-1));
        if(i<t) swap(a[i],a[t]);//原地翻转
    }
    for(int l=2;l<=n;l*=2){//l=1不用求 就是系数
        int m=l/2;
        for(xu *p=a;p!=a+n;p+=l){//l为一段要求 由两段l/2合并得到
            //当前处理[p,p+l)
            for(int i=0;i<m;++i){
                //蝴蝶操作  omega_{l}^{i}=omega_{N}^{N/l*i}
                xu t=omega[n/l*i]*p[i+m];
                p[i+m]=p[i]-t;
                p[i]+=t;
            }
        }
    }
}
void dft(xu *a,const int n){
    trans(a,n,omega);
}
void idft(xu *a,const int n){
    trans(a,n,omegaInverse);
    for(int i=0;i<n;++i) a[i]/=n;
}
xu a[maxn<<2], b[maxn<<2];
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    n++;
    m++;
    int tp;
    for(int i=0;i<n;++i){
        cin>>tp;
        a[i]=xu(tp,0);
    }
    for(int i=0;i<m;++i){
        cin>>tp;
        b[i]=xu(tp,0);
    }
    int N=1;
    while(N<m+n-1) N<<=1;
    init(N);
    dft(a,N);
    dft(b,N);
    for(int i=0;i<N;++i) a[i]*=b[i];
    idft(a,N);
    for(int i=0;i<n+m-1;++i) cout<<(ll)(a[i].real()+0.5)<<" ";
    return 0;
}
