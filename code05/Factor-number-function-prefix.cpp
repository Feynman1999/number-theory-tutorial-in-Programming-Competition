void init_f(int n)
{
    //f(n)=sum_{i=1}^{n} \ceil(n/i)
    // sigma_0后移一位并加1 对应f
    //处理完之后全部加1并后移一位  再做一次前缀和就是f
    f[0]=0;
    for(int i=1;i<=n;++i){
        f[i]=(sigma_0[i-1]+1);
    }
    for(int i=1;i<=n;++i){
        f[i]=(f[i]+f[i-1])%mod;
    }
}