#include<bits/stdc++.h>
using namespace std;

#define int long long
#define fi first
#define se second
#define pb push_back

int n,m,i,a,b,c,dis[20010],x;
vector<pair<int,int>> adj[20010];
bool vis[20010];
priority_queue<pair<int,int>> q;

signed main()
{
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>a;
	for (i=1;i<m+1;i++)
	{
		cin>>a>>b>>c;
		adj[a].pb({b,c});
		adj[b].pb({a,c});
	}
	for (i=1;i<n+1;i++) dis[i]=1e16;
	for (i=1;i<n+1;i++) vis[i]=false;
	dis[1]=0;q.push({0,1});
	while (!q.empty())
	{
		a=q.top().se;q.pop();
		if (vis[a]) continue;
		vis[a]=true;
		for (auto u:adj[a])
		{
			b=u.fi;c=u.se;
			if (dis[a]+c<dis[b])
			{
				dis[b]=dis[a]+c;
				q.push({-dis[b],b});
			}
		}
	}
	if (dis[n]!=1e16) cout<<dis[n];else cout<<-1;
}
