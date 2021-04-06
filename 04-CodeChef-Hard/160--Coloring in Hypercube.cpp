#include <cstdio>
#include <cstring>
typedef long long i64;
const int N = 10, S = 60, MOD = 1000000009;
int n;
i64 l[N], r[N];
int solve(int state) {
  static int layer[S];
  for (int i = 0; i < S; ++i) {
    layer[i] = 0;
    for (int j = 0; j < n; ++j) {
      i64 cur = (state >> j & 1) ? (l[j] - 1) : r[j];
      if (cur < 0) return 0;
      if (cur >> i & 1) layer[i] |= 1 << j;
    }
  }
  static int f[S][1 << N];
  memset(f, 0, sizeof f);
  f[S - 1][0] = 1;
  for (int i = S - 2; i >= 0; --i) {
    for (int s = 0; s < (1 << n); ++s) {
      int cur = f[i + 1][s];
      if (!cur) continue;
      for (int j = 0; j <= n; ++j) {
        if (!(s >> j & 1) && j < n && !(layer[i] >> j & 1)) continue;
        int t = s | (layer[i] & ~(1 << j));
        f[i][t] = (f[i][t] + cur) % MOD;
      }
    }
  }
  int res = 0;
  for (int i = 0; i < (1 << n); ++i) res = (res + f[0][i]) % MOD;
  return res;
}
int main() {
  int tcase;
  for (scanf("%d", &tcase); tcase--;) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%lld", &l[i]);
    for (int i = 0; i < n; ++i) scanf("%lld", &r[i]);
    int ans = 0;
    for (int s = 0; s < (1 << n); ++s) {
      int cur = solve(s);
      if (__builtin_parity(s)) ans = (ans - cur + MOD) % MOD; else ans = (ans + cur) % MOD;
    }
    printf("%d\n", ans);
  }
  return 0;
}