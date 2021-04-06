#include<bits/stdc++.h>
using namespace std;
int arr[1000];
int dp[1001][1001];
int s(int a,int b)
{
	int sum=0;
	for(int i=a;i<=b;i++)
	{
		sum=(sum+arr[i])%100;;

	}
	return sum%100;
}
int solve(int i,int j)
{
	if(i==j)
	{
		dp[i][j]=0;
		return 0;
	}
	if(dp[i][j]!=-1)
		return dp[i][j];
	int ans=INT_MAX;
	for(int k=i;k<j;k++)
	{
		ans=min(ans,solve(i,k)+solve(k+1,j)+s(i,k)*s(k+1,j));
	}
	dp[i][j]=ans;
	return dp[i][j];
}
int main()
{
	int n;
	while(cin>>n)
	{
		for(int i=0;i<n;i++)
		{
			cin>>arr[i];
		}
		memset(dp,-1,sizeof(dp));
		cout<<solve(0,n-1)<<endl;
	}
}
