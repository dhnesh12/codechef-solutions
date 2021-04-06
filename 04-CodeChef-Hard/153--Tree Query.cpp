#define taskname "test"

#include <bits/stdc++.h>

using namespace std;

#define sz(x) (int)x.size()
#define fi first
#define se second

typedef long long lli;
typedef pair<int, int> pii;

const int maxn = 1e5 + 5;

int n, Q;
int w[maxn];
vector<int> gr[maxn];

int ntime = 0;
int tin[maxn], tout[maxn];
int arr[maxn];

int tvert;
int p[maxn];

int sub[maxn];
bool del[maxn];

int up_centroid[maxn];
vector<int> down_centroids[maxn], childs[maxn];

struct segment_tree
{
    int from[maxn * 4], to[maxn * 4];
    lli total[maxn * 4], lazy[maxn * 4];

    void build(int x, int l, int r)
    {
        from[x] = l; to[x] = r;
        if(l == r)
        {
            total[x] = w[arr[l]];
            return;
        }
        int mid = (l + r) / 2;
        build(x * 2, l, mid);
        build(x * 2 + 1, mid + 1, r);
        total[x] = total[x * 2] + total[x * 2 + 1];
    }

    void push(int x)
    {
        if(lazy[x] == 0) return;
        lli t = lazy[x];

        for(int i = x * 2; i <= x * 2 + 1; ++i)
        {
            lazy[i] += t;
            total[i] += (to[i] - from[i] + 1) * 1LL * t;
        }

        lazy[x] = 0;
    }

    void update(int x, int l, int r, int L, int R, int k)
    {
        if(L > r || l > R) return;
        if(l >= L && r <= R)
        {
            total[x] += (to[x] - from[x] + 1) * 1LL * k;
            lazy[x] += k;
            return;
        }
        push(x);
        int mid = (l + r) / 2;
        update(x * 2, l, mid, L, R, k);
        update(x * 2 + 1, mid + 1, r, L, R, k);
        total[x] = total[x * 2] + total[x * 2 + 1];
    }

    lli get(int x, int l, int r, int L, int R)
    {
        if(L > r || l > R) return 0;
        if(l >= L && r <= R)
            return total[x];
        push(x);
        int mid = (l + r) / 2;
        return get(x * 2, l, mid, L, R) + get(x * 2 + 1, mid + 1, r, L, R);
    }
} tree_data;

void read_input()
{
    cin >> n >> Q;
    for(int i = 1; i <= n; ++i)
        cin >> w[i];
    for(int i = 1; i < n; ++i)
    {
        int u, v;
        cin >> u >> v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
}

void dfs_prep(int u, int par)
{
    p[u] = par;
    tin[u] = ++ntime;
    arr[ntime] = u;
    for(auto&v: gr[u])
        if(v != par) dfs_prep(v, u);
    tout[u] = ntime;
}

void dfs_calc_sub(int u, int par)
{
    sub[u] = 1;
    for(auto&v: gr[u])
        if(v != par && !del[v])
        {
            dfs_calc_sub(v, u);
            sub[u] += sub[v];
        }
}

int centroid(int u, int par, const int&all)
{
    for(auto&v: gr[u])
        if(v != par && !del[v] && sub[v] * 2 > all)
            return centroid(v, u, all);
    return u;
}

int centroid_decompose(int u)
{
    dfs_calc_sub(u, 0);
    u = centroid(u, 0, sub[u]);
    del[u] = true;
    for(auto&v: gr[u])
    {
        if(del[v]) continue;
        if(v == p[u])
            up_centroid[u] = centroid_decompose(v);
        else
        {
            down_centroids[u].push_back(centroid_decompose(v));
            childs[u].push_back(v);
        }
    }
    return u;
}

void init()
{
    dfs_prep(1, 0);
    tvert = centroid_decompose(1);
}

int get_ans(int u)
{
    if(tree_data.get(1, 1, n, tin[u], tout[u]) * 2 == tree_data.get(1, 1, n, 1, n))
        return min(u, p[u]);
    if(tree_data.get(1, 1, n, tin[u], tout[u]) * 2 > tree_data.get(1, 1, n, 1, n))
    {
        int low = 0, high = sz(childs[u]) - 1;
        while(low <= high)
        {
            int mid = (low + high) / 2;
            if(tree_data.get(1, 1, n, tin[u] + 1, tout[childs[u][mid]]) * 2 >= tree_data.get(1, 1, n, 1, n))
                high = mid - 1;
            else low = mid + 1;
        }
        if(low < sz(childs[u]) && tree_data.get(1, 1, n, tin[childs[u][low]], tout[childs[u][low]]) * 2 >= tree_data.get(1, 1, n, 1, n))
            return get_ans(down_centroids[u][low]);
        return u;
    }
    return get_ans(up_centroid[u]);
}

void solve()
{
    tree_data.build(1, 1, n);
    for(; Q > 0; --Q)
    {
        int type, u, x;
        cin >> type >> u >> x;
        if(type == 1)
            tree_data.update(1, 1, n, tin[u], tin[u], x);
        else tree_data.update(1, 1, n, tin[u], tout[u], x);
        cout << get_ans(tvert) << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    read_input();
    init();
    solve();
}

