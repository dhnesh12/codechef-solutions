#include <bits/stdc++.h>
 
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
#define pb push_back
 
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef double ld;
typedef pair<ll, ll> pll;

struct edge {
	int from, to;
};

vector<edge> edges;
vector<bool> used;
vector<vector<int> > g;
vector<bool> vis;

void dfs1(int v) {
	vis[v] = true;
	for (int e : g[v]) {
		int u = edges[e].to;
		if (!vis[u]) {
			dfs1(u);
		}
	}
}

vector<int> ptr;

void dfs2(int v) {
	while (ptr[v] != sz(g[v])) {
		int e = g[v][ptr[v]];
		++ptr[v];
		if (used[e] || used[e ^ 1]) {
			continue;
		}
		int u = edges[e].to;
		used[e] = true;
		dfs2(u);
	}
}

int main()
{
 
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    //freopen("input.txt", "r", stdin);
                                               
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    g.resize(n);
    vis.assign(n, false);
    for (int i = 0; i < m; ++i) {
    	int u, v;
    	cin >> u >> v;
    	--u, --v;
    	g[u].pb(sz(edges));
    	edges.pb({u, v});
    	g[v].pb(sz(edges));
    	edges.pb({v, u});
    	used.pb(false);
    	used.pb(false);
    }

    dfs1(0);
    for (int i = 0; i < n; ++i) {
    	if (!vis[i] || g[i].size() % 2 == 1) {
    		cout << "NO\n";
    		return 0;
    	}
    }

    cout << "YES\n";
    ptr.assign(n, 0);
    dfs2(0);

    for (int i = 0; i < 2 * m; ++i) {
    	if (used[i]) {
    		cout << edges[i].from + 1 << " " << edges[i].to + 1 << "\n";
    	}
    }

}                 
