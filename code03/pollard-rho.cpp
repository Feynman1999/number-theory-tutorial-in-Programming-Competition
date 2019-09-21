int f(int x,int c,int n)
{
    return (x*x+c)%n;
}
int pollard_rho(int N)
{
    int c=rand()%(N-1)+1;
    int t=f(0,c,N),r=f(f(0,c,N),c,N);//两倍
    while(t!=r)
    {
        int d=gcd(abs(t-r),N);
        if(d>1) return d;
        t=f(t,c,N),r=f(f(r,c,N),c,N);
    }
    return N;//没有找到,重新调整参数c
}