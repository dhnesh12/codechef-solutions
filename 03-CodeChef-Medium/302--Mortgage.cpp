#define _CRT_SECURE_NO_DEPRECATE
#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include "bits/stdc++.h"
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
//using namespace __gnu_pbds;
#define int long long int
#define SYNC std::ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
#define FRE freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
typedef long double ld;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
typedef vector<ii>   vii;
//typedef tree<int, null_type, less<int>, rb_tree_tag,
//             tree_order_statistics_node_update>
//    ost;
#define rep(i,l,r)   for (int i = (l); i < (r); i++)
#define here cout << " Hey!!\n";
#define  pb push_back
#define  F  first
#define  S  second
#define all(v) (v).begin(),(v).end()
#define sz(a) (int)((a).size())
#define sq(x) ((x)*(x))
template <typename T>
void etch(T V) {
    for (auto x : V)    cout << x << ' ' ;
    cout << '\n';
}
vector<string> vec_splitter(string s) {
    s += ',';
    vector<string> res;
    while(!s.empty()) {
        res.push_back(s.substr(0, s.find(',')));
        s = s.substr(s.find(',') + 1);
    }
    return res;
}
void debug_out(
        vector<string> __attribute__ ((unused)) args,
        __attribute__ ((unused)) int idx,
        __attribute__ ((unused)) int LINE_NUM) { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
    if(idx > 0) cerr << ", "; else cerr << "Line(" << LINE_NUM << ") ";
    stringstream ss; ss << H;
    cerr << args[idx] << " = " << ss.str();
    debug_out(args, idx + 1, LINE_NUM, T...);
}
#ifndef ONLINE_JUDGE
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) 42
#endif
const int MOD = 1e9+7;
const int MOD1 = 998244353;
const int N = 2e5+5;
const int INF = 1000111000111000111LL;
const ld EPS = 1e-12;
const ld PI = 3.141592653589793116;

bool comp(pair<ld, ld> a, pair<ld, ld> b) {
    return a.S < b.S;
}

ld mypow(ld base, int exp) {
    ld ans = 1.0;
    while (exp > 0) {
        if (exp & 1LL)  ans *= base;
        base = base * base;
        exp /= 2;
    }
    return ans;
}

ld reduce(ld p, ld r, int days) {
    return p / mypow(r, days);
}

int32_t main()
{
    SYNC
    int n, m, t; cin >> n >> m >> t;
    vector<pair<ld, ld> > v(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        v[i].F = x;
    }
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        v[i].S = x / 1000000.0l;
    }
    sort(all(v), comp);

    auto can = [&] (ld val) -> bool {
        vector<double> s(n, 0.0);
        for (int i = 0; i < n; i++) {
            if (val >= v[i].F) {
                s[i] = v[i].F;
                val -= s[i];
            } else {
                s[i] = val;
                val = 0.0;
            }
        }
        int lst = n - 1;
        for (int days = 1; days <= m; days++) {
            ld have = t;
            while (lst >= 0 && have > EPS) {
                ld fac = mypow(1.0 + v[lst].S, days);
                if (fac >= INF) return false;
                ld redHave = have / fac;
                if (redHave + EPS >= s[lst]) {
                    have -= (s[lst] * fac);
                    s[lst] = 0.0;
                    lst--;
                } else {
                    s[lst] -= redHave;
                    have = 0.0;
                    if (s[lst] < 0.0)   s[lst] = 0.0, lst--;
                }
            }
        }
        return (lst < 0);
    };  
    ld lo = 0, hi = 1.0;
    for (auto it : v) {
        hi += it.F;
    }
    int lol = 75;
    while (lol--) {
        ld mid = (lo + hi)/2.0;
        // cout << mid << endl;
        if (can(mid)) 
            lo = mid;
        else
            hi = mid;
    }
    cout << fixed << setprecision(9) << lo;
    return 0;
}