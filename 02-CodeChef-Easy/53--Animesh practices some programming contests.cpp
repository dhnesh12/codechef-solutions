#include<bits/stdc++.h>
using namespace std;
// number_of _prob index k time
int n,dp[51][51][51][51],arr[100][3],tim[100][3];
int func(int num,int ind,int k,int tt)
{
	if(num>n||tt<0||k<0)
		return -50000022;
	if(ind==n)
		return 0;
	int& ans=dp[num][ind][k][tt]; 
	if(ans!=-1)
		return ans;
	ans=0;
	for(int i=0;i<8;i++)
	{
		int c=0;
		int ansa=0,tot=0;
		for(int j=0;j<3;j++)
		{
			if(i&(1<<j))
			{
				c++;
				ansa=ansa+arr[ind][j];
				tot=tot+tim[ind][j];
			}
		}
		if(num+c>n||tt<tot||k<max(0,c-1))
			continue;
		ans=max(ans,ansa+func(num+c,ind+1,k-max(0,c-1),tt-tot));
	}
	return ans;	
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		memset(dp,-1,sizeof(dp));
		int k,ti,i;
		cin>>n>>k>>ti;
		for(i=0;i<n;i++)
		{
			scanf("%d%d%d",&tim[i][0],&tim[i][1],&tim[i][2]);
		}
		for(i=0;i<n;i++)
		{
			scanf("%d%d%d",&arr[i][0],&arr[i][1],&arr[i][2]);
		}
		
		cout<<func(0,0,min(n,k),ti)<<endl;
	}
	return 0;
}