#include <bits/stdc++.h>
using namespace std;
#define int long long
#define float long double
#define FOR(i, a, b, c) for (int i = a; i < b; i += c)
#define ff first
#define ss second
#define pb push_back
#define pii pair<int, int>
#define vi vector<int>
#define inf 1e18
#define ps(x, y) fixed << setprecision(y) << x
#define w(x)  \
    int x;    \
    cin >> x; \
    while (x--)
#define trace(x) cerr << #x << ": " << x << " " << endl;
#define trace3(x, y, z) cerr << #x << ": " << x << " " << #y << ": " << y << " " << #z << ": " << z << " " << endl;
#define FIO                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0);
int N, M;
vector<vector<pii>> adj;
vector<vector<int>> radj;

bool visu[505], visv[505];
void dfs(int u, bool c = 1)
{
    if (c)
    {
        visu[u] = 1;
        for (auto it = adj[u].begin(); it != adj[u].end(); it++)
            if (!visu[(*it).ff])
                dfs((*it).ff);
    }
    else
    {
        visv[u] = true;
        for (auto it = radj[u].begin(); it != radj[u].end(); it++)
            if (!visv[*it])
                dfs(*it, 0);
    }
}
bool Bellman_Ford(int src, int dest, float x, int n = ::N)
{
    vector<float> d(n + 1, inf);
    d.at(src) = 0;
    FOR(i, 1, n, 1)
    {
        FOR(j, 1, n + 1, 1)
        for (auto it = adj[j].begin(); it != adj[j].end(); it++)
        {
            int u = j, v = it->ff;
            float w = it->ss - x;
            //trace3(u, v, w);
            if (d[u] < inf)
            {
                d[v] = min(d[v], d[u] + w);
            }
        }
    }
    if (d[dest] <= 0)
        return true;
    for (int j = 1; j <= n; j++)
    {
        for (auto it = adj[j].begin(); it != adj[j].end(); it++)
        {
            float w = it->ss - x;
            int v = it->ff;
            // cycle found
            if ((d[j] + w) < d[v])
            {
                if (visu[j] && visv[j])
                    return true;
            }
        }
    }
    return false;
}
signed main()
{

    FIO;
    w(T)
    {
        cin >> N;
        adj.clear(), radj.clear(), adj.resize(N + 1), radj.resize(N + 1), memset(visu, 0, sizeof(visu)), memset(visv, 0, sizeof(visv));
        w(M)
        {
            float u, v, w;
            cin >> u >> v >> w;
            adj[u].pb({v, w}), radj[v].pb(u);
        }
        int src, dest;
        cin >> src >> dest;
        dfs(src);
        if (!visu[dest])
        {
            cout << "-1\n";
            continue;
        }
        dfs(dest, 0);
        //binary search on beintaman ford
        float l = 0, x, r = 100;
        for (int i = 0; i <= 26; i++)
        {
            x = (l + r) / 2;
            bool flag = Bellman_Ford(src, dest, x);
            if (flag == 1)
                r = x;
            else
                l = x;
        }
        cout << ps(l, 7) << "\n";
    }
    return 0;
}