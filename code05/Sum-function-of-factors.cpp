ll g[maxn];// g(n)=\sum_{i|n} i
int ans[maxn/10];
int help[maxn];//存每个数最小质因子^指数的值 如12存2^2  18存2^1  32存2^5
bool valid[maxn];
int tot;
void get_prime(int n)
{
    memset(valid,true,sizeof(valid));
    tot=0;
    g[1]=1;
    for(int i=2;i<=n;++i){
        if(valid[i]){
            ans[++tot]=i;
            g[i]=i+1;
            help[i]=i;
        }
        for(int j=1;j<=tot && ans[j]*i<=n;++j){
            valid[ans[j]*i]=false;
            if(i%ans[j]==0){
                help[i*ans[j]]=help[i]*ans[j];
                g[i*ans[j]]=g[i]*ans[j]+g[i/help[i]];
                break;
            }
            else{
                help[i*ans[j]]=ans[j];
                g[i*ans[j]]=g[i]*g[ans[j]];
            }
        }
    }
}