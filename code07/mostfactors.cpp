//51nod 1060
typedef unsigned long long ll;
int prime[60];
bool is_prime(ll x)
{
    for(int i=2;i*i<=x;++i){
        if(x%i==0) return false;
    }
    return true;
}
int tot;
void init()
{
    tot=0;
    for(int i=2;i<2000&&(tot<20);++i){
        if(is_prime(i)){
            prime[++tot]=i;
        }
    }
}
ll ans,res;
ll up;
void dfs(int last,ll cur,ll num,int pre)//last 是最后一个访问的素数下标  cur是当前数 num是当前数的约数个数   pre是上一次的指数
{
    if(last>=tot) return ;
    if(num>ans){
        res=cur;//当前数
        ans=num;//约数个数
    }
    else if(num==ans){
        res=min(res,cur);
    }
    for(int i=1;i<=61 && i<=pre;++i){//枚举指数
        if(cur<=up/prime[last+1]){
            //cout<<cur<<endl;
            cur*=prime[last+1];
            dfs(last+1,cur,num*(i+1),i);
        }
        else break;
    }
}
int main()
{
    init();
    //cout<<tot<<endl;
    //for(int i=1;i<=tot;++i) cout<<prime[i]<<" ";
    int t;
    cin>>t;
    while(t--)
    {
        ans=0;
        cin>>up;
        dfs(0,1,1,61);
        cout<<res<<" "<<ans<<endl;//该数和因子数目   若因子数目相同则输出最小的数
    }
    return 0;
}
