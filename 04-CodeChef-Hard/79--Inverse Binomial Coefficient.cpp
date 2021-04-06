#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstring>

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <stack>
#include <queue>

#include <tuple>

#define getchar getchar_unlocked
#define putchar putchar_unlocked

#define _rep(_1, _2, _3, _4, name, ...) name
#define rep2(i, n) rep3(i, 0, n)
#define rep3(i, a, b) rep4(i, a, b, 1)
#define rep4(i, a, b, c) for (int i = int(a); i < int(b); i += int(c))
#define rep(...) _rep(__VA_ARGS__, rep4, rep3, rep2, _)(__VA_ARGS__)

using namespace std;

using i64 = long long;
using u8 = unsigned char;
using u32 = unsigned;
using u64 = unsigned long long;
using u128 = __uint128_t;
using f80 = long double;

u128 get_u128() {
  int c; u128 ret = 0;
  while ((c = getchar()) < '0');
  ret = c - '0';
  while ((c = getchar()) >= '0') ret = ret * 10 + c - '0';
  return ret;
}

u128 mod_inv_2pow(u128 a) {
  u128 ret = a;
  rep(i, 6) ret *= 2 - ret * a;
  return ret;
}

int ctz(u128 a) {
  u64 lo = a;
  if (lo) return __builtin_ctzll(lo);
  else return __builtin_ctzll(u64(a >> 64)) + 64;
}

void solve() {
  const int N = 120;
  vector<u128> pre(2 * N - 1);
  pre[N - 1] = 1;
  rep(i, 1, N) {
    pre[N - 1 + i] = pre[N - 2 + i] * (2 * i - 1);
    pre[N - 1 - i] = mod_inv_2pow(pre[N - 1 + i]);
    if (i & 1) pre[N - 1 - i] = -pre[N - 1 - i];
  }
  vector<u128> ifs(2 * N - 1, 1); vector<int> fvs(2 * N - 1);
  rep(i, 1, 2 * N - 1) {
    int e = ctz(i);
    fvs[i] = fvs[i - 1] + e;
    ifs[i] = ifs[i - 1] * mod_inv_2pow(i >> e);
  }
  auto fact_p = [&] (u128 n) {
    u128 ret = (n & 1) ? n : 1;
    n = ((n >> 1) + N - 1);
    if (n < 2 * N - 1) return ret * pre[n];
    int vs[2 * N - 1]; u128 inv[2 * N - 1];
    int v = 0; u128 prod = 1;
    rep(i, 2 * N - 1) {
      v += vs[i] = ctz(n - i);
      inv[i] = prod;
      prod *= (n - i) >> vs[i];
    }
    u128 iprod = mod_inv_2pow(prod);
    for (int i = 2 * N - 2; i >= 0; --i) {
      inv[i] *= iprod;
      iprod *= (n - i) >> vs[i];
    }
    u128 s = 0;
    rep(i, 2 * N - 1) {
      int j = 2 * N - 2 - i;
      int ex = v - vs[i] - fvs[j] - fvs[i];
      if (ex >= N) continue;
      u128 denom = ifs[j] * ifs[i];
      if (j & 1) denom = -denom;
      s += (prod * inv[i] * denom * pre[i]) << ex;
    }
    assert(s & 1);
    return ret * s;
  };

  vector<u128> fact_p_pre(N + 1);
  rep(i, N + 1) fact_p_pre[i] = fact_p((u128(1) << i) - 1);

  int T; scanf("%d", &T);
  rep(_, T) {
    int n; scanf("%d", &n);
    u128 r = get_u128();
    if (!(r & 1)) {
      puts("-1");
    } else {
      const int parity = (r >> 1) & 1;
      u128 ans = 0, binom = 1, numer = 3;
      rep(i, 3, n + 1) {
        numer = numer * 2 + 1;
        binom *= fact_p_pre[i];
        binom *= mod_inv_2pow(fact_p(2 * ans) * fact_p(numer - 2 * ans));
        u128 cbinom = binom;
        if (parity) cbinom = cbinom * (numer - 2 * ans) * mod_inv_2pow(2 * ans + 1);
        if ((cbinom & numer) != (r & numer)) {
          int s = ctz(2 * ans + 2);
          binom *= ((numer - 2 * ans - 0) >> 0) * mod_inv_2pow((2 * ans + 1) >> 0);
          binom *= ((numer - 2 * ans - 1) >> s) * mod_inv_2pow((2 * ans + 2) >> s);
          ans += 1;
        }
        ans <<= 1;
      }
      ans += parity;
      const u64 ten19 = 1e19;
      if (ans >= ten19) printf("%llu%019llu\n", u64(ans / ten19), u64(ans % ten19));
      else printf("%llu\n", (u64) ans);
    }
  }
}

int main() {
  clock_t beg = clock();
  solve();
  clock_t end = clock();
  fprintf(stderr, "%.3f sec\n", double(end - beg) / CLOCKS_PER_SEC);
  return 0;
}
