# include <bits/stdc++.h>
using namespace std;
# define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
# define FDR(i, a, b) for (int i = (a); i >= (b); --i)
# define mem(a, x) memset(a, x, sizeof(a));
# define mp make_pair
# define pb push_back
typedef vector<int> Vi;
typedef tuple<int, int, int> Ti;
typedef pair<int, int> Pi;
typedef long long i64;
const int N = 100005;
const int MOD = 1000000007;
const int INF = 1000000000;
const int DEG = 23;

struct Node{int u, v, w;}node[8];
int w[N], e[N], F[N];
Pi ee[N], p[N];
Vi E[N];
int fa[N][DEG], deg[N], dep[N];
queue<int> que;
stack<i64> st;

int find(int x) {return F[x] == 0 ? x : F[x] = find(F[x]);}
void BFS(int root) {
    deg[root] = 0; fa[root][0] = root;
    dep[root] = w[root]; que.push(root);
    while (!que.empty()) {
        int tmp = que.front(); que.pop();
        FOR(i, 1, DEG-1) fa[tmp][i] = fa[fa[tmp][i-1]][i-1];
        for (auto i: E[tmp]) {
            if (i == fa[tmp][0]) continue;
            deg[i] = deg[tmp] + 1;
            dep[i] = dep[tmp] + w[i];
            fa[i][0] = tmp;
            que.push(i);
        }
    }
}
int LCA(int u, int v) {
    if (deg[u] > deg[v]) swap(u, v);
    int hu = deg[u], hv = deg[v], tu = u, tv = v;
    for (int det = hv-hu, i = 0; det; det>>=1, ++i) {
        if (det & 1) tv = fa[tv][i];
    }
    if (tu == tv) return tu;
    FDR(i, DEG-1, 0) {
        if (fa[tu][i] == fa[tv][i]) continue;
        tu = fa[tu][i];
        tv = fa[tv][i];
    }
    return fa[tu][0];
}
bool comp(Node a, Node b) {return a.w > b.w;}
i64 inv(i64 a, i64 m) {
    if (a == 1) return 1;
    return inv(m%a, m) * (m - m/a) % m;
}
int main ()
{
    int n, u, v;
    scanf("%d", &n);
    i64 ans = 1;
    FOR(i, 1, n) scanf("%d", w + i), p[i] = mp(i, i), ans = ans * w[i] % MOD;
    FOR(i, 1, n-1) scanf("%d %d", &u, &v), E[u].pb(v), E[v].pb(u), ee[i] = mp(u, v);
    FOR(i, 1, n-1) scanf("%d", e + i);
    BFS(1);
    FDR(i, n-1, 1) {
        st.push(ans);
        u = ee[e[i]].first, v = ee[e[i]].second;
        u = find(u); v = find(v);
        int u1 = p[u].first, u2 = p[u].second, v1 = p[v].first, v2 = p[v].second;
        int u1u2 = LCA(u1, u2), v1v2 = LCA(v1, v2);
        int u1v1 = LCA(u1, v1), u1v2 = LCA(u1, v2);
        int u2v1 = LCA(u2, v1), u2v2 = LCA(u2, v2);
        node[1] = Node{u1, u2, dep[u1] + dep[u2] - 2*dep[u1u2] + w[u1u2]}; node[2] = Node{v1, v2, dep[v1] + dep[v2] - 2*dep[v1v2] + w[v1v2]};
        node[3] = Node{u1, v1, dep[u1] + dep[v1] - 2*dep[u1v1] + w[u1v1]}; node[4] = Node{u1, v2, dep[u1] + dep[v2] - 2*dep[u1v2] + w[u1v2]};
        node[5] = Node{u2, v1, dep[u2] + dep[v1] - 2*dep[u2v1] + w[u2v1]}; node[6] = Node{u2, v2, dep[u2] + dep[v2] - 2*dep[u2v2] + w[u2v2]};
        sort(node + 1, node + 7, comp);
        F[v] = u; p[u] = mp(node[1].u, node[1].v);
        ans = ans * node[1].w % MOD * inv(dep[u1] + dep[u2] - 2*dep[u1u2] + w[u1u2], MOD) % MOD * inv(dep[v1] + dep[v2] - 2*dep[v1v2] + w[v1v2], MOD) % MOD;
    }
    st.push(ans);
    while (!st.empty()) printf("%lld\n", st.top()), st.pop();
    return 0;
}
