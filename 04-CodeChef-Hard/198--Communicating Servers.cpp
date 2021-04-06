#include <cstdio>

int read() {
  static int c, x;
  while ((c = getchar()) < 48) {}
  x = c ^ 48;
  while ((c = getchar()) >= 48) x = (((x << 2) + x) << 1) + (c ^ 48);
  return x;
}

#define MAXN 50
#define MAXM 210

struct edge {
  int f, t, c;
} e[MAXM];

int n, m;
int fa[MAXN];
int b[MAXM], q[MAXM], lst[MAXM];
bool vis[MAXM];

int findf(const int &x) {
  return fa[x] ? (fa[x] = findf(fa[x])) : x;
}

void build() {
  for (int i = 1; i <= n; ++i) fa[i] = 0;
  for (int i = 1; i <= m; ++i)
    if (vis[i]) fa[findf(e[i].f)] = findf(e[i].t);
}

int main() {
  for (int T = read(); T--; ) {
    n = read();
    m = read();
    const int k = read();
    for (int i = 1; i <= k; ++i) b[i] = read();
    for (int i = 1; i <= m; ++i) {
      vis[i] = false;
      e[i].f = read();
      e[i].t = read();
      e[i].c = read();
    }
    int ans = 0;
    while (true) {
      build();
      int hd = 1, tl = 0, t = 0;
      for (int i = 1; i <= m; ++i) {
        lst[i] = 0;
        if (!vis[i] && findf(e[i].f) != findf(e[i].t)) {
          lst[i] = -1;
          q[++tl] = i;
        }
      }
      while (hd <= tl) {
        const int x = q[hd++];
        if (vis[x]) {
          vis[x] = false;
          build();
          vis[x] = true;
          for (int y = 1; y <= m; ++y) {
            if (!lst[y] && !vis[y] && findf(e[y].f) != findf(e[y].t)) {
              q[++tl] = y;
              lst[y] = x;
            }
          }
        } else {
          if (b[e[x].c]) {
            t = x;
            break;
          }
          for (int y = 1; y <= m; ++y) {
            if (!lst[y] && vis[y] && (b[e[x].c] || e[x].c == e[y].c)) {
              q[++tl] = y;
              lst[y] = x;
            }
          }
        }
      }
      if (!t) break;
      ++ans;
      while (~t) {
        if (vis[t]) {
          vis[t] = false;
          ++b[e[t].c];
        } else {
          vis[t] = true;
          --b[e[t].c];
        }
        t = lst[t];
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
