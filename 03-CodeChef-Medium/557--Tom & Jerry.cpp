#include <bits/stdc++.h>
#define WRAP
#ifdef WRAP
  using namespace std;
  #define sim template < class c
  #define ris return * this
  #define dor > debug & operator <<
  #define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
  sim > struct rge { c b, e; };
  sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
  sim > auto dud(c* x) -> decltype(cerr << *x, 0);
  sim > char dud(...);
  struct debug {
  #ifdef LOCAL
  ~debug() { cerr << endl; }
  eni(!=) cerr << boolalpha << i; ris; }
  eni(==) ris << range(begin(i), end(i)); }
  sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
  }
  sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
  }
  #else
  sim dor(const c&) { ris; }
  #endif
  };
  #define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
  #define deb debug()
  #define ll long long
#endif
using namespace std;

const int N = 1e5 + 5;
const int M = 18;
vector<int> tab[N];
bool met[N];
int j[N][M];
int down[N];
int up[N];
int tim;
int in[N];
int out[N];
int gb[N];

void dfs1(int w, int par) {
  met[w] = 1;
  j[w][0] = par;
  for (int v : tab[w]) {
    if (met[v]) continue;
    dfs1(v, w);
  }   
}

int dfs2(int w) { 
  met[w] = 1;
  for (int v : tab[w]) {
    if (met[v]) continue;
    down[w] = max(down[w], dfs2(v) + 1);
  }   
  return down[w];
}

void dfs3(int w, int above, int par) {
  met[w] = 1;
  up[w] = above;
  vector<pair<int, int>> vec;
  vec.push_back({above, par});
  for (int v : tab[w]) {
    if (v == par) continue;
    vec.push_back({down[v], v});
  }
  sort(vec.begin(), vec.end());
  reverse(vec.begin(), vec.end());

  for (int v : tab[w]) {
    if (v == par) continue;
    if (v == vec[0].second) {
      if (vec.size() > 1) {
        dfs3(v, vec[1].first + 1, w);
      } else {
        dfs3(v, 0, w);
      }
    } else {
      dfs3(v, vec[0].first + 1, w);
    }
  }
}

void dfs4(int w) {
  met[w] = 1;
  in[w] = ++tim;
  for (int v : tab[w]) {
    if (met[v]) continue;
    gb[v] = gb[w] + 1;
    dfs4(v);
  }
  out[w] = ++tim;
}

bool anc(int x, int y) {
  return in[x] <= in[y] && out[y] <= out[x];
}

int query(int x, int y) {
  if (x == y) return x;
  if (gb[x] > gb[y]) swap(x, y);
  if (anc(x, y)) return x;
  for (int i = M - 1; i >= 0; i--) {
    if (!anc(j[x][i], y)) x = j[x][i];
  }
  return j[x][0];
}

int jump(int x, int k) {
  for (int i = M - 1; i >= 0; i--) {
    if ((1 << i) <= k) {
      x = j[x][i];
      k -= (1 << i);
    }
  }
  return x;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, q;
    cin >> n >> q;
    for (int a = 1; a <= n; a++) tab[a].clear();
    for (int a = 1; a < n; a++) {
      int x, y;
      cin >> x >> y;
      tab[x].push_back(y);
      tab[y].push_back(x);
    }

    for (int a = 1; a <= n; a++) met[a] = 0;
    dfs1(1, 1);
    for (int i = 1; i < M; i++) {
      for (int a = 1; a <= n; a++) {
        j[a][i] = j[j[a][i - 1]][i - 1];
      }
    }

    for (int a = 1; a <= n; a++) met[a] = 0;
    for (int a = 1; a <= n; a++) down[a] = 0;
    dfs2(1);

    for (int a = 1; a <= n; a++) met[a] = 0;
    for (int a = 1; a <= n; a++) up[a] = 0;
    dfs3(1, -1, -1);

    for (int a = 1; a <= n; a++) met[a] = 0;
    for (int a = 1; a <= n; a++) gb[a] = 0;
    for (int a = 1; a <= n; a++) in[a] = 0;
    for (int a = 1; a <= n; a++) out[a] = 0;
    dfs4(1);

    for (int a = 1; a <= q; a++) {
      int x, y;
      cin >> x >> y;
      if (x == y) {
          cout << 0 << endl;
          continue;
      }
      int lca = query(x, y);
      int dy = gb[y] - gb[lca];
      int dx = gb[x] - gb[lca];
      int d = dx + dy;
      int dback = (d - 1) / 2;
      int ystop;
      int ans;
      // cout << endl << x << " " << y << endl;
      if (dy <= dback) {
        int xstop = jump(x, d - dback - 1);
        // cout << "xstop " << xstop << endl;
        ans = d - dback + up[xstop];
      } else if (dy > dback) {
        ystop = jump(y, dback);
        ans = (d - dback) + down[ystop];
      }

      // cout << "lca " << lca << endl;
      // cout << "ystop " << ystop << endl;
      // cout << "ans " << ans << endl;

      cout << ans << endl;
    }
  }
  return 0;
}