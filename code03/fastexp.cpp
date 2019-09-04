ll fast_exp(ll a,ll b,ll c){
    ll res=1;
    a=a%c;
    assert(b>=0);
    while(b>0)
    {
        if(b&1) res=(a*res)%c;
        b=b>>1;
        a=(a*a)%c;
    }
    return res;
}