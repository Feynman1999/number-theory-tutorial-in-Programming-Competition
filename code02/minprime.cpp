const int maxn=1e6+10;
int min_prime[maxn];
int tot;
int prime[maxn];
//每个数最小的质因子
void getprime(int n)
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