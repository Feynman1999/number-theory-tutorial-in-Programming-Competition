const int maxn=1e5+10;
int ans[maxn];//数的最大质因子 素数就是自己
void get_prime(int n)
{
    for(int i=2;i<=n;++i) ans[i]=i;
    for(int i=2;i<=n;++i){
        if(ans[i]==i){//素数
            for(int j=i*2;j<=n;j+=i)//最后筛去的即为最大质因子
                ans[j]=i;
        }
    }
}