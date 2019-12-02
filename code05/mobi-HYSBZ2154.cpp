//先筛g(n)=n* sum_{d|n}d*\mu(d)
typedef long long ll;
const int mod=20101009;
const int ni4=15075757;
const int maxn=1e7+10;
int ans[maxn];
bool valid[maxn];
ll g[maxn];//g(n)=n* sum_{d|n}d*\mu(d)
ll sum[maxn];
int tot;
void get_prime(int n)
{
    memset(valid,true,sizeof(valid));
    //mu[1]=1;
    g[1]=1;
    tot=0;
    for(int i=2;i<=n;++i){
        if(valid[i]){
            ans[++tot]=i;
            g[i]=1LL*i*(1-i)%mod;
        }
        for(int j=1;j<=tot && ans[j]*i<=n;++j){
            valid[i*ans[j]]=false;
            if(i%ans[j]==0){
                g[i*ans[j]]=g[i]*ans[j]%mod;
                break;
            }
            else{
                g[i*ans[j]]=g[i]*g[ans[j]]%mod;
            }
        }
    }
    for(int i=1;i<=n;++i) sum[i]=sum[i-1]+g[i];//这里不模了 不会爆long long 下面再模
}
ll solve(ll up1,ll up2){
    ll ans=0;
    ll up=min(up1,up2);
    for(ll l=1,r;l<=up;l=r+1){
        r=min(up1/(up1/l),up2/(up2/l));
        ll tp1=up1/l;
        tp1=tp1*(tp1+1)%mod;
        ll tp2=up2/l;
        tp2=tp2*(tp2+1)%mod;
        ans=(ans+tp1*tp2%mod*((sum[r]-sum[l-1])%mod)%mod)%mod;
    }
    if(ans<0) ans=ans+mod;//不要忘记了
    return ans*ni4%mod;
}
int main()
{
    ios::sync_with_stdio(false);
    get_prime(1e7+5);
    ll n,m;
    cin>>n>>m;
    cout<<solve(n,m)<<endl;
    return 0;
}