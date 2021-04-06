#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

#define mp	make_pair
#define pb push_back

int dp[10][1801][301];

ll mod = 1e9+7;

ll dp_solve(int wickets,int runs,int balls)
{
	if( wickets < 0  || runs > 6*balls || runs < 0)	return 0;
	if( balls == 0 ){
		if( runs == 0 )	return 1;
		else	return 0;
	}
	if(dp[wickets][runs][balls] != -1 )	return dp[wickets][runs][balls];
	
	ll answer = (dp_solve(wickets-1,runs,balls-1) + dp_solve(wickets,runs-4,balls-1) + dp_solve(wickets,runs-6,balls-1) + dp_solve(wickets,runs,balls-1))%mod;
	
	dp[wickets][runs][balls] = answer;
	return answer;
}

void solve()
{
	int runs,balls,wk;
	cin>>runs>>balls>>wk;
	cout<<dp_solve(wk,runs,balls)<<endl;
}

int main()
{
	int T;
	cin>>T;
	memset(dp,-1,sizeof(dp));
	for(int i=1;i<=T;i++){
		solve();
	}
	return 0;
}