#include <bits/stdc++.h>
 
#define long long long
 
using namespace std;

const int N = 2e5 + 10;
const int BASE = 998244353;

int n, m;

struct Edge {
    int u, v, w;
} E[N];

struct DSU {
    int n;
    int p[N];
    void Init(int _n) {
        n = _n;
        for (int i = 1; i <= n; ++i) p[i] = -1;
    }
    int Root(int u) {
        return p[u] < 0 ? u : p[u] = Root(p[u]);
    }
    bool Union(int u, int v) {
        u = Root(u); v = Root(v);
        if (u == v) return false;
        if (p[u] < p[v]) swap(u, v);
        p[u] += p[v];
        p[v] = u;
        return true;
    }
} DSU;

const int LG = 18;

struct Tree {
    int n, m, timer;
    int comp[N], root[N], x[N], y[N], V[N], cost[N], h[N];
    int p[N][LG + 2];
    vector <pair <int, int> > adj[N];
    Edge E[N];
    void Init(int _n) {
        n = _n;
        m = 0;
        timer = 0;
    }
    void AddEdgeToList(int u, int v, int w) {
        E[++m] = {u, v, w};
    }
    void AddEdgeToAdj(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    int Root(int u) {
        return root[u] < 0 ? u : root[u] = Root(root[u]);
    }
    void Binarization() {
        assert(m == n - 1);
        sort(E + 1, E + m + 1, [&](Edge x, Edge y) {
            return x.w < y.w;
        });
        for (int i = 1; i <= n; ++i) root[i] = -1;
        for (int i = 1; i <= n; ++i) comp[i] = i;
        for (int i = 1; i <= m; ++i) {
            int u = E[i].u, v = E[i].v, w = E[i].w;
            int ru = Root(u), rv = Root(v);
            assert(ru != rv);
            AddEdgeToAdj(n + i, comp[ru], w);
            AddEdgeToAdj(n + i, comp[rv], w);
            
            if (root[ru] < root[rv]) swap(u, v);
            root[ru] += root[rv];
            root[rv] = ru; comp[ru] = n + i;
        }
        n = 2 * n - 1;
        // cout << "Tree after binarization\n";
    }
    void DFS(int u) {
        x[u] = ++timer; V[timer] = u;
        for (auto x: adj[u]) {
            int v = x.first, w = x.second;
            if (v == p[u][0]) continue;

            // cout << u << " -- " << v << " = " << w << '\n';
            cost[u] = w;
            p[v][0] = u; h[v] = h[u] + 1;
            DFS(v);
        }
        y[u] = timer;
    }
    void InitLCA() {
        for (int j = 1; (1 << j) <= n; ++j)
            for (int i = 1; i <= n; ++i) p[i][j] = p[p[i][j - 1]][j - 1];
    }
    int LCA(int u, int v) {
        if (h[u] < h[v]) swap(u, v);
        for (int i = LG; i >= 0; --i) if (h[u] - (1 << i) >= h[v]) u = p[u][i];
        if (u == v) return u;
        for (int i = LG; i >= 0; --i) if (p[u][i] != p[v][i]) u = p[u][i], v = p[v][i];
        return p[u][0];
    }
} T1, T2;

int sz[N], par[N], val[N];
int fa[N], fb[N];

bool dead[N];

void dfs(int u, int all_size, pair <int, int> &centroidEdge) {
    // dfs on tree T1
    sz[u] = 1;
    for (auto x: T1.adj[u]) {
        int v = x.first, w = x.second;
        if (v != par[u] && !dead[v]) {
            par[v] = u;
            dfs(v, all_size, centroidEdge);
            sz[u] += sz[v];
        }
    }
    int min_sz = max(sz[u], all_size - sz[u]);
    if (centroidEdge.second == -1 || min_sz < centroidEdge.second) {
        centroidEdge = {u, min_sz};
    }
}

void dfsSubtree(int u, int p, vector <int> &vertex) {
    int child = 0;
    for (auto x: T1.adj[u]) {
        int v = x.first, w = x.second;
        if (v != p && !dead[v]) {
            ++child;
            val[v] = max(val[u], w);
            dfsSubtree(v, u, vertex);
        }
    }
    if (u <= n) {
        vertex.push_back(u);
    }
}

vector <int> tree[N];

bool is_root[N];

int ans = 0;

void Add(int &a, int b) {
    a += b; if (a >= BASE) a -= BASE; if (a < 0) a += BASE;
}

int Mul(int a, int b) {
    return 1LL * a * b % BASE;
}

void DP(int u) {
    for (int v: tree[u]) {
        DP(v);
        // combine DP(u) and DP(v)
        int s = Mul(fa[u], fb[v]);
        Add(s, Mul(fb[u], fa[v]));

        Add(ans, Mul(s, T2.cost[u]));

        Add(fa[u], fa[v]);
        Add(fb[u], fb[v]);
    }
    // cout << u << " = " << ans << '\n';
}

void SolveT1(int root, int sz_subtree) {
    // start centroid decomposition edges here
    if (sz_subtree == 1) return;
    pair <int, int> centroidEdge = {-1, -1};
    par[root] = -1;
    dfs(root, sz_subtree, centroidEdge);

    // cout << "Centroid at root = " << root << " has " << centroidEdge.first << " " << centroidEdge.second << '\n'; 
    // if (centroidEdge.first == -1) return;
    assert(centroidEdge.first != -1);
    int v = centroidEdge.first;

    vector <int> vertex_in, vertex_out;
    val[v] = val[par[v]] = 0;
    dfsSubtree(v, par[v], vertex_in); // b
    dfsSubtree(par[v], v, vertex_out); // a

    // compute here
    if (T1.h[v] < T1.h[par[v]]) swap(vertex_in, vertex_out);
    vector <int> vertex;
    for (int v: vertex_in) vertex.push_back(v), fa[v] = 0, fb[v] = 1;
    for (int v: vertex_out) vertex.push_back(v), fa[v] = val[v], fb[v] = 0; 
    // cout << "vertex in = "; for (int v: vertex_in) cout << v << ' '; cout << '\n';
    // cout << "vertex out = "; for (int v: vertex_out) cout << v << ' '; cout << '\n';
    sort(vertex.begin(), vertex.end(), [&](int u, int v) {
        return T2.x[u] < T2.x[v];
    });
    // cout << "before vertex = "; for (int v: vertex) cout << v << ' '; cout << '\n';
    
    // build compressed tree
    int m = vertex.size();
    for (int i = 1; i < m; ++i) {
        int u = vertex[i - 1], v = vertex[i];
        vertex.push_back(T2.LCA(u, v));
    }
    sort(vertex.begin(), vertex.end(), [&](int u, int v) {
        return T2.x[u] < T2.x[v];
    });
    // cout << "after vertex = "; for (int v: vertex) cout << v << ' '; cout << '\n';
    vector <int> st; // stack
    for (int i = 0; i < vertex.size(); ++i) {
        if (i > 0 && vertex[i] == vertex[i - 1]) continue;
        int u = vertex[i];
        while (st.size() && T2.y[st.back()] < T2.x[u]) st.pop_back();
        if (st.size()) {
            // cout << "compressed tree has edge " << st.back() << " " << u << '\n';
            is_root[u] = true;
            tree[st.back()].push_back(u);
        }
        st.push_back(u);
    }
    if (vertex.size()) {
        int r = -1;
        int cnt = 0;
        // sort(vertex.begin(), vertex.end());
        // vertex.resize(unique(vertex.begin(), vertex.end()) - vertex.begin());
        for (int v: vertex) if (is_root[v] == false) r = v, ++cnt;
        assert(r != -1);
        // assert(cnt == 1);
        // cout << "DP in compressed tree at root = " << r << '\n';
        DP(r);
    }

    // reset
    for (int v: vertex) tree[v].clear(), fa[v] = 0, fb[v] = 0, is_root[v] = false;
    
    // cout << "ans = " << ans << '\n';
    // continue decompose
    dead[v] = true;
    SolveT1(par[v], sz_subtree - sz[v]);
    dead[v] = false;

    dead[par[v]] = true;
    SolveT1(v, sz[v]);
    dead[par[v]] = false;
    
}

void Generate() {
    srand(time(NULL));
    int n = 1e5;
    cout << n << " " << 2 * n << '\n';
    for (int i = 1; i <= 2; ++i) {
        for (int j = 2; j <= n; ++j) {
            int u = j, v = rand() % (j - 1) + 1, w = rand() % 10;
            cout << u << " " << v << " " << w << '\n';
        }
        for (int j = 1; j <= n + 1; ++j) {
            int u = rand() % n + 1, v = rand() % n + 1, w = rand() % 10 + 1;
            cout << u << " " << v << " " << w << '\n';
        }
    }
}

int main() {
    // Generate();
    // return 0;
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int k = 0; k < 2; ++k) {
        for (int i = 1; i <= m; ++i) {
            int u, v, w; cin >> u >> v >> w;
            E[i] = {u, v, w};
        }
        sort(E + 1, E + m + 1, [&](Edge u, Edge v) {
            return u.w < v.w;
        });
        Tree &T = (k == 0) ? T1 : T2;
        T.Init(n);
        DSU.Init(n);
        int t = 0;
        for (int i = 1; i <= m; ++i) {
            int u = E[i].u, v = E[i].v, w = E[i].w;
            bool ok = DSU.Union(u, v);
            if (ok == true) {
                T.AddEdgeToList(u, v, w);
            }
        }
    }
    T1.Binarization();
    T1.DFS(T1.n); T1.InitLCA();

    T2.Binarization();
    T2.DFS(T2.n); T2.InitLCA();

    SolveT1(T1.n, T1.n);
    cout << ans << '\n';
    return 0;
}
