typedef long long ll;
const int maxn=1e6+10;
bool valid[maxn];
int ans[maxn];
ll sum[maxn];
int phi[maxn];
int tot;
void get_prime(int n)
{
    memset(valid,true,sizeof(valid));
    tot=0;
    phi[1]=1;
    for(int i=2;i<=n;++i){
        if(valid[i]){
            tot++;
            ans[tot]=i;
            phi[i]=i-1;
        }
        for(int j=1;j<=tot && ans[j]*i<=n;++j){
            valid[ans[j]*i]=false;
            if(i%ans[j]==0){
                phi[i*ans[j]]=phi[i]*ans[j];
                break;
            }
            else phi[i*ans[j]]=phi[i]*(ans[j]-1);
        }
    }
    for(int i=1;i<=1e6;++i){
        sum[i]=sum[i-1]+phi[i];
    }
}
ll solve(ll up1,ll up2)
{
    ll ans=0;
    ll up=min(up1,up2);
    for(ll l=1,r;l<=up;l=r+1){
        r=min(up1/(up1/l),up2/(up2/l));//这里取最小的右边界
        ans+=(sum[r]-sum[l-1])*(up1/l)*(up2/l);
        //cout<<"l r:"<<l<<" "<<r<<endl;
    }
    return ans;
}
int main()
{
    get_prime(1e6);
    //cout<<phi[6]<<endl;
    //cout<<tot<<endl;
    ll n,m;
    cin>>n>>m;
    //cout<<n<<" "<<m<<endl;
    cout<<solve(n,m)<<endl;
    return 0;
}