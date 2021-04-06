#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct dinic {
  struct edge {
    ll j, f, c, r;
  };
  int n;
  vector<int> l, p;
  vector<vector<edge>> e;
  dinic(int n) : n(n), e(n) {}
  void addEdge(int i, int j, ll c) {
    e[i].push_back({j, 0, c, e[j].size() + (i == j)});
    e[j].push_back({i, 0, 0, e[i].size() - 1});
  }
  ll dfs(int i, int t, ll f) {
    if (i == t || !f)
      return f;
    for (int &j = p[i]; j < e[i].size(); j++) {
      edge &ed = e[i][j];
      if (l[ed.j] == l[i] + 1)
        if (ll r = dfs(ed.j, t, min(f, ed.c - ed.f))) {
          ed.f += r; e[ed.j][ed.r].f -= r;
          return r;
        }
    }
    return 0;
  }
  ll maxFlow(int s, int t) {
    ll f = 0;
    do {
      l = p = vector<int>(n);
      l[s] = 1;
      queue<int> q;
      q.push(s);
      while (!q.empty() && !l[t]) {
        int i = q.front(); q.pop();
        for (edge &ed : e[i])
          if (l[ed.j] == 0 && ed.c > ed.f)
            l[ed.j] = l[i] + 1, q.push(ed.j);
      }
      while (ll r = dfs(s, t, LLONG_MAX))
        f += r;
    } while (l[t]);
    return f;
  }
};

const ll inf = 1LL << 30;

int main() {
  int n, m, k, e, a, b;
  cin >> n >> m;
  dinic d(n * (m + 1) + 2);
  for (int i = 0; i < n; i++) {
    d.addEdge(0, 2 + i, inf);
    d.addEdge(2 + i + n * m, 1, inf);
    for (int j = 0; j < m; j++) {
      cin >> e;
      if (e == -1)
        e = inf;
      else
        e = 100 - e;
      d.addEdge(2 + i + n * j, 2 + i + n * (j + 1), e);
    }
  }
  cin >> k;
  for (int i = 0; i < k; i++) {
    cin >> a >> b, a--, b--;
    for (int j = 0; j < m; j++)
      d.addEdge(2 + a + n * j, 2 + b + n * (j + 1), inf);
  }
  ll r = 100 * n - d.maxFlow(0, 1);
  cout << fixed << setprecision(2) << (long double) r / n << "\n";
}
