#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
typedef long long ll;
int pre[100010], hou[100010];
double inv[100010];
int primes[100010];
ll ni[40], Fac[40], Fac_inv[40];
const int mod = 1e9+7;
inline int add(const int x, const int v) {return x + v >= mod ? x + v - mod : x + v;}
inline int dec(const int x, const int v) {return x - v < 0 ? x - v + mod : x - v;}
int n,nowk,M,tot;
int dfs(int res, int last, int f){
    int g = dec(res > M ? hou[n/res] : pre[res], pre[primes[last]-1]);
    int ans = 1LL*g*f%mod*nowk%mod;
    for(int i=last;i<tot;++i){
        int p = primes[i];
        if((ll)p*p > res) break;
        int num=1;
        for(ll q=p, nres=res, nf=1LL*f*nowk%mod; q*p<=res; q*=p){
            ans = add(ans, dfs(nres/=p,i+1,nf));
            nf = nf*(num + nowk)%mod*ni[num+1]%mod;
            num++;
            ans = add(ans, nf);
        }
    }
    return ans;
}
int solve(int n){
    M=sqrt(n);
    tot=0;
	while (ll(M+1)*(M+1) <= n) M++;
    for(int i=1;i<=M;++i){
        pre[i]=i-1;
        hou[i]=(n/i-1);//n 1e9 不用模
        inv[i] = 1./i;
    }
    for(int p=2;p<=M;++p){
        if(pre[p]==pre[p-1]) continue;
        primes[tot++] = p;
        const int q=p*p, pnt=pre[p-1];
        const int mid=M/p;
        const int End=min(M, n/q);
        for(int i=1;i<=mid;++i) hou[i]-=(hou[i*p]-pnt);
        const int m=n/p;
        for(int i=mid+1;i<=End;++i){
            int j = m*inv[i] + 1e-6;
            hou[i]-=(pre[j]-pnt);
        }
        for(int i=M/p; i>=p ; --i)
            for(int j=p-1; j>=0;--j){
                pre[i*p+j]-=(pre[i]-pnt);
            }
    }
	primes[tot++] = M+1;
	assert(n>1);
    return dfs(n,0,1);
}
void init()
{
    ni[1]=1;
    Fac[0]=1;
    Fac_inv[0]=1;
    for(int i=1;i<40;++i){
        if(i!=1) ni[i]=((mod-mod/i)*(ni[mod%i]))%mod;
        Fac[i]=Fac[i-1]*i%mod;
        Fac_inv[i]=Fac_inv[i-1]*ni[i]%mod;
    }
}
int main()
{
    init();
    int k;
    while(scanf("%d%d",&n,&k)!=EOF){
        if(n==1 || k>=n){cout<<0<<endl; continue;}
        int ans = 0;
        for(int i=0;i<k;++i){
            nowk = k-i;
            ll tp = Fac[k]*Fac_inv[i]%mod*Fac_inv[k-i]%mod;
            if(!(i&1)) ans = add(ans, tp*solve(n)%mod);
            else ans = dec(ans, tp*solve(n)%mod);
        }
        cout<<ans<<endl;
    }
    return 0;
}
