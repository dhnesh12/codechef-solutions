#include <bits/stdc++.h>

using namespace std;

struct maximum_matching {
  int n, mm = 0, t = 0;
  vector<int> m, l, p, o, v;
  vector<vector<int>> &e;
  queue<int> q;
  maximum_matching(int n, vector<vector<int>> &e) : n(n), m(n, -1), l(n), p(n), o(n), v(n), e(e) {
    for (int i = 0; i < n; i++)
      if (m[i] == -1)
        mm += bfs(i);
  }
  int lca(int i, int j) {
    for (t++; ; swap(i, j))
      if (i != -1) {
        if (v[i] == t)
          return i;
        v[i] = t; i = m[i] == -1 ? -1 : o[p[m[i]]];
      }
  }
  void blossom(int i, int j, int a) {
    while (o[i] != a) {
      p[i] = j; j = m[i];
      if (l[j] == 1)
        l[j] = 0, q.push(j);
      o[i] = o[j] = a; i = p[j];
    }
  }
  bool bfs(int s) {
    for (int i = 0; i < n; i++)
      l[i] = -1, o[i] = i;
    while (!q.empty())
      q.pop();
    l[s] = 0; q.push(s);
    while (!q.empty()) {
      int i = q.front(); q.pop();
      for (int j : e[i])
        if (l[j] == -1) {
          l[j] = 1; p[j] = i;
          if (m[j] == -1) {
            while (j != -1)
              m[j] = p[j], swap(j, m[m[j]]);
            return true;
          }
          l[m[j]] = 0; q.push(m[j]);
        } else if (l[j] == 0 && o[i] != o[j]) {
          int a = lca(o[i], o[j]);
          blossom(i, j, a);
          blossom(j, i, a);
        }
    }
    return false;
  }
};

int main() {
  int t, n, m, a, b;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    vector<vector<int>> e(n);
    for (int i = 0; i < m; i++) {
      cin >> a >> b, a--, b--;
      e[a].push_back(b);
      e[b].push_back(a);
    }
    maximum_matching mm(n, e);
    cout << (2 * mm.mm == n ? "YES\n" : "NO\n");
  }
}
