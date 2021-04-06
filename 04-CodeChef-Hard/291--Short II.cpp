#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ui unsigned int
#define ull unsigned long long
#define db double
#define ld long double
#define pii pair<ll,int>
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define vi vector<int>
#define vii vector<vi>
#define lb lower_bound
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,b,a) for(register int i=(b);i>=(a);--i)
#define rep0(i,a,b) for(register int i=(a);i<(b);++i)
#define fore(i,a) for(register int i=0;i<a.size();++i)
#define ls x<<1,l,m
#define rs x<<1|1,m+1,r
ll p,lim,ans;
inline void sol()
{
	//number of (a,b): p\in Pr  p<a,b (a-p)(b-p)|ab.
	//(a-p)(b-p)|ab-(a-p)(b-p) (a-p)(b-p)|p(a+b-p) (p<a,b)
	//ab|p(a+b+p) 0<a<b (a=b->a=b=p+1 1)
	//(a,p)=(b,p)=1: ab|a+b+p 
	//p|a (b,p)=1: ?
	//p|a p|b: a=b=(p,p),(p,2p),(2p,3p) 5 
	scanf("%lld",&p);ans=0;
	lim=sqrt(p+2+sqrt(p+1));
	for(ll b=1;b<=lim;b++)
	{
		ll a=b-p%b,d=(a+p)/b;
		if((d+1)%a==0&&a<b&&b<=d&&a%p&&b%p)ans++;
	}
	for(ll d=1;d<=lim;d++)
	{
		ll a=-p%d;
		do
		{
			a+=d;ll b=(a+p)/d;
			if((d+1)%a==0&&a<b&&d<b&&a%p&&b%p)ans++;
		}
		while(a<=d+1);
	}
	printf("%lld\n",3*(2*ans+1)+5);
}
int main(){int T;scanf("%d",&T);while(T--)sol();return 0;}
