#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef int ll;
typedef long double ld;
const ll N = 1000005;
ll inf = 1e16, mod = 1e9 + 7;
char en = '\n';
ll abs1(ll x){if (x < 0){return -x;}return x;}
ll power(ll x, ll n, ll mod){ll res = 1; x %= mod;
    while (n){if (n & 1){res = (res * x) % mod;} x = (x * x) % mod; n >>= 1; }return res;}
int32_t main(){ios_base::sync_with_stdio(false); cin.tie(NULL); ll t; cin >> t;
  while (t--){ll n; string s; cin >> n >> s; ll m = s.length();
    if (n <= m){cout << 0 << en; continue;}
        cout << (power(26,n-m,mod)+25*m%mod*power(26,n-m-1,mod)%mod)%mod << en;}}