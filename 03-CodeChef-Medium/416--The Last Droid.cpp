#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

#define ll long long
#define F first
#define S second
#define pb push_back

const int N = 5e5 + 5;
const int LOG = 25;
const int MOD = 1e9 + 7;
const ll  inf = 1e9 + 10;

int t, n, m, q, a[N];
int  ans[N];
int par[N], sz[N], is[N];
int mn[N];
vector < pair < int, pair <int, int> > > vec[N];

struct edge{
    int u = 0, v = 0, w = 0, id = 0;
} e[N];

struct query{
    int u = 0, v = 0;
} qu[N];

inline bool cmp(edge e1, edge e2){
    return make_pair(e1.w, e1.id) < make_pair(e2.w, e2.id);
} 

inline void clear(){
    for (int v = 1; v <= n; v ++){
        sz[v] = 1;
        par[v] = v;
        is[v] = (0 < a[v]);
    }
    return;
}

int get_par(int v){
    if (par[v] == v) return v;
    return par[v] = get_par(par[v]);
}

inline void merge(int u, int v){
    u = get_par(u); v = get_par(v);
    if (u == v) return;
    if (sz[v] < sz[u]) swap(u, v);
    par[u] = v;
    sz[v] += sz[u];
    is[v] += is[u];
    return;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0); cout.tie(0);
    cin >> t;
    while (t --){
        cin >> n >> m;
        for (int v = 1; v <= n; v ++){
            cin >> a[v];
            mn[v] = inf;
        }
        for (int i = 0; i < m; i ++){
            int u, v, w;
            cin >> u >> v >> w;
            e[i] = {u, v, w, i};
            mn[u] = min(mn[u], w);
            mn[v] = min(mn[v], w);            
        }
        sort(e, e + m, cmp);
        clear();
        for (int i = 0; i < m; i ++){
            merge(e[i].u, e[i].v);
        }
        cin >> q;
        for (int i = 0; i < q; i ++){
            cin >> qu[i].u >> qu[i].v;
            if (get_par(qu[i].u) != get_par(qu[i].v)){
                ans[i] = -1;
            }
            else if (qu[i].u == qu[i].v){
                ans[i] = 0;
            }
            else if (a[qu[i].u]){
                ans[i] = max(0, mn[qu[i].u] - a[qu[i].u]);
            }
            else {
                int l = -1, r = m;
                int mid = (l + r) / 2;
                vec[mid].pb({i, {l, r}});
            }
        }
        int lg2 = LOG;
        while (lg2 --){
            clear();
            for (int i = 0; i < m; i ++){
                merge(e[i].u, e[i].v);
                for (auto it : vec[i]){
                    int id = it.F;
                    int l = it.S.F;
                    int r = it.S.S;
                    auto ok = [&](){
                        int u = get_par(qu[id].u);
                        int v = get_par(qu[id].v);
                        return (0 < is[u] || u == v);
                    };
                    (ok() ? r : l) = i;
                    if (l + 1 == r){
                        if (r == m){
                            ans[id] = -1;
                        }
                        else {
                            ans[id] = max(0, e[r].w - a[qu[id].u]);
                        }
                    }
                    else {
                        int mid = (l + r) / 2;
                        vec[mid].pb({id, {l, r}});
                    }
                }
                vec[i].clear();
            }
        }
        for (int i = 0; i < q; i ++){
            cout << ans[i] << '\n';
        }
    }
    return 0;
    
}