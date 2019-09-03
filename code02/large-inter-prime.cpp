//R<= 2^{32}
const int maxn=(1<<16)+10;
bool valid[maxn];
int ans[maxn];
int tot;
void get_prime(int n)
{
    tot=0;
    for(int i=2;i<=n;++i) valid[i]=true;
    for(int i=2;i<=n;++i){
        if(valid[i]){
        	ans[++tot]=i;
        }
        for(int j=1;j<=tot &&  ans[j]*i<=n;++j){
            valid[ans[j]*i]=false;
            if(i%ans[j]==0) break;
        }
    }
}
//区间长度1e6
bool vis[maxn<<4];//用于被筛  起平移标记作用
int main()
{
    //求区间素数 闭区间
    ios::sync_with_stdio(false);
    get_prime(1<<16);
    ll L,R;
    while(cin>>L>>R)
    {
        for(int i=1;i<=(R-L+1);++i){vis[i]=true;}//-L+1编号    即L-> 1, L+1 ->2,...
        if(L==1) vis[1]=false;//1不是素数
        //下面用素数筛
        for(int i=1;i<=tot;i++)//tot 是预处理的所有素数的个数
            for(ll j=max(ans[i],(L-1)/ans[i]+1);j<=R/ans[i];j++)//当前素数的j倍
                vis[ans[i]*j-L+1]=false;//ans[i]*j是合数
//(L-1)/ans[i]+1)找的是从L开始第一个ans[i]的倍数是其多少倍
//考虑这里为什么当L较小时 从ans[i]倍ans[i]开始筛 (当L较大时自然从(L-1)/ans[i]+1倍开始)
//能从ans[i]*ans[i]开始的条件是 ans[i]的ans[i-1]倍、ans[i-2]倍...已经筛过了(如果在L,R区间里)
//那当i=i-1、i-2...时不就是吗    和埃筛一样
        vector<ll> tep;//答案
        for(int i=1;i<=(R-L+1);++i){
            if(vis[i]) tep.push_back(L+i-1);
        }
        cout<<tep.size()<<endl;
    }
    return 0;
}