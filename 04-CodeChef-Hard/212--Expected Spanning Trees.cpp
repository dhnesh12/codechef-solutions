// Author: wlzhouzhuan
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define pb push_back
#define fir first
#define sec second
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define per(i, l, r) for (int i = l; i >= r; i--)
#define mset(s, t) memset(s, t, sizeof(s))
#define mcpy(s, t) memcpy(s, t, sizeof(t))
template<typename T1, typename T2> void ckmin(T1 &a, T2 b) { if (a > b) a = b; }
template<typename T1, typename T2> void ckmax(T1 &a, T2 b) { if (a < b) a = b; }
ll read() {
  ll x = 0, f = 0; char ch = getchar();
  while (!isdigit(ch)) f |= ch == '-', ch = getchar();
  while (isdigit(ch)) x = 10 * x + ch - '0', ch = getchar();
  return f ? -x : x;
}
template<typename T> void print(T x) {
  if (x < 0) putchar('-'), x = -x;
  if (x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
template<typename T> void print(T x, char let) {
  print(x), putchar(let);
}

const int N = 105;
const int inf = 1e9;
const int mod = 1e9 + 7;

void add(int &x, int y) {
  if ((x += y) >= mod) x -= mod;
}
void sub(int &x, int y) {
  if ((x -= y) < 0) x += mod;
}
int qpow(int a, int b = mod - 2) {
  if (a < 0) a += mod;
  int res = 1;
  while (b > 0) {
    if (b & 1) res = 1ll * res * a % mod;
    a = 1ll * a * a % mod;
    b >>= 1;
  }
  return res;
}

int fac[N], ifac[N];
void init(int n) {
  fac[0] = ifac[0] = 1;
  rep(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % mod;
  ifac[n] = qpow(fac[n]);
  per(i, n - 1, 1) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
}
int C(int n, int m) {
  assert(n >= m);
  return 1ll * fac[n] * ifac[n - m] % mod * ifac[m] % mod;
}

int n, m, q;

int mp[N][N], a[N][N], eval[N];

int Matrix_tree(int n) {
  int res = 1;
  for (int i = 1; i <= n; i++) {
    int id = i;
    for (int j = i; j <= n; j++) {
      if (a[j][i] > a[id][i]) {
        id = j;
      }
    }
    if (id != i) swap(a[i], a[id]), res = (mod - res) % mod;
    for (int j = i + 1; j <= n; j++) {
      while (a[j][i]) {
        int div = a[i][i] / a[j][i];
        for (int k = i; k <= n; k++) sub(a[i][k], 1ll * a[j][k] * div % mod);
        swap(a[i], a[j]), res = (mod - res) % mod;
      }
    }
    res = 1ll * res * a[i][i] % mod;
  }
  return res;
}
int cnt[N], tmp[N];
void Lagrange() {
  for (int i = 1; i <= n; i++) {
    memset(tmp, 0, sizeof(tmp));
    tmp[0] = 1;
    int fm = 1;
    for (int j = 1; j <= n; j++) {
      if (j == i) continue;
      fm = 1ll * fm * (i + mod - j) % mod;
      for (int k = j; k >= 0; k--) tmp[k] = ((k ? tmp[k - 1] : 0) - 1ll * tmp[k] * j % mod + mod) % mod;
    }
    fm = 1ll * eval[i] * qpow(fm) % mod;
    for (int j = 0; j <= n - 1; j++) add(cnt[j], 1ll * fm * tmp[j] % mod);
  }
}
int coef[N << 1];

int main() {
  init(100);
  n = read(), m = read(), q = read();
  rep(i, 1, m) {
    int u = read(), v = read();
    mp[u][v] = mp[v][u] = 1;
  }
  rep(x, 1, n) {
    rep(i, 1, n) rep(j, 1, n) a[i][j] = 0;
    rep(i, 1, n) rep(j, 1, n) {
      if (mp[i][j]) add(a[i][i], x), sub(a[i][j], x);
      else add(a[i][i], 1), sub(a[i][j], 1);
    } 
    eval[x] = Matrix_tree(n - 1);
//    printf("eval[%d] = %d\n", x, eval[x]);
  }
  Lagrange();
//  for (int i = 0; i <= n - 1; i++) printf("cnt[%d] = %d\n", i, cnt[i]);
  for (int i = 0; i <= n - 1; i++) { // cnt[i]
    for (int k = 0; k <= i; k++) {
      for (int t = 0; t <= n - 1 - i; t++) {
        // e^gx ，-n+1\le g\le n-1 ，指数整体 + (n-1)   
        add(coef[2 * (n - 1) - 2 * i + 2 * (k - t)], 1ll * cnt[i] * C(i, k) % mod * (t & 1 ? mod - 1 : 1) % mod * C(n - 1 - i, t) % mod);
      }
    }
  }
//  for (int i = 0; i <= 2 * (n - 1); i++) printf("coef[%d] = %d\n", i - (n - 1), coef[i]);
  
  int _ = 1ll * (n - 1) * (n - 2) / 2 % mod, iv2 = qpow(qpow(2, n - 1));
  int edge = 1ll * n * (n - 1) / 2 % mod;
  while (q--) {
    ll T = read();
    if (T) T = (T + mod - 2) % (mod - 1) + 1;
    int ans = 0;
    for (int i = 0; i <= 2 * (n - 1); i++) {
      if (coef[i]) add(ans, 1ll * coef[i] * qpow(_ + i - (n - 1), T) % mod);
    }
    print(1ll * ans * iv2 % mod * qpow(qpow(edge, T)) % mod, '\n');
  }
  return 0;
} 