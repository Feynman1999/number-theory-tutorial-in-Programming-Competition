using namespace std;
typedef long long ll;
int debug_num=0;
const int maxn=5e6+10;
bool valid[maxn];
int ans[maxn/10];
ll phi[maxn];
int mu[maxn];
const int maxm=(1LL<<32)/maxn;
ll help1[maxm];
int help2[maxm];
bool vis[maxm];
int tot,up,m;
void get_prime(int n)
{
    memset(valid,true,sizeof(valid));
    tot=0;
    mu[1]=phi[1]=1;
    for(int i=2;i<=n;++i){
        if(valid[i]){
            ans[++tot]=i;
            mu[i]=-1;
            phi[i]=i-1;
        }
        for(int j=1;j<=tot && ans[j]*i<=n;++j){
            int tp=ans[j]*i;
            valid[tp]=false;
            if(i%ans[j]==0){
                mu[tp]=0;
                phi[tp]=phi[i]*ans[j];
                break;
            }
            else{
                mu[tp]=-mu[i];
                phi[tp]=phi[i]*(ans[j]-1);
            }
        }
    }
    for(int i=1;i<=n;++i){
        phi[i]+=phi[i-1]; mu[i]+=mu[i-1];
    }
}
ll get_phi(ll n)
{
    return (n<=up) ? phi[n] : help1[m/n] ;
}
ll get_mu(ll n)
{
    return (n<=up) ? mu[n] : help2[m/n] ;
}
void solve(ll n)
{
    int t;
    if(n<=up || vis[t=m/n]) return ;
    vis[t]=true;
    help1[t]=n*(n+1)/2; help2[t]=1;
    for(ll l=2,r;l<=n;l=r+1){
        r=n/(n/l);
        solve(n/r);
        help1[t]-=(r-l+1)*get_phi(n/r);
        help2[t]-=(r-l+1)*get_mu(n/r);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    up=maxn-10;
    get_prime(up);
    //cout<<clock()<<endl;
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        m=n;
        if(n<=up) cout<<phi[n]<<" "<<mu[n]<<endl;
        else{
            memset(vis,false,sizeof(vis));
            solve(n);
            cout<<help1[1]<<" "<<help2[1]<<endl;
        }
    }
    return 0;
}