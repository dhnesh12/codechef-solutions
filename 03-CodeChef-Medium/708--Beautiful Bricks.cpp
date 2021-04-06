#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#pragma GCC optimize("-Ofast")
#pragma GCC optimize("trapv")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.2,popcnt,abm,mmx,avx2,tune=native")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-funroll-loops")

using namespace std;
using namespace __gnu_pbds;

#define vi vector<int>
#define vll vector<ll>
#define vii vector<pair<int, int>>
#define vvi vector<vi>
#define vvii vector<vii>
#define pii pair<int, int>
#define pll pair<ll, ll>
#define loop(_) for (int __ = 0; __ < (_); ++__)
#define forn(i, n) for (int i = 0; i < n; ++i)
#define pb push_back
#define f first
#define s second
#define sz(_) ((int)_.size())
#define all(_) _.begin(), _.end()
#define uni(_) unique(_)
#define lb lower_bound
#define ub upper_bound
#define si set<int>
#define ms multiset<int>
#define qi queue<int>
#define pq prioriry_queue<int>
#define mi map<int, int>
#define inc(i, l, r) for (int i = l; i <= r; i++)
#define dec(i, l, r) for (int i = l; i >= r; i--)

using lll = __int128;
using ll = long long;
using ld = long double;

const int N = 1e5 + 7;
const ll mod = 1e9 + 7;
const ll inf = 2e18;

auto ra = [] {char *p = new char ; delete p ; return ll(p) ; };
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() * (ra() | 1));
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> os;

const int S = 2005;
int dp[S][4][S];

inline int nor(int x)
{
       x %= mod;
       (x < 0) && (x += mod);
       return x;
}

int faspow(int x, int y)
{
       int ret = 1ll;
       while (y)
       {
              if (y & 1)
                     ret = 1ll * ret * x % mod;
              x = 1ll * x * x % mod;
              y >>= 1ll;
       }
       return ret;
}
int add(int x, int y) { return (x + y) >= mod ? x + y - mod : x + y; }
int mul(int x, int y) { return 1ll * nor(x) * nor(y) % mod; }
int inv(int x)
{
       return faspow(x, mod - 2);
}

int dv(int x, int y) { return mul(nor(x), inv(nor(y))); }

int solve(int i, int mask, int r)
{
       if (i == 0)
              return r == 0;
       if (~dp[i][mask][r])
              return dp[i][mask][r];
       int ret = 0;
       for (int j = 0; j < 3; ++j)
       {
              if ((mask & j) == 0)
              {
                     ret = (ret + solve(i - 1, j, r - (!!j)));
                     ret %= mod;
              }
       }
       return dp[i][mask][r] = ret;
}

int calc(int n, int k, vector<int> pt)
{
       int z = sz(pt);
       int ret = 0;
       int now = 1;
       for (int i = 1; i < z; ++i)
       {
              now = mul(now, nor(n - i));
              now = mul(now, inv(nor(0 - i)));
       }

       for (int i = 0; i < z; ++i)
       {
              ret = add(ret, mul(pt[i], now));
              if (i + 1 != z)
              {
                     now = mul(now, dv(n - i, n - (i + 1)));
                     now = mul(now, dv(i + 1 - z, i + 1));
              }
       }
       return ret;
}

int interpolate(int n, int k)
{
       vector<int> v;
       for (int i = k; i <= 2 * k + 2; ++i)
       {
              v.pb(solve(i, 0, k));
       }
       if (n < k)
              return 0;
       if (n - k < sz(v))
              return v[n - k];
       return calc(n - k, k, v);
}

int main()
{
       ios_base::sync_with_stdio(0);
       cin.tie(0);
#ifndef ONLINE_JUDGE
       freopen("in.in", "r", stdin);
#endif
       memset(dp, -1, sizeof dp);
       int t;
       cin >> t;
       while (t--)
       {
              int n, k;
              cin >> n >> k;
              cout << interpolate(n, k) << "\n";
       }
       return 0;
}
