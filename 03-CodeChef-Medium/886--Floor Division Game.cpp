#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#pragma GCC optimize("-Ofast")
// #pragma GCC optimize("trapv")
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

int n;
int ans[N];
map<ll, int> dp;
int solve(ll x)
{
       if (x > 1000)
              return solve(x / 12);
       if (x == 0)
              return 0;
       if (dp.count(x))
              return dp[x];
       int ret = 0;
       vi ve;
       for (auto u : {2, 3, 4, 5, 6})
       {
              ve.pb(solve(x / u));
       }
       sort(all(ve));
       for (auto u : ve)
       {
              if (u == ret)
              {
                     ++ret;
              }
       }
       return dp[x] = ret;
}

int grund(ll x)
{

       ll now = 6;
       while (x >= now)
       {
              x -= now;
              now *= 12;
       }
       now /= 6;
       if (x / now == 0)
              return 0;
       if (x / now == 1)
              return 1;
       else if (x / now < 4)
              return 2;
       return 3;
}

int main()
{
       ios_base::sync_with_stdio(0);
       cin.tie(0);
#ifndef ONLINE_JUDGE
       freopen("in.in", "r", stdin);
#endif
       int t;
       cin >> t;
       while (t--)
       {
              cin >> n;
              ll ret = 0;
              while (n--)
              {
                     ll x;
                     cin >> x;
                     ret ^= solve(x);
              }
              cout << (ret ? "Henry" : "Derek") << "\n";
       }
       return 0;
}
