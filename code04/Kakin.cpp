//快速乘
inline ll mod_mul(ll a,ll b,ll c){return (a*b-(ll)((long double)a*b/c)*c+c)%c;}
//拓展欧几里得
ll e_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0){x=1;y=0;return a;}
    ll ans=e_gcd(b,a%b,x,y);
    ll temp=x; x=y; y=temp-a/b*y;
    return ans;
}
//求逆元 已知gcd(a,mod)=1
ll inv(ll a,ll mod)
{
    ll ans,tmp;
    e_gcd(a,mod,ans,tmp);
    return (ans+mod)%mod;
}
ll fast_exp(ll a,ll b,ll c){
    ll res=1;
    a=a%c;
    assert(b>=0);
    while(b>0)
    {
        if(b&1) res=mod_mul(res,a,c);
        b=b>>1;
        a=mod_mul(a, a, c);
    }
    return res;
}
int main(void)
{
    //freopen("in.txt","r",stdin);
    int t;
    cin>>t;
    ll n,c;
    ll zhi = (1<<30)+3;
    for(int tcase=1;tcase<=t;++tcase){
        cout<<"Case "<<tcase<<": ";
        cin>>n>>c;
        ll p,q;
        ll M = sqrt(n)+1e1;
        while(1)
        {
            if(n%M==0){
                p = M;
                q = n / M;
                break;
            }
            M--;
        }
        ll ni = inv(zhi, (p-1)*(q-1));
        ll ans = fast_exp(c, ni, n);
        cout<<ans<<endl;
    }
	return 0;
}
