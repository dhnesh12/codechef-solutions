#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ui unsigned int
#define ull unsigned long long
#define db double
#define ld long double
#define pii pair<int,ll>
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define vi vector<int>
#define vii vector<vi>
#define lb lower_bound
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,b,a) for(int i=(b);i>=(a);--i)
#define rep0(i,a,b) for(int i=(a);i<(b);++i)
#define fore(i,a) for(int i=0;i<a.size();++i)
#define ls x<<1,l,m
#define rs x<<1|1,m+1,r
#define gc() getchar()
inline ll rd()
{
	ll x=0;char c=gc();while(!isdigit(c))c=gc();
	while(isdigit(c))x=x*10+c-48,c=gc();return x;
}
const int N=400005,M=6000;
int cc,tt,pr[N],lst[N];ll n,K,ans,d[N];
void init(int n)
{
	lst[1]=n+1;
	rep(i,2,n)
	{
		if(!lst[i])lst[i]=pr[++cc]=i;
		for(int j=1;j<=cc&&1ll*i*pr[j]<=n;j++)
		{
			lst[i*pr[j]]=pr[j];
			if(i%pr[j]==0)break;
		}
	}
}
int tp,stk[105];
void prt(__int128 x)
{
	tp=0;if(!x)stk[++tp]=0;while(x)stk[++tp]=x%10,x/=10;
	per(i,tp,1)putchar('0'+stk[i]);putchar('\n');
}
void sol()
{
	n=rd();K=rd()-1;ans=0;
	if(!n){prt((__int128)K*K);return;}
	for(ll a=n+1;a<=3.43*n&&a<=K;a++)
	{
		if(a>n+M)
		{
			ll t=(a*a-n)/((a-n)*(a-n)),p=a*n-n;
			for(ll k=a/(a-n)+1;k<=t;k++)
			{
				ll b=n+p/(k*a-k*n-a);
				if(b<=K&&!((a*b-n)%((a-n)*(b-n))))ans+=a!=b?2:1;
			}
		}
		else
		{
			ll p1=a-1,p2=n;d[tt=1]=1;
			while(p1>1||p2>1)
			{
				ll t=min(lst[p1],lst[p2]),c=0;
				while(lst[p1]==t)p1/=t,c++;
				while(lst[p2]==t)p2/=t,c++;
				per(i,tt,1)
				{
					ll p=1;
					rep(j,1,c)p*=t,d[++tt]=d[i]*p;
				}
			}
			ll o=(a-1)*n;
			rep(i,1,tt)
			{
				ll b=o/d[i]+a;
				if(!(b%(a-n))&&n+d[i]<=K&&n+d[i]>=a)ans+=n+d[i]!=a?2:1;
			}
		}
	}
	printf("%lld\n",ans); 
} 
int main(){init(N-1);int T=rd();while(T--)sol();return 0;} 
