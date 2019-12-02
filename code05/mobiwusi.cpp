short getmob(ll a){
    ll x=a;
    int cnt=0,now=0;
    for(int j=1;1LL*ans[j]*ans[j]<=x && j<=tot;j++){
        now=0;
        if(x%ans[j]==0){
            while(x%ans[j]==0){
                now++;
                if(now>1) return 0;
                x/=ans[j];
            }
            cnt++;
        }
    }
    if(x!=1) cnt++;
    return (cnt&1)?-1:1;
}