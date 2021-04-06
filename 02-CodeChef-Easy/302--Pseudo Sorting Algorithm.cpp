#include<iostream>
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<ll, null_type,less<>, rb_tree_tag,tree_order_statistics_node_update>

#define ll long long
#define FOR(i,a,b)  for(ll i=a;i<=b;i++)
#define FORR(i,a,b)  for(ll i=a;i>=b;i--)
#define vl vector<ll>
#define ld long double
#define vld vector<ld>
#define vvl vector<vector<long long>>
#define vvld vector<vector<ld>>
#define pll pair<long,long>
#define vpll vector<pll>
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define lb(v,x) lower_bound(v.begin(),v.end(),x)
#define ub(v,x) upper_bound(v.begin(),v.end(),x)
#define d1(x) cout<<(x)<<endl
#define d2(x,y) cout<<(x)<<" "<<(y)<<endl
#define d3(x,y,z) cout<<(x)<<" "<<(y)<<" "<<(z)<<endl
#define d4(a,b,c,d) cout<<(a)<<" "<<(b)<<" "<<(c)<<" "<<(d)<<endl
#define PI 3.14159265358979323846264338327950288419716939937510
#define fix(f,n) fixed<<setprecision(n)<<f
#define all(x) x.begin(),x.end()
#define rev(p) reverse(p.begin(),p.end());
#define mset(a,val) memset(a,val,sizeof(a));
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define popcount(x) __builtin_popcountll(x)
#define sz(x) ((ll)x.size())
const ll M = 1000000007;
const ll MM = 998244353;
#define endl "\n"
ll begtime = clock();
#define end_routine() cout << "\n\nTime elapsed: " << (clock() - begtime)*1000/CLOCKS_PER_SEC << " ms\n\n";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T, typename F>
void chmax( T &a, F b) {
  if (b > a)a = b;
}

template<typename T, typename F>
void chmin( T &a, F b) {
  if (b < a)a = b;
}

ll powM(ll a, ll b, ll m) {
  if (b < 0 || a <= 0)return 0;
  a %= m;
  ll ans = 1LL;
  while (b) {
    if (b & 1)ans = ans * a % m;
    a = a * a % m;
    b >>= 1;
  }
  return ans;
}

ll poww(ll a, ll b) {
  if (b < 0 || a <= 0)return 0;
  ll ans = 1LL;
  while (b) {
    if (b & 1)ans = ans * a;
    a = a * a;
    b >>= 1;
  }
  return ans;
}

const ll N = 2e3 + 5;

vl a;
vl sg;

void build(ll x, ll lx, ll rx) {
  if (lx == rx) {
    sg[x] = a[lx];
    return;
  }
  ll mx = (lx + rx) / 2;
  build(2 * x, lx, mx);
  build(2 * x + 1, mx + 1, rx);
  sg[x] = max(sg[2 * x + 1] , sg[2 * x]);
}
/*
void update(ll x, ll lx, ll rx, ll idx, ll v) {
  if (lx == rx) {
    sg[x] = v;
    return;
  }
  ll mx = (lx + rx) / 2;
  if (idx <= mx) {
    update(2 * x, lx, mx, idx, v);
  } else {
    update(2 * x + 1, mx + 1, rx, idx, v);
  }
  sg[x] = (sg[2 * x] + sg[2 * x + 1]);
}

*/

ll calc(ll x, ll lx, ll rx, ll l, ll r, ll val) {
  if (l > r)return -1;
  if (lx >= l && rx <= r) {
    while (lx < rx) {
      ll mx = (lx + rx) / 2;
      if (sg[2 * x] >= val) {
        x = 2 * x;
        rx = mx;
      }
      else {
        x = 2 * x + 1;
        lx = mx + 1;
      }
    }
    if (sg[x] >= val)return lx;
    return -1;
  }

  if (lx > r || rx < l)return -1;

  ll mx = (lx + rx) / 2;

  ll temp = calc(2 * x, lx, mx, l, r, val);

  if (temp == -1) {
    return calc(2 * x + 1, mx + 1, rx, l, r, val);
  }

  return temp;
}




int main() {

  IOS;

#ifndef ONLINE_JUDGE

  freopen("input1.txt", "r", stdin);
  freopen("output1.txt", "w", stdout);

#endif

  ll tt; cin >> tt;
  while (tt--) {
    ll n; cin >> n;
    a.assign(n, 0);
    sg.assign(4 * n, 0);
    FOR(i, 0, n - 1)cin >> a[i];
    build(1, 0, n - 1);
    vpll dp(n);
    dp[0] = {1, a[0]};
    FOR(i, 1, n - 1) {
      if (a[i] >= dp[i - 1].ss) {
        dp[i] = {dp[i - 1].ff + 1, a[i]};
      } else dp[i] = dp[i - 1];
    }
    ll ans = dp[n - 1].ff;
    vl pr(n);
    for (ll i = n - 1; i >= 0; i--) {
      ll idx = calc(1, 0, n - 1, i + 1, n - 1, a[i]);
      if (idx == -1)pr[i] = 1;
      else pr[i] = pr[idx] + 1;
    }

    for (ll i = 0; i < n - 2; i++) {
      ll l1 = dp[i].ff;
      ll idx = calc(1, 0, n - 1, i + 2, n - 1, dp[i].ss);
      if (idx != -1)l1 += pr[idx];
      chmax(ans, l1);
    }
    if (n > 1) chmax(ans, pr[1]);
    cout << ans << endl;

  }





  return 0;
}
