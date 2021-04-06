#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1010;
const ll INF = 1ll << 61;

int T, n, m, s, t;
vector<tuple<int, int, char>> adj[N];
priority_queue<tuple<ll, int, int>> q;
ll dist[N][N];
int main() {
    ios:: sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
    cin >> T;
    while (T--) {
        ll ans = INF;
        cin >> n >> m >> s >> t, --s, --t;
        for (int i = 0; i < n; i++)
                fill(dist[i], dist[i] + n, INF);
        for (int i = 0, u, v, w; i < m; i++) {
            char c;
            cin >> u >> v >> w >> c;
            adj[--u].push_back({--v, w, c}), adj[v].push_back({u, w, c});
        }
        q.push({0, s, t});
        while (!q.empty()) {
            int v = get<1>(q.top()), u = get<2>(q.top());
            ll w = -get<0>(q.top());
            q.pop();
            if (u == v) {
                ans = min(ans, w);
                continue;
            }
            for (auto x: adj[v]) {
                for (auto y: adj[u]) {
                    if (get<0>(x) == u && get<0>(y) == v)
                        ans = min(ans, w + get<1>(x));
                    else if (get<2>(x) == get<2>(y) && w + get<1>(x) + get<1>(y) < dist[get<0>(x)][get<0>(y)]) {
                        dist[get<0>(x)][get<0>(y)] = w + get<1>(x) + get<1>(y); 
                        q.push({-w - get<1>(x) - get<1>(y), get<0>(x), get<0>(y)});
                    }
                }
            }
        }
        cout << (ans ^ INF? ans: -1) << '\n';
        for (int i = 0; i < n; i++)
            adj[i].clear();
    }
}
