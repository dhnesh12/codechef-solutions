#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> pii;

#define x first
#define y second

const int N = 1000010;
const int INF = 1e9 + 5;
const int MOD = 998244353;

int id[69][69];
pii costs[] = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
inline pii mul (pii a, pii b) {return pii(a.x * b.x - a.y * b.y, a.x * b.y + b.x * a.y);}

bitset <N> vis, srcReach, snkReach;
vector <pii> g[N], h[N], dag[N], revDAG[N];
int t, n, m, src, snk, dist[N], st[N], top, col[N], cur, comp[N], dp[N];

int bigMod (int a, int e) {
  int ret = 1;
  while (e) {
    if (e & 1) ret = (long long) ret * a % MOD;
    a = (long long) a * a % MOD, e >>= 1;
  }
  return ret;
}

void go (int u) {
  vis[u] = 1;
  for (auto it : g[u]) {
    int v = it.x, w = it.y;
    if (!vis[v]) go(v);
  }
  st[top++] = u;
}

void bacw (int u) {
  col[u] = cur;
  for (auto it : h[u]) {
    int v = it.x, w = it.y;
    if (col[v] == -1) bacw(v);
  }
}

void srcDFS (int u) {
  srcReach[u] = 1;
  for (auto it : dag[u]) if (!srcReach[it.x]) srcDFS(it.x);
}

void snkDFS (int u) {
  snkReach[u] = 1;
  for (auto it : revDAG[u]) if (!snkReach[it.x]) snkDFS(it.x);
}

void dfs (int u) {
  dp[u] = -INF, vis[u] = 1;
  if (u == col[snk]) dp[u] = 0;
  for (auto it : dag[u]) {
    int v = it.x, w = it.y;
    if (!vis[v]) dfs(v); 
    dp[u] = max(dp[u], w + dp[v]);
  }
}

int main() {
  for (int i = 0; i < 9; ++i) id[costs[i].x + 1][costs[i].y + 1] = i;
  cin >> t;
  while (t--) {
    scanf("%d %d %d %d", &n, &m, &src, &snk);
    --src, --snk;
    for (int i = 0; i <= 9 * n; ++i) g[i].clear(), h[i].clear(), dag[i].clear(), revDAG[i].clear();
    while (m--) {
      int u, v; pii w, cur(0, 0);
      scanf("%d %d %d %d", &u, &v, &w.x, &w.y);
      --u, --v;
      int gcd = __gcd(abs(w.x), abs(w.y));
      if (gcd == 2) ++cur.y, w.x /= gcd, w.y /= gcd;
      for (int i = 0; i < 9; ++i) {
        pii prod = mul(w, costs[i]), tmp = cur;
        gcd = __gcd(abs(prod.x), abs(prod.y));
        if (gcd == 2) ++tmp.y, prod.x /= gcd, prod.y /= gcd;
        tmp.x = v + id[prod.x + 1][prod.y + 1] * n;
        g[u + i * n].emplace_back(tmp);
        h[tmp.x].emplace_back(u + i * n, tmp.y);
        // cout << u << " " << i << " -----> " << v << " " << id[prod.x + 1][prod.y + 1] << " ----- " << tmp.y << endl;
        assert(tmp.y <= 1);
      }
    }
    for (int i = 0; i <= 9 * n; ++i) vis[i] = 0;
    top = 0; go(src + n);
    if (vis[snk + 2 * n]) {
      src += n, snk += 2 * n, top = cur = 0;
      for (int i = 0; i <= 9 * n; ++i) vis[i] = comp[i] = srcReach[i] = snkReach[i] = 0, col[i] = -1;
      for (int i = 0; i < 9 * n; ++i) if (!vis[i]) go(i);
      for (int i = top - 1; i >= 0; --i) if (col[st[i]] == -1) ++cur, bacw(st[i]);
      for (int i = 0; i < 9 * n; ++i) for (auto it : g[i]) {
        int j = it.x, w = it.y;
        if (col[i] ^ col[j]) dag[col[i]].emplace_back(col[j], w), revDAG[col[j]].emplace_back(col[i], w);
        else comp[col[i]] += w;
      }
      int inf = 0;
      srcDFS(col[src]); snkDFS(col[snk]);
      for (int i = 1; i <= cur; ++i) if (srcReach[i] and snkReach[i] and comp[i]) {
        inf = 1; break;
      }
      if (inf) {
        puts("NEGATIVE INFINITY");
        continue;
      }
      for (int i = 0; i <= 9 * n; ++i) vis[i] = 0;
      dfs(col[src]);
      assert(dp[col[src]] < INF);
      int ans = bigMod(2, dp[col[src]]);
      if (ans) ans = MOD - ans;
      printf("%d\n", ans);
    } else if (vis[snk]) {
      puts("0");
    } else if (vis[snk + n]) {
      deque <int> dq({src + n});
      for (int i = 0; i <= 9 * n; ++i) dist[i] = INF;
      dist[src + n] = 0;
      while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();
        for (auto it : g[u]) {
          int v = it.x, w = it.y;
          if (dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            if (w) dq.emplace_back(v); 
            else dq.emplace_front(v);
          }
        }
      }
      assert(dist[snk + n] < INF);
      int ans = bigMod(2, dist[snk + n]);
      printf("%d\n", ans);
    } else {
      puts("NEGATIVE");
    }
  }
  return 0;
}