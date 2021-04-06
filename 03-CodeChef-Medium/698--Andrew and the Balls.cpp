#include <bits/stdc++.h>
#define pb push_back
#define vii vector<int>
#define task "promote"
#define pll pair<ll, ll>
#define pii pair< ll, pair< ll, ll > >
#define fi first
#define se second

using namespace std;
using ll = long long;
using ull = unsigned long long;
const int N = 305;
const int Q = 2e6+5;
const ll mod = 1e9+7;
ll m, n, k, t, T, ans, u, v, tong;
ll a[N], c[N], b[N], d[N], lab[N], st[N], dp[N][N], in[N], res[N], h[N], out[N], P[N][20], fe[N];
string sa, sb;
vector<ll> kq, adj[N];
vector<ll> adt[N], kind[N];
ll dx[4] = {0, 0, -1, 1};
ll dy[4] = {1, -1, 0, 0};
bool ok;
void dfs(ll u, ll p)
{
    for(int i = 1; i <= 18; i ++)P[u][i] = P[P[u][i-1]][i-1];
    in[u] = ++k;
    d[k] = u;
    for(ll v : adj[u])
    {

        if(v == p)continue;
        h[v] = h[u] + 1;
        P[v][0] = u;
        dfs(v, u);
    }
    out[u] = k;
}
struct dang
{
    ll x, y, c, pos, w;
};
ll lca(ll u, ll v)
{
    if(h[u] < h[v])swap(u, v);
    ll log = log2(h[u]);
    for(int i = log; i >= 0; i --)
    {
        if(h[u] >= h[v] + (1 << i))u = P[u][i];
    }
    if(u == v)return u;
    for(int i = log; i >= 0; i --)
    {
        if(P[u][i] != 0 && P[u][i] != P[v][i])
        {
            u = P[u][i];
            v = P[v][i];
        }
    }
    return  P[u][0];
}
ll dis(ll u, ll v)
{
    return h[u] + h[v] - 2 * h[lca(u, v)];
}

void bfs(ll u, ll p)
{
    vector<ll> l, r;
    l.resize(adj[u].size()+2);
    r.resize(adj[u].size()+2);
    int j = 0;
    for(ll v : adj[u])
    {
        ++j;
        l[j] = l[j-1];
        if(v == p)continue;
        bfs(v, u);
        P[u][0] += max(P[v][1], P[v][0]);
        l[j] += P[v][1];
    }
    j = adj[u].size()+1;
    for(int i = adj[u].size()-1; i >= 0; i --)
    {
        --j;
        ll v = adj[u][i];
        r[j] = r[j+1];
        if(v == p)continue;
        P[u][1] = max(P[u][1], P[v][0] + l[j-1] + r[j+1]);
        r[j] += P[v][1];
    }
    if(adj[u].size()>1)++P[u][1];
    //cout << u <<" "<<P[u][1] <<" "<<P[u][0] << '\n';
}
bool cmp(const dang& X, const dang& Y)
{
    return X.w > Y.w;
}
void up(ll id)
{
    for(; id <= n; id += id & -id)fe[id] += 1;
}
ll gets(ll id)
{
    ll total = 0;
    for(; id; id -= id & -id)total += fe[id];
    return total;
}
ll pw(ll k, ll n)
{
    ll total = 1;
    for(; n; n >>= 1)
    {
        if(n & 1)total = (total * k) % mod;
        k = (k * k) % mod;
    }
    return total;
}
ll cal(ll u, ll v)
{
    if(u > v)return 0;
    return a[v] * b[u] % mod * b[v-u] % mod;
}
void sol()
{
    cin >> n;
    a[0] = b[0] = 1;

    memset(dp, 0, sizeof(dp));
    d[0] = 1;
    for(int i = 1; i <= n; i ++)
    {
        cin >> c[i];
        d[i] = d[i-1] + c[i];
    }
    for(int i = 1; i <= d[n]; i ++)
    {
        a[i] = (a[i-1] * i) % mod;
        b[i] = pw(i ,mod-2);
        b[i] = (b[i] * b[i-1]) % mod;
    }
    dp[0][0] = 1;
    for(int i = 1; i <= n; i ++)
    {
        for(int ij = 0; ij <= c[i]; ij ++)
        {
            for(int l = 0; l <= d[i-1]; l ++)
            {
                if(dp[i-1][l] > 0)
                {
                    for(int r = 0; r <= min(ij, l); r ++)
                    {
                        ll il = ij-r, z = d[i-1] - l;
                        dp[i][l-r+c[i]-ij] = ( dp[i][l-r+c[i]-ij] + dp[i-1][l] * cal(il, z) % mod * cal(r, l) % mod * cal(ij-1, c[i]-1) % mod) % mod;
                    }
                }
            }
        }
    }
    cout << dp[n][0] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if(fopen(task".in", "r"))
    {
		freopen(task".in","r",stdin);
		freopen(task".out","w",stdout);
    }
    int ntest;
    ntest = 1;
    cin >> ntest;
    while(ntest -- > 0)
    sol();
}
/*
3 2 10
2 1 1
1 2 1
2 2 1
1 1 2
3 1 2
1 2 2
2 2 2
2 1 2
3 2 4
2 1 5
*/
