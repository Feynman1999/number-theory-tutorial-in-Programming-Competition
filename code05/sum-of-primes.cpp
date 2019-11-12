#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
inline __int128 ff(__int128 x){return (x&1) ? (x+1)/2*x : x/2*(x+1)  ;}
__int128 scanf128(string s)
{
    __int128 res = 0;
    for(int i=0;i<s.length();++i){
        res*=10;
        res+=s[i]-'0';
    }
    return res;
}
void print128(__int128 x)
{
    vector<int> vec;
    while(x){
        int tp = x%10;
        vec.push_back(tp);
        x/=10;
    }
    for(int i=vec.size()-1;i>=0;--i){
        cout<<vec[i];
    }
    cout<<endl;
}
__int128 pre[1000010 + 1010], hou[1000010];
//+1010很关键 用于后面除法变乘法时方便不用if  1010 = (n)^0.25
double inv[1000010];
int primes[100010];
__int128 S;
__int128 solve(ll n){
    int M=sqrt(n);
    int tot=0;
	while (ll(M+1)*(M+1) <= n) M++;
    for(int i=1;i<=M;++i){
        pre[i]=ff(i)-1;
        hou[i]=ff(n/i)-1;
        inv[i] = 1./i;
    }
    for(int p=2;p<=M;++p){
        if(pre[p]==pre[p-1]) continue;
        primes[++tot] = p;
        const ll q=(ll)p*p, pnt=pre[p-1];
        const int mid=M/p;
        const int End=min((ll)M, n/q);
        for(int i=1;i<=mid;++i) hou[i]-=(hou[i*p]-pnt)*p;
        const ll m=n/p;
        for(int i=mid+1;i<=End;++i){
            int j = m*inv[i] + 1e-6;
            hou[i]-=(pre[j]-pnt)*p;
        }
        for(int i=M/p; i>=p ; --i)
            for(int j=p-1; j>=0;--j){
                pre[i*p+j]-=(pre[i]-pnt)*p;
            }
    }
    return hou[1];
}
double upper_func(__int128 x)
{
    if(x >= 110118925){
        double x2 = x*x;
        double lgx = log((double)x);
        double lgx2 = lgx * lgx;
        double lgx3 = lgx2 * lgx;
        double lgx4 = lgx3 * lgx;
        return x2/(2*lgx) + x2/(4*lgx2) + x2/(4*lgx3) + 5.3*x2/(8*lgx4);
    }
    else return solve(x);
}
double lower_func(__int128 x)
{
    if(x >= 905238547){
        double x2 = x*x;
        double lgx = log((double)x);
        double lgx2 = lgx * lgx;
        double lgx3 = lgx2 * lgx;
        double lgx4 = lgx3 * lgx;
        return x2/(2*lgx) + x2/(4*lgx2) + x2/(4*lgx3) + 1.2*x2/(8*lgx4);
    }
    else return solve(x);
}
const int maxn=(1<<20);//1e6+x 平方之后肯定够用了
bool valid[maxn+10];
ll ans[maxn/5];
bool vis[maxn*25];//用于被筛 2.5*1e7 够用了
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
int main()
{
    ios::sync_with_stdio(false);
    string str;
    cin>>str;
    S = scanf128(str);
    ll l,r,up,low;
    l = 0, r = 1e12 + 1e10;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(lower_func(mid)>=S) r=mid;
        else l=mid;
    }
    up = r;//up比实际值大
    l = 0;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(upper_func(mid)>=S) r=mid;
        else l=mid;
    }
    low = r;
    if(up==low) cout<<low<<endl;
    else{
        get_prime(maxn);
        ll L,R;
        L = low;
        R = up;
        assert(R-L+1 < maxn*25);
        //cout<<L<<" "<<R<<endl;
        for(int i=1;i<=(R-L+1);++i){//-L+1 来编号
            vis[i]=true;
        }
        assert(L!=1);//应该不会出现L为1的情况
        for(int i=1;i<=tot;i++)
            for(ll j=max(ans[i],(L-1)/ans[i]+1);j<=R/ans[i];j++)//当前素数的j倍
                vis[ans[i]*j-L+1]=false;//ans[i]*j是合数

        //先MLLMO Method 求出low点的值
        __int128 now = solve(low);
        if(now == S && vis[1]) cout<<low<<endl;
        else{
            for(int i=2;i<=(R-L+1);++i){
                if(vis[i]){
                    now+=L+i-1;
                    if(now==S){
                        cout<<L+i-1<<endl;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
