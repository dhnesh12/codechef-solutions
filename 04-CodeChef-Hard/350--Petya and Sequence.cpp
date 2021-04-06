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
#define gc() getchar()
inline int rd()
{
	int x=0,w=1;char c=gc();while(!isdigit(c)&&c!='-')c=gc();
	if(c=='-')w=-1,c=gc();while(isdigit(c))x=x*10+c-48,c=gc();return x*w;
}
const int N=100005;
ll n,m,P,G,a[N];
inline ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
inline ll mul(ll a,ll b,ll p=P){return (a*b-(ll)((ld)a*b/p)*p+p)%p;}
inline ll pw(ll a,ll b){ll r=1;for(;b;b>>=1,a=mul(a,a))if(b&1)r=mul(r,a);return r;}
inline int ispr(ll x){for(ll i=2;i*i<=x;i++)if(x%i==0)return 0;return 1;}
namespace Poly
{
	int r[N];ll w[N];
	inline void ntt(int n,ll*a,int f)
	{
		int l=1;while((1<<l)<n)l++;
		rep0(i,1,n)r[i]=r[i>>1]>>1|(i&1)<<(l-1);
		rep0(i,0,n)if(i<r[i])swap(a[i],a[r[i]]);
		for(int i=2;i<=n;i<<=1)
		{
			ll wn=pw(G,f==1?(P-1)/i:P-1-(P-1)/i);
			w[0]=1;rep0(j,1,(i>>1))w[j]=mul(w[j-1],wn);
			for(int j=0;j<n;j+=i)
			{
				ll*x=a+j,*y=a+j+(i>>1);
				rep0(k,0,(i>>1)){ll v=mul(y[k],w[k]);y[k]=(x[k]+P-v)%P;x[k]=(x[k]+v)%P;}
			}
		}
		if(f==-1)
		{
			ll iv=pw(n,P-2);
			rep0(i,0,n)a[i]=mul(a[i],iv);
		}
	}
} 
using Poly::ntt;
ll A[N],B[N],w[N];
inline void bluestein(ll*a)
{
	rep0(i,0,m)A[i]=B[i]=0; 
	rep0(i,0,n)A[n-1-i]=mul(a[i],w[(n-1ll*i*(i-1)/2%n)%n]);
	rep0(i,0,2*n)B[i]=w[1ll*i*(i-1)/2%n];
	ntt(m,A,1);ntt(m,B,1);
	rep0(i,0,m)A[i]=mul(A[i],B[i]);
	ntt(m,A,-1);
	rep0(i,0,n)a[i]=mul(A[n-1+i],w[(n-1ll*i*(i-1)/2%n)%n]);
}
void sol()
{
	n=rd();rep0(i,0,n)a[i]=rd();
	for(m=1;m<=2*n;m<<=1); 
	ll t=n*m/gcd(n,m);P=t+1;
	per(i,30,0)if(P+(t<<i)<1000*n)P+=t<<i;
	while(P<1000*n||!ispr(P))P+=t;
	for(G=2;;G++)
	{
		int ff=1;ll t=P-1;
		for(ll i=2;i*i<=P;i++)if(t%i==0)
		{
			if(pw(G,(P-1)/i)==1){ff=0;break;}
			while(t%i==0)t/=i;
		}
		if(t>1&&pw(G,(P-1)/t)==1)continue;
		if(ff)break;
	}
	ll wn=pw(G,(P-1)/n);w[0]=1;
	rep0(i,1,n)w[i]=mul(w[i-1],wn);
	bluestein(a);int ff=1;
	rep0(i,0,n)if(!a[i])ff=0;
	puts(ff?"NO":"YES");
}
int main(){int T=rd();while(T--)sol();return 0;}
