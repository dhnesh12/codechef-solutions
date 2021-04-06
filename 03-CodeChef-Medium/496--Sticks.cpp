/*
    Author: Arjan Singh Bal, IIIT Gwalior
    "Everything in this world is magic, except to the magician"
*/

#include						<bits/stdc++.h>
#ifdef LOCAL
#include						"pprint.hpp"
#else
#define trace 					//
#endif

using namespace std;

template <typename Arg1>
void prn(Arg1&& arg1)
{ cout << arg1 << "\n"; }
template <typename Arg1, typename... Args>
void prn(Arg1&& arg1, Args&&... args)
{ cout << arg1 << " "; prn(args...); }

template <typename Arg1>
void prs(Arg1&& arg1)
{ cout << arg1 << " ";}
template <typename Arg1, typename... Args>
void prs(Arg1&& arg1, Args&&... args)
{ cout << arg1 << " "; prs(args...); }

template <typename Arg1>
void read(Arg1&& arg1)
{ cin >> arg1; }
template <typename Arg1, typename... Args>
void read(Arg1&& arg1, Args&&... args)
{ cin >> arg1; read(args...); }

#define ll						long long
#define pii						pair<int, int>
#define pli						pair<ll, int>
#define pil						pair<int, ll>
#define pll						pair<ll, ll>
#define vi						vector<int>
#define vll						vector<ll>
#define vb						vector<bool>
#define vd						vector<double>
#define vs						vector<string>
#define ff						first
#define ss						second
#define pb						push_back
#define eb						emplace_back
#define ppb						pop_back
#define pf						push_front
#define ppf						pop_front
#define vpii					vector<pii>
#define umap					unordered_map
#define all(x)					x.begin(),x.end()
#define clr(a,b)				memset(a,b,sizeof a)
#define fr(i, n)				for (int i = 0; i < n; ++i)
#define fr1(i, n)				for (int i = 1; i <= n; ++i)
#define rfr(i, n)				for (int i = n - 1; i >= 0; --i)
#define precise(x)				cout << fixed << setprecision(x)
typedef double					f80;

inline void solve();

signed main()
{
#ifdef LOCAL
    freopen("in.txt" , "r" , stdin);
    //freopen("out.txt" , "w" , stdout);
#else	
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#endif
    
    int t = 1;
    read(t);
    fr1 (tc, t) {
        // cout << "Case #" << tc << ": ";
        solve();
    }
    return 0;
}

int need;
vpii vec;

bool check(ll tar)
{
    // trace(vec);
    int n1 = vec.size();
    map<ll, int> dp;
    dp[0] = 0;
    int mx = 0;

    for (auto i : vec) {
        ll maxPartner = tar / i.ff;
        auto it = dp.upper_bound(maxPartner);
        --it;
        // trace(*it, i);
        int cur = it->ss;
        if (1LL * i.ff * i.ff <= tar) cur += i.ss;
        else cur += min(2, i.ss);
        dp[i.ff] = cur;
        if (cur >= need) return 1;
    }
    return (mx >= need);
}

inline void solve()
{
    map<int, int> have;
    int n, maxf = 0, k;
    read(n, k);

    fr (i, n) {
        int cur;
        read(cur);
        ++have[cur];
        maxf = max(maxf, have[cur]);
    }

    // // rect can be formed by 4 or 2 + 2
    // // atmost one size can be taken upto 3 times
    // if (have.size() + min(maxf - 1, 2) >= k) {
    //     prn(-1);
    //     return ;
    // }

    // take one of each, then start taking in increasing order
    // start taking extra in increasing order
    need = k - have.size();
    vec.clear();
    
    for (auto i : have) {
        if (i.ss > 1) {
            vec.eb(i.ff, i.ss - 1);
        }
    }

    ll lo = 0, hi = 1e18;
    // trace(check(1));
    // return ;

    while (lo < hi) {
        ll mid = (lo + hi) >> 1;
        // trace(mid, check(mid));
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }

    if (!lo) lo = -1;
    prn(lo);
}
