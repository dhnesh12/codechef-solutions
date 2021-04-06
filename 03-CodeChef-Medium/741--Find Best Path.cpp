#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-O3")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("no-stack-protector")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

#define int long long 
#define REP(i, a, b) for (ll i = a; i < b; i++)
#define REPI(i, a, b) for (ll i = b - 1; i >= a; i--)
#define FOR(i, a, b, c) for (ll i = a; i < b; i += c)
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
#define INF 1e18
#define ps(x, y) fixed << setprecision(y) << x
#define mk(arr, n, type) type *arr = new type[n];
#define range(a, b) substr(a, b - a + 1)
#define w(x)  \
    int x;    \
    cin >> x; \
    while (x--)
#define trace(x) cerr << #x << ": " << x << " " << endl;
#define FIO                       \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);                   \
    cout.tie(0)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define epsilon 1e-9
#define sign(x) (x > 0) - (x < 0)
#define is_poweroftwo(n) (n && !(n & (n - 1)))
typedef long long ll;

typedef unsigned long long ull;

typedef long double ld;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

vector<vi> edges;

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
void print(vi a, int l, int u)
{
    for (int i = 0; i < u; i++)
    {
        cout << a[i] << " ";
    }
    cout << "\n";
}
void print(vi a)
{

    print(a, 0, a.size());
}
void printl(vi a, int l)
{
    print(a, l, a.size());
}
void printu(vi a, int u)
{
    print(a, 0, u);
}
int leftbit(long long n)
{

    (((((n |= n >> 1) |= n >> 2) |= n >> 4) |= n >> 8) |= n >> 16);
    //n |= n >> 1;
    // n |= n >> 2;
    // n |= n >> 4;
    // n |= n >> 8;
    // n |= n >> 16;
    n = n + 1;
    // return the nearest power of 2
    //return (n >> 1);
    // return the left bit
    return (log2(n >> 1));
}
// ultall takes a number and toggles all bits till the Most significant bit (MSB)
// and return this number
int ultall(unsigned long long n)
{

    int max = leftbit(n);
    for (int i = 0; i <= max; i++)
    {
        n ^= (1 << i);
    }
    return n;
}
// ensure that the length of the array passed is m
// calculates inverse modullo from [1,m-1] and stores it in the array inv
// m is the modulus ex : 1e9+7 , 1e9+3
void modinv(int m, int inv[])
{
    inv[1] = 1;
    for (int i = 2; i < m; ++i)
        inv[i] = m - (m / i) * inv[m % i] % m;
}
// ensure that the length of the vector  passed is m and it is vector<int>
// calculates inverse modullo from [1,m-1] and stores it in the array inv
// m is the modulus ex : 1e9+7 , 1e9+3
void modinv(int m, vi inv)
{
    inv.at(1) = 1;
    for (int i = 2; i < m; ++i)
        inv[i] = m - (m / i) * inv.at((m % i)) % m;
}
//Calculation of (x^y)%mm
ll mod_exp(ll x, ll y, ll mm)
{
    if (y == 0)
        return (1);
    else if (y % 2 == 0)
        return (mod_exp((x * x) % mm, y / 2, mm));
    else
        return ((x * mod_exp((x * x) % mm, (y - 1) / 2, mm)) % mm);
}
long long binpow(long long a, long long b)
{
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
long long binpow(long long a, long long b, long long m)
{
    a %= m;
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

void Miden(ll **p1, ll n)
{
    ll(*x)[n] = (ll(*)[n])p1;
    REP(i, 0, n)
    {
        REP(j, 0, n)
        {
            x[i][j] = 0;
        }
        x[i][i] = 1;
    }
    return;
}
// p1 is the first matrix
// p2 is the second matrix
// ans is the output matrix
//x is number of rows in p1
//y is number of columns in p1
//z is number of columns in p2
//m is the mod
void Mmult(ll **p1, ll **p2, ll **ans, ll x, ll y, ll z, ll m = mod)
{
    ll(*a)[y] = (ll(*)[y])p1;
    ll(*b)[z] = (ll(*)[z])p2;
    ll(*c)[z] = (ll(*)[z])ans;
    REP(i, 0, x)
    {
        REP(j, 0, z)
        {
            c[i][j] = 0;
            REP(k, 0, y)
            {
                c[i][j] += a[i][k] * b[k][j];
                c[i][j] %= m;
            }
        }
    }
    return;
}
// p1 is the input matrix
//ans is the matrix in which the answer is to be stored
//n is the order of the square matrix p1
// y is the power given
// m is the mod
void Mpow(ll **p1, ll **ans, ll n, ll y, ll m = mod)
{
    if (y == 0)
    {
        Miden(ans, n);
        return;
    }
    ll t[n][n];
    Mpow(p1, (ll **)t, n, y / 2, m);
    ll z[n][n];
    Mmult((ll **)t, (ll **)t, (ll **)z, n, n, n, m);
    if (y % 2)
    {
        Mmult((ll **)z, p1, ans, n, n, n, m);
    }
    else
    {
        Miden((ll **)t, n);
        Mmult((ll **)z, (ll **)t, ans, n, n, n, m);
    }
    return;
}
int n, m;
vi Bellman_Ford(int n=::n)
{
    vi d(n + 1);

    for (int i = 0; i < 2 * n; i++)
    {
        for (vi &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            if (i < n - 1)
            {
                d[v] = min(d[v], d[u] + w);
            }
            else
            {
                if (d[v] > d[u] + w)
                {
                    d[v] = -INF;
                }
            }
        }
    }
    return d;
}

signed main()
{
    FIO;
    w(T)
    {
        
        cin >> n >> m;
        edges.clear();
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            edges.pb({u, v, w});
        }
        vi e = Bellman_Ford();
        // reverse the graph
        for (vi &e : edges)
        {
            swap(e[0], e[1]);
        }
        vi s = Bellman_Ford();
        for (int i = 1; i <= n; i++)
        {
            if (s[i] == -INF || e[i] == -INF)
            {
                cout << "INF\n";
            }
            else
            {
                cout << s[i] + e[i] << "\n";
            }
        }
    }

    // cerr << "\n"
    //      << duration;
    return 0;
}