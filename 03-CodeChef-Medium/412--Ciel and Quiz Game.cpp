#include<bits/stdc++.h>
#include<math.h>
#define rep(i,k,n) for(int i=k;i<n;i++)
#define ll long long
#define MOD 1000000007ll
#define ROD 1000000009ll
#define INF 1e18
#define MIN(a,b) (a>b?b:a)
using namespace std;
#define mp make_pair
#define pb push_back
#define  piii pair<pair<ll,ll>,ll>
#define pii pair<ll,ll>
#define fi first
#define se second
#define MAXN 200010
ll t,n,k,br[40];
pii ar[40];
double func(ll,ll),dp[40][2];
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld %lld",&n,&k);
		rep(i,0,n)
		{
			scanf("%lld",&ar[i].fi);
			ar[i].se=i+1;
		}
		sort(ar,ar+n);
		double ans=0;
		ll idx=0;
		rep(i,0,k+1)
		{
			ll size_=0;
			rep(j,0,i)
				br[size_++]=ar[j].fi;
			rep(j,n-(k-i),n)
				br[size_++]=ar[j].fi;
			rep(i,0,40)
			dp[i][0]=dp[i][1]=-1;
			// cout<<func(0,0)<<" ";
			if(ans<func(0,0))
			{
				ans=func(0,0);
				idx=i;
			}
		}
		rep(j,0,idx)
			printf("%lld ",ar[j].se);
		rep(j,n-(k-idx),n)
			printf("%lld ",ar[j].se);
		printf("\n");		
	}
}
double func(ll idx,ll bit)
{
	if(idx==k)
		return (bit==1);
	if(dp[idx][bit]>=0)
		return dp[idx][bit];
	if(bit)
		return dp[idx][bit]=func(idx+1,1)*br[idx];
	else
		return dp[idx][bit]=func(idx+1,0)*br[idx]+func(idx+1,1)*(100-br[idx]);
}