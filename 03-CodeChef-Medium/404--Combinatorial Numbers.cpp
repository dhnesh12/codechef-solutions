#include<bits/stdc++.h>
#include<math.h>
#define rep(i,k,n) for(int i=k;i<n;i++)
#define ll long long
#define MOD 100000007ll
#define ROD 1000000009ll
#define INF 1e18
#define MIN(a,b) (a>b?b:a)
using namespace std;
#define mp make_pair
#define pb push_back
#define  piii pair<ll,pair<ll,ll>>
#define pii pair<ll,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) \
    for ( \
        auto blockTime = make_pair(chrono::high_resolution_clock::now(), true); \
        blockTime.second; \
        debug("%s: %lld ms\n", d, chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - blockTime.first).count()), blockTime.second = false \
    )
#define MAXN 100005
ll t,n,k,m;
ll ans[355];
ll ncr[400][400];
void pre()
{
	memset(ncr,-1,sizeof(ncr));
	rep(i,0,360)
	ncr[i][0]=1,ncr[i][i]=1;

	rep(i,0,21)
	{
		ll num=1,dem=1;
		rep(j,1,i+1)
		{
			num*=(i-j+1);
			dem*=j;
			// cout<<num<<" "<<dem<<"\n";
			ncr[i][j]=(num/dem);
			// if(ncr[i][j]>=1000000000)
			// 	break;
		}
		num=1,dem=1;
		for(int j=i-1;j>=1;j--)
		{
			num*=(j+1);
			dem*=(i-j);
			// cout<<num<<" "<<dem<<"\n";			
			ncr[i][j]=(num/dem);
			// if(ncr[i][j]>=1000000000)
			// 	break;
		}
		// rep(j,0,i+1)
		// 	if(ncr[i][j]==-1)
		// 		ncr[i][j]=1000000000;
	}
}
ll func(ll,ll,ll);
int main()
{
	pre();
	// rep(i,0,10)
	// {
	// 	rep(j,0,i+1)
	// 	cout<<ncr[i][j]<<" ";
	// 	cout<<"\n";
	// }
	scanf("%lld ",&t);
	while(t--)
	{
		scanf("%lld %lld %lld",&n,&k,&m);
		if(ncr[n][k]<m)
		{
			printf("-1\n");
		}
		else
		{
			func(0,k,m);
			rep(i,0,n)
			printf("%d",ans[i]);
			printf("\n");
		}	
	}
}
ll func(ll idx,ll k,ll rem)
{
	if(idx==n)
		return 0;
	if(k!=(n-idx)&&ncr[n-idx-1][k]>=rem)
	{
		ans[idx]=0;
		func(idx+1,k,rem);
	}
	else
	{
		ans[idx]=1;
		func(idx+1,k-1,rem-ncr[n-idx-1][k]);
	}
}