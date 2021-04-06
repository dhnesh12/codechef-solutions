#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <cassert>

using namespace std;

const int DEBUG = 0;

#define REP(i, s, n) for (int i = (int)(s); i < (int)(n); ++i)

typedef long long ll;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef pair<int, int> PI;

/*
 * Dependencies: typedef long long ll
 * Headers: iostream
 * Verified by: ARC099-F
 *              https://beta.atcoder.jp/contests/arc099/submissions/2743855
 */

template<ll mod = (ll)998244353>
struct ModInt {
  ll x;
  ModInt(void): x(0) {}
  ModInt(ll x): x(x % mod){}
  ModInt(const ModInt &x): x(x.x) {}
  ModInt operator+(ModInt o) const {
    ll y = x + o.x;
    if (y >= mod) y -= mod;
    return ModInt(y);
  }
  ModInt operator-(ModInt o) const {
    ll y = x - o.x + mod;
    if (y >= mod) y -= mod;
    return ModInt(y);
  }
  ModInt operator*(ModInt o) const {
    return ModInt((x * o.x) % mod);
  }
  void operator+=(ModInt o) { *this = *this + o; }
  void operator-=(ModInt o) { *this = *this - o; }
  void operator*=(ModInt o) { *this = *this * o; }
  ModInt operator-(void) const { return ModInt() - *this; }
  ll to_ll() const {
    return x;
  }
  bool operator<(ModInt o) const {
    return x < o.x;
  }
  ModInt pow(ll e) {
    assert (e >= 0);
    ModInt sum = 1;
    ModInt cur = *this;
    while (e > 0) {
      if (e % 2) {
        sum = sum * cur;
      }
      cur = cur * cur;
      e /= 2;
    }
    return sum;
  }
  ModInt inv(void) {
    return pow(mod - 2);
  }
};

template<ll mod>
ostream &operator<<(ostream &os, ModInt<mod> mi) {
  return os << mi.x;
}

const int M = 245;
int t[M];
const int Q = 1 << 20;
int hot[Q];

const int N = 245;

ModInt<> acc[N];
ModInt<> cur[N]; // down
ModInt<> cur2[N]; // up
ModInt<> nxt[N], nxt2[N];
ModInt<> ans[N];

VI g[N];
VI ch[N];
int par[N];
void dfs(int v, int p) {
  par[v] = p;
  for (int w: g[v]) {
    if (p == w) {
      continue;
    }
    ch[v].push_back(w);
    dfs(w, v);
  }
}

ModInt<> inv[N];


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  REP(i, 1, N) inv[i] = ModInt<>(i).inv();
  int n, m;
  cin >> n;
  REP(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  par[0] = -1;
  dfs(0, -1);
  cin >> m;
  REP(i, 0, m) {
    cin >> t[i];
  }
  int q;
  cin >> q;
  REP(i, 0, m) {
    if (t[i] <= q)
      hot[q - t[i]] += 1;
  }
  cur[0] = 1;
  REP(_, 0, q + 1) {
    if (DEBUG) {
      cerr << "acc:";
      REP(i, 0, n) cerr << " " << acc[i];
      cerr << endl;
      cerr << "cur:";
      REP(i, 0, n) cerr << " " << cur[i];
      cerr << endl;
      cerr << "cur2:";
      REP(i, 0, n) cerr << " " << cur2[i];
      cerr << endl;
    }
    REP(j, 0, n) {
      acc[j] += cur[j];
      acc[j] += cur2[j];
    }
    if (hot[_]) {
      REP(j, 0, n) {
        ans[j] += acc[j] * hot[_];
      }
    }
    // transition
    REP(i, 0, n) nxt[i] = 0;
    // down first
    REP(v, 0, n) {
      ModInt<> val = cur[v] * inv[ch[v].size()];
      if (DEBUG) {
        cerr << "val[" << v << "] = " << val << endl;
      }
      for (int w: ch[v]) {
        nxt[w] = val;
      }
    }
    REP(v, 0, n) nxt2[v] = 0;
    REP(v, 1, n) {
      nxt2[par[v]] += cur2[v];
    }
    REP(v, 0, n) {
      if (ch[v].size()) {
        cur[v] = nxt[v];
      } else {
        cur2[v] = nxt[v];
      }
    }
    REP(v, 1, n) cur2[v] += nxt2[v];
    cur[0] += nxt2[0];
  }
  REP(i, 0, n) {
    cout << ans[i] << (i == n - 1 ? "\n" : " ");
  }
}
