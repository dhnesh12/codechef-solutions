#include <bits/stdc++.h>
using namespace std;
// incomplete
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int MAXN = 1e5+7;

typedef struct{
	bool isb = false;
	int u, v;
} edge;
vector<edge> es;
vector<vector<pair<int, int>>> adj;
int n, m;

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (auto e : adj[v]) {
    	int to = e.first;
    	int br = e.second;
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                es[br].isb = true;
        }
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(n+1, false);
    tin.assign(n+1, -1);
    low.assign(n+1, -1);
    for (int i = 1; i < n+1; ++i) {
        if (!visited[i])
            dfs(i);
    }
}

bool dfs2(int v, int p, int mm){
	visited[v] = true;
	for (auto e : adj[v]) {
    	int to = e.first;
        if (to == p || to == mm) continue;
        if (visited[to]) {
            return false;
        } else {
            if (!dfs2(to, v, mm)){
            	return false;
            }
        }
    }
    return true;
}

bool acyclic(int mm){
	visited.assign(n+1, 0);
	rep(i,1,n+1){
		if (!visited[i] && i!=mm){
			if(!dfs2(i,-1,mm)) return false;
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t;
	cin >> t;
	while(t--){
		es.clear();
		adj.clear();
		// int n, m;
		cin >> n >> m;
		adj.resize(n+1);
		rep(i,0,m){
			int a, b;
			cin >> a >> b;
			es.push_back({false, a, b});
			adj[a].push_back({b, sz(es)-1});
			adj[b].push_back({a, sz(es)-1});
		}
		if (acyclic(0)){
			cout << -1 << endl;
			continue;
		}

		find_bridges();
		// adj.clear();
		// adj.resize(n+1);
		vi n_edge(n+1, 0);
		int mm = 0;
		rep(i,0,m){
			if (es[i].isb == false){
				int a = es[i].u;
				int b = es[i].v;
				n_edge[a]++;
				n_edge[b]++;
				// printf("%d %d\n%d %d\n", a, n_edge[a], b, n_edge[b]);
				if ( (n_edge[a] > n_edge[mm]) || (n_edge[a]==n_edge[mm] && a<mm)){
					mm = a;
				}
				if ((n_edge[b] > n_edge[mm]) || (n_edge[b]==n_edge[mm] && b<mm)){
					mm = b;
				}
			}
		}
		if (acyclic(mm)) cout << mm << endl;
		else cout << -1 << endl;
	}
}
