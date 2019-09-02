//O(sqrt n)
const int maxn=100;
int a[maxn];//质因子
int b[maxn];//质因子的指数
int tot;//1~tot
void factor(int n)
{
    int now=n;
    tot=0;
    for(int i=2;i*i<=now;++i) if(now%i==0){//时间稍紧后使用素数ans[i]代替i
        a[++tot]=i;
        b[tot]=0;
        while(now%i==0){
            ++b[tot];
            now/=i;
        }
    }
    if(now>1){//一个合数n必定有小于等于sqrt{n} 的质因子   将其全部除尽后 若不为1 则为大于sqrt{n}的质因子 且仅有一个
        a[++tot]=now;
        b[tot]=1;
    }
}
int main()
{
    int n;
    cin>>n;
    factor(n);//n>1
    for(int i=1;i<=tot;++i){
        if(i==tot) cout<<a[i]<<'^'<<b[i]<<endl;
        else cout<<a[i]<<'^'<<b[i]<<" * ";
    }
}