//f(pq) = f(p)f(q)
//f(p) = -1
//f(p^k) = 0 when k>1
//need p^0
typedef long long ll;
ll n,M;
vector<ll> pre,hou,primes;
ll dfs(ll res, int last, ll f){
    ll g=(res > M ? hou[n/res] : pre[res])-pre[primes[last]-1];
    //g(n/k) - g(L)  L is largest prime in k   ;  g(L) =  g(primes[last] - 1 )
    ll ret= f*g;
    //cout<<"now: "<<n/res<<"   f:"<<f<<"   g: "<<g<<"  ret: "<<ret<<endl;
    for(int i=last;i<(int) primes.size();++i){
        int p = primes[i];
        if((ll)p*p > res) break;
        for(ll q=p,nres=res,nf=f*(-1); q*p<=res ;q*=p){//nf开始为指数是1的贡献 nres无需修改
            ret += dfs(nres/=p, i+1, nf);//枚举更大的数
            //指数大于1时，无贡献 直接break
            break;
        }
    }
    return ret;
}
ll solve(ll n){
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
        const ll q=(ll)p*p,m=n/p;
        const int pnt0=pre[p-1];
        const int mid=M/p;
        const int End=min((ll)M, n/q);
        for(int i=1;i<=mid;++i) hou[i]=hou[i]-(hou[i*p]-pnt0);
        for(int i=mid+1;i<=End;++i) hou[i]=hou[i]-(pre[m/i]-pnt0);
        for(int i=M;i>=q;--i) pre[i]=pre[i]-(pre[i/p]-pnt0);
    }
    primes.push_back(M+1);
    for (int i = 1; i <= M; i++) {
        pre[i] = -pre[i];//-p^0
        hou[i] = -hou[i];
    }
    return n>1 ? dfs(n,0,1)+1 : 1;
}//
int main(){
    cin>>n;
    n--;
    ll ansa = solve(n);
    cin>>n;
    ll ansb = solve(n);
    cout<<ansb - ansa<<endl;
}
