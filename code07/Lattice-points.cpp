typedef pair<ll,ll> pll;
#define mp make_pair
ll fun45(double x){if(x>=0) return x+0.5;return x-0.5;}
ll mod_mul(ll a,ll b,ll c){__int128 tp=1;return tp*a*b%c;}
ll fast_exp(ll a,ll b,ll c){
    ll res=1;a=a%c;assert(b>=0);
    while(b>0)
    {
        if(b&1) res=mod_mul(a,res,c);
        b=b>>1;a=mod_mul(a,a,c);
    }
    return res;
}
ll ran(ll n){//求解x^2 \equiv -1 (mod n)     //要保证n%4=1
    assert(n%4==1);
    srand(time(0));
    for(;;){
        ll a=rand()%(n-1)+1;//1~ n-1
        ll b=fast_exp(a, (n-1)/4 ,n);
        if(mod_mul(b,b,n)==n-1) return b<=(n-1)/2 ? b:n-b;
    }
}
pll solveprime(ll p)
{
    if(p==2) return mp(1,1);
    if(p%4!=1) return mp(-1,-1);
    ll A,B,u,v,M;
    A=ran(p); B=1;
    __int128 tmp=1;
    M=(tmp*A*A+tmp*B*B)/p;
    assert(M<p);
    while(M>1)
    {
        u=(A%M+M)%M;v=(B%M+M)%M;
        if(2*u>M) u-=M;//注意可能是负数
        if(2*v>M) v-=M;
        assert(u<=M/2 && u>=-M/2);
        assert(v<=M/2 && v>=-M/2);
        ll ta=A;
        A=(tmp*u*A+tmp*v*B)/M;
        B=(tmp*v*ta-tmp*u*B)/M;
        M=(tmp*u*u+tmp*v*v)/M;
    }
    return make_pair(min(abs(A),abs(B)),max(abs(A),abs(B)));
}
const int maxn = 100;
ll a[maxn];//质因子
int b[maxn];//质因子的指数
int tot;//1~tot
void factor(ll n)
{
    assert(n>=1);
    int now=n;
    tot=0;
    for(int i=2;i*i<=now;++i) if(now%i==0){
        a[++tot]=i;
        b[tot]=0;
        while(now%i==0){
            ++b[tot];
            now/=i;
        }
    }
    if(now>1){a[++tot]=now;b[tot]=1;}
}
vector<pll> ans;
vector<pll> bns;
vector<int> cns;//每个模4余1的素数的指数
vector<complex<double> > pre;//维护每个模4余1的素数的a-bi前缀乘积
vector<complex<double> > p3;//size = 4   %4=3 和 2 的贡献
void dfs(int last, complex<double> now)
{
    if(last==cns.size()){
        //一种方案 可以扩展为4种  即分别乘以p3  -p3   p3i  -p3i
        //cout<<now.real()<<" * "<<now.imag()<<endl;
        for(int i=0;i<4;++i){
            complex<double> tp = p3[i]*now;
            ans.push_back(mp(fun45(tp.real()), fun45(tp.imag())));
        }
        return ;
    }
    complex<double> z{1,0};
    complex<double> z1{1.0*bns[last].first, 1.0*bns[last].second};
    complex<double> z2 = pre[last];
    complex<double> z3{1.0*bns[last].first, -1.0*bns[last].second};
    for(int i=0;i<=cns[last];++i){
        dfs(last+1, now*z*z2);
        z = z*z1;
        z2 = z2/z3;
    }
}
void solve(ll r)
{
    ans.clear();bns.clear();cns.clear();
    pre.clear();p3.clear();
    //对r质因子分解
    factor(r);
    for(int i=1;i<=tot;++i) b[i]*=2;//r^2质因子分解
    ll tp=1;    //对那些模4余3的质数 平分贡献
    for(int i=1;i<=tot;++i) if((a[i]&3) == 3) tp=tp*fast_exp(a[i], b[i]>>1 , 1e18);
    int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
    complex<double> z;
    for(int i=0;i<4;++i){
        z.imag(tp*dir[i][0]);
        z.real(tp*dir[i][1]);
        if(a[1]==2 && tot>=1){//2的贡献加进去 tot>=1是排除n=1的情况
            complex<double> z1{1.0,1.0};
            z = z*pow(z1,b[1]);
        }
        p3.push_back(z);
    }
    for(int i=1;i<=tot;++i){//对那些模4余1的质数求出它们的解 并且有 指数+1 种情况
        if((a[i]&3) == 1){
            pll tp = solveprime(a[i]);
            bns.push_back(tp);
            z.real(tp.first);
            z.imag(-tp.second);
            pre.push_back(pow(z,b[i]));
            cns.push_back(b[i]);
        }
    }
    z.imag(0);z.real(1);
    dfs(0, z);
    //check ans
    ll res =1;
    for(int i=1;i<=tot;++i)
    {
        if((a[i]&3) == 1) res*=(b[i]+1);
        else if((a[i]&3) == 3 && (b[i]&1)==1){
            res = 0;
            break;
        }
    }
    res*=4;
    assert(res == ans.size());//由于这里求得是r^2的情况 所以一定存在
	//当然任意的N都可以求
}
int main()
{
    ll r;
    cin>>r;
    solve(r);
    if(ans.size()==0){
        cout<<"no solution"<<endl;
        return 0;
    }
    cout<<ans.size()<<endl;
    for(auto k:ans){
        assert(k.first*k.first + k.second*k.second == r*r);
        cout<<k.first<<" "<<k.second<<endl;
    }
    return 0;
}
