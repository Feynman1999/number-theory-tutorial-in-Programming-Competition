const int mod = 1e9+7;
ll ans[3010];
ll help[3010];
ll helpni[3010];
stack<int> sta;
int up = 3000;
int n=3000;
ll fast_exp(ll a,ll b,ll c){
    ll res=1;a=a%c;
    while(b)
    {
        if(b&1) res=(res*a)%c;
        b>>=1;a=(a*a)%c;
    }
    return res;
}
void solve(int len)
{
    int len2 = sta.size();
    assert(len2>1);
    int len1 = len-len2;
    ll res = help[len]*helpni[len1]%mod;
    stack<int> sta_tp = sta;
    vector<int> vec;
    while(!sta_tp.empty()){
        vec.push_back(sta_tp.top());
        sta_tp.pop();
    }
    vec.push_back(-1);
    int num=1;
    for(int i=1;i<vec.size();++i){
        if(vec[i]==vec[i-1]) num++;
        else{
            res = res*helpni[num]%mod;
            num=1;
        }
    }
    ans[len] = (ans[len] + res)%mod;
}

void dfs(int len, ll sum, ll jie)
{
    ll tp = jie-sum+len;//tp为序列长度
    if(tp<=n){
        if(tp>=3){
            //1的数量： jie-sum   >1的数量： len
            //ans[tp]++;
            //取当前的sta 然后计算
            solve(tp);
        }
        else ;
    }
    else return;
    int low;
    if(sta.empty()) low = 2;
    else low = sta.top();
    for(int i=low;i<=up;++i){
        sta.push(i);
        dfs(len+1, sum+i,jie*i);
        sta.pop();
    }
}
void init()
{
    help[1] = 1;helpni[1] = 1;
    for(int i=2;i<=3000;++i){
        help[i] = help[i-1]*i%mod;
        helpni[i] = fast_exp(help[i], mod-2,mod);
    }
}
int main()
{
    init();
    dfs(0,0,1);
    int t;
    cin>>t;
    while(t--)
    {
        int m;
        cin>>m;
        if(m==2) cout<<1<<endl;
        else cout<<ans[m]<<endl;
    }
}
