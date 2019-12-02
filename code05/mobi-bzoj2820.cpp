//O(1e7+T*\sqrt{n})
typedef long long ll;
const int maxn=1e7+10;
int ans[maxn/10];
int mu[maxn];
ll sum[maxn];
bool valid[maxn];
int g[maxn];//sum_{p|n} mu(n/p)
int tot;
void get_prime(int n)
{
    tot=0;
    mu[1]=1;
    g[1]=0;
    memset(valid,true,sizeof(valid));
    for(int i=2;i<=n;++i){
        if(valid[i]){
            ans[++tot]=i;
            mu[i]=-1;
            g[i]=1;
        }
        for(int j=1;j<=tot && ans[j]*i<=n;++j){
            valid[i*ans[j]]=false;
            if(i%ans[j]==0){
                mu[i*ans[j]]=0;
                g[i*ans[j]]=mu[i];//妙啊 展开细算即可  发现只有最小质因子对应的那个非0
                break;
            }
            else{
                mu[i*ans[j]]=-mu[i];
                g[i*ans[j]]=mu[i]-g[i];//妙啊 展开细算即可
            }
        }
    }
    for(int i=1;i<=n;++i){
        sum[i]=sum[i-1]+g[i];
    }
}
ll solve(int up)
{
    ll ans=0;
    for(int l=1,r;l<=up;l=r+1){
        r=up/(up/l);
        // l r
        ll tp=up/l;
        ans+=tp*tp*(sum[r]-sum[l-1]);
    }
    return ans;
}
int main()
{
    get_prime(1e7);
    ios::sync_with_stdio(false);
    int n;
    while(cin>>n) cout<<solve(n)<<endl;
    return 0;
}