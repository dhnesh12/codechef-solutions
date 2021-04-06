#include <bits/stdc++.h>
using namespace std;
#pragma optimize("-O3")
#define int long long int
#define f first
#define s second
#define pb push_back
#define endl '\n'
const int N=1e5+5;
vector<vector<pair<int, int>>>vec;
vector<vector<pair<int, int>>>adj;
const int MOD=1e9+7;
bool vis[N];
int val[N];
int x[N];

void dfs(int v, int co){
	vis[v]=1;
	val[v]=co;
	for(auto u:adj[v]){
		if(vis[u.f]==1){
			continue;
		}
		dfs(u.f, (co+u.s+MOD)%MOD);
	}
}
 
main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, e;
	cin>>n>>e;
	vec.resize(n+1);
	adj.resize(n+1);
	for(int i=0; i<e; i++){
		int u, v, w;
		cin>>u>>v>>w;
		v-=n;
		vec[u].pb({v, w});
	}
	for(int i=1; i<=n; i++){
		sort(vec[i].begin(), vec[i].end());
	}
	for(int i=1; i<=n; i++){
		for(int j=0; j<vec[i].size()-1; j++){
			int v1=vec[i][j].f;
			int v2=vec[i][j+1].f;
			int w=vec[i][j+1].s-vec[i][j].s;
			adj[v1].pb({v2, w});
			adj[v2].pb({v1, (-w+MOD)%MOD});
		}
	}
	dfs(1, 0);
	for(int i=1; i<=n; i++){
		int node=vec[i][0].f;
		int nw=vec[i][0].s;
		x[i]=(nw-val[node]+MOD)%MOD;
	}
	int s1=0;
	int ans=0;
	for(int i=1; i<=n; i++){
		s1=(s1+x[i]*x[i])%MOD;
	}
	ans=(ans+s1*n)%MOD;
	s1=0;
	for(int i=1; i<=n; i++){
		s1=(s1+(val[i]*val[i]))%MOD;
	}
	ans=(ans+s1*n)%MOD;
	int s2=0;
	int s3=0;
	for(int i=1; i<=n; i++){
		s2=(s2+val[i])%MOD;
		s3=(s3+x[i])%MOD;
	}
	ans=(ans+2*s2*s3)%MOD;
	cout<<ans;
	return 0;
}
