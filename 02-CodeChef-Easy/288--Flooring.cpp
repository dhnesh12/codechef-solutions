//#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
//#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define test puts("QAQ");
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int n;
int mod;
int _;
inline int get(int x)
{
	int res=x%mod*(x+1)%mod*(2*x+1)%mod*(x%mod*x%mod*3%mod+x*3%mod-1);
	return (res%mod+mod)%mod;
}

signed main()
{	
	for(_=read();_;_--)
	{
		n=read(),mod=read();
		mod*=30;
		int res=0;
		for(int l=1,r;l<=n;l=r+1)
		{
			r=n/(n/l);
			int tmp=n/l;
			res=(res+tmp*((get(r)-get(l-1))%mod+mod)%mod)%mod;
		}
		res/=30;
		printf("%lld\n",res);
	}
}