#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type,less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
#define int long long
#define mp make_pair
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define nbits(x) __builtin_popcount(x)
#define gcd(x, y) __gcd(x, y)
#define SYNC_OFF ios::sync_with_stdio(0); cin.tie(0);  
const int MOD = 1e9 + 7; // 998244353;
const int N = 100100;
const int INF = 1e15; // 1e18;
const double PI = acos(-1);
const int dx[] = {-1,0,1,0,-1,1,1,-1};
const int dy[] = {0,1,0,-1,1,1,-1,-1};
int powmod(int a, int b, int m = MOD) {
    int res = 1;
    a %= m; assert(b >= 0);
    for (; b; b>>=1) {
        if (b & 1) res = res*a % m;
        a = a*a % m;
    }
    return res;
}

int cnt(string& s) {
    int num = 0, rnum = 0, ans = 0;
    for (int i = 0; i < s.size(); i++) {
        num = num * 2 + (s[i] - '0');
        rnum = rnum + (s[i] - '0') * (1<<i);
        ans += i and num == rnum;
    }
    return ans;
}

int solve(string& s) {
    int n = s.size();
    int ans = n;
    for (int p = 2; p <= n; p++) {
        for (int st = 1; st * p <= n; st++) {
            string t;
            for (int i = st; i <= n; i *= p) {
                t += s[i - 1];
            }
            ans += cnt(t);
        }
    }
    return ans;
}

signed main() {
    SYNC_OFF;
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << solve(s) << "\n";
    }
    return 0;
}