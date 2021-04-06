#include <bits/stdc++.h>
using namespace std;

const int N = 305;

int tc, n, m, k;
int vi[N];
set<int> g[N];

void Dfs(int step) {
  if (k < 0) return;
  if (step == n) {
    --k;
    return;
  }
  int x = 0;
  for (int i = 1; i <= 2 * n; ++i)
    if (!vi[i] && (!x || g[i].size() < g[x].size())) x = i;
  vi[x] = 1;
  for (int y : g[x]) g[y].erase(x);
  for (int y : g[x]) {
    vi[y] = 1;
    for (int z : g[y]) g[z].erase(y);
    Dfs(step + 1);
    vi[y] = 0;
    for (int z : g[y]) g[z].insert(y);
  }
  vi[x] = 0;
  for (int y : g[x]) g[y].insert(x);
}

int main() {
  for (tc = 1; tc--; ) {
    memset(vi, 0, sizeof vi);
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n * 2; ++i)
      g[i].clear();
    for (int i = 1, x, y; i <= m; ++i) {
      scanf("%d%d", &x, &y);
      g[x].insert(y);
      g[y].insert(x);
    }
    Dfs(0);
    printf(k < 0? "Yes\n" : "No\n");
  }
  return 0;
}
