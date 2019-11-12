typedef long long ll;
const int mod=10007;
ll inv[mod+10];
ll Fac[mod+10];
ll Fac_inv[mod+10];
void init()
{
    inv[1]=1;
    Fac[0]=1;
    Fac_inv[0]=1;
    for(int i=1;i<mod;++i){
        if(i!=1) inv[i]=((mod-mod/i)*(inv[mod%i]))%mod;
        Fac[i]=Fac[i-1]*i%mod;
        Fac_inv[i]=Fac_inv[i-1]*inv[i]%mod;
    }
}