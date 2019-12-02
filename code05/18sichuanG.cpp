typedef long long ll;
typedef __int128 lll;
const int mod=1e9+7;
inline lll cal(lll l,lll r)
{
    return (l+r)*(r-l+1)/2;
}
inline lll solve(ll up)//solve \sum_{i=1}^{n} up/i *i;
//显然只有i<=up时有贡献
{
//    num++;
//    if(num%10000==0) cout<<clock()<<endl;
    lll res=0;
    for(ll l=1,r;l<=up;l=r+1){
        r=up/(up/l);
        res=(res+up/l*cal(l,r));
    }
    return res;
}
inline void write(__int128 x)
{
    if(x<0)
    {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
//lll help1[maxn];//solve f(n/1) f(n/2) f(n/3) f(n/\sqrt(n))
//lll help2[maxn];//solve 1 2 3  \sqrt{n}
const int maxn=21550000;
ll g[maxn];//n^(2/3)  g(n)=\sum_{i|n} i
lll f[maxn];//sum_{i=1}^{n} [n/i]*i  
int ans[maxn/10];
int help[maxn];//存每个数最小质因子^指数 如12存2^2  18存2^1  32存2^5
bool valid[maxn];
int tot;
void get_prime(int n)
{
    memset(valid,true,sizeof(valid));
    tot=0;
    g[1]=1;help[1]=1;
    for(int i=2;i<=n;++i){
        if(valid[i]){
            ans[++tot]=i;
            g[i]=i+1;
            help[i]=i;
        }
        for(int j=1;j<=tot && ans[j]*i<=n;++j){
            valid[ans[j]*i]=false;
            if(i%ans[j]==0){
                help[i*ans[j]]=help[i]*ans[j];
                g[i*ans[j]]=g[i]*ans[j]+g[i/help[i]];
                break;
            }
            else{
                help[i*ans[j]]=ans[j];
                g[i*ans[j]]=g[i]*g[ans[j]];
            }
        }
    }
}
int main()
{
    get_prime(maxn);
    f[0]=0;
    for(int i=1;i<maxn;++i) f[i]=f[i-1]+g[i];
    //cout<<clock()<<endl;
    //freopen("in.txt","r",stdin);
    int t;
    cin>>t;
    while(t--)
    {
        ll n;
        cin>>n;
        lll ans1=0;
        for(ll l=1,r;l<=n;l=r+1){
            r=n/(n/l);
            ll tp=n/l;
            if(tp<maxn) ans1+=f[tp]*cal(l,r);
            else ans1+=solve(tp)*cal(l,r);
        }
        lll ans2=0;//i=j
        for(ll i=1;i*i<=n;++i){
            ll tp=i*i;
            ans2+=n/tp*tp;
        }
        ans1+=ans2;
        assert(ans1%2==0);
        ans1/=2;
        ans1=((lll)n)*n*(n+1)/2-ans1;
        write(ans1);
        cout<<endl;
    }
    return 0;
}