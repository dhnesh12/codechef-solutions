#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 300010;
const ll INF = 1000000000000000LL;
int n;
pair<int, pair<ll, ll>> arr[N];
ll dp[N];

struct Line {
  mutable ll k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  static const ll inf = LLONG_MAX;
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(ll k, ll m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};

LineContainer bit[N];

void add(int id, ll m, ll c) {
  for (; id <= n; id += id & -id) {
    bit[id].add(m, c);
  }
}

ll query(int id, ll x) {
  ll ret = INF;
  for (; id > 0; id -= id & -id) {
    ret = min(ret, -bit[id].query(x));
  }
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> arr[i].first;
  for (int i = 1; i <= n; ++i) cin >> arr[i].second.first;
  for (int i = 1; i <= n; ++i) cin >> arr[i].second.second;
  for (int i = 1; i <= n; ++i) add(i, 0, -INF);
  add(1, -(-2*arr[1].second.second), -(arr[1].second.first+arr[1].second.second*arr[1].second.second));
  for (int i = 2; i <= n; ++i) {
    int p = arr[i].first;
    ll a = arr[i].second.first;
    ll h = arr[i].second.second;
    dp[p] = query(p, h) + h*h + a;
    add(p, -(-2LL*h), -(dp[p]+h*h));
  }
  cout << dp[n] << '\n';
}