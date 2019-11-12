//f(pq) = f(p)f(q)
//f(p) = p-1
//f(p^k) = p^k - p^{k-1} = p^{k-1}*(p-1)    so f(p^k) = f(p^{k-1})*p when k>1
//need p^0 and p^1
typedef long long ll;
const int mod=1e9+7;
const int ni2=500000004;
inline int add(const int x, const int v) { return x + v >= mod ? x + v - mod : x + v; }
inline int dec(const int x, const int v) { return x - v < 0 ? x - v + mod : x - v; }
inline int ff(ll x){
    x%=mod;
    return x*(x+1)%mod*ni2%mod;
}
ll n,M;
vector<int> pre[2],hou[2],primes;

int dfs(ll res, int last, ll f){
    int g=dec((res > M ? hou[1][n/res] : pre[1][res]), pre[1][primes[last]-1]);
    //g(n/k) - g(L)  L is largest prime in k   ;  g(L) =  g(primes[last] - 1 )
    int ret= f*g%mod;
    for(int i=last;i<(int) primes.size();++i){
        int p = primes[i];
        if((ll)p*p > res) break;
        for(ll q=p,nres=res,nf=f*(p-1)%mod;q*p<=res;q*=p){//nf开始为指数是1的贡献 nres无需修改
            ret = add(ret, dfs(nres/=p, i+1, nf));//枚举更大的数
            nf = nf*p%mod;//继续枚举当前素数，指数大于1时，指数每加1, nf=nf*p;
            ret =add(ret,nf);
        }
    }
    return ret;
}
ll solve(ll n){
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
        const int pnt0=pre[0][p-1], pnt1=pre[1][p-1];
        const int mid=M/p;
        const int End=min((ll)M, n/q);
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
    primes.push_back(M+1);
    for (int i = 1; i <= M; i++) {
        pre[1][i] = dec(pre[1][i], pre[0][i]);//p-1
        hou[1][i] = dec(hou[1][i], hou[0][i]);
    }
    return n>1 ? add(dfs(n,0,1),1) : 1;
}//
int main(){
    cin>>n;  cout<<solve(n)<<endl;
}
