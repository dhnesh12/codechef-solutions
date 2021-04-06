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

const int N = 301;
int dp[N][N][N];
// [lft1][lft2][lft3], 
int n;
// if mod 4 is 2, then not possible to write as diff of squares

bool isWin(int lft1, int lft2, int lft3, int rem) 
{
    if (rem == 2) {
        return 1;
    }
    if (!lft1 && !lft2 && !lft3) {
        return 0;
    }
    int &ans = dp[lft1][lft2][lft3];
    if (ans != -1) return ans;
    ans = 0;
    if (lft1) ans |= !isWin(lft1 - 1, lft2, lft3, (rem + 1)&3);
    if (lft2) ans |= !isWin(lft1, lft2 - 1, lft3, (rem + 2)&3);
    if (lft3) ans |= !isWin(lft1, lft2, lft3 - 1, (rem + 3)&3);
    return ans;
}

inline void solve()
{
    read(n);

    array<int, 4> have;
    fill(all(have), 0);

    fr (i, n) {
        int cur;
        read(cur);
        ++have[cur & 3];
    }

    // trace(have);

    bool st = have[0] & 1;

    // now only have rem 1, 2, 3
    clr(dp, -1);
    if (isWin(have[1], have[2], have[3], 0) ^ st) {
        prn("Ghayeeth");
    } else {
        prn("Siroj");
    }
}
