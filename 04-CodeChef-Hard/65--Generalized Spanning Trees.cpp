#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

typedef long long ll;
const int maxn = 400;
const double eps = 1e-6;
const double inf = 1e20;
double w[maxn][maxn], deg[maxn];
double c[maxn][maxn];
int dcount[maxn + maxn];
int dist[maxn], par[maxn];
int N, M, mid[maxn][maxn];
vector<int> g[maxn], subset;
bool mark[maxn];
int lastSrc;

void add_edge(int a, int b, double cap) {
    if (a < b) {
        if (mid[a][b] == -1) {
            g[a].push_back(b);
            g[b].push_back(a);
            mid[a][b] = 0;
        }
        c[a][b] += cap;
        return;
    }

    int x = mid[a][b] == -1 ? mid[a][b] = N++ : mid[a][b];
    if (c[a][x] == 0 && c[x][a] == 0) {
        g[a].push_back(x);
        g[x].push_back(a);
        g[x].push_back(b);
        g[b].push_back(x);
    }
    c[a][x] += cap;
    c[x][b] += cap;
}

void clear_flow() {
    subset.clear();
    fill_n(mark, maxn, 0);
    fill_n(c[0], maxn*maxn, 0);
    fill_n(dcount, maxn, 0);
    fill_n(mid[0], maxn*maxn, -1);
    for (int i = 0; i < maxn; ++i) g[i].clear();
}

int advance(int v) {
    for (int w : g[v]) {
        if (c[v][w] > eps && dist[v] == dist[w] + 1) {
            par[w] = v;
            return w;
        }
    }
    return -1;
}

int retreat(int v) {
    int old = dist[v];
    --dcount[dist[v]];
    for (int w : g[v]) {
        if (c[v][w] > eps) dist[v] = min(dist[v], dist[w]);
    }
    ++dist[v];
    ++dcount[dist[v]];
    if (dcount[old] == 0) return -1;
    return par[v];
}

double augment(int s, int t) {
    double delta = c[par[t]][t];
    for (int v = t; v != s; v = par[v]) delta = min(delta, c[par[v]][v]);
    for (int v = t; v != s; v = par[v]) {
        c[par[v]][v] -= delta;
        c[v][par[v]] += delta;
    }
    return delta;
}

queue<int> q;
void bfs(int v) {
    fill_n(dist, maxn, -1);
    while (!q.empty()) q.pop();
    q.push(v);
    dist[v] = 0;
    ++dcount[dist[v]];
    while (!q.empty()) {
        v = q.front();
        q.pop();
        for (int w : g[v]) {
            if (c[w][v] > 0 && dist[w] == -1) {
                dist[w] = dist[v] + 1;
                ++dcount[dist[w]];
                q.push(w);
            }
        }
    }
}

double find_flow(int s, int t, int n) {
    bfs(t);
    int v = s;
    par[s] = s;
    double ans = 0;
    while (v != -1 && dist[s] < n) {
        int newv = advance(v);
        if (newv != -1)
            v = newv;
        else
            v = retreat(v);
        if (v == t) {
            v = s;
            ans += augment(s, t);
        }
    }
    return ans;
}

int n, tc;

bool solve(int s, int t) {
    clear_flow(); lastSrc = s;
    for (int v = 0; v < n; ++v) {
        if (v != s && v != t) add_edge(v, t, 1);
        if (v != s) add_edge(s, v, 0.5*deg[v]);

        for (int u = 0; u < v; ++u) {
            if (w[u][v] == 0) continue;
            add_edge(u, v, 0.5*w[u][v]);
            add_edge(v, u, 0.5*w[u][v]);
        }
    }

    double flow = find_flow(s, t, N);

    N = n;
    return flow < n-1-eps;
}

void dfs(int u) {
    mark[u] = 1;
    if (u < n) subset.push_back(u+1);
    for (int v : g[u]) {
        if (c[u][v] > eps && !mark[v]) dfs(v);
    }
}

int main() {
    cin >> tc;
    while (tc--) {
        double sum = 0;
        cin >> N >> M; n = N;
        fill_n(w[0], maxn*maxn, 0);
        fill_n(deg, maxn, 0);

        ll num, den; int u, v;
        for (int i = 0; i < M; ++i) {
            scanf("%d %d %lld/%lld", &u, &v, &num, &den);
            u--; v--;
            w[u][v] = w[v][u] = 1.0*num/den;
            deg[u] += w[u][v];
            deg[v] += w[v][u];
            sum += w[u][v];
        }

        if (abs(sum - n + 1) > eps) {
            cout << 1 << endl << endl; continue; }

        int s = 0, t;
        bool ok = true;
        for (t = 1; t < n && ok; ++t) {
            if (solve(s, t) || solve(t, s)) ok = false;
        }

        if (ok) cout << "GST" << endl;
        else {
            dfs(lastSrc);
            cout << 2 << endl << subset.size() << endl;
            for (int i = 0; i < (int)subset.size(); ++i)
                cout << subset[i] << (i == (int)subset.size()-1 ? "\n" : " ");
        }
        cout << endl;
    }

    return 0;
}
