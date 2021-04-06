/*One touch and i IGNITE*/
#include<bits/stdc++.h>
using namespace std;
#define cloud_007 ios_base::sync_with_stdio(false),cin.tie(0)
#define ll long long
#define F first
#define S second
#define endl "\n"
#define Endl "\n"

const int sz = 2e5 + 5;
int tc, n, a[sz];
const int mod = 1e9 + 7;

ll bigmod(ll a, ll p, ll m) {
    ll res = 1;
    ll x = a;
    while(p) {
        if(p & 1)res = (res * x) % m;
        x = (x * x) % m;
        p /= 2;
    }

    return res;
}

int main() {
#ifdef cloud007
    freopen("in.txt", "r", stdin);
#endif // cloud007
    cloud_007;
    cin >> tc;
    while(tc--) {
        ll x, y, s, u, v, ans;
        cin >> x >> y >> s >> u >> v;
        if(s % y == 0 && ((s / y) & (s / y - 1)) == 0) {
            s /= y;
            ll p = (s % mod * v) % mod;
            ll inv = bigmod(v - u, mod - 2, mod);
            ans = (inv * p) % mod;
        } else {
            s /= x;
            ll p = (s % mod * v) % mod;
            ll inv = bigmod(u, mod - 2, mod);
            ans = (inv * p) % mod;
        }
        cout << ans << endl;
    }


    return 0;
}
