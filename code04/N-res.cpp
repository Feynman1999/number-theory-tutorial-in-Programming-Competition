//51Nod - 1038
//N次剩余 O(\sqrt{p}*大常数)
typedef long long ll;
struct pli{
    ll first;
    int second;
    pli(){}
    pli (ll x_,int y_){
        first=x_;
        second=y_;
    }
    bool operator < (const pli &b) const {
        if(first==b.first) return second>b.second;//因为second更大的解更小，所以重载>
        return first<b.first;
    }
};
//ll mod_mul(ll a,ll b,ll c){//a*b %c 乘法改加法 防止超long long
//    ll res=0;
//    a=a%c;
//    assert(b>=0);
//    while(b)
//    {
//        if(b&1) res=(res+a)%c;
//        b>>=1;
//        a=(a+a)%c;
//    }
//    return res;
//}
ll fast_exp(ll a,ll b,ll c){
    ll res=1;
    a=a%c;
    assert(b>=0);
    while(b>0)
    {
        if(b&1) res=(a*res)%c;
        b=b>>1;
        a=(a*a)%c;
    }
    return res;
}
vector<ll> a;//p-1的所有质因子
bool g_test(ll g,ll p){
    for(ll i=0;i<a.size();++i)
        if(fast_exp(g,(p-1)/a[i],p)==1)//非素数时，要将p-1换为\varphi(p)
            return 0;
    return 1;
}
ll primitive_root(ll p)
{
    a.clear();
    ll tmp=p-1;//非素数时，要将p-1换为\varphi(p)
    for(ll i=2;i<=tmp/i;++i)
        if(tmp%i==0){
            a.push_back(i);
            while(tmp%i==0) tmp/=i;
        }
    if(tmp!=1) a.push_back(tmp);
    long long g=1;
    while(1)
    {
        if(g_test(g,p)) return g;
        ++g;
    }
}
ll gcd(ll a,ll b){
    if(b==0) return a;
    return gcd(b,a%b);
}
//a^x\equiv b (mod m)
ll bsgs(ll a,ll b,ll m)
{
    a%=m,b%=m;
    if(b==1) return 0;
    int cnt=0;
    ll t=1;
    for(ll g=gcd(a,m);g!=1;g=gcd(a,m)){
        if(b % g) return -1;
        m/=g , b/=g , t = t * a / g % m;//记录下要算逆元的值
        ++cnt;
        if(b==t) return cnt;
    }
    //cout<<a<<" "<<b<<" "<<m<<endl;
    //bsgs
    int M=int(sqrt(m)+1);//这里的m不等于参数中的值了
    ll base=b;
//    std::unordered_map<ll,int> hash;
//    for(int i=0;i!=M;++i){
//        hash[base]=i;//存的是大的编号
//        base=base*a%m;
//    }
//    base=fast_exp(a,M,m);//必要时要用快速乘
//    ll now=t;
//    for(int i=1;i<=M+1;++i){
//        now=now*base%m;//这里乘在左边了 相当于右边乘逆元
//        if(hash.count(now)) return i*M-hash[now]+cnt;
//    }
    pli hash[int(1e5)];
    for(int i=0;i!=M;++i){
        hash[i]=pli(base,i);
        base=base*a%m;
    }
    sort(hash,hash+M);//默认以first
    base=fast_exp(a,M,m);
    ll now=t;
    for(int i=1;i<=M+1;++i){
        now=now*base%m;
        //找大于等于now的值
        //注意下面M+10  这样可以保证解最小，若设为-1,则找不到解了
        int id=lower_bound(hash,hash+M,pli(now,M+10))-hash;//默认是first
        assert(id>=0 &&id<=M);
        if(id!=M && hash[id].first==now) return i*M-hash[id].second+cnt;//减去的编号second越大越好
    }
    return -1;
}
ll e_gcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    ll ans=e_gcd(b,a%b,x,y);
    ll temp=x;
    x=y;
    y=temp-a/b*y;
    return ans;
}
vector<int> residue(int p,int N,int a){
    int g=primitive_root(p);
    ll t=bsgs(g,a,p);
    vector<int> ans;
    if(a==0){
        ans.push_back(0);
        return ans;
    }
    if(t==-1) return ans;
    //解不定方程
    ll A=N,B=p-1,C=t,x,y;
    ll d=e_gcd(A,B,x,y);
    if(C % d !=0) return ans;
    x=x*(C/d)%B;
    ll delta=B/d;
    for(int i=0;i<d;++i){//一共d组解
        x=((x+delta)%B+B)%B;
        ans.push_back((int)fast_exp(g,x,p));
    }
    sort(ans.begin(),ans.end());
//unique的作用是“去掉”容器中相邻元素的重复元素（不一定要求数组有序），
//它会把重复的元素添加到容器末尾（所以数组大小并没有改变），而返回值是去重之后的尾地址
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    int t,p,N,A;
    //x^N=A (mod p)
    cin>>t;
    while(t--)
    {
        cin>>p>>N>>A;
        vector<int> ans=residue(p,N,A);
        if(ans.size()){
            for(int i=0;i<ans.size()-1;++i){
                cout<<ans[i]<<" ";
            }
            cout<<*ans.rbegin()<<endl;
        }
        else cout<<"No Solution"<<endl;
    }
    return 0;
}