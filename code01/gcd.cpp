//欧几里得算法求解gcd
long long gcd(long long a,long long b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}