typedef long long ll;
const int maxn=101;//方程个数
//拓展欧几里得模板
ll e_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    ll ans=e_gcd(b,a%b,x,y);
    ll temp=x;
    x=y;
    y=temp-a/b*y;
    return ans;
}
//x同余a  mod m
//a为方程右值 m为方程的模 n为方程数
//下标从0开始
ll CRT(ll a[],ll m[],int n){
    ll M=1;
    for(int i=0;i<n;++i) M*=m[i];
    ll ret=0;
    for(int i=0;i<n;++i){
        ll x,y;
        ll tm=M/m[i];
        ll tmp=e_gcd(tm,m[i],x,y);//tm 和 m[i]互质  只有一个解
        //cout<<x<<endl;
        ret=(ret+tm*x*a[i])%M;//这里x可能为负值  但不影响结果
    }
    return (ret+M)%M;
}
ll a[maxn];
ll m[maxn];
int n;
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=0;i<n;++i)
        cin>>a[i]>>m[i];
    cout<<"一个解为:"<<CRT(a,m,n)<<endl;
    return 0;
}