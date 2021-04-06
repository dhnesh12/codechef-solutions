#include <bits/stdc++.h>

using namespace std;

#define st first
#define nd second
#define PII pair <int, int>

const int N = 507;
const int N2 = 2 * N;

int n, k;
bitset <N> Edge[N];

int adj[N2];
bool vis[N2];
vector <int> G[N2];

bool dfs(int u){
	vis[u] = true;
	for(auto v: G[u])
		if(adj[v] == 0 || (!vis[adj[v]] && dfs(adj[v]))){
			adj[u] = v;
			adj[v] = u;
			return true;
		}
	
	return false;
}

int getMatching(){
	for(int i = 1; i <= n + n; ++i){
		adj[i] = 0;
		G[i].clear();
	}
	
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(Edge[i][j])
				G[i].push_back(n + j);
	
	while(true){
		for(int i = 1; i <= n; ++i)
			vis[i] = false;
		
		bool ok = false;
		for(int i = 1; i <= n; ++i)
			if(adj[i] == 0 && dfs(i))
				ok = true;
		
		if(!ok)
			break;
	}
	
	int ans = 0;
	for(int i = n + 1; i <= n + n; ++i)
		ans += adj[i] == 0;
	return ans;
}

void solve(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= n; ++j)
			Edge[i][j] = 1;
		Edge[i][i] = 0;
	}

	for(int i = 1; i <= k; ++i){
		bitset <N> not_vis;
		for(int j = 1; j <= n; ++j)
			not_vis[j] = 1;

		for(int j = 1; j <= n; ++j){
			int cur;
			scanf("%d", &cur);
			not_vis[cur] = 0;
			Edge[cur] &= not_vis;
		}
	}
	
	int v = getMatching();
	printf("%d\n", v);
	
	for(int i = 1; i <= n; ++i){
		if(adj[i])	adj[i] -= n;
		printf("%d ", adj[i]);
	}

	puts("");
}

int main(){
	int cases;
	scanf("%d", &cases);
	
	while(cases--)
		solve();
	return 0;
}