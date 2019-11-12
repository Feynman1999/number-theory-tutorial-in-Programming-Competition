#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
ll solve(ll n)
{
    vector<ll> pre, hou;
    vector<int> primes;
    vector<double> inv;
    int M=sqrt(n);
    pre.resize(M+1+sqrt(M)+1);
    hou.resize(M+1);
    inv.resize(M+1);
    primes.reserve(M+1);
    for(int i=1;i<=M;++i){
        pre[i]=i-1;
        hou[i]=(n/i-1);
        inv[i]=1./i;
    }
    for(int p=2;p<=M;++p){
        if(pre[p]==pre[p-1]) continue;
        primes.push_back(p);
        const ll q=(ll)p*p,m=n/p;
        const int pnt0=pre[p-1];
        const int mid=M/p;
        const int End=min((ll)M, n/q);
        for(int i=1;i<=mid;++i) hou[i]-=hou[i*p]-pnt0;
        for(int i=mid+1;i<=End;++i){
            int j = m*inv[i] + 1e-6;
            hou[i]-=pre[j]-pnt0;
        }
        for(int i=M/p;i>=p;--i){
            for(int j=p-1;j>=0;--j)
                pre[i*p+j]-=pre[i]-pnt0;
        }
    }
    return hou[1];
}
double upper_func(ll x)//1~x中素数的个数估计 上界
{
    if(x >= 2953652287){
        double lgx = log((double)x);
        double lgx2 = lgx * lgx;
        return x/lgx*(1+1/lgx+2.334/lgx2);
    }
    else return solve(x);
}
double lower_func(ll x)
{
    if(x >= 88783){
        double lgx = log((double)x);
        double lgx2 = lgx * lgx;
        return x/lgx*(1+1/lgx+2.0/lgx2);
    }
    else return solve(x);
}
const int maxn=2e5;//2e5 平方之后肯定 > 1e9*23 + 1.5*1e7
bool valid[maxn+10];
ll ans[maxn/5];
bool vis[maxn*75];//用于被筛 1.5*1e7 够用了
int tot;
void get_prime(int n)
{
    tot=0;
    for(int i=2;i<=n;++i) valid[i]=true;
    for(int i=2;i<=n;++i){
        if(valid[i]) ans[++tot]=i;
        for(int j=1;j<=tot &&  ans[j]*i<=n;++j){
            valid[ans[j]*i]=false;
            if(i%ans[j]==0) break;
        }
    }
}
ll nthprime(ll n)
{
    ll l,r,up,low;
    l=2-1, r=1e9*23;//1e9 *23就够了
    while(r-l>1)
    {
        ll mid = (l+r)/2;
        if(lower_func(mid)>=n) r = mid;
        else l = mid;
    }
    up = r;//up比实际值大
    l = 2-1;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(upper_func(mid)>=n) r=mid;
        else l=mid;
    }
    low = r;
    //cout<<low<<" "<<up<<endl;
    if(up==low) return low;
    else{
        get_prime(maxn);
        ll L,R;
        L = low;
        R = up;
        assert(R-L+1 < maxn*75);
        for(int i=1;i<=(R-L+1);++i) vis[i]=true;
        assert(L!=1);//应该不会出现L为1的情况
        for(int i=1;i<=tot;i++)
            for(ll j=max(ans[i],(L-1)/ans[i]+1);j<=R/ans[i];j++)//当前素数的j倍
                vis[ans[i]*j-L+1]=false;//ans[i]*j是合数

        //先MLLMO Method 求出low点的值
        ll now = solve(low);
        if(now == n && vis[1]) return low;
        else{
            for(int i=2;i<=(R-L+1);++i){
                if(vis[i]){
                    now+=1;
                    if(now==n) return L+i-1;
                }
            }
        }
    }
}
int main()
{
    ll n;cin>>n;// 1<= n <= 10^9
    cout<<nthprime(n)<<endl;
}

