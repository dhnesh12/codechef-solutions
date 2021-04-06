#include<bits/stdc++.h>
#define int long long
#define mod  1000000007
using namespace std;
const int n=10005;

vector<int>val(n);
vector<int>par(n);
map<int,int>mp;


int find(int x)
{
	if(x==par[x])return x;
	return par[x]=find(par[x]);
}
int solve()
{
	int n;cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>val[i];
		par[i]=i;
		mp[i]=val[i];
	}
	
	int q;cin>>q;
	while(q--)
	{
		int t;cin>>t;
		if(t==0)
		{
			int x,y;
			cin>>x>>y;
			int a=find(x);
			int b=find(y);
			if(a==b)cout<<"Invalid query!\n";
			
			else if(val[a]>val[b])
			par[b]=a;
			else if(val[a]<val[b])
			par[a]=b;
		}
		else
		{
			int x;cin>>x;
			x=find(x);
			cout<<x<<"\n";
		}
	}
}

signed main()
{
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	
	int t=1;
	cin>>t;
	while(t--)
	solve();
	
	return 0;
}