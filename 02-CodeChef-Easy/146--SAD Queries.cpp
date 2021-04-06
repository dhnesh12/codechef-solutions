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

unordered_map<int, int> dp[N];

int32_t main()
{
    SYNC
    int k; cin >> k;
    vector<vector<int>> a(k);
    vector<vector<int>> cum(k);
    for (int i = 0; i < k; i++) {
        int l; cin >> l;
        a[i].resize(l);
        cum[i].assign(l, 0);
        for (auto &x : a[i])    cin >> x;
        sort(all(a[i]));
        cum[i][0] = a[i][0];
        for (int j = 1; j < l; j++) {
            cum[i][j] = cum[i][j-1] + a[i][j];
        }
    }
    int Q; cin >> Q;
    auto get_sum = [&] (int l, int r, int &idx) -> int {
        if (!l) return cum[idx][r];
        else    return cum[idx][r] - cum[idx][l-1];
    };
    while (Q--) {
        int l, r; cin >> l >> r;
        l--, r--;
        if (dp[l].count(r)) {
            cout << dp[l][r] << '\n';
            continue;
        }
        if (sz(a[l]) > sz(a[r]))    swap(l, r);
        int cost = 0;
        for (auto x : a[l]) {
            int cnt = lower_bound(all(a[r]), x) - a[r].begin();
            if (cnt) {
                cost += (cnt * x - get_sum(0, cnt - 1, r));
            }
            cnt = sz(a[r]) - cnt;
            if (cnt) {
                cost += (get_sum(sz(a[r]) - cnt, sz(a[r]) - 1, r)  - cnt * x);
            }
        }
        dp[l][r] = cost;
        dp[r][l] = cost;
        cout << cost << '\n';
    }
    return 0;
}