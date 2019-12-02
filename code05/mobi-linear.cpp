const int maxn=1e7+10;
bool valid[maxn];
short mu[maxn];
int ans[maxn/10];
int tot;
void get_prime(int n)
{
    tot=0;
    mu[1]=1;
    memset(valid,true,sizeof(valid));
    for(int i=2;i<=n;++i){
        if(valid[i]){
            ans[++tot]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=tot&&ans[j]*i<=n;j++){
            valid[i*ans[j]]=false;
            if(i%ans[j]==0){
                mu[i*ans[j]]=0;
                break;
            }
            else{
                mu[i*ans[j]]=-mu[i];
            }
        }
    }
}