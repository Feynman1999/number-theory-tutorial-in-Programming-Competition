typedef long long ll;
#define random(a,b) (rand()%(b-a+1)+a) // [a,b]
ll mod;
ll w2;//a^2-n = omega^2     random find a s.t. a^2-n  is non-quad-res
ll fast_exp(ll a, ll b, ll c){
    ll res=1;
    a=a%c;
    while(b)
    {
        if(b&1) res=(res*a)%c;
        b>>=1;
        a=(a*a)%c;
    }
    return res;
}
//p>2
//x^2 = n  (mod p)
bool isqr(ll n, ll p)
{
    if(fast_exp(n, (p-1)/2, p)!=1) return 0;//欧拉准则
    return true;
}
struct FP2{//Field p^2
    ll x,y;
    FP2 operator * (FP2 tmp)
    {
        FP2 ans;
        ans.x = (this->x * tmp.x %mod + this->y * tmp.y %mod * w2 %mod) %mod;
        ans.y = (this->x * tmp.y %mod + this->y * tmp.x %mod) %mod;
        return ans;
    }
    FP2 operator ^ (ll b)
    {
        FP2 ans;
        ans.x = 1;
        ans.y = 0;//幺元
        FP2 a = *this;
        while(b)
        {
            if(b&1) ans = ans*a;
            b>>=1;
            a = a*a;
        }
        return ans;
    }
};
//return the smaller solution -1 means no solution
//solve x^2 = n  (mod p)
ll solve(ll n, ll p)
{
    mod = p;
    n=(n%p+p)%p;
    if(n==0) return 0;//这里考虑了解x=0的情况   注意[1,p-1]中解成对出现  而0只有一个解
    if(p==2) return n%p;
    if(!isqr(n,p)) return -1;//no solution
    ll x;
    if(p%4==3) x=fast_exp(n, (p+1)/4, p);//直接求解
    else{//Cipolla's algorithm
        //random find a s.t. a^2-n  is non-quad-res
        ll a;
        srand(time(0));
        while(1)
        {
            a = random(0,p-1);
            w2 = ((a*a-n)%p+p)%p;
            if(!isqr(w2,p)) break;//have found
        }
        FP2 ans;
        ans.x = a;
        ans.y = 1;
        ans = ans ^ ((p+1)/2);
        assert(ans.y==0);//FP^2 Field -> FP Field
        x = ans.x;
    }
    if(2*x>=p) x = p-x;//取较小解
    return x;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        ll n,p;
        cin>>n>>p;
        ll ans = solve(n,p);
        if(ans==-1) cout<<"Hola!"<<endl;//no solution
        else{
            assert(ans>=0 && ans<p && ans<p-ans);
            if(ans%p == (p-ans)%p) cout<<ans%p<<endl; //解为0时只有1个解
            else cout<<ans<<" "<<p-ans<<endl;
        }
    }
    return 0;
}
