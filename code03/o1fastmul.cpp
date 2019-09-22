inline ll mod_mul(ll a,ll b,ll p){
    a%=p,b%=p;
    ll c=a*b-(ll)((long double)a*b/p+0.5)*p;
    return c<0?c+p:c;
}