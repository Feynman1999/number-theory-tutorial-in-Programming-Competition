//欧拉筛法 O(n)
const int maxn=1e7+10;
bool valid[maxn];
int phi[maxn];
int ans[maxn];
void getprime(int n,int &tot,int ans[])
{
    tot=0;
    phi[1]=1;
    memset(valid,true,sizeof(valid));
    for(int i=2;i<=n;++i){
        if(valid[i]){
            tot++;
            ans[tot]=i;
            phi[i]=i-1;//i为素数
        }
        //下面的主角是小于等于i的每个质数
        for(int j=1;(j<=tot) && (i*ans[j]<=n);++j){
            valid[i*ans[j]]=false;
            if(i%ans[j]==0){//ans[j]是i的素因子
                phi[i*ans[j]]=phi[i]*ans[j];
                break;//如果整除就break;
            }
            else phi[i*ans[j]]=phi[i]*(ans[j]-1);
        }
    }
}
int main()
{
    int Count;//素数个数
    getprime(1e7,Count,ans);
    cout<<Count<<endl;
    return 0;
}