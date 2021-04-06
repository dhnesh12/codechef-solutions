#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll arr[1002][1002][2], INF1 = 1e18 + 1;
long double dp[1002][1002][2], INF = (long double)INF1;
long double takeBest(long double a, long double b, long double c, long double d)
{if (a >= INF || b >= INF || c >= INF || d >= INF){return INF;} return max(max(a,b),max(c,d));}
int main(){int n,m; ll D; scanf("%d %d %lld",&n,&m,&D);
	for (int i = 0; i < n; i++){for(int j = 0; j < m; j++){scanf("%lld %lld",&arr[i][j][1],&arr[i][j][0]);}}
	for (int i = 0; i < n; i++){dp[i][0][0] = dp[i][0][1] = 1.00;}
	for (int j = 1; j <= m; j++){for (int i = 0; i < n; i++){
			long double goLeft = (i==0)?0:dp[i-1][j-1][0], goRight = (i==(n-1))?0:dp[i+1][j-1][0];
			long double stayHere = dp[i][j-1][0], buying = (dp[i][j-1][1])*arr[i][m-j][0];
			dp[i][j][0] = takeBest(goLeft,goRight,stayHere,buying);
	        goLeft = (i==0)?0:dp[i-1][j-1][1]; goRight = (i==(n-1))?0:dp[i+1][j-1][1];
			stayHere = dp[i][j-1][1]; buying = (dp[i][j-1][0])/arr[i][m-j][1];
			dp[i][j][1] = takeBest(goLeft,goRight,stayHere,buying);}}
	long double ans = 0; for (int i = 0; i < n; i++){ans=max(ans,dp[i][m][1]);} ans *= D;
	if (ans >= INF){printf("Quintillionnaire\n");} else{printf("%.8LF\n",ans);} return 0;}