typedef long long ll;
//ll mod_mul(ll a,ll b,ll c){//快速乘
//    ll res=0;
//    a=a%c;
//    while(b)
//    {
//        if(b&1) res=(res+a)%c;
//        b>>=1;
//        a=(a+a)%c;
//    }
//    return res;
//}
ll mod_mul(ll a, ll b, ll c){
    return a*b%c;
}
ll fast_exp(ll a,ll b,ll c){
    ll res=1;
    a=a%c;
    while(b)
    {
        if(b&1) res=mod_mul(res,a,c);
        b>>=1;
        a=mod_mul(a,a,c);
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
        t=mod_mul(t,t,n);//平方  使用快速乘 因为t,n 1e18
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
