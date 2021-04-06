//author: hitch_hiker42;
#include<bits/stdc++.h>
using namespace std;

//solution:
#define int int64_t
constexpr int mod = 998244353;

struct segtree {
  int n;
  static inline int size = 1;
  vector<int> t1, t2, lazy;
  segtree() = default;
  segtree(int n): n(n) {
    while(size < n) size <<= 1;
    t1.assign(size << 1, 0);
    t2.assign(size << 1, 0);
    lazy.assign(size << 1, 0);
  }
  void build(vector<int>& a, int x = 0, int l = 0, int r = size) {
    if(r - l == 1) {
      if(l < n) {
        t1[x] = a[l];
        t2[x] = a[l] * a[l] % mod;
        return;
      }
      return;
    }
    int m = l + r >> 1;
    build(a, 2 * x + 1, l, m);
    build(a, 2 * x + 2, m, r);
    t1[x] = (t1[2 * x + 1] + t1[2 * x + 2]) % mod;
    t2[x] = (t2[2 * x + 1] + t2[2 * x + 2]) % mod;
  }
  void push(int x, int l, int r) {
    int m = l + r >> 1;
    (t2[2 * x + 1] += (2 * lazy[x] * t1[2 * x + 1] % mod + lazy[x] * lazy[x] % mod * (m - l) % mod) % mod) %= mod;
    (t2[2 * x + 2] += (2 * lazy[x] * t1[2 * x + 2] % mod + lazy[x] * lazy[x] % mod * (r - m) % mod) % mod) %= mod;
    (t1[2 * x + 1] += (m - l) * lazy[x] % mod) %= mod;
    (t1[2 * x + 2] += (r - m) * lazy[x] % mod) %= mod;
    (lazy[2 * x + 1] += lazy[x]) %= mod;
    (lazy[2 * x + 2] += lazy[x]) %= mod;
    lazy[x] = 0;
  }
  int query(int lo, int hi, int x = 0, int l = 0, int r = size) {
    if(lo >= r || l >= hi) return 0;
    if(lo <= l and r <= hi) return t2[x];
    push(x, l, r);
    int m = l + r >> 1;
    return (query(lo, hi, 2 * x + 1, l, m) + query(lo, hi, 2 * x + 2, m, r)) % mod;
  }
  void update(int lo, int hi, int v, int x = 0, int l = 0, int r = size) {
    if(lo >= r || l >= hi) return;
    if(lo <= l and r <= hi) {
      (t2[x] += (2 * v * t1[x] % mod + v * v % mod * (r - l) % mod) % mod) %= mod;
      (t1[x] += (r - l) * v % mod) %= mod;
      (lazy[x] += v) %= mod;
      return;
    }
    push(x, l, r);
    int m = l + r >> 1;
    update(lo, hi, v, 2 * x + 1, l, m);
    update(lo, hi, v, 2 * x + 2, m, r);
    t2[x] = (t2[2 * x + 1] + t2[2 * x + 2]) % mod;
    t1[x] = (t1[2 * x + 1] + t1[2 * x + 2]) % mod;
  }
};

void hike() {
  int n, m, q; cin >> n >> m >> q;
  vector<int> a(n), b{0};
  for(int& i: a) cin >> i;
  for(int i = 0, k = n - m + 1, sum = 0; i < n; ++i) {
    if(i < k) {
      (sum += a[i]) %= mod;
      (b.front() += a[i]) %= mod;
      continue;
    }
    (sum += a[i] - a[i - k]) %= mod;
    b.push_back(sum);
  }
  segtree s(m); s.build(b);
  while(q--) {
    int i, v; cin >> i >> v;
    int l = max((int)1, i - (n - m)), r = min(m, i);
    l--;
    s.update(l, r, ((v - a[i - 1]) % mod + mod) % mod);
    a[i - 1] = v;
    cout << s.query(0, m) << "\n";
  }
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);
  int t = 1; cin >> t;
  while(t--) hike();
  return 0;
} //farewell, until we meet again..