#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define SPEED ios_base::sync_with_stdio(false); cin.tie(NULL);
#define FOR(i, a, b) for (ll i = a; i < b; ++i)
#define RFOR(i, b, a) for (ll i = b; i >= a; --i)
#define ALL(x) x.begin(), x.end()
#define DEBUG(args...) { string _s = #args; replace(ALL(_s), ' ', '\0');\
replace(ALL(_s), ',', ' ');\
stringstream _ss(_s); istream_iterator<string> _it(_ss); _debug(_it, args);}
#define endl "\n"
#define F first
#define S second
#define pb(x) push_back(x)a
#define mp(x, y) make_pair(x, y)

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void _debug(istream_iterator<string>) {}
template<typename T, typename... Args>
void _debug(istream_iterator<string> it, T first, Args... args) {
    cerr << ">> " << *it << " : " << first << endl; _debug(++it, args...);
}
template <typename T1, typename T2>
inline ostream& operator << (ostream& out, const pair<T1, T2>& p) {
    return out << "(" << p.F << ", " << p.S << ")";
}
template<typename T>
inline ostream& operator << (ostream& out, const vector<T>& v) {
    if (v.empty()) return out << "[]";
    else { out << '['; for (auto& e : v) { out << e << ", "; } return out << "\b\b]"; }
}
template<typename T>
inline ostream& operator << (ostream& out, const set<T>& s) {
    if (s.empty()) return out << "{}";
    else { out << '{'; for (auto& e : s) { out << e << ", "; } return out << "\b\b}"; }
}
template<typename T>
inline ostream& operator << (ostream& out, const unordered_set<T>& s) {
    return out << set<T>(ALL(s));
}
template<typename T1, typename T2>
inline ostream& operator << (ostream& out, const map<T1, T2>& m) {
    if (m.empty()) return out << "{}";
    out << '{'; for (auto& p : m) { out << p << ", "; } return out << "\b\b}";
}
template<typename T1, typename T2>
inline ostream& operator << (ostream& out, const unordered_map<T1, T2>& m) {
    return out << map<T1, T2>(ALL(m));
}
template<typename T>
inline ostream& operator << (ostream& out, const ordered_set<T>& s) {
    return out << set<T>(ALL(s));
}

typedef long long ll;
typedef long double ld;
typedef vector<long long> vll;
typedef pair<ll, ll> pll;
typedef vector<pair<ll, ll>> vpll;
typedef unordered_map<ll, ll> STll;
/************************************** MAIN PROGRAM ********************************************/
const ll MOD = 998244353;

ll myPow(ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}
const ll INF = 2e18;

ll specialPow(ll base, ll exp) {
    ll res = 1;
    for (ll i = 1; i <= exp; ++i) {
        if (res > INF / base) return INF;
        res = res * base;
    }
    return res;
}

int main()
{
    //freopen("input.txt", "r", stdin);
    SPEED
    //DEBUG(myPow(2, 10))

    int t;
    cin >> t;
    FOR(_, 0, t) {
        ll n, m;
        cin >> n >> m;

        auto bad_in_range = [&](ll l, ll r) {
            return r / m - (l - 1) / m;
        };


        auto of_size = [&](ll k) {
            ll r = n / specialPow(m, k - 1);
            ll l = n / specialPow(m, k) + 1;

            return r - l + 1 - bad_in_range(l, r);
        };

        auto ways = [](ll x) {
            if (x & 1) return 1ll;
            return x / 2 + 1;
        };

        ll len = 0;
        ll ans = 1;
        for (int sz = 1; sz <= 60; ++sz) {
            ll cnt = of_size(sz);
            len += cnt * ((sz + 1) / 2);

            ll cur = myPow(ways(sz), cnt, MOD);

            ans = ans * cur % MOD;
        }
        cout << len << ' ' << ans << endl;
    }
}
/************************************** END OF PROGRAM ******************************************/
/** Stuff you should look for:
 * int overflow, array bounds, over-counting
 * special cases (n=1?), set/unordered_set TLE, multi-set/set error
 * do something instead of nothing and stay organized
 */
