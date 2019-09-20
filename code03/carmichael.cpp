typedef long long ll;
const int maxn=1e7+10;
bool valid[maxn];
int ans[maxn/10];
int res[maxn];//每个数的最小质因子
void getprime(int n,int &tot)
{
    tot=0;
    memset(valid,true,sizeof(valid));
    for(int i=2;i<=n;++i){
        if(valid[i]){
            tot++;
            ans[tot]=i;
            res[i]=i;
        }
        for(int j=1;(j<=tot) && (i*ans[j]<=n);++j){
            int tp=i*ans[j];
            valid[tp]=false;
            res[tp]=ans[j];//记录每个数的最小质因子
            if(i%ans[j]==0) break;
        }
    }
}
bool check(int x)
{
    if (x%2==0) return false;
    if (valid[x]) return false;
    //对x进行分解 要求每个素因子的指数均为1且p-1 | x-1
    int tp=x;
    while(tp!=1)//是合数
    {
        int minp=res[tp];
        if((x-1)%(minp-1)) return false;
        tp=tp/minp;
        if(tp%minp==0) return false;//p指数>1
    }
    return true;
}
vector<int> carmichael;
int main()
{
    int tot;
    getprime(1e7,tot);
    for(int i=2;i<=1e7;++i) if(check(i)) carmichael.push_back(i);
    for(auto k:carmichael) cout<<k<<endl;
    cout<<carmichael.size()<<"个"<<endl;
    return 0;
}
