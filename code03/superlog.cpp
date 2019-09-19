ll vis[8][5];
ll phi(ll x)
{
    if(x==1) return 1;
    ll res=x;
    for(int i=2;i*i<=x;++i){
        if(x%i==0){
            res-=res/i;
            do{
                x/=i;
            }while(x%i==0);
        }
    }
    if(x>1) res-=res/x;
    return res;
}
ll fast_exp(ll a,ll b,ll c){
    ll res=1;
    a=a%c;
    assert(b>=0);
    while(b>0)
    {
        if(b&1) res=a*res%c;
        b=b>>1;
        a=a*a%c;
    }
    return res;
}
ll solve(ll a, ll b, ll m)
{
    if(b==1) return a%m;
    if(m==1) return 0;
    ll phim = phi(m);
    //cout<<"phim: "<<phim<<endl;
    if(a<=7 && b<5 && vis[a][b] && vis[a][b]<=phim) return fast_exp(a, solve(a, b-1, phim), m);
    return fast_exp(a, solve(a, b-1, phim) + phim, m);
}
void init()
{
    for(int i=3;i<=7;++i){
        vis[i][2] = pow(i,i);
        vis[i][2] = pow(i,i);
        vis[i][2] = pow(i,i);
    }
    vis[2][2] = 1LL<<2;
    vis[2][3] = 1LL<<(vis[2][2]);
    vis[2][4] = 1LL<<(vis[2][3]);
}
int main()
{
    init();
    int t;
    cin>>t;
    while(t--)
    {
        ll a,b,m;
        cin>>a>>b>>m;
        if(a==1 || b==0){
            cout<<1%m<<endl;
            continue;
        }
        cout<<solve(a,b,m)<<endl;
    }
    return 0;
}
