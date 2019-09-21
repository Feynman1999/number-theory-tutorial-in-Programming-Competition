#include<bits/stdc++.h>
using namespace std;
typedef __int128 lll;
typedef long long ll;
ll f(lll x, ll c, ll n){ return (x*x+c)%n; }
ll gcd(ll a, ll b){
    if(b==0) return a;
    return gcd(b, a%b);
}
ll mod_mul(lll a, ll b, ll c){return a*b%c;}
ll fast_exp(ll a,ll b,ll c){
    ll res=1;a=a%c;
    while(b)
    {
        if(b&1) res=mod_mul(res,a,c);
        b>>=1;  a=mod_mul(a,a,c);
    }
    return res;
}
bool test(ll n,ll a)//false表示为合数
{
    ll d = n-1;
    if(!(n&1)) return false;
    while(!(d&1))  d>>=1;//将d分解为奇数 至少有一个2因子，所以d!=n-1
    ll t=fast_exp(a,d,n);
    while(d!=n-1 && t!=1 && t!=n-1){
        t=mod_mul(t,t,n);//平方  使用快速乘 因为t,n 1e18  或者int128
        d<<=1;
    }
    return ((t==n-1) || (d&1) ==1 );//两个条件都不成立则一定是合数; 第二个条件d为奇数 即t一开始为1 (mod n)
    //若两个有一个成立，且多次，对于合数来说，可能性极小，所以可以认为是素数
}
bool is_prime(ll n){
    if(n<2) return false;
    if(n==2) return true;
    srand(time(0));
    int test_num = 10;
    for(int i=0;i<test_num;++i) {//test test_num times
        ll tpa=1LL*rand()*rand()%(n-2)+2;//取[2,n-1]随机数
        if(!test(n,tpa)) return false;//找到证据说明是合数
    }
    return true;//如果上面所有测试都是true
}
ll pollard_rho(ll N){
    assert(N!=1);
    ll s=0,t=0,c=1LL*rand()*rand()%(N-1)+1;
    int goal, stp;
    lll val = 1;
    int up = (1<<7)-1;
    for(goal = 1;;goal<<=1,s=t,val=1)//维护区间
    {
        for(stp=1;stp<=goal;++stp){
            t = f(t,c,N);
            val = val * abs(t-s) % N;//int 128 或者快读乘
            if(!(stp&up))
            {
                ll d = gcd(val, N);
                if(d>1) return d;
            }
        }
        ll d = gcd(val, N);
        if(d>1) return d;
    }
}
set<ll> factors;//所有质因子
//ll max_factor;//最大质因子
void solve(ll x)
{
    if(x==1) return ;
    //if(x<=max_factor) return ;  发现这样剪枝并不快多少 2333
    if(is_prime(x)){
        //max_factor = max(max_factor, x);
        factors.insert(x);
        return ;
    }
    ll y = pollard_rho(x);
    while(y>=x) y = pollard_rho(x);
    solve(y),solve(x/y);
}
int main(){
    int t;
    cin>>t;
    while(t--)
    {
        //max_factor = 0;
        factors.clear();
        ll n;
        cin>>n;
        if(is_prime(n)){cout<<"Prime"<<endl;}
        else{
            solve(n);
            if(n>1) //cout<<max_factor<<endl;
                cout<<*factors.rbegin()<<endl;
        }
    }
    return 0;
}
