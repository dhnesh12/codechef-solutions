#include <bits/stdc++.h>
using namespace std;
string ip()
{
	string ans="";
	int temp=getchar_unlocked();
	while(temp<'0' || temp>'1')temp=getchar_unlocked();
	while(temp>='0' and temp<='1')
	{
		ans+=(char)temp;
		temp=getchar_unlocked();
	}
	return ans;
}
int main() {
	int n;
	scanf("%d",&n);
	vector<string> A(n);
	vector<int> out(n,0);
	for(int i=0;i<n;i++)
	{
		A[i]=ip();
		for(int j=0;j<n;j++)if(A[i][j]=='1')out[i]++;
	}
	vector<bool> vis(n,0);
	int c=0;
	vector<vector<int>> ans(n,vector<int> (n,0));
	for(int i=0;i<n;i++)
	
	{
		int v=-1;
		for(int j=n-1;j>=0;j--)
		{
			if(out[j]==0 and !vis[j])
			{
				v=j;break;
			}
		}
		vis[v]=1;
		
		for(int j=0;j<n;j++)
		{
			if(j!=v and A[j][v]=='0' and !vis[j])
			{
				c++;
				ans[j][v]=1;
			}
			else if(A[j][v]=='1')out[j]--;
		}
		
	}
	printf("%d\n",c);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)if(ans[i][j]==1)printf("%d %d\n",i+1,j+1);
	}
	
	
}