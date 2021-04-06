#include <bits/stdc++.h>

#define fastio ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define all(x) (x).begin(), (x).end()

using namespace std;

typedef long long ll;

template <const int &MOD>
struct _m_int {
  int val;
  _m_int(long long v = 0) {
    if (v < 0) v = v % MOD + MOD;
    if (v >= MOD) v %= MOD;
    val = int(v);
  }
  _m_int(uint64_t v) {
    if (v >= MOD) v %= MOD;
    val = int(v);
  }
  _m_int(int v) : _m_int((long long)v) {}
  _m_int(unsigned v) : _m_int(uint64_t(v)) {}
  static int inv_mod(int a, int m = MOD) {
    int g = m, r = a, x = 0, y = 1;
    while (r != 0) {
      int q = g / r;
      g %= r;
      swap(g, r);
      x -= q * y;
      swap(x, y);
    }
    return x < 0 ? x + m : x;
  }
  explicit operator int() const { return val; }
  explicit operator unsigned() const { return val; }
  explicit operator long long() const { return val; }
  explicit operator uint64_t() const { return val; }
  explicit operator double() const { return val; }
  explicit operator long double() const { return val; }
  _m_int &operator+=(const _m_int &other) {
    val -= MOD - other.val;
    if (val < 0) val += MOD;
    return *this;
  }
  _m_int &operator-=(const _m_int &other) {
    val -= other.val;
    if (val < 0) val += MOD;
    return *this;
  }
  static unsigned fast_mod(uint64_t x, unsigned m = MOD) {
#if !defined(_WIN32) || defined(_WIN64)
    return unsigned(x % m);
#endif
    unsigned x_high = unsigned(x >> 32), x_low = unsigned(x);
    unsigned quot, rem;
    asm("divl %4\n"
        : "=a"(quot), "=d"(rem)
        : "d"(x_high), "a"(x_low), "r"(m));
    return rem;
  }
  _m_int &operator*=(const _m_int &other) {
    val = fast_mod(uint64_t(val) * other.val);
    return *this;
  }
  _m_int &operator/=(const _m_int &other) { return *this *= other.inv(); }
  friend _m_int operator+(const _m_int &a, const _m_int &b) { return _m_int(a) += b; }
  friend _m_int operator-(const _m_int &a, const _m_int &b) { return _m_int(a) -= b; }
  friend _m_int operator*(const _m_int &a, const _m_int &b) { return _m_int(a) *= b; }
  friend _m_int operator/(const _m_int &a, const _m_int &b) { return _m_int(a) /= b; }
  _m_int &operator++() {
    val = val == MOD - 1 ? 0 : val + 1;
    return *this;
  }
  _m_int &operator--() {
    val = val == 0 ? MOD - 1 : val - 1;
    return *this;
  }
  _m_int operator++(int) {
    _m_int before = *this;
    ++*this;
    return before;
  }
  _m_int operator--(int) {
    _m_int before = *this;
    --*this;
    return before;
  }
  _m_int operator-() const { return val == 0 ? 0 : MOD - val; }
  friend bool operator==(const _m_int &a, const _m_int &b) { return a.val == b.val; }
  friend bool operator!=(const _m_int &a, const _m_int &b) { return a.val != b.val; }
  friend bool operator<(const _m_int &a, const _m_int &b) { return a.val < b.val; }
  friend bool operator>(const _m_int &a, const _m_int &b) { return a.val > b.val; }
  friend bool operator<=(const _m_int &a, const _m_int &b) { return a.val <= b.val; }
  friend bool operator>=(const _m_int &a, const _m_int &b) { return a.val >= b.val; }
  _m_int inv() const { return inv_mod(val); }
  _m_int pow(long long p) const {
    if (p < 0)
      return inv().pow(-p);
    _m_int a = *this, result = 1;
    while (p > 0) {
      if (p & 1)
        result *= a;
      p >>= 1;
      if (p > 0)
        a *= a;
    }
    return result;
  }
  friend ostream &operator<<(ostream &os, const _m_int &m) { return os << m.val; }
};

const int M = int(1e9) + 7;
using mint = _m_int<M>;

int main() {
  fastio;
  int t;
  cin >> t;
  while (t--) {
    int n, x;
    ll m;
    cin >> n >> x >> m;
    vector<int> a(n);
    for (int &i : a) {
      ll rd;
      cin >> rd;
      i = rd % M;
    }
    mint ans = 0, num = 1, den = 1;
    for (int i = x - 1, j = 0; i >= 0; i--, j++) {
      if (j) {
        num *= m + j - 1;
        den *= j;
      }
      ans += num / den * a[i];
    }
    cout << ans << '\n';
  }
  return 0;
}

/*
A(0, i) = A[i]
A(1, i) = A(0, 0) + A(0, 1) + ... + A(0, i)
A(2, i) = A(1, 0) + A(1, 1) + ... + A(1, i)
        = (A(0, 0)) + (A(0, 0) + A(0, 1)) + ... + (A(0, 0) + A(0, 1) + ... + A(0, i))
        = (i+1)A(0, 0) + (i)A(0, 1) + (i-1)A(0, 2) + (i-2)A(0, 3) + ... + A(0, i)
A(3, i) = A(2, 0) + A(2, 1) + ... + A(2, i)
        = (1.A(0, 0)) + (2.A(0, 0) + 1.A(0, 1)) + ... + ((i+1)A(0, 0) + (i)A(0, 1) + ...)
        = (1+2+3+...+(i+1))A(0, 0) + (1+2+...+i)A(0, 1) + (1+2+...+i-1)A(0, 2) +... + (1)A(0, i)
A(4, i) = A(3, 0) + A(3, 1) + ... + A(3, i)
        = (1)A(0, 0) + ((1+2)A(0,0) + (1)A(0,1)) + ((1+2+3)A(0,0) + (1+2)A(0,1) + 1A(0,0)) + ... +
*/
