#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		long long n,m,index=0;
		cin>>n;
		long long a[n];
		
		for(int i=0;i<n;i++)
		cin>>a[i];
		
		cin>>m;
		long long b[m];
		for(int i=0;i<m;i++)
		cin>>b[i];
		
		int cnt=0;
		
		for(int i=0;i<m;i++)
		{
			for(int j=0;j<n;j++)
			{
				if(b[i]==a[j]&&j>=index)
				{
					cnt++;
					index=j;
					break;
				}
			}
		}
		if(cnt>=m)
		cout<<"Yes"<<endl;
		else 
		cout<<"No"<<endl;
	}
}