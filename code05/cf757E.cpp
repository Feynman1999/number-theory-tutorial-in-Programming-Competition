typedef long long ll;
const int mod=1e9+7;
const int maxn=1e6+10;
ll help[maxn][21];// r  k 给定时 不同p结果相同
bool valid[1010];
int ans[500];
int tot;
void init()
{
    help[0][0]=1;
    for(int k=1;k<=20;++k) help[0][k]=2;
    for(int r=1;r<=int(1e6);++r){
            help[r][0]=help[r-1][0];
        for(int k=1;k<=20;++k){
            help[r][k]=(help[r][k-1]+help[r-1][k])%mod;
        }
    }
}
void get_prime(int n)
{
    tot=0;
    memset(valid,true,sizeof(valid));
    for(int i=2;i<=n;++i){
        if(valid[i]){
            ans[++tot]=i;
        }
        for(int j=1;ans[j]*i<=n;++j){
            valid[ans[j]*i]=false;
            if(i%ans[j]==0){
                break;
            }
        }
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    //cout<<clock()<<endl;
    init();
    get_prime(1010);
    //cout<<tot<<endl;
    //cout<<clock()<<endl;
    //cout<<help[1][1]<<" "<<help[1][2]<<endl;
    while(t--)
    {
        int r,n;
        scanf("%d%d",&r,&n);
        ll res=1;
        for(int j=1;ans[j]*ans[j]<=n && j<=tot;++j){
            int i=ans[j];
            if(n%i==0){
                int k=0;
                while(n%i==0){
                    n/=i;
                    k++;
                }
                //cout<<i<<" "<<k<<endl;
                res=(res*help[r][k])%mod;
            }
        }
        if(n>1){
            res=(res*help[r][1])%mod;
            //cout<<n<<endl;
        }
        printf("%lld\n",res);
    }
    return 0;
}