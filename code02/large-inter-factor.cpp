const int maxn=(1<<16)+10;
bool valid[maxn];
int prime[maxn];
int tot;
void get_prime(int n)
{
    tot=0;
    for(int i=2;i<=n;++i) valid[i]=true;
    for(int i=2;i<=n;++i){
        if(valid[i]==true){
            prime[++tot]=i;
        }
        for(int j=1;j<=tot && prime[j]*i<=n;++j){
            valid[prime[j]*i]=false;
            if(i%prime[j]==0) break;
        }
    }
}
//<<2是为了1e6区间长度
vector<int> ans[maxn<<2];//区间每个数的质因子   0 对应 L
vector<int> bns[maxn<<2];//质因子对应的指数
int main()
{
    get_prime(1<<16);
    int L,R;
    cin>>L>>R;
    for(int i=1;i<=tot;++i){
        for(int j=(L-1)/prime[i]+1;j<=R/prime[i];++j){
            ans[j*prime[i]-L].push_back(prime[i]);
        }
    }
    //L存在0这里
    for(int i=0;i<R-L+1;++i){
        if(ans[i].size()==0){
            ans[i].push_back(i),bns[i].push_back(1);
            continue;
        }
        int x=i+L;//加上偏移 还原
        for(int j=0;j<ans[i].size();++j){
            int tp=ans[i][j];
            int num=0;
            while(x%tp==0){
                x/=tp;
                num++;
            }
            bns[i].push_back(num);
        }
        if(x!=1) ans[i].push_back(x),bns[i].push_back(1);
    }
    return 0;
}