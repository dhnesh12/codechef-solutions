#include <bits/stdc++.h>
const int MAXN = 1e5;
const int P = 1e9 + 7;
using namespace std;

int ans, cnt, n, m;

struct Dsu {
  int fa[MAXN + 5];

  void init(const int n) {
    for (int i = 1; i <= n; ++i) fa[i] = i;
  }
  int find(int x) {
    return fa[x] == x ? fa[x] : fa[x] = find(fa[x]);
  }
  void unionSet(int x, int y) {
    int p = find(x), q = find(y);
    if (p == q) return;
    fa[p] = q, ++cnt;
  }
} D;

void init() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  D.init(n);
}

int main() {
#ifdef forever23
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif
  init();

  for (int i = 1; i <= m; ++i) {
    int l, r; cin >> l >> r;
    D.unionSet(l, r + 1);
  }

  int ans = 1;
  for (int i = 1; i <= cnt; ++i) ans = 1LL * ans * 2 % P;
  cout << ans << endl;
  return 0;
}