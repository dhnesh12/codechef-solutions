#include<bits/stdc++.h>
#include<math.h>
#define rep(i,k,n) for(int i=k;i<n;i++)
#define ll long long
#define MOD 1000000009ll
#define ROD 100000000ll
#define INF 123456789123456ll
#define MIN(a,b) (a>b?b:a)
using namespace std;
#define mp make_pair
#define  piii pair< string ,pair<vector <ll>,ll>>
#define pii pair<ll,ll>
#define fi first
#define se second
ll t,n,k,ar[1005],dr[1005];
double func(ll,ll),dp[1005][1005];
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld %lld",&n,&k);
		rep(i,0,n)
		scanf("%lld",&ar[i]);
		rep(i,0,k)
		scanf("%lld",&dr[i]);
		sort(ar,ar+n,greater <ll> ());
		sort(dr,dr+k,greater <ll> ());
		rep(i,0,n+1)
		rep(j,0,k+1)
		dp[i][j]=-1;
		printf("%0.3lf\n",func(0,0));
	}
}
double func(ll idx,ll k)
{
	//cout<<idx<<" "<<k<<"L\n";
	if(dp[idx][k]>=0)
	{
		return dp[idx][k];
	}
	if(idx==n||k==::k)
	{
		return 0;
	}
	if(n-idx==::k-k)
	{
		return dp[idx][k]=func(idx+1,k+1)+(dr[k]*ar[idx])/100.0;
	}
	else
	{	
		//cout<<idx<<" "<<k<<" "<<0.5*(func(idx+1,k+1)+((dr[k]*ar[idx])/100))<<" "<<func(idx+1,k+1)<<" "<<((dr[k]*ar[idx])/100)<<" "<<0.5*func(idx+1,k)<<"AA\n";	
		return dp[idx][k]=((::k-k)/(n-idx+0.0))*(func(idx+1,k+1)+((dr[k]*ar[idx])/100.0))+((n-idx-::k+k)/(n-idx+0.0))*func(idx+1,k);
	}	
}
