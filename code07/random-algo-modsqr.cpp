//求解x^2 \equiv -1 (mod p)
//O(log p)
ll ran(ll n){
    assert(n%4==1);
    srand(time(0));
    for(;;){
        ll a=rand()*rand()%(n-1)+1;
        ll b=fast_exp(a,(n-1)/4,n);
        if(b*b%n==n-1) return b<=(n-1)/2 ? b:n-b;
    }
}