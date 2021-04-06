#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <assert.h>

using namespace std;

#define debug(x) cout << #x << ": " << x << endl

using ll = long long;

template<typename T1, typename T2> bool chkmin(T1 &x, T2 y) { return y < x ? (x = y, true) : false; };
template<typename T1, typename T2> bool chkmax(T1 &x, T2 y) { return y > x ? (x = y, true) : false; };

struct triple {
  int first, second, third;

  triple() {}
  triple(int _first, int _second, int _third): first(_first), second(_second), third(_third) {}
};

const int INF = 1e9 + 1337;
const int logN = 20;
const int maxN = 300099;

int N, Q;
int par[maxN];
int a[maxN];
vector<int> G[maxN];
int tin[maxN];
int tout[maxN];
int up[maxN];
int down1[maxN];
int down2[maxN];
int big[maxN];
int furthest[maxN];
int ord[2 * maxN];
int H[maxN];

bool parent(int u, int v) {
  if (u == -1) {
    return false;
  }
  return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int timer = 0;
void dfs0(int v) {
  ord[tin[v] = timer++] = v;
  big[v] = -1;
  for (int &u : G[v]) {
    H[u] = H[v] + 1;
    dfs0(u);
    if (down1[u] + 1 >= down1[v]) {
      big[v] = u;
      down2[v] = down1[v];
      down1[v] = down1[u] + 1;
    } else {
      chkmax(down2[v], down1[u] + 1);
    }
    ord[timer++] = v;
  }
  tout[v] = timer - 1;
}

void dfs1(int v) {
  furthest[v] = max(up[v], down1[v]);
  for (int &u : G[v]) {
    chkmax(up[u], up[v] + 1);
    if (down1[u] + 1 < down1[v]) {
      chkmax(up[u], down1[v] + 1);
    } else {
      chkmax(up[u], down2[v] + 1);
    }
    dfs1(u);
  }
}

namespace spt {
  int t[logN][2 * maxN];
  int lg[2 * maxN];
  
  void build() {
    lg[1] = 0;
    int nxt = 2;
    for (int i = 2; i <= timer; ++i) {
      lg[i] = lg[i - 1];
      if (i == nxt) {
        lg[i]++;
        nxt <<= 1;
      }
    }
    for (int i = 0; i < timer; ++i) {
      t[0][i] = ord[i];
    }
    for (int j = 1; j <= lg[timer]; ++j) {
      for (int i = 0; i + (1 << j) - 1 < timer; ++i) {
        int d = i + (1 << (j - 1));
        if (H[t[j - 1][i]] < H[t[j - 1][d]]) {
          t[j][i] = t[j - 1][i];
        } else {
          t[j][i] = t[j - 1][d];
        }
      }
    }
  }

  int gt(int l, int r) {
    int j = lg[r - l + 1];
    int v1 = t[j][l];
    int v2 = t[j][r + 1 - (1 << j)];
    if (H[v1] < H[v2]) {
      return v1;
    } else {
      return v2;
    }
  }
}

int lca(int u, int v) {
  int L = tin[u];
  int R = tin[v];
  if (L > R) {
    swap(L, R);
  }
  return spt::gt(L, R);
}



namespace cht {
  struct line {
    int k, b;
    
    line(): k(-INF), b(-INF) {}
    line(int _k, int _b): k(_k), b(_b) {}

    ll y(int x) {
      return k * (ll)x + b;
    }
  };

  double intersect(line A, line B) {
    return (A.b - B.b) / (double)(B.k - A.k);
  }
  
  int X;
  int rx[maxN];
  line ln[4 * maxN];
  vector< pair<line&, line> > mem;

  void init() {
    sort(rx, rx + X);
    X = unique(rx, rx + X) - rx;
  }

  void add(int k, int b) {
    line L(k, b);
    for (int v = 1, vl = 0, vr = X - 1; ;) {
      int vm = (vl + vr) >> 1;
      if (L.y(rx[vm]) > ln[v].y(rx[vm])) {
        mem.emplace_back(ln[v], ln[v]);
        swap(L, ln[v]);
      }
      if (vl == vr) {
        break;
      }
      if (intersect(L, ln[v]) <= rx[vm]) {
        v <<= 1;
        vr = vm;
      } else {
        v <<= 1;
        v |= 1;
        vl = vm + 1;
      }
    }
  }

  ll gt(int x) {
    ll ans = 0;
    for (int v = 1, vl = 0, vr = X - 1; ;) {
      chkmax(ans, ln[v].y(x));
      if (vl == vr) {
        break;
      }
      int vm = (vl + vr) >> 1;
      if (x <= rx[vm]) {
        v <<= 1;
        vr = vm;
      } else {
        v <<= 1;
        v |= 1;
        vl = vm + 1;
      }
    }
    return ans;
  }

  void backtrack(int sz) {
    while (mem.size() > sz) {
      mem.back().first = mem.back().second;
      mem.pop_back();
    }
  }
}





int T = 0;
pair<int, int> qr[maxN];
ll ans[maxN];
vector<int> vtx[4 * maxN];

void _addv(int v, int vl, int vr, int l, int r, int u) {
  if (l > r || vr < l || r < vl) {
    return;
  }
  if (l <= vl && vr <= r) {
    vtx[v].push_back(u);
    return;
  }
  int vm = (vl + vr) >> 1;
  _addv(v << 1, vl, vm, l, r, u);
  _addv(v << 1 | 1, vm + 1, vr, l, r, u);
}

void addv(int v, int l, int r) {
  if (l > r) {
    return;
  }
  _addv(1, 0, T - 1, l, r, v);
}

int V[2 * maxN];
int st[maxN];
int p[maxN];
bool active[maxN];
int cnt[maxN];
int head[maxN];
int que[maxN];
vector<int> tree[maxN];

void dfs2(int i) {
  int v = V[i];
  int stk_sz = cht::mem.size();
  if (p[i] != -1 && active[V[p[i]]]) {
    int u = V[p[i]];
    ll d = up[u];
    if (parent(big[u], v)) {
      chkmax(d, down2[u]);
    } else {
      chkmax(d, down1[u]);
    }
    cht::add(d, a[V[p[i]]]);
  }
  for (int l = head[v]; l < head[v] + cnt[v]; ++l) {
    int q = que[l];
    assert(qr[q].first == v);
    chkmax(ans[q], cht::gt(qr[q].second));
  }
  for (int &j : tree[i]) {
    dfs2(j);
  }
  cht::backtrack(stk_sz);
}

void solve(int v, int vl, int vr) {
  for (int i = 0; i < vtx[v].size(); ++i) {
    active[vtx[v][i]] = true;
  }
  copy(vtx[v].begin(), vtx[v].end(), V);
  int sz = vtx[v].size();
  for (int i = vl; i <= vr; ++i) {
    int u = qr[i].first;
    V[sz++] = u;
  }
  sort(V, V + sz, [&](int u, int v) -> bool {
    return tin[u] < tin[v];
  });
  sz = unique(V, V + sz) - V;
  int _sz = sz;
  for (int i = 0; i + 1 < _sz; ++i) {
    int c = lca(V[i], V[i + 1]);
    if (c != V[i] && c != V[i + 1]) {
      V[sz++] = c;
    }
  }
  sort(V, V + sz, [&](int u, int v) -> bool {
    return tin[u] < tin[v];
  });
  sz = unique(V, V + sz) - V;

  for (int i = 0; i < sz; ++i) {
    tree[i].clear();
  }
  int ptr = 0;
  p[0] = -1;
  for (int i = 0; i < sz; ++i) {
    while (ptr > 0 && !parent(V[st[ptr - 1]], V[i])) {
      --ptr;
    }
    if (ptr > 0) {
      p[i] = st[ptr - 1];
      tree[p[i]].push_back(i);
    }
    st[ptr++] = i;
  }

  for (int i = vl; i <= vr; ++i) {
    int u = qr[i].first;
    ++cnt[u];
  }
  head[V[0]] = 0;
  for (int i = 1; i < sz; ++i) {
    head[V[i]] = head[V[i - 1]] + cnt[V[i - 1]];
  }
  for (int i = vl; i <= vr; ++i) {
    que[head[qr[i].first]++] = i;
  }
  for (int i = 0; i < sz; ++i) {
    head[V[i]] -= cnt[V[i]];
  }

  dfs2(0);

  for (int i = vl; i <= vr; ++i) {
    int u = qr[i].first;
    --cnt[u];
  }
  for (int i = 0; i < vtx[v].size(); ++i) {
    active[vtx[v][i]] = false;
  }

  if (vl < vr) {
    int vm = (vl + vr) >> 1;
    solve(v << 1, vl, vm);
    solve(v << 1 | 1, vm + 1, vr);
  }
}

int32_t main() {
#ifdef DEBUG
  freopen("in", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> N >> Q;
  for (int v = 2; v <= N; ++v) {
    cin >> par[v];
    G[par[v]].push_back(v);
  }
  for (int v = 1; v <= N; ++v) {
    cin >> a[v];
  }
  dfs0(1);
  dfs1(1);
  spt::build();
  T = 0;
  vector<int> last(N + 1, 0);
  vector<triple> _addv;
  for (int i = 0; i < Q; ++i) {
    char cmd;
    int v;
    cin >> cmd >> v;
    if (cmd == '?') {
      qr[T].first = v;
      cin >> qr[T++].second;
      cht::rx[cht::X++] = qr[T - 1].second;
      if (last[v] != -1) {
        chkmax(ans[T - 1], a[v] + qr[T - 1].second * (ll)furthest[v]);
      } else {
        chkmax(ans[T - 1], a[v]);
      }
    } else {
      if (last[v] != -1) {
        _addv.emplace_back(v, last[v], T - 1);
        last[v] = -1;
      } else {
        last[v] = T;
      }
    }
  }
  cht::init();
  for (auto &e : _addv) {
    addv(e.first, e.second, e.third);
  }
  for (int v = 1; v <= N; ++v) {
    if (last[v] != -1) {
      addv(v, last[v], T - 1);
    }
  }
  solve(1, 0, T - 1);
  for (int t = 0; t < T; ++t) {
    cout << ans[t] << '\n';
  }
  
  return 0;
}