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

const ll N = 1e5 + 5;



int main() {

  IOS;

#ifndef ONLINE_JUDGE

  freopen("input1.txt", "r", stdin);
  freopen("output1.txt", "w", stdout);

#endif

  ll tt; cin >> tt;
  while (tt--) {

    ll a, b, x, y;
    cin >> a >> b >> x >> y;
    if (a == b) {
      d1("no");
      continue;
    }

    ll h = (a - b) * max({x + b, y + b, a - x, a - y});

    if (a * b <= h) {
      d1("yes");

    } else d1("no");



  }

  return 0;

}