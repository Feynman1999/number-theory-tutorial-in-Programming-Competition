const int maxn=1e5+10;
bool valid[maxn];
int ans[maxn];//素数
int tot;
ll all;
void get_prime(int n)
{
    tot=0;
    memset(valid,true,sizeof(valid));
    valid[1]=false;
    for(int i=2;i<=n;++i){
        if(valid[i]) ans[++tot]=i;
        for(int j=1;(j<=tot) && (i*ans[j]<=n) ;++j){
            valid[i*ans[j]]=false;
            if(i%ans[j]==0) break;
        }
    }
}
bool is_prime(ll x){
    for(int i=2;i<=floor(sqrt(x));++i)
        if(x%i==0) return false;
    return true;
}
ll up;
void dfs(int last,ll num,ll phi){//对num进行分解  last是最后一次选到第几个
    if(num==1){
        all=min(all,phi);
        return ;
    }
    if(num>up && is_prime(num+1)){//如果当前因子num比\sqrt{n}大
        all=min(all,phi*(num+1));
        return ;
    }
    for(int i=last+1;i<=tot && ans[i]<=num;i++)
        if(num%(ans[i]-1)==0){//如果num能整除当前素数-1
            ll num_ = num/(ans[i]-1);//除去
            ll phi_ = phi*ans[i];//搞上
            dfs(i,num_,phi_);
            while(num_%ans[i]==0){//同时phi可以有更多的该素数
                num_/=ans[i];
                phi_*=ans[i];
                dfs(i,num_,phi_);
            }
        }
}
int main()
{
    get_prime(1e5);//1e5很稳
    ll n;
    cin>>n;
    up=floor(sqrt(n));//注意至少要加1
    all=1LL<<31;
    dfs(0,n,1);
    if(all<(1LL<<31)) cout<<all<<endl;//本题的特殊要求
    else cout<<-1<<endl;
    return 0;
}
