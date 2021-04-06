#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ui unsigned int
#define ull unsigned long long
#define db long double
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
#define gc() getchar()
#define lc x<<1
#define rc x<<1|1
#define ls lc,l,m
#define rs rc,m+1,r
inline int rd()
{
	int x=0;char c=gc();while(!isdigit(c))c=gc();
	while(isdigit(c))x=x*10+c-48,c=gc();return x;
}
const int N=60000005;
const db pi=acos(-1.0);
map<int,int>smu; 
ll n;int cc,vis[N],pr[N>>3],mu[N],mu2[N];
inline void init()
{
	mu[1]=mu2[1]=1;
	rep(i,2,N-1)
	{
		if(!vis[i])pr[++cc]=i,mu[i]=-1;
		for(int j=1;j<=cc&&1ll*i*pr[j]<N;j++)
		{
			int t=i*pr[j];vis[t]=1;
			if(i%pr[j]==0)break;else mu[t]=-mu[i];
		}
	}
	rep(i,2,N-1)mu2[i]=mu2[i-1]+abs(mu[i]),mu[i]+=mu[i-1];
}
inline int S(int n)
{
	if(n<N)return mu[n];
	if(smu.count(n))return smu[n];
	int res=1;
	for(int l=2,r;l<=n;l=r+1){int t=n/l;r=n/t;res-=S(t)*(r-l+1);}
	return smu[n]=res;
}
inline ll calc(ll n)
{
	if(n<N)return n-mu2[n];
	ll res=0,lst=0,tmp,t,i=1;
	for(;i*i*i<=n;i++)res+=(n/(i*i))*((tmp=mu[i])-lst),lst=tmp;
	for(res-=(t=n/(i*i))*lst;t;t--)res+=S(sqrt(n/t));
    return n-res;
/*
    ll s=0,ed=sqrt(n);
	while((ed+1)*(ed+1)<=n)ed++;
	while(ed*ed>n)ed--;
	for(ll l=1,r;l<=ed;l=r+1)
	{
		ll t=n/l/l;r=t>l?l:sqrt(n/t);//r=max(l,r);
		while(1ll*(r+1)*(r+1)*t<=n)r++;
		while(1ll*r*r*t>n)r--;
		s+=t*(S(r)-S(l-1));
	}
	return n-s;
*/
}
int main()
{
	scanf("%lld",&n);init();ll L,R,mid,ans;
	L=n/(1-6.0/pi/pi);R=L+400000;L=max(1ll,L-400000);
	while(L<=R)if(calc(mid=L+R>>1)>=n)ans=mid,R=mid-1;else L=mid+1;
	printf("%lld\n",ans);return 0;
}