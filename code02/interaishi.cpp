//注意多个vector push速度很慢
//若无需记录 尽量不用vector
const int maxn=1e6+10;
vector<int> ans[maxn];//质因子
vector<int> bns[maxn];//对应指数
//先预处理每个数有哪些质因数
void init1(int n)//处理1000005个数本机跑了1s左右
{
    for(int i=2;i<=n;++i){
        if(ans[i].size()==0){//说明是素数
            for(int j=i;j<=n;j+=i){
                ans[j].push_back(i);
            }
        }
    }
}
void init2(int n)
{
    for(int i=2;i<=n;++i){
        int tp=i;
        for(int j=0;j<ans[i].size();++j){
            bns[i].push_back(0);
            while(tp%ans[i][j]==0)
            {
                bns[i][j]++;
                tp/=ans[i][j];
            }
        }
    }
}
int main()
{
    int n;
    cin>>n;
    init1(n);
    init2(n);
}