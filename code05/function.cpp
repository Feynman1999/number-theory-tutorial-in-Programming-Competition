const int mod=998244353;
const int ni2=499122177;
ll n,M;
ll nmod;
vector<int> pre[2],hou[2],primes;
inline int add(const int x, const int v) {
    return x + v >= mod ? x + v - mod : x + v;
}
inline int dec(const int x, const int v) {
    return x - v < 0 ? x - v + mod : x - v;
}
//这里res是n/枚举的数
int dfs(ll res, int last, ll f, ll k){// k is now number
    //最大质因子是prime[last-1] 但将1放在外面值显然一样
    int t1 = nmod*dec((res > M ? hou[0][n/res] : pre[0][res]),pre[0][primes[last]-1])%mod;
    int t2 = k%mod*dec((res > M ? hou[1][n/res] : pre[1][res]),pre[1][primes[last]-1])%mod;
    int ret= (f+1)*dec(t1,t2)%mod;
    for(int i=last;i<(int) primes.size();++i){
        int p = primes[i];
        if((ll)p*p > res) break;
        for(ll q=p,nres=res,nk=k,nf=f+1;q*p<=res;q*=p){//nf需修改
            ret = add(ret,dfs(nres/=p,i+1,nf,nk*=p));//枚举更大的数
            nf+=1;//继续枚举当前素数
            ret =add(ret,nf*dec(nmod, k*q*p%mod)%mod);//指数大于1时，记上贡献
        }
    }
    return ret;
}
inline int ff(ll x){
    x%=mod;
    return x*(x+1)%mod*ni2%mod;
}
int solve(ll n){
    M=sqrt(n);
    for(int i=0;i<2;++i){
        pre[i].clear();pre[i].resize(M+1);
        hou[i].clear();hou[i].resize(M+1);
    }
    primes.clear();primes.reserve(M+1);
    for(int i=1;i<=M;++i){
        pre[0][i]=i-1;
        hou[0][i]=(n/i-1)%mod;
        pre[1][i]=dec(ff(i),1);;
        hou[1][i]=dec(ff(n/i),1);
    }
    for(int p=2;p<=M;++p){
        if(pre[0][p]==pre[0][p-1]) continue;
        primes.push_back(p);
        const ll q=(ll)p*p,m=n/p;
        const int pnt0=pre[0][p-1],pnt1=pre[1][p-1];
        const int mid=M/p;
        const int End=min((ll)M,n/q);
        for(int i=1;i<=mid;++i){
            hou[0][i]=dec(hou[0][i],dec(hou[0][i*p],pnt0));
            hou[1][i]=dec(hou[1][i],dec(hou[1][i*p],pnt1)*(ll)p%mod);
        }
        for(int i=mid+1;i<=End;++i){
            hou[0][i]=dec(hou[0][i],dec(pre[0][m/i],pnt0));
            hou[1][i]=dec(hou[1][i],dec(pre[1][m/i],pnt1)*(ll)p%mod);
        }
        for(int i=M;i>=q;--i){
            pre[0][i]=dec(pre[0][i],dec(pre[0][i/p],pnt0));
            pre[1][i]=dec(pre[1][i],dec(pre[1][i/p],pnt1)*(ll)p%mod);
        }
    }
    //cout<<clock()<<endl;
    primes.push_back(M+1);
    return n>1 ? add(dfs(n,0,0,1),0) : 0;
}
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    nmod = (n+1)%mod;
    cout<<solve(n)<<endl;
    return 0;
}