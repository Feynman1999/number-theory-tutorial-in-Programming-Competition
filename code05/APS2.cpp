//f(pq) = f(p)  p<q
//f(p) = p
//f(p^e) = p
//need p^0 p^1
typedef unsigned long long u64;
u64 n,M;
vector<u64> pre[2],hou[2];
vector<int> primes;
inline u64 ff(u64 x){
    if(x&1) return (x+1)/2*x;
    return x/2*(x+1);
}
u64 dfs(u64 res, int last, u64 f){
    u64 g,ans;
    if(last==0){//第一次进入dfs 统计所有素数的和
        g=(res > M ? hou[1][n/res] : pre[1][res])-pre[1][primes[last]-1];
        ans = g;
    }
    else{
        g=(res > M ? hou[0][n/res] : pre[0][res])-pre[0][primes[last]-1];//否则拿当前数的f值直接乘以素数个数即可
        ans = f*g;
    }
    for(int i=last;i<(int) primes.size();++i){
        int p = primes[i];
        if((u64)p*p > res) break;
        for(u64 q=p,nres=res,nf=(last==0? p: f); q*p<=res ;q*=p){//nf开始为指数是1的贡献 nres无需修改
            ans += dfs(nres/=p, i+1, nf);//枚举更大的数
            ans += nf;
        }
    }
    return ans;
}
u64 solve(u64 n){
    M=sqrt(n);
    for(int i=0;i<2;++i){
        pre[i].clear();pre[i].resize(M+1);
        hou[i].clear();hou[i].resize(M+1);
    }
    primes.clear();primes.reserve(M+1);
    for(int i=1;i<=M;++i){
        pre[0][i]=i-1;
        hou[0][i]=(n/i)-1;
        pre[1][i]=ff(i)-1;
        hou[1][i]=ff(n/i)-1;
    }
    for(int p=2;p<=M;++p){
        if(pre[0][p]==pre[0][p-1]) continue;
        primes.push_back(p);
        const u64 q=(u64)p*p, m=n/p;
        const u64 pnt0=pre[0][p-1], pnt1=pre[1][p-1];
        const int mid=M/p;
        const int End=min(M, n/q);
        for(int i=1;i<=mid;++i){
            hou[0][i]=hou[0][i]-(hou[0][i*p]-pnt0);
            hou[1][i]=hou[1][i]-(hou[1][i*p]-pnt1)*p;
        }
        for(int i=mid+1;i<=End;++i){
            hou[0][i]=hou[0][i]-(pre[0][m/i]-pnt0);
            hou[1][i]=hou[1][i]-(pre[1][m/i]-pnt1)*p;
        }
        for(int i=M;i>=q;--i){
            pre[0][i]=pre[0][i]-(pre[0][i/p]-pnt0);
            pre[1][i]=pre[1][i]-(pre[1][i/p]-pnt1)*p;
        }
    }
    primes.push_back(M+1);
    return n>1 ? dfs(n,0,0) : 0;
}//
int main(){
    int t; cin>>t;
    while(t--){
        cin>>n;
        cout<<solve(n)<<endl;
    }
}
