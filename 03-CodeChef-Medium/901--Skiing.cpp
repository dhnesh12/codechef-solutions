#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("no-stack-protector")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <type_traits>
using namespace __gnu_pbds;
using namespace std;

#define int long long
#define all(a) a.begin(), a.end()
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define lc(x) (x << 1)
#define rc(x) ((x << 1) | 1)
#define pii pair<int, int>
#define vi vector<int>
#define mii map<int, int>
#define pqb priority_queue<int>
#define pqs priority_queue<int, vi, greater<int>>
#define setbits(x) __builtin_popcountll(x)
#define mod 1000000007
#define inf 1e18
#define ps(x, y) fixed << setprecision(y) << x
#define mk(arr, n, type) type *arr = new type[n];
#define range(a, b) substr(a, b - a + 1)
#define w(x)  \
    int x;    \
    cin >> x; \
    while (x--)
#define trace(x) cerr << #x << ": " << x << " " << endl;
#define trace3(x, y, z) cerr << #x << ": " << x << " " << #y << ": " << y << " " << #z << ": " << z << " " << endl;
#define trace2(x, y) cerr << #x << ": " << x << " " << #y << ": " << y << endl;
#define FIO                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
void tracearr(vi a)
{
    for (int i = 0; i < a.size(); i++)
    {
        cerr << i << "th index " << a[i] << endl;
    }
    cerr << endl;
}

void tracearr(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cerr << i << "th index " << a[i] << endl;
    }
    cerr << endl;
}
void trace2d(vector<vi> a)
{
    for (int i = 0; i < a.size(); i++)
    {
        trace(i);
        for (int j = 0; j < a[i].size(); j++)
        {
            cerr << a[i][j] << " ";
        }
        cerr << endl;
    }
}
int n, m;
vector<vi> adj, rev, cg_adj, rev_cg;
int num(int i, int j)
{
    return (i * m + j + 1);
}
void add_edge(int i, int j, const vector<vector<int>> &h)
{
    if (j + 1 < m and h[i][j] >= h[i][j + 1])
    {
        adj.at(num(i, j)).pb(num(i, j + 1));
        rev.at(num(i, j + 1)).pb(num(i, j));
    }
    if (j - 1 >= 0 and h[i][j] >= h[i][j - 1])
    {
        adj.at(num(i, j)).pb(num(i, j - 1));
        rev.at(num(i, j - 1)).pb(num(i, j));
    }
    if (i + 1 < n and h[i][j] >= h[i + 1][j])
    {
        adj.at(num(i, j)).pb(num(i + 1, j));
        rev.at(num(i + 1, j)).pb(num(i, j));
    }
    if (i - 1 >= 0 and h[i][j] >= h[i - 1][j])
    {
        adj[num(i, j)].pb(num(i - 1, j));
        rev[num(i - 1, j)].pb(num(i, j));
    }
}
vi scc_no; //strongly connected component number
void dfs(int i, vi &vis, vi &vals)
{
    vis[i] = 1;

    for (int j : adj[i])
        if (!vis[j])
            dfs(j, vis, vals);

    vals.pb(i); //nodes in increasing order of out time
}

void rev_dfs(int i, int num)
{
    // the ith node is in the C (num) connected component
    scc_no[i] = num;

    for (int j : rev[i])
    {
        if (!scc_no[j])
            rev_dfs(j, num);
    }
}

int condensation_graph(int n)
{
    vi vis(n + 1), vals;

    for (int i = 1; i <= n; ++i)
        if (!vis[i])
            dfs(i, vis, vals);

    reverse(vals.begin(), vals.end());

    // number of strongly connected components
    int num = 1;

    scc_no.assign(n + 1, 0);

    for (int i : vals)
    {
        if (!scc_no[i])
        {
            rev_dfs(i, num);
            /* all nodes which are visitable from i
            in the reverse graph are part of the 
            same strongly connected component as i
            */
            num++;
        }
    }
    rev_cg.clear();
    cg_adj.clear();
    cg_adj.resize(num); //num = no_of_sccs + 1
    rev_cg.resize(num); //num = no_of_sccs + 1

    for (int i = 1; i <= n; ++i)
        for (int j : adj[i])
            if (scc_no[i] != scc_no[j])
            {
                cg_adj[scc_no[i]].pb(scc_no[j]);
                rev_cg[scc_no[j]].pb(scc_no[i]);
            }

    return num - 1; // return number of strongly connected components
}
signed main()
{
    FIO;
    w(T)
    {
        cin >> n >> m;
        adj.clear(), rev.clear(), scc_no.clear();
        adj.resize(n * m + 1), rev.resize(n * m + 1);
        vector<vi> h(n, vi(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> h[i][j];
                
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                add_edge(i, j, h);
                
        int num = condensation_graph(n * m);
        int s = 0;
        // we need the conncted componenents with 0 indegree because they cannot 
        // be reached from any other component and we choose one cell from that connected component 
        // if there is no such componenet then s will remain 0 then we will add 1
        // to it because we can choose any such cell and we will be able to reach 
        // all other cells 
        // in reverse condensation graph choose the nodes which have 0 outdegree 
        // because they will be having 0 indegree in the normal condensation graph 
        for (auto v : rev_cg)
            if ((int)v.size() == 0)
                s++;
        s--;
        if (s == 0)
            s++;
        cout << s << "\n";
    }
    return 0;
}