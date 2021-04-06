// 离线 + splay 维护后缀树的 DFS 序
#include <bits/stdc++.h>
#define N 100007
#define Q 500007
using namespace std;

int T, n, m, q, a[N], b[N], d[Q], k[Q], qid[Q], ans[Q];
bool cmq(int u, int v) { return d[u] < d[v]; }

int tot, slink[N * 2], len[N * 2], pos[N * 2], t[N * 2];
map < int, int > trans[N * 2];
int get(int u, int c) {
    if(trans[u].find(c) == trans[u].end()) return -1;
    return trans[u][c];
}
int add(int u, int c) {
    int z = ++ tot;
    slink[z] = -1, len[z] = len[u] + 1;
    trans[z].clear();
    int v = u;
    while(v != -1 && get(v, c) == -1) trans[v][c] = z, v = slink[v];
    if(v == -1) { slink[z] = 0; return z; }
    int x = get(v, c);
    if(len[x] == len[v] + 1) { slink[z] = x; return z; }
    int y = ++ tot;
    slink[y] = slink[x], len[y] = len[v] + 1, pos[y] = pos[x], t[y] = 0;
    trans[y].clear();
    for(auto i: trans[x]) trans[y][i.first] = i.second;
    while(v != -1  && get(v, c) == x) trans[v][c] = y, v = slink[v];
    slink[x] = slink[z] =y;
    return z;
}

int ch[N * 2], pid[N * 2];
bool cmp(int u, int v) { return ch[u] < ch[v]; }
vector <int> E[N * 2];

int idx, px[N * 2], lx[N * 2], rx[N * 2];
void dfs(int u) {
    px[lx[u] = ++ idx] = u;
    for(int v: E[u]) dfs(v);
    rx[u] = idx;
}
int root, parent[N * 2], child[N * 2][2], siz[N * 2], Siz[N * 2];
int build(int l, int r) {
    if(l > r) return -1;
    int mid = (l + r) >> 1;
    int x = px[mid], u = build(l, mid - 1), v = build(mid + 1, r);
    child[x][0] = u, child[x][1] = v, siz[x] = t[x], Siz[x] = 1;
    if(u != -1) siz[parent[u] = x] += siz[u], Siz[x] += Siz[u];
    if(v != -1) siz[parent[v] = x] += siz[v], Siz[x] += Siz[v];
    return px[mid];
}
void push(int x) {
    siz[x] = t[x], Siz[x] = 1;
    if(child[x][0] != -1) siz[x] += siz[child[x][0]], Siz[x] += Siz[child[x][0]];
    if(child[x][1] != -1) siz[x] += siz[child[x][1]], Siz[x] += Siz[child[x][1]];
}
void rot(int x) {
    int y = parent[x], z = parent[y], o = child[y][0] == x ? 0 : 1;
    if(z != -1) child[z][0] == y ? child[z][0] = x : child[z][1] = x;
    parent[x] = z, parent[y] = x;
    if(child[x][o ^ 1] != -1) parent[child[x][o ^ 1]] = y;
    child[y][o] = child[x][o ^ 1], child[x][o ^ 1] = y;
    push(y), push(x);
}
void splay(int x, int u) {
    while(parent[x] != u) {
        int y = parent[x], z = parent[y];
        if(z != u) (child[y][0] == x) ^ (child[z][0] == y) ? rot(x):rot(y);
        rot(x);
    }
    push(x);
    if(u == -1) root = x;
    else push(root);
}
int lst(int x) {
    splay(x, -1);
    int y = child[x][0];
    while(child[y][1] != -1) y = child[y][1];
    return y;
}
int nxt(int x) {
    splay(x, -1);
    int y = child[x][1];
    while(child[y][0] != -1) y = child[y][0];
    return y;
}
int getKth(int x, int K) {
    int cnt = child[x][0] != -1 ? siz[child[x][0]] : 0;
    if(t[x] && K == cnt + 1) return pos[x];
    if(K <= cnt) return getKth(child[x][0], K);
    return getKth(child[x][1], K - cnt - t[x]);
}
int GetKth(int x, int K) {
    int cnt = child[x][0] != -1 ? Siz[child[x][0]] : 0;
    if(K == cnt + 1) return x;
    if(K <= cnt) return GetKth(child[x][0], K);
    return GetKth(child[x][1], K - cnt - 1);
}

int main() {
    scanf("%d", &T);
    while(T -- ) {
        scanf("%d%d%d", &n, &m, &q);
        for(int i = 1; i <= n; ++ i) scanf("%d", &a[i]), b[i] = m - a[i];
        b[n + 1] = m, sort(b + 1, b + n + 2);
        b[0] = unique(b + 1, b + n + 2) - b - 1;
        for(int i = 1; i <= q; ++ i) scanf("%d%d", &d[i], &k[i]), d[qid[i] = i] %= m;
        sort(qid + 1, qid + q + 1, cmq);

        // 后缀自动机
        slink[tot = 0] = -1, len[0] = pos[0] = t[0] = 0;
        trans[0].clear();
        int u = 0;
        for(int i = n; i; -- i) pos[u = add(u, a[i])] = i, t[u] = 1;

        // 后缀树
        for(int i = 1; i <= tot; ++ i) ch[pid[i] = i] = a[pos[i] + len[slink[i]]];
        sort(pid + 1, pid + tot + 1, cmp);
        for(int i = 0; i <= tot; ++ i) E[i].clear();
        for(int i = 1; i <= tot; ++ i) E[slink[pid[i]]].push_back(pid[i]);

        // 伸展树
        idx = 0, dfs(0);
        t[px[++ idx] = ++ tot] = 0;
        parent[root = build(1, idx)] = -1;

        int pi = tot - 1, qi = 1;
        while(qi <= q && d[qid[qi]] < b[1]) {
            ans[qid[qi]] = getKth(root, k[qid[qi]]);
            ++ qi;
        }
        for(int i = 1; i <= b[0]; ++ i) {
            while(pi && m - ch[pid[pi]] == b[i]) {
                int l = pid[pi];
                int u = lst(l), x = slink[l];
                splay(x, -1);
                int v = GetKth(child[x][1], rx[x] - lx[x] + 1);
                if(u == x) { -- pi; continue; }

                // 将子树 x 的 DFS 序上 l 开始的后缀接到 x 后面
                splay(u, -1), splay(v, u);
                int tmp = child[v][0];
                parent[tmp] = child[v][0] = -1;
                push(v), push(u);

                int y = nxt(x);
                splay(x, -1), splay(y, x);
                parent[child[y][0] = tmp] = y;
                push(y), push(x);

                -- pi;
            }
            while(qi <= q && d[qid[qi]] < b[i + 1]) {
                ans[qid[qi]] = getKth(root, k[qid[qi]]);
                ++ qi;
            }
        }
        for(int i = 1; i <= q; ++ i) printf("%d\n", ans[i]);
    }
}
