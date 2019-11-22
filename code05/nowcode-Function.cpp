//f(1)=1
//f(p)= (p%4==1)? 4 : 1
//f(p^e) = (p%4==1)? 3e+1 : 1
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,M;
vector<int> pre[2],hou[2],primes;
//0      1~n  素数个数
//1      1~n中  %4=1素数个数 减去  %4=3素数个数
ll dfs(ll res, int last, ll f){
    ll t=(res > M ? hou[0][n/res] : pre[0][res])-pre[0][primes[last]-1];
    ll ans= t*f;
    for(int i=last;i<(int) primes.size();++i){
        int p = primes[i];
        if(p*p > res) break;
        for(ll q=p, nres=res, nf=f*(((p&3)==1)?4:1);q*p<=res;q*=p){
            ans += dfs (nres/=p,i+1,nf);
            nf += f*(((p&3)==1)?3:0);
            ans += nf;
        }
    }
    return ans;
}
int help1[4]={0,1,1,0};
int help2[4]={0,1,0,-1};
ll solve(int n){
    M=sqrt(n);
    for(int i=0;i<2;++i){
        pre[i].clear();pre[i].resize(M+1);
        hou[i].clear();hou[i].resize(M+1);
    }
    primes.clear();primes.reserve(M+1);
    for(int i=1;i<=M;++i){
        pre[0][i]=i-1;
        hou[0][i]=n/i-1;
        pre[1][i]=help1[i&3]-1;//kafang function
        hou[1][i]=help1[(n/i)&3]-1;
    }
    for(int p=2;p<=M;++p){
        if(pre[0][p]==pre[0][p-1]) continue;
        primes.push_back(p);
        const int q=p*p,m=n/p, pnt0 = pre[0][p-1], pnt1 = pre[1][p-1];
        const int mid=M/p;
        const int End=min(M,n/q);
        for(int i=1;i<=mid;++i){
            hou[0][i]-=hou[0][i*p]-pnt0;
            hou[1][i]-=(hou[1][i*p]-pnt1)*help2[p&3];
        }
        for(int i=mid+1;i<=End;++i){
            hou[0][i]-=pre[0][m/i]-pnt0;
            hou[1][i]-=(pre[1][m/i]-pnt1)*help2[p&3];
        }
        for(int i=M;i>=q;--i){
            pre[0][i]-=pre[0][i/p]-pnt0;
            pre[1][i]-=(pre[1][i/p]-pnt1)*help2[p&3];
        }
    }
    primes.push_back(M+1);
    //由0 和 1 可推出 1~n中模4余1的素数个数 覆盖入1中
    for (int i = 2; i <= M; ++i) {
        assert((pre[0][i] + pre[1][i] - 1)%2==0);
        assert((hou[0][i] + hou[1][i] - 1)%2==0);
        pre[1][i] = (pre[0][i] + pre[1][i] - 1)/2;
        hou[1][i] = (hou[0][i] + hou[1][i] - 1)/2;
    }
    hou[1][1] = (hou[0][1] + hou[1][1] - 1)/2;
    //对于本题 计算的贡献为3*pre[1] + pre[0]
    //覆盖到0中
    for(int i = 1;i <= M; ++i){
        pre[0][i]+=3*pre[1][i];
        hou[0][i]+=3*hou[1][i];
    }
    return n>1 ? 1+dfs(n,0,1) : 1;
}
int main()
{
    int t;cin>>t;while(t--)
    {cin>>n;cout<<solve(n)<<endl;}
    return 0;
}