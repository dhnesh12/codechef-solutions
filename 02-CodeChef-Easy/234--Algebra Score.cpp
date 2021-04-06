#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		long long int nums[n];
		char sigs[n-1];
		int j=0;
		int k=0;
		for(int i=0;i<n+n-1;i++)
		{
			if(i%2==0)
			{
				cin>>nums[j];
				j++;
			}
			else
			{
				cin>>sigs[k];
				k++;
			}
		}
		long long int dp[201][201];
		long long int dpmin[201][201];
		for(int i=0;i<n;i++)
		{
			dp[i][i]=nums[i];
			dpmin[i][i]=nums[i];
		}
		for(int len=2;len<=n;len++)
		{
			for(int l=0;l<n-len+1;l++)
			{
				int r=l+len-1;
				dp[l][r]=INT_MIN;
				dpmin[l][r]=INT_MAX;
				for(int i=l;i<r;i++)
				{
					if(sigs[i]=='+')
					{
						dp[l][r]=max(dp[l][r],dp[l][i]+dp[i+1][r]);
						dpmin[l][r]=min(dpmin[l][r],dpmin[l][i]+dpmin[i+1][r]);
					}
					else if(sigs[i]=='-')
					{
						dp[l][r]=max(dp[l][r],dp[l][i]-dpmin[i+1][r]);
						dpmin[l][r]=min(dpmin[l][r],dpmin[l][i]-dp[i+1][r]);
					}
				}
			}
		}
		/*for(int i=0;i<n-1;i++)
		{
			cout<<sigs[i]<<" ";
		}
		cout<<endl;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				cout<<dp[i][j]<<" ";
			}
			cout<<endl;
		}*/
		cout<<dp[0][n-1]<<endl;
	}
	return 0;
}
