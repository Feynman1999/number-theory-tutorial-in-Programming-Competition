typedef long long ll;
ll gcd(ll a, ll b){if(b==0) return a; return gcd(b,a%b);}
ll fast_exp(ll a,ll b,ll c){
    ll res=1;a=a%c;
    while(b){
        if(b&1) res=(res*a)%c;
        b>>=1; a=(a*a)%c;
    }
    return res;
}
ll phi(ll x)
{
    if(x==1) return 1;
    ll res=x;
    for(int i=2;i*i<=x;++i){
        if(x%i==0){
            res-=res/i;
            do{
                x/=i;
            }while(x%i==0);
        }
    }
    if(x>1) res-=res/x;
    return res;
}
//返回 循环节前面有多少位  以及 最小循环节长度
//ans的size为1表示有限小数
//ans的size为2表示无限循环小数
vector<ll> solve(ll p, ll q)
{
    p = p%q;
    ll d = gcd(p,q);
    p/=d;
    q/=d;
    vector<ll> ans;
    ll m=q;    //看q里有多少个2和5
    int num2=0, num5=0;
    while(!(m&1)){
        m>>=1; num2++;
    }
    while(m%5==0){
        m/=5; num5++;
    }
    ll i = max(num2,num5),j=-1;
    //10^{j-i} \equiv 1 (mod m)
    //so solve 10^x = 1 (mod m)  and  j=x+i
    ll varphi = phi(m);
    vector<ll> fac1;//从小到大
    vector<ll> fac2;//从大到小
    for(ll x=1;x*x<=varphi;++x){
        if(varphi%x==0){
            fac1.push_back(x);
            fac2.push_back(varphi/x);
        }
    }
    reverse(fac2.begin(), fac2.end());
    fac1.insert(fac1.end(),fac2.begin(),fac2.end());
    for(int k=0;k<fac1.size();++k){
        if(fast_exp(10,fac1[k],m)==1){
            j = i + fac1[k];
            break;
        }
    }
    ans.push_back(i);//循环节前面有多少位
    if(j==-1) return ans;//ans的size为1表示有限小数
    ans.push_back(j-i);//最小循环节长度
    return ans;//ans的size为2表示无限循环小数
}
int main()
{
    stringstream ss;
    streambuf* buffer = cout.rdbuf(); //oldbuffer,STDOUT的缓冲区
    cout.rdbuf(ss.rdbuf());

    ll p,q;
    cin>>p>>q;
    ll zheng = p/q;
    p = p%q;
    vector<ll> ans = solve(p,q);
    cout<<zheng;//整数部分

    if(p==0){
        cout<<".0";//视题目情况 这一题是整除时输出".0"
        assert(ans[0]==0);//整除时一定是0
    }
    else cout<<".";

    int num1=ans[0];//循环节前面有多少位
    while(num1){
        cout<<p*10/q;
        p = p*10%q;
        num1--;
    }
    if(ans.size()>1){
        cout<<"(";
        int num2 = ans[1];
        while(num2){
            cout<<p*10/q;
            p = p*10%q;
            num2--;
        }
        cout<<")";
    }
    string out(ss.str());
    cout.rdbuf(buffer); //重新载入STDOUT的缓冲区

    for(int i=0;i<out.length();++i){
        if(i%76==0 && i>0){
            cout<<endl;
        }
        cout<<out[i];
    }
    cout<<endl;
    return 0;
}
/*
1/3 = 0.(3)
22/5 = 4.4
1/7 = 0.(142857)
2/2 = 1.0
3/8 = 0.375
45/56 = 0.803(571428)
*/
