#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
typedef long long ll;
const int maxn = 200;
bool valid[maxn];
int primes[maxn];
int tot;
void getprime(int n, int ans[])
{
    tot=0;
    memset(valid,true,sizeof(valid));
    for(int i=2;i<=n;++i){
        if(valid[i]){tot++;  ans[tot]=i;}
        for(int j=1;(j<=tot) && (i*ans[j]<=n);++j){
            valid[i*ans[j]]=false;  if(i%ans[j]==0) break;
        }
    }
}
ll mod_mul(const ll & a,const ll & b,const ll & c){
    __int128 tp = 1;    return tp*a*b%c;
}
ll fast_exp(ll a,ll b,ll c){
    ll res=1; a=a%c;
    while(b){
        if(b&1) res=mod_mul(res,a,c);
        b>>=1;  a=mod_mul(a,a,c);
    }
    return res;
}
bool test(ll n,ll a,ll d)
{//d=n-1
    if(!(n&1)) return false;
    while(!(d&1))  d>>=1;//将d分解为奇数 至少有一个2因子，所以d!=n-1
    ll t=fast_exp(a,d,n);
    while(d!=n-1 && t!=1 && t!=n-1){
        t=mod_mul(t,t,n);
        d<<=1;
    }
    return ((t==n-1) || (d&1) ==1 );//两个条件都不成立则一定是合数; 若两个有一个成立，且多次，对于合数来说，可能性极小，所以可以认为是素数
}
bool is_prime(ll n){
    if(n<2) return false;
    for(int i=1;i<=tot;++i){
        if(n==primes[i]) return true;
        if(n%primes[i]==0) return false;
    }
    ll a[10];
    srand(time(0));
    for(int i=0;i<6;++i) {//测试6次
        a[i]=rand()%(n-2)+2;//取[2,n-1]随机数
        if(!test(n,a[i],n-1)) return false;//找到证据说明是合数
    }
    return true;//如果上面所有测试都是true
}
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
ll nthprime(ll n)
{
    ll l=2-1, r=n*23;//问题区间[2,x] 由于是左开右闭 所以l为2 -1
    //23 是对于1e9测试出来的 因为输入1e9 答案是22801763489
    int num = 0;
    ll res;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        res = solve(mid);
        if(res>=n){
            r=mid;
            if(num>=16) break;
        }
        else l=mid;
        num++;
    }
    //cout<<clock()<<endl;
    for(;;r--){//当前r的答案是res 即[1,r]中素数个数为res
        if(is_prime(r)){
            if(res==n) return r;
            else res--; //res>n
        }
    }
}
int main()
{
    getprime(100, primes);//100以内的素数 用于加速miller-rabin
    ll n;
    cin>>n;// 1<= n <= 10^9
    //n=1e9;
    cout<<nthprime(n)<<endl;
    return 0;
}

