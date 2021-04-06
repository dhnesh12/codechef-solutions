#include<bits/stdc++.h>
#define int long long
#define mod  1000000007
using namespace std;
vector<int>vec[100005];
vector<bool>vis(100005);
vector<int>c(100005);
int mi;

void dfs(int nod)
{
	vis[nod]=true;
	if(c[nod]>=0)
	mi=min(mi,c[nod]);
	
	for(auto i:vec[nod])
	if(!vis[i])dfs(i);
	
}

int solve()
{
	int n,m;cin>>n>>m;
	while(m--)
	{
		int a,b;
		cin>>a>>b;
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
	
	for(int i=1;i<=n;i++)
	cin>>c[i];
	
	vector<int>ans;
	int var=0;
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			mi=100000;
			dfs(i);
			if(mi==100000)var++;
			else ans.push_back(mi);
		}
	}
	
	if(var+(int)ans.size()==1){cout<<0;return 0;}
	if(var>0){cout<<-1;return 0;}
	
	sort(ans.begin(),ans.end());
	int val=0,i;	
	for(i=1;i<ans.size();i++)
	val+=ans[i]+ans[0];

	cout<<val<<"\n";
}

signed main()
{
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	
	int t=1;
//	cin>>t;
	while(t--)
	solve();
	
	return 0;
}