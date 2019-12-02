//O sqrt(p) 求解欧拉函数
//若时间卡的比较紧 先筛选下素数
ll phi(ll x)
{
    if(x==1) return 1;
    ll res=x;
    for(int i=2;i*i<=x;++i){
        if(x%i==0){
            res-=res/i;
            do{
                x/=i;
            }while(x%i==0);
        }
    }
    if(x>1) res-=res/x;
    return res;
}