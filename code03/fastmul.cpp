ll mod_mul(ll a,ll b,ll c){//a*b %c 乘法改加法 防止超long long
    ll res=0;
    a=a%c;
    assert(b>=0);
    while(b)
    {
        if(b&1) res=(res+a)%c;
        b>>=1;
        a=(a+a)%c;
    }
    return res;
}