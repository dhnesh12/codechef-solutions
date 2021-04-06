#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0); int t; cin >> t;
    while (t--){int n, m;cin >> n >> m;vector<vector<int>> graph(n + 1);vector<int> cnt(n + 1, 0);
        int u, v; int mx = 0;
        for (int i = 0; i < m; i++){cin >> u >> v;graph[u].push_back(v);graph[v].push_back(u);cnt[u]++;cnt[v]++;
            mx = max(mx, cnt[u]);mx = max(mx, cnt[v]);}
        if (mx == 2){for (int u = 1; u <= n; u++){if (cnt[u] == 2){int v1 = graph[u][0], v2 = graph[u][1];
                    for (auto v : graph[v1]){if (v == v2){mx = 3; break;}}}}}cout << mx << endl;}}