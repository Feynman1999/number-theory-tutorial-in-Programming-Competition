//素数筛法 O(n)
const int maxn=1e6+10;
bool valid[maxn];
int ans[maxn];
void getprime(int n,int &tot,int ans[])
{
    tot=0;
    memset(valid,true,sizeof(valid));
    for(int i=2;i<=n;++i){
        if(valid[i]){
            tot++;
            ans[tot]=i;
        }
        //下面的主角是小于等于i的每个质数
        for(int j=1;(j<=tot) && (i*ans[j]<=n);++j){
            valid[i*ans[j]]=false;
            if(i%ans[j]==0) break;//如果整除就break;
        }
    }
}