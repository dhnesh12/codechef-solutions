#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>
using namespace std;

const int M = 20;
const int N = 200000 + 100;
int n;
vector<int> vec[N];
vector<int> dis[N];
vector<int> clr[N];
int B;
int fa[N][M];
int dep[N];
vector<int> calculated;

void bfs(int c) {

    if (dis[c].empty()) {
        dis[c].assign(n + 1, N);
        calculated.push_back(c); 
    }

    queue<int> que;
    for (int u: clr[c]) { que.push(u); dis[c][u] = 0; }

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int v: vec[u]) {
            if (dis[c][v] > dis[c][u] + 1) {
                dis[c][v] = dis[c][u] + 1;
                que.push(v);
            }
        }
    }
}

void add(int u, int c) {
    assert(u <= n);
    ++n;
    int v = n;
    vec[v].clear();
    clr[c].push_back(v);
    dep[v] = dep[u] + 1;
    if (u > 0) { 
        vec[u].push_back(v);
        vec[v].push_back(u); 
    }

    for (int c: calculated) {
        dis[c].push_back(dis[c][u] + 1);
    }

    fa[v][0] = u;
    for (int i = 1; i < M; i++) fa[v][i] = fa[fa[v][i-1]][i-1];

}

int get_lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int delta = dep[u] - dep[v];
    for (int i = M - 1; i >= 0; i--) {
        if (delta >> i & 1) {
            u = fa[u][i];
        }
    }

    if (u == v) return u;
    for (int i = M - 1; i >= 0; i--) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int get_dist(int u, int v) {
    int lca = get_lca(u, v);
    return dep[u] + dep[v] - 2 * dep[lca];
}

int query(int u, int c) {

    if (clr[c].empty() && dis[c].empty()) return -1;

    if (clr[c].size() >= B) {
        bfs(c);
        clr[c].clear();
    }

    int ans = N;
    if (!dis[c].empty()) ans = dis[c][u];
    for (int v: clr[c]) {
        ans = min(ans, get_dist(u, v));
    }

    if (ans == N) ans = -1;
    return ans;
}

void solve() {
    n = 0;

    int q, u, v;
    scanf("%d%d", &q, &v);

    B = 400;
    add(0, v);
    
    vector<int> used_color;
    int last_ans = -1;
    char cmd[10];
    for (int i = 0; i < q; i++) {
        scanf("%s%d%d", cmd, &u, &v);
        u ^= (last_ans + 1);
        v ^= (last_ans + 1);
        //cout << "fix " << u << " " << v << endl;
        if (cmd[0] == '+') {
            used_color.push_back(v);
            add(u, v);
        } else {
            last_ans = query(u, v);
            printf("%d\n", last_ans);
        }
    }

    for (int c: used_color) {
        clr[c].clear();
        dis[c].clear();
    }
    calculated.clear();
    //used_color.clear();
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}
