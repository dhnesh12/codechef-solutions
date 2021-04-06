#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define vll vector<ll>
#define vii vector<pair<int, int>>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define loop(_) for (int __ = 0; __ < (_); ++__)
#define pb push_back
#define f first
#define s second
#define sz(_) ((int)_.size())
#define all(_) _.begin(), _.end()
#define lb lower_bound
#define ub upper_bound

using ll = long long;
using ld = long double;

const int N = 5e5 + 7;
const ll mod = 1e9 + 7;

int n, m;

struct edge
{
       int src, dst;
};
struct graph
{
       int n;
       vector<vector<edge>> adj, rdj;
       graph(int n = 0) : n(0) {}
       void add_edge(int src, int dst)
       {
              n = max(n, max(src, dst) + 1);
              adj.resize(n);
              rdj.resize(n);
              adj[src].push_back({src, dst});
              rdj[dst].push_back({dst, src});
       }

       vector<int> rank, semi, low, anc;
       int eval(int v)
       {
              if (anc[v] < n && anc[anc[v]] < n)
              {
                     int x = eval(anc[v]);
                     if (rank[semi[low[v]]] > rank[semi[x]])
                            low[v] = x;
                     anc[v] = anc[anc[v]];
              }
              return low[v];
       }
       vector<int> prev, ord;
       void dfs(int u)
       {
              rank[u] = ord.size();
              ord.push_back(u);
              for (auto e : adj[u])
              {
                     if (rank[e.dst] < n)
                            continue;
                     dfs(e.dst);
                     prev[e.dst] = u;
              }
       }
       vector<int> idom; // idom[u] is an immediate dominator of u
       void dominator_tree(int r)
       {
              idom.assign(n, n);
              prev = rank = anc = idom;
              semi.resize(n);
              iota(all(semi), 0);
              low = semi;
              ord.clear();
              dfs(r);

              vector<vector<int>> dom(n);
              for (int i = ord.size() - 1; i >= 1; --i)
              {
                     int w = ord[i];
                     for (auto e : rdj[w])
                     {
                            int u = eval(e.dst);
                            if (rank[semi[w]] > rank[semi[u]])
                                   semi[w] = semi[u];
                     }
                     dom[semi[w]].push_back(w);
                     anc[w] = prev[w];
                     for (int v : dom[prev[w]])
                     {
                            int u = eval(v);
                            idom[v] = (rank[prev[w]] > rank[semi[u]] ? u : prev[w]);
                     }
                     dom[prev[w]].clear();
              }
              for (int i = 1; i < ord.size(); ++i)
              {
                     int w = ord[i];
                     if (idom[w] != semi[w])
                            idom[w] = idom[idom[w]];
              }
       }
       vector<int> dominators(int u)
       {
              vector<int> S;
              for (; u < n; u = idom[u])
                     S.push_back(u);
              return S;
       }
} domi;

vi adj[N];
ll ans;
int vis[N];

ll dfs(int x)
{
       ll ret = 1;
       assert(vis[x]++ == 0);
       for (auto u : adj[x])
       {
              if (vis[u])
                     continue;
              ll w = dfs(u);
              if (x == 0)
              {
                     ans -= 1ll * w * (w - 1) / 2ll;
              }
              ret += w;
       }
       return ret;
}

int main()
{
       ios_base::sync_with_stdio(0);
       cin.tie(0);
#ifndef ONLINE_JUDGE
       freopen("in.in", "r", stdin);
#endif
       cin >> n >> m;
       for (int i = 0; i < m; ++i)
       {
              int u, v;
              cin >> u >> v;
              domi.add_edge(u - 1, v - 1);
       }
       domi.dominator_tree(0);

       ans = 1ll * n * (n - 1) / 2ll;
       for (int i = 1; i < n; ++i)
       {
              adj[domi.idom[i]].pb(i);
       }
       dfs(0);
       cout << ans;
       return 0;
}
