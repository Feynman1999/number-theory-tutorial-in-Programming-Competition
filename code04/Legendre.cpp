//poj 1808
//p>2
typedef long long ll;
ll a,p;//求解勒让德符号(a/p)
ll Legendre(ll a,ll p)
{
    a=a%p;
    if(a<0) a+=p;
    int num=0;//将a的2次幂提出 保证是奇数
    while(a%2==0){
        a>>=1;
        num++;
    }
    ll ans1,ans2=1;//ans2是2的次幂的答案,默认为1
    if(a==1) ans1=1;
    else if(a==2){
        if(p%8==1||p%8==7) ans1=1;
        else ans1=-1;
    }
    else{
        if(p%4==3 && a%4==3) ans1=-Legendre(p,a);
        else ans1=Legendre(p,a);
    }
    if(num%2 &&(p%8==3||p%8==5)) ans2=-1;
    return ans1*ans2;
}
int main()
{
    int t;
    cin>>t;
    int T=0;
    while(t--)
    {
        T++;
        cin>>a>>p;
        cout<<"Scenario #"<<T<<":"<<endl<<Legendre(a,p)<<endl<<endl;
    }
    return 0;
}
