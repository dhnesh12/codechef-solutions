#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 100010
int t, n, m, head[MAXN], to[MAXN << 1], next[MAXN << 1], tot;
inline void $(int u, int v) {
    next[tot] = head[u], to[tot] = v, head[u] = tot++;
    next[tot] = head[v], to[tot] = u, head[v] = tot++;
}

int p[MAXN], qx[MAXN], qy[MAXN], vis[MAXN], res[MAXN], cnt;
inline int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
struct answer {
    int max0, max1;
} ans[MAXN];
inline void update(int x) {
    while (ans[x].max0 >= 1 && find(ans[x].max0) == find(x)) ans[x].max0--;
    ans[x].max1 = ans[x].max0 - 1;
    while (ans[x].max1 >= 1 && find(ans[x].max1) == find(x)) ans[x].max1--;
    if (!ans[x].max1) ans[x].max1 = -1;
    if (!ans[x].max0) ans[x].max0 = -1;
}
inline int $() {
    register int x = 0;
    register char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    return x;
}
int main() {
    t = $();
    while (t--) {
        n = $(), m = $();
        memset(head, -1, sizeof(head));
        memset(vis, 0, sizeof(vis));
        tot = cnt = 0;
        for (int i = 1; i < n; i++) $($(), $());
        for (int i = 1; i <= n; i++) p[i] = i, ans[i] = {n, n - 1 ? n - 1 : -1};
        for (int i = 1; i <= m; i++) {
            qx[i] = $(), qy[i] = $();
            if (qx[i] == 1) {
                if (vis[qy[i]])
                    i--, m--;
                else
                    vis[qy[i]] = 1;
            }
        }
        for (int i = 1; i <= n; i++)
            if (!vis[i]) update(find(i));
        for (int i = 0; i < n - 1; i++) {
            int u = to[i << 1];
            int v = to[i << 1 | 1];
            if (vis[u] || vis[v]) continue;
            int U = find(u), V = find(v);
            p[U] = V;
            if (ans[U].max1 < ans[V].max1) ans[V] = ans[U];
            update(V);
        }
        for (int i = m; i >= 1; i--) {
            if (qx[i] == 1) {
                int x = qy[i];
                vis[x] = 0;
                update(find(x));
                for (int j = head[x]; ~j; j = next[j]) {
                    if (vis[to[j]]) continue;
                    int U = find(x);
                    int V = find(to[j]);
                    p[U] = V;
                    if (ans[U].max1 < ans[V].max1) ans[V] = ans[U];
                    update(V);
                }
            } else {
                int x = qy[i];
                res[++cnt] = ans[find(x)].max1;
            }
        }
        for (int i = cnt; i >= 1; i--) printf("%d\n", res[i]);
    }
    return 0;
}