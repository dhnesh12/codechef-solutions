// KALAM
# include<bits/stdc++.h>

using namespace std;

const int N = 100000 + 77 , LOG = 18;
int n , Sz[N] , d[N] , Mxd[N] , dp[N] , H[N][LOG] , F[N][LOG] , S[N][LOG];
vector < int > adj[N];
bool CMP(int x , int y) {
	return make_pair(dp[x] , Sz[x]) < make_pair(dp[y] , Sz[y]);
}
void dfs(int v) {
	Sz[v] = 1;
	Mxd[v] = v;
	int sz = adj[v].size();
	if(sz == 0) {
		dp[v] = 0;
		for(int i = 0;i < LOG;++ i)
			H[v][i] = v , S[v][i] = F[v][i] = -N;
		return ;
	}

	vector < pair < int , int > > V;
	for(int u : adj[v]) {
		adj[u].erase(find(adj[u].begin() , adj[u].end() , v));
		d[u] = d[v] + 1;
		dfs(u);
		if(d[Mxd[u]] > d[Mxd[v]])
			Mxd[v] = Mxd[u];
		Sz[v] += Sz[u];
		V.push_back(make_pair(dp[u] , u));
	}
	sort(V.begin() , V.end());
	sort(adj[v].begin() , adj[v].end() , CMP);
	dp[v] = N;
	for(int u : adj[v]) {
		int xx = V.back().first + 1;
		if(u == V.back().second)
			xx = (sz > 1 ? (V[sz - 2].first + 1) : -N);
		int cost = xx;
		if(H[u][0] != u)
			cost = max(cost , S[u][0] + 2);
		int h2 = H[u][0];
		if(u != h2)
			cost = max(cost , F[h2][0] + 2);
		int dw = H[u][LOG - 1];
		cost = max(cost , (int)ceil(log2(d[dw] - d[v])) + 1);
		if(cost <= dp[v]) {
			dp[v] = cost;
			S[v][0] = xx - 1;
			H[v][0] = u;
			for(int i = 1;i < LOG;++ i)
				S[v][i] = max(S[v][i - 1] , S[H[v][i - 1]][i - 1]),H[v][i] = H[H[v][i - 1]][i - 1];
			F[v][0] = max(S[v][0] + 1 , F[H[v][0]][1] + 1);
			for(int i = 1;i < LOG;++ i) {
				F[v][i] = max(S[v][i] + 1 , (i < LOG - 1 ? F[H[v][i]][i + 1] + 1 : -N));
			}
		}
	}


}
inline void Test() {
	scanf("%d" , & n);
	for(int v , u , i = 1;i < n;++ i)
		scanf("%d %d" , & v , & u) , adj[v].push_back(u) , adj[u].push_back(v);
	dfs(1);
   printf("%d\n" , dp[1]);

	for(int i = 1;i <= n;++ i)
			dp[i] = d[i] = Sz[i] = Mxd[i] = 0 , adj[i].clear();
	for(int i = 0;i <= n;++ i)
		for(int j = 0;j < LOG;++ j)
			H[i][j] = F[i][j] = S[i][j] = 0;
}
int main() {
	int T;
	scanf("%d" , & T);
	while(T --)
		Test();
	return 0;
}
