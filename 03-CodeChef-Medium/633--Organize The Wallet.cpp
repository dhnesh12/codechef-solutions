/*And I thought my jokes were bad*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define dbg puts("Viva la vida");
#define CHECK(x) cout << (#x) << " is " << (x) << endl;
#define nl puts("");
#define mp make_pair
#define IN(x) scanf("%d",&x);
#define INL(x) scanf("%lld",&x);
#define OUT(x) printf("%d",x);
#define OUTL(x) printf("%lld",x);
#define MAX 100005
#define MOD 1000000007
#define INF (1 << 31)
#define CASE(x,y) printf("Case %d: %d\n",++x,y);
#define FASTIO ios::sync_with_stdio(false);cin.tie(0);
using namespace std;
// #define int ll
/*
	I don't do this for the riches
	I'm infected, my condition is I'm always in my head
	These words are my religion
	I'm obsessive by decision
	I'ma do this 'til I'm dead-ead
*/
int arr[]={10, 20, 50, 100, 200, 500,2000};
int dp[MAX][129][7];
int mx[MAX][129];
int sh[MAX];
int n;
// int sol(int k,int mask,int cur=6)
// {
// 	if(k==n) return 0;
// 	int &ret=dp[k][mask][cur];
// 	if(~ret) return ret;
// 	for(int i=0;i<7;i++)
// 	{
// 		if(!(mask&(1<<i))||i==cur)
// 		{
// 			if(arr[i]==sh[k])	ret=max(ret,sol(k+1,mask|(1<<i),i)+1);
// 			else	ret=max(ret,sol(k+1,mask|(1<<i),i));
// 		}
// 	}
// 	return ret;
// }
void solve()
{
	int i,j,k,l,m,x,y;
	memset(dp,0,sizeof dp);
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&sh[i]);
		for(int j=0;j<7;j++)
			if(arr[j]==sh[i])
			{
				sh[i]=j;
				break;
			}
	}
	for(i=0;i<128;i++)
	{
		for(j=0;j<7;j++)
			dp[n][i][j]=0;
	}
	for(k=n-1;k>=0;k--)
	{
		for(int mask=0;mask<128;mask++)
		{
			for(int cur=0;cur<7;cur++)
			{
				if(cur==sh[k])
					dp[k][mask][cur]=dp[k+1][mask][cur];
				else if(mask&(1<<sh[k]))
				{
					dp[k][mask][cur]=dp[k+1][mask][cur]+1;
				}
				else
				{
					dp[k][mask][cur]=min(1+dp[k+1][mask][cur],dp[k+1][(mask|(1<<cur))][sh[k]]);
				}
			}
		}
	}
	int ans=n;
	for(int i=0;i<7;i++)
		ans=min(ans,dp[0][0][i]);
	printf("%d\n",ans);;
	
}
int32_t main()
{
	int t;
	t=1;
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}