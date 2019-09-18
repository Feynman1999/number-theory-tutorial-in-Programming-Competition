typedef long long ll;
typedef __int128 lll;
lll e_gcd(lll a,lll b,lll &x,lll &y)
{
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    lll ans=e_gcd(b,a%b,x,y);
    lll temp=x;
    x=y;
    y=temp-a/b*y;
    return ans;
}
//x = a (mod m)  index form 0
bool crt_flag;
const int maxn = 1e5+10;
ll a[maxn],m[maxn];
lll lcm;
ll EXCRT(ll a[], ll m[], int n){//n 是方程数量  时间复杂度: nlogm
    lll m1 = m[0], a1 = a[0], m2, a2, k1, k2, x0, gcd, c;
    a1 = a1%m1;
    lcm = m1;//lcm 是最小公倍数
    for(int i=1;i<n;i++){
        m2 = m[i], a2 = a[i];
        a2 = a2%m2;
        c = a2 - a1;
        gcd = e_gcd(m1, m2, k1, k2);// solve m1*k1 + m2*k2 = gcd(m1,m2)
        lcm = m2/gcd*m1;
        if(c%gcd){
            crt_flag = 1;//无解
            return 0;//注意0也不一定无解  要先看crt_flag
        }
        x0 = c/gcd*k1;
        ll mod = m2/gcd;// 应该一定为正数
        x0 = (x0%mod+mod)%mod;//最小非负整数解
        a1 = (a1+m1*x0%lcm)%lcm;
        m1 = lcm;
    }
    return (a1%lcm+lcm)%lcm;
}
int main()
{
    crt_flag = false;
    int n;     cin>>n;
    for(int i=0;i<n;++i) cin>>m[i]>>a[i];
    ll ans = EXCRT(a,m, n);
    if(crt_flag) cout<<"no solution"<<endl;
    else cout<<ans<<endl;
    return 0;
}
