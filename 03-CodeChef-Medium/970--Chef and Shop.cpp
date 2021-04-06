#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin>>t;
	while(t--)
	{
	    long long int i,j,n,k;
	    cin>>n>>k;
	    vector<long long int>costs(n),weights(n);
	    for(i=0;i<n;++i)
	    {
	        cin>>costs[i]>>weights[i];
	    }
	    vector<vector<long long int>>dp(n+1,vector<long long int>(k+1,0));
	    for(i=1;i<=n;++i)
	    {
	        for(j=1;j<=k;++j)
	        {
	            if(j>=costs[i-1])
	            {
	                dp[i][j]=max(dp[i-1][j],dp[i-1][j-costs[i-1]]+weights[i-1]);
	            }
	            else
	            {
	                dp[i][j]=dp[i-1][j];
	            }
	        }
	    }
	    cout<<dp[n][k]<<"\n";
	}
	return 0;
}
