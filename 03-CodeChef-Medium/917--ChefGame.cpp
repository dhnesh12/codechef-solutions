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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define epsilon 1e-9
#define sign(x) (x > 0) - (x < 0)
#define is_poweroftwo(n) (n && !(n & (n - 1)))
typedef int ll;
typedef unsigned int ull;
typedef long double ld;
template <typename T>
#define ordered_set(T) = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
void nothing();
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
        for (int j = 0; j < a[i].size(); j++)
        {
            cerr << a[i][j] << " ";
        }
        cerr << endl;
    }
}
int binpow(int a, int b)
{
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
int binpow(int a, int b, int m)
{
    a %= m;
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
int n, d;
int mod = 747474747;
vector<vi> dst; //adjacency matrix stores distance between two nodes
int get_ans()
{
    int ans = 1;
    vector<bool> marked(n);
    vi maxEdge(n);
    for (int it = 1; it <= n; it++)
    {

        int i = -1;
        for (int j = 0; j < n; j++)
        {
            if (marked.at(j) == 0 and (i == -1 or maxEdge[j] >= maxEdge[i]))
                i = j;
        }
        if (maxEdge[i] == 0 and it > 1)
            break;
        if (it > 1)
        {
            int e = maxEdge[i] % mod;
            ans = (ans * e) % mod;
        }
        marked[i] = 1;
        for (int j = 0; j < n; j++)
        {
            maxEdge[j] = max(maxEdge[j], dst[i][j]);
        }
    }
    return ans;
}
signed main()
{
    FIO;
    w(T)
    {
        cin >> n >> d;
        //trace2(n, d);
        vector<vi> v(n, vi(d));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < d; j++)
            {
                cin >> v[i][j];
            }
        }
        dst.assign(n, vi(n));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int w = 0;
                for (int k = 0; k < d; k++)
                {
                    w += binpow(abs(v[i][k] - v[j][k]), 2);
                }
                dst[i][j] = w;
            }
        }
        cout << get_ans() << "\n";
        dst.clear();
    }

    return 0;
}