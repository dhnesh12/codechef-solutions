#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pi;
typedef pair<ll, ll> pll;
#define fi first
#define se second
#define pb push_back
#define ppb pop_back

int main() {
  ll n,a[100010],q,k,t,m;
  ll sm[55],ans;
  bool dp[55][55];
  vector<ll> v;
  scanf("%lld", &n);
  for (ll i=0;i<n;++i) {
    scanf("%lld", a+i);
  }
  scanf("%lld", &q);
  while (q--) {
    scanf("%lld", &k);
    v.clear();
    for (ll i=0;i<n;++i) {
      scanf("%lld", &t);
      if (t) {
        v.pb(a[i]*t);
      }
    }
    m = v.size();
    if (k>m) {
      puts("0");
      continue;
    }
    sm[0] = 0;
    for (ll i=0;i<m;++i) {
      sm[i+1] = sm[i]+v[i];
    }
    ans = 0;
    for (ll y=60;y>=0;--y) {
      ans ^= (1LL<<y);
      memset(dp, 0, sizeof dp);
      dp[0][0] = 1;
      for (ll i=1;i<=m;++i) {
        for (ll j=1;j<=k;++j) {
          for (ll x=1;x<=i;++x) {
            if (((sm[i]-sm[x-1])&ans)==ans && dp[x-1][j-1]) {
              dp[i][j] = 1;
              break;
            }
          }
        }
      }
      if (!dp[m][k]) ans ^= (1LL<<y);
    }
    printf("%lld\n", ans);
  }
  return 0;
}