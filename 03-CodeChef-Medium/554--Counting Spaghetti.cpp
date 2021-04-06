#include <bits/stdc++.h>
using namespace std;
long long l,r;
long long f(long long x)
{
	return x*x+(l-r)*x+l-1;
}
int main()
{
	int t;
	scanf("%d",&t);
	while (t--)
	{
		scanf("%lld%lld",&l,&r);
		long long ans=r*(r+1)/2-l*(l-1)/2,pre=0,suf=r-l;
		while (pre<=suf && f(pre)>0)
		ans-=f(pre++);
		while (suf>pre && f(suf)>0)
		ans-=f(suf--);
		printf("%lld\n",ans);
	}
} 
