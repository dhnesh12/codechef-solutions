#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long LL;
typedef long double LD;
/*inline LL quick_mult(LL x,LL r,LL mod)
{
	LL ret=0;
	for(;r;r>>=1)
	{
		if(r&1)
		{
			ret+=x;
			if(ret>=mod)ret-=mod;
		}
		x<<=1;
		if(x>=mod)x-=mod;
	}
	return ret;
}*/
inline LL quick_mult(LL x,LL r,LL mod)
{
	LL d=(LD)x*r/mod+0.5;
	LL ret=x*r-d*mod;
	if(ret<0)ret+=mod;
	return ret;
}
inline LL quick_pow(LL x,LL r,LL mod)
{
	LL ret=1;
	for(;r;r>>=1)
	{
		if(r&1)ret=quick_mult(ret,x,mod);
		x=quick_mult(x,x,mod);
	}
	return ret;
}
inline bool isprime(LL x)
{
	if(x==2)return true;
	if(x<2||!(x&1))return false;
	LL y,a,pre;
	int ord=0;
	for(y=x-1;!(y&1);y>>=1)ord++;
	for(int i=0;i<15;i++)
	{
		a=quick_pow(rand()%(x-2)+2,y,x);
		pre=a;
		for(int j=0;j<ord;j++)
		{
			a=quick_mult(a,a,x);
			if(a==1&&pre!=1&&pre!=x-1)return false;
			pre=a;
		}
		if(a!=1)return false;
	}
	return true;
}
int main(void)
{
	int t,_a,_b,_c;
	LL a,b;
	bool ans;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&_a,&_b,&_c);
		a=33-2*_a-_c,b=_b-_a;
		if(b)ans=isprime(a*a+a*b+3*b*b);
		else
		{
			a=abs(a);
			ans=(a==2||(isprime(a)&&quick_pow((a-11%a)%a,a-1>>1,a)==a-1));
		}
		puts(ans?"PRIME":"NOT PRIME");
	}
	return 0;
}
