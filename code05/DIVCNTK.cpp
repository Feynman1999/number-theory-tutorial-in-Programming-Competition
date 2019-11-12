//f(pq) = f(p)f(q)
//f(p) = k+1
//f(p^e) = ek+1    so f(p^e) = f(p^{e-1}) + k
//need p^0
typedef unsigned long long u64;
u64 n,M,k;
vector<u64> pre,hou;
vector<int> primes;
u64 dfs(u64 res, int last, u64 f){
    u64 g=(res > M ? hou[n/res] : pre[res])-pre[primes[last]-1];
    u64 ret= f*g;
    for(int i=last;i<(int) primes.size();++i){
        int p = primes[i];
        if((u64)p*p > res) break;
        for(u64 q=p,nres=res,nf=f*(k+1); q*p<=res ;q*=p){//nf开始为指数是1的贡献 nres无需修改
            ret += dfs(nres/=p, i+1, nf);//枚举更大的数
            nf = nf + f*k;
            ret += nf;
        }
    }
    return ret;
}
u64 solve(u64 n){
    M=sqrt(n);
    pre.clear();pre.resize(M+1);
    hou.clear();hou.resize(M+1);
    primes.clear();primes.reserve(M+1);
    for(int i=1;i<=M;++i){
        pre[i]=i-1;
        hou[i]=(n/i-1);
    }
    for(int p=2;p<=M;++p){
        if(pre[p]==pre[p-1]) continue;
        primes.push_back(p);
        const u64 q=(u64)p*p,m=n/p;
        const int pnt0=pre[p-1];//由于是素数个数 所以可以用int 不过这里要注意
        const int mid=M/p;
        const int End=min(M, n/q);
        for(int i=1;i<=mid;++i) hou[i]=hou[i]-(hou[i*p]-pnt0);
        for(int i=mid+1;i<=End;++i) hou[i]=hou[i]-(pre[m/i]-pnt0);
        for(int i=M;i>=q;--i) pre[i]=pre[i]-(pre[i/p]-pnt0);
    }
    primes.push_back(M+1);
    for (int i = 1; i <= M; i++) {
        pre[i] = pre[i]*(k+1);
        hou[i] = hou[i]*(k+1);
    }
    return n>1 ? dfs(n,0,1)+1 : 1;
}//
int main(){
    int t; cin>>t;
    while(t--){
        cin>>n>>k;
        cout<<solve(n)<<endl;
    }
}
