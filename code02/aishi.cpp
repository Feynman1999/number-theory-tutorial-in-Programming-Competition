//埃氏筛法 O(nloglogn)
const int maxn=1e6+10;
bool valid[maxn];
int ans[maxn];//存素数
void getprime(int n,int &tot,int ans[])
{
    tot=0;
    for(int i=2;i<=n;++i) valid[i]=true;
    for(int i=2;i<=n;++i){
        if(valid[i]){
            if(n/i<i) break;//防止下面爆int 
            for(int j=i*i;j<=n;j+=i) valid[j]=false;
        }
    }
    for(int i=2;i<=n;++i) if(valid[i]) ans[tot++]=i;
}

int main()
{
    int Count;//素数个数
    getprime(1e6,Count,ans);
    cout<<Count<<endl;
    return 0;
}