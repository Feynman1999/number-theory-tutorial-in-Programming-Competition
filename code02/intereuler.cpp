const int maxn=1e6+10;
vector<int> ans[maxn];
vector<int> bns[maxn];
int min_prime[maxn];
int tot;
int prime[maxn];
void init1(int n)//预处理每个数最小的质因子
{
    tot=0;
    for(int i=2;i<=n;++i){
        if(min_prime[i]==0){
            prime[++tot]=i;
            min_prime[i]=i;
        }
        for(int j=1;j<=tot && prime[j]*i<=n;++j){
            min_prime[prime[j]*i]=prime[j];
            if(i%prime[j]==0) break;
        }
    }
}
void init2(int n)
{
    for(int i=2;i<=n;++i){
        int tp=i;
        while(tp!=1)
        {
            int num=0;
            int tem=min_prime[tp];
            ans[i].push_back(tem);
            while(tp%tem==0)
            {
                num++;
                tp/=tem;
            }
            bns[i].push_back(num);
        }
    }
}