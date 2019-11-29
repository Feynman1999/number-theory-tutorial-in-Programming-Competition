#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const double pi=acos(-1.0);
const int maxn=1e5;
typedef complex<double> xu;
xu a[maxn<<2],b[maxn<<2];
int inver;
void FFT(xu *s ,int n){
    if(n==1) return ;//n=1时值就是系数  因为只有w_1^0这一点
    xu a1[n>>1],a2[n>>1];
    for(int i=0;i<n;i+=2){
        a1[i>>1]=s[i];
        a2[i>>1]=s[i+1];
    }
    FFT(a1,n>>1); FFT(a2,n>>1);
    xu w=xu(cos(2*pi/n),inver*sin(2*pi/n));
    xu wn=xu(1,0);
    for(int i=0;i<(n>>1);++i,wn=wn*w){
        s[i]=a1[i]+wn*a2[i];
        s[i+(n>>1)]=a1[i]-wn*a2[i];
    }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
#endif
    ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    int tp;
    n++;
    m++;
    for(int i=0;i<n;++i){
        cin>>tp;
        a[i]=xu(tp,0);
    }
    for(int i=0;i<m;++i){
        cin>>tp;
        b[i]=xu(tp,0);
    }
    int N=1; while(N<n+m-1) N<<=1;
    inver=1;
    FFT(a,N); FFT(b,N);
    for(int i=0;i<N;++i) a[i]=a[i]*b[i];
    //现在a中的值是上面的傅里叶变化的结果啦 wn0,wn1,wn2,...,wn n-1
    //下面作为逆变化的系数
    inver=-1;
    FFT(a,N);
    for(int i=0;i<n+m-1;++i) cout<<ll(a[i].real()/N+0.5)<<' ';
    return 0;
}