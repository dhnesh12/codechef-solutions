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

void solve() {
	int n; cin >> n;
	vector<pair<int, int>> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i].F >> v[i].S;
	}
	int cnt = 0;
    int pos = -1;
	for (int i = 1; i < n - 1; i++) {
		pair<ld, ld> v1 = {v[i].F - v[i-1].F, v[i].S - v[i-1].S};
		pair<ld, ld> v2 = {v[i+1].F - v[i].F, v[i+1].S - v[i].S};
		ld mdv1 = sqrtl(sq(v1.F) + sq(v1.S));
		ld mdv2 = sqrtl(sq(v2.F) + sq(v2.S));
		ld dot_prod = v1.F * v2.F + v1.S * v2.S;
		dot_prod /= (mdv1 * mdv2);
		if (dot_prod >= acos(PI/4.0l) - EPS and dot_prod <= 1.0l + EPS) {}
		else {
            cnt++;
            pos = i;
        }
	}
	if (!cnt)	cout << "yes ";
	else cout << "no ";
    bool can = false;
    if (!cnt)   can = true;
	for (int j = 0; j < n; j++) {
        if (abs(j-pos) <= 1) {
            for (int x = 0; x <= 50; x++) {
                for (int y = 0; y <= 50; y++) {
                    ii old = v[j];
                    v[j] = {x, y};
                    int res = 0;
                    for (int i = 1; i < n - 1; i++) {
                        pair<ld, ld> v1 = {v[i].F - v[i-1].F, v[i].S - v[i-1].S};
                        pair<ld, ld> v2 = {v[i+1].F - v[i].F, v[i+1].S - v[i].S};
                        ld mdv1 = sqrtl(sq(v1.F) + sq(v1.S));
                        ld mdv2 = sqrtl(sq(v2.F) + sq(v2.S));
                        ld dot_prod = v1.F * v2.F + v1.S * v2.S;
                        dot_prod /= (mdv1 * mdv2);
                        if (dot_prod >= acos(PI/4.0l) - EPS and dot_prod <= 1.0l + EPS) {}
                        else  res++;
                    }
                    v[j] = old;
                    if (!res)   can = true;
                }
            }
        }
    }
    if (can)    cout << "yes\n";
    else    cout << "no\n";
}
int32_t main()
{
    SYNC
	int T; cin >> T;
	while (T--) {
		solve();
	}
    return 0;
}
