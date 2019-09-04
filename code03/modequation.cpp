#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
//拓展欧几里得模板
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
//ax同余c(mod m) 输出[0,m) 中的解
vector<ll> mod_equation(ll a,ll c,ll m){
    ll u,v;
    ll d=e_gcd(a,m,u,v);
    vector<ll>ans;
    ans.clear();
    if(c%d==0){
        u=(u*(c/d));
        u=(u%(m/d) + (m/d))%(m/d);//最小正整数解
        ans.push_back(u);
        for(ll k=1;k<d;++k)//mod n意义下有d(gcd)个解
            ans.push_back((ans[0]+k*(m/d))%m);
    }
    return ans;
}
vector<long long>ans;
int main()
{
    ll a,c,mod;
    cin>>a>>c>>mod;
    ans=mod_equation(a,c,mod);
    if(!ans.size()) cout<<"无解"<<endl;
    else{
        for(int i=0;i<ans.size();++i){
            cout<<ans[i]<<' ';
        }
    }
    return 0;
}

