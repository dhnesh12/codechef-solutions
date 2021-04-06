#include <bits/stdc++.h>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#define ri register int
#define ptf printf
using namespace std;
typedef double db;
typedef long double ld;
typedef long long ll;
typedef vector <int> poly;
typedef pair <int, int> pii;
typedef pair <ll, int> pli;
typedef pair <int, ll> pil;
typedef pair <ll, ll> pll;
typedef unsigned long long ulll;
typedef unsigned int uii;
typedef string strr;
#define fi first
#define se second
#define pb push_back
#define ppp pop_back
#define rez resize
const ll Inf = 2e18;
const int rlen = 1 << 20, inf = 1e9;
char buf[rlen], *ib = buf, *ob = buf;
#define gc() (((ib == ob) && (ob = (ib =  buf) + fread(buf, 1, rlen, stdin)), ib == ob) ? -1 : *ib++)
inline int read() {
  static int ans, f;
  static char ch;
  ans = 0, ch = gc(), f = 1;
  while (!isdigit(ch)) f ^= ch == '-', ch = gc();
  while (isdigit(ch)) ans = (ans << 3) + (ans << 1) + (ch ^ 48), ch = gc();
  return f ? ans: -ans;
}
inline ll readl() {
  static ll ans;
  static char ch;
  for (ans = 0, ch = gc(); !isdigit(ch); ch = gc());
  while (isdigit(ch)) ans = ((ans << 2) + ans << 1) + (ch ^ 48), ch = gc();
  return ans;
}
inline int Read(char *s) {
  static int top;
  static char ch;
  top = 0, ch = gc();
  while (!isalpha(ch) && !isdigit(ch)) ch = gc();
  while (isalpha(ch) || isdigit(ch)) s[++top] = ch, ch = gc();
  return top;
}
namespace modular {
  const int mod = 998244353;// = 1e9 + 7;
  //int mod;
  int ret;
  inline int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
  inline int dec(int a, int b) { return a < b ? a - b + mod : a - b; }
  inline int mul(int a, int b) { return (ll) a * b % mod; }
  inline void Add(int &a, int b) { a = a + b < mod ? a + b : a + b - mod; }
  inline void Dec(int &a, int b) { a = a < b? a - b + mod : a - b; }
  inline void Mul(int &a, int b) { a = (ll) a * b % mod; }
  inline int ksm(int a, int p) {
    for (ret = 1; p; p >>= 1, Mul(a, a)) (p & 1) && (Mul(ret, a), 1);
    return ret;
  }
  inline int Inv(int a) { return ksm(a, mod - 2); }
  inline int sqr(int a) { return (ll) a * a % mod; }
  inline int cub(int a) { return (ll) a * a % mod * a % mod; }
} using namespace modular;
template <typename T> inline void ckmax(T &a, T b) { a < b ? a = b : 0; }
template <typename T> inline void ckmin(T &a, T b) { a > b ? a = b : 0; }
template <typename T> inline T Abs(T a) { return a < 0 ? -a : a; }
template <typename T> inline T gcd(T a, T b) {
  T t;
  while (b) t = a, a = b, b = t - t / a * a;
  return a;
}
template <typename T> inline void exgcd(T a, T b, T &x, T &y) {
  if (!b) {
    x = 1, y = 0;
    return;
  }
  exgcd(b, a - a / b * b, y, x);
  y -= a / b * x;
}
const int N = 105, M = 2005;
int a[N][N];
inline int Det(int n) {
  static int ps[N], tp;
  int res = 1;
  for (ri i = 1, pos; i <= n; ++i) {
    for (pos = i; pos <= n; ++pos) if (a[pos][i]) break;
    if (pos > n) return 0;
    if (pos ^ i) {
      res = mod - res;
      for (ri j = i; j <= n; ++j) swap(a[i][j], a[pos][j]);
    }
    ps[tp = 1] = i;
    for (ri j = i + 1; j <= n; ++j) if (a[i][j]) ps[++tp] = j;
    for (ri iv = Inv(a[i][i]), t, j = i + 1; j <= n; ++j) if (a[j][i]) {
      t = mul(iv, a[j][i]);
      for (ri k = 1; k <= tp; ++k) Dec(a[j][ps[k]], mul(a[i][ps[k]], t));
    }
    Mul(res, a[i][i]);
  }
  return res;
}
int X[M], Y[M], w[M], vl[M], tt = 0;
inline poly operator + (poly a, poly b) {
  int n = b.size();
  if (a.size() < n) a.rez(n);
  for (ri i = 0; i < n; ++i) Add(a[i], b[i]);
  return a;
}
inline void operator += (poly &a, poly b) {
  int n = b.size();
  if (a.size() < n) a.rez(n);
  for (ri i = 0; i < n; ++i) Add(a[i], b[i]);
}
inline poly operator * (poly a, int b) {
  for (ri i = 0, n = a.size(); i < n; ++i) if (a[i]) Mul(a[i], b);
  return a;
}
inline poly operator * (poly a, poly b) {
  int n = a.size(), m = b.size(), t = n + m - 1;
  poly c(t);
  for (ri i = 0; i < n; ++i) if (a[i]) for (ri j = 0; j < m; ++j) Add(c[i + j], mul(a[i], b[j]));
  return c;
}
inline void operator *= (poly &a, int b) {
  for (ri i = 0, n = a.size(); i < n; ++i) if (a[i]) Mul(a[i], b);
}
inline void ins(int x, int y) {
  w[++tt] = 1, X[tt] = x, Y[tt] = y;
  for (ri i = 1; i < tt; ++i) {
    Mul(w[i], dec(X[i], x));
    Mul(w[tt], dec(x, X[i]));
  }
}
inline poly lagrange(int n) {
  poly res, pre;
  for (ri i = 0; i <= n; ++i) ins(i, vl[i]);
  for (ri i = 1; i <= tt; ++i) w[i] = mul(Y[i], Inv(w[i]));
  pre = poly(1, 1);
  for (ri i = 1; i <= tt; ++i) {
    poly tp(2, 1);
    tp[0] = mod - X[i];
    pre = pre * tp;
  }
  for (ri i = tt; i; --i) {
    poly tp(pre.size() - 1), tmp;
    for (ri j = (int) tp.size() - 1; ~j; --j) {
      tp[j] = pre[j + 1];
      Add(pre[j], mul(tp[j], X[i]));
    }
    pre.ppp();
    tmp = poly(2, 1);
    tmp[0] = mod - X[i];
    pre = tmp * tp;
    res += tp * w[i];
  }
  return res;
}
int _w;
inline pii operator * (pii a, pii b) {
  return pii(add(mul(a.fi, b.fi), mul(mul(a.se, b.se), _w)), add(mul(a.fi, b.se), mul(a.se, b.fi)));
}
inline pii Ksm(pii a, int k) {
  pii res(1, 0);
  for (; k; k >>= 1, a = a * a) if (k & 1) res = res * a;
  return res;
}
inline int rd() { return rand() | rand() << 15; }
inline int cipolla(int x) {
  while (1) {
    int t = (rd() % mod + mod) % mod;
    _w = dec(mul(t, t), x);
    if (ksm(_w, (mod - 1) >> 1) != mod - 1) continue;
    return Ksm(pii(t, mod - 1), (mod + 1) >> 1).fi;
  }
}
poly G;
inline bool poly_sqrt(poly F) {
  int n = 2000;
  G.rez(n);
  int ps = 0, dt;
  while (ps < n && !F[ps]) ++ps;
  if (ps == n) return 0;
  int val = cipolla(F[ps]), iv = Inv(add(val, val));
  dt = ps >> 1, G[dt] = val;
  for (ri i = ps + 1; i < n; ++i) {
    G[i - dt] = F[i];
    for (ri j = dt + 1; j < i - dt; ++j) Dec(G[i - (ps >> 1)], mul(G[j], G[i - j]));
    Mul(G[i - dt], iv);
  }
  return 1;
}
struct Edge {
  int u, v, w, _w;
  Edge(int u = 0, int v = 0, int w = 0, int _w = 0) : u(u), v(v), w(w), _w(_w) {}
} E[10005];
int n, m, pw[35];
int main() {
  #ifdef ldxcaicai
  freopen("lx.in", "r", stdin);
  #endif
  srand(time(NULL));
  n = read(), m = read();
  for (ri i = 1, u, v, w; i <= m; ++i) {
    u = read() + 1, v = read() + 1, w = read(), _w = (rd() % mod + mod) % mod;
    E[i] = Edge(u, v, w, _w);
  }
  for (ri i = 0; i <= 2000; ++i) {
    for (ri x = 1; x <= n; ++x) for (ri y = 1; y <= n; ++y) a[x][y] = 0;
    pw[0] = 1;
    for (ri j = 1; j <= 20; ++j) pw[j] = mul(pw[j - 1], i);
    for (ri j = 1; j <= m; ++j) {
      int val = mul(pw[E[j].w], E[j]._w);
      a[E[j].u][E[j].v] = val;
      a[E[j].v][E[j].u] = dec(0, val);
    }
    vl[i] = Det(n);
  }
  poly F = lagrange(2000);
  if (!poly_sqrt(F)) return puts("YOU ARE IN TROUBLE"), 0;
  vector <int> ans;
  for (ri i = 0; i < G.size(); ++i) if (G[i]) ans.pb(i);
  cout << ans.size() << '\n';
  for (ri i = 0; i < ans.size(); ++i) cout << ans[i] << ' ';
  return 0;
}