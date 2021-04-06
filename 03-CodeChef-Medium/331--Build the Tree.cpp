#include <bits/stdc++.h>
#define int long long
#define all(v) v.begin(),v.end()
#define endl "\n"
#ifdef Raghav
  #include "Raghav.h"
#else
  #define dbg(...) 42
#endif
using namespace std;
struct Edge {
  int from, to, capacity, cost;
  Edge(int a, int b, int c, int d) {
    from = a; to = b;
    capacity = c; cost = d;
  }
};
vector<vector<int>> adj, cost, capacity;
const int INF = 1e9;
void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
  d.assign(n, INF);
  d[v0] = 0;
  vector<bool> inq(n, false);
  queue<int> q;
  q.push(v0);
  p.assign(n, -1);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    inq[u] = false;
    for (int v : adj[u]) {
      if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
        d[v] = d[u] + cost[u][v];
        p[v] = u;
        if (!inq[v]) {
          inq[v] = true;
          q.push(v);
        }
      }
    }
  }
}
int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t) {
  adj.assign(N, vector<int>());
  cost.assign(N, vector<int>(N, 0));
  capacity.assign(N, vector<int>(N, 0));
  for (Edge e : edges) {
    adj[e.from].push_back(e.to);
    adj[e.to].push_back(e.from);
    cost[e.from][e.to] = e.cost;
    cost[e.to][e.from] = -e.cost;
    capacity[e.from][e.to] = e.capacity;
  }
  int flow = 0;
  int cost = 0;
  vector<int> d, p;
  while (flow < K) {
    shortest_paths(N, s, d, p);
    if (d[t] == INF) {
      break;
    }
    int f = K - flow;
    int cur = t;
    while (cur != s) {
      f = min(f, capacity[p[cur]][cur]);
      cur = p[cur];
    }
    flow += f;
    cost += f * d[t];
    cur = t;
    while (cur != s) {
      capacity[p[cur]][cur] -= f;
      capacity[cur][p[cur]] += f;
      cur = p[cur];
    }
  }
  if (flow < K) {
    return -1;
  } else {
    return cost;
  }
}
class Task {
 private:
  int n, q;
  vector<int> a;
  vector<vector<int>> v;
  vector<int> subtree;
  void init(int cur, int par) {
    for (auto &child : v[cur]) {
      if (child != par) {
        init(child, cur);
        ++subtree[cur];
      }
    }
  }
  void Read() {
    cin >> n;
    a = vector<int>(n + 1, 0LL);
    subtree = vector<int>(n + 1, 0LL);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    v.resize(n + 1);
    for (int i = 1; i < n; i++) {
      int x, y; cin >> x >> y;
      v[x].push_back(y);
      v[y].push_back(x);
    }
    init(1, 0);
    cin >> q;
  }
  void Solve() {
    vector<tuple<int, int>> info;
    for (int i = 1; i <= n; i++) {
      info.push_back(make_tuple(a[i], subtree[i]));
    }
    sort(info.begin(), info.end());
    int smallest = get<0>(info[0]);
    for (int tt = 1; tt <= q; tt++) {
      int m, x, y; cin >> m >> x >> y;
      vector<Edge> edges;
      vector<int> val(m);
      for (auto &i : val) {
        cin >> i;
      }
      int max_vertices = 1 + m + m + m + m + 1;
      int S = 0, T = max_vertices;
      for (int i = 0; i < m; i++) {
        edges.push_back(Edge(S, 1 + i, 1, 0));
      }
      int count = 0;
      for (auto &i : info) {
        int subtree = get<1>(i);
        int value = get<0>(i);
        if (subtree < x) {
          for (int i = 0; i < m; i++) {
            edges.push_back(Edge(1 + i, 1 + m + count, 1, val[i] * value));
          }
          edges.push_back(Edge(1 + m + count, T, x - subtree, 0));
          count += (x - subtree);
          if (count >= m) {
            break;
          }
        }
      }
      for (int i = 0; i < m; i++) {
        for (int j = 0; j < i; j++) {
          edges.push_back(Edge(1 + i, 1 + m + m + j, 1, val[i] * val[j]));
          edges.push_back(Edge(1 + i, 1 + m + m + m + j, 1, val[i] * val[j]));
        }
        edges.push_back(Edge(1 + m + m + i, T, x, 0));
        edges.push_back(Edge(1 + m + m + m + i, T, m, y));
        edges.push_back(Edge(1 + i, 1 + m + m + m + m, 1, val[i] * smallest));
      }
      edges.push_back(Edge(1 + m + m + m + m, T, m, y));
      cout << min_cost_flow(max_vertices + 1, edges, m, S, T) << endl;
    }
  }
 public:
  void Perform() {
    Read();
    Solve();
  }
};
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  Task t;
  t.Perform();
}