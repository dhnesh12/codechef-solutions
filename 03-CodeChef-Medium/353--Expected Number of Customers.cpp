#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
namespace io {
const int _kReadBufferSize = 1 << 15;
char _readBuffer[_kReadBufferSize];
int _readPos;
int _readLength;
bool _ended = false;
inline void _loadBuffer() {
  _readLength = static_cast<int>(fread(_readBuffer, sizeof(char), _kReadBufferSize, stdin));
  _readPos = 0;
}
inline char readChar(bool advance = true) {
  if (_ended) {
    return 0;
  }
  if (_readPos >= _readLength) {
    _loadBuffer();
    if (_readLength == 0) {
      _ended = true;
      return 0;
    }
  }
  return _readBuffer[advance ? _readPos++ : _readPos];
}
template<typename T>
inline bool readInt(T& res) {
  char ch;
  while (true) {
    ch = readChar(false);
    if (!ch) {
      return false;
    }
    if (!isspace(ch)) {
      break;
    }
    ++_readPos;
  }
  ch = readChar(false);
  bool negative = ch == '-';
  if (negative) {
    ++_readPos;
  }
  res = 0;
  while (true) {
    ch = readChar(false);
    if (!isdigit(ch)) {
      break;
    }
    res = (res << 3) + (res << 1) + (ch & 15);
    ++_readPos;
  }
  if (negative) {
    res = -res;
  }
  return true;
}
const int _kWriteBufferSize = 1 << 15;
int _writePos = 0;
char _writeBuffer[_kWriteBufferSize];
inline void writeChar(char x) {
  if (_writePos == _kWriteBufferSize) {
    fwrite(_writeBuffer, 1, _kWriteBufferSize, stdout);
    _writePos = 0;
  }
  _writeBuffer[_writePos++] = x;
}
struct _Flusher {
  inline void flush() {
    if (_writePos) {
      fwrite(_writeBuffer, 1, _writePos, stdout);
      _writePos = 0;
    }
    fflush(stdout);
  }
  inline ~_Flusher() {
    flush();
  }
} _flusher;
template<class T>
inline void writeInt(T x, int padding = 0) {
  static char s[32];
  if (x < 0) {
    writeChar('-');
    x = -x;
  }
  int n = 0;
  while (x || !n) {
    T newX = x / 10;
    s[n++] = '0' + (x - newX * 10);
    x = newX;
  }
  for (int i = n; i < padding; ++i) {
    writeChar('0');
  }
  for (; n > 0; writeChar(s[--n])) {}
}
} // namespace io
namespace math {
template<typename V = int32_t>
inline V extGcd(V a, V b, V& x, V& y) {
  bool negativeA = false;
  if (a < 0) {
    negativeA = true;
    a = -a;
  }
  bool negativeB = false;
  if (b < 0) {
    negativeB = true;
    b = -b;
  }
  x = 1;
  y = 0;
  V xTmp = 0;
  V yTmp = 1;
  while (b) {
    V q = a / b;
    tie(x, xTmp) = make_tuple(xTmp, x - q * xTmp);
    tie(y, yTmp) = make_tuple(yTmp, y - q * yTmp);
    tie(a, b) = make_tuple(b, a - q * b);
  }
  if (negativeA) {
    x = -x;
  }
  if (negativeB) {
    y = -y;
  }
  return a;
}
template<typename V, typename V_SQR, V MOD>
struct ModInt {
  template<typename T>
  inline static V fix(T v) {
    if (v < 0) {
      v += MOD;
    } else if (v >= MOD) {
      v -= MOD;
    } else {
      return v;
    }
    if (v < 0 || v >= MOD) {
      v %= MOD;
    } else {
      return v;
    }
    if (v < 0) {
      v += MOD;
    } else if (v >= MOD) {
      v -= MOD;
    }
    return v;
  }
  inline ModInt(V_SQR v = 0) {
    _v = fix(v);
  }
  inline void operator+=(const ModInt& o) {
    _v += o._v;
    if (_v >= MOD) {
      _v -= MOD;
    }
  }
  inline void operator-=(const ModInt& o) {
    _v -= o._v;
    if (_v < 0) {
      _v += MOD;
    }
  }
  inline void operator*=(const ModInt& o) {
    _v = fix(static_cast<V_SQR>(_v) * o._v);
  }
  inline ModInt inv() const {
    ModInt res = *this;
    res.invInline();
    return res;
  }
  inline void invInline() {
    V x0, x1;
    extGcd<V>(_v, MOD, x0, x1);
    _v = fix(x0);
  }
  int _v;
};
inline uint32_t nextPow2_32(uint32_t v) {
  if (!v) {
    return 1;
  }
  uint32_t res = 1U << (31 - __builtin_clz(v));
  return res == v ? res : res << 1;
}
template<typename T = double>
struct Complex {
  inline Complex(T _real = 0, T _imag = 0) : real(_real), imag(_imag) {}
  inline Complex<T> operator+(const Complex<T>& o) const {
    return Complex<T>(real + o.real, imag + o.imag);
  }
  inline void operator+=(const Complex<T>& o) {
    real += o.real;
    imag += o.imag;
  }
  inline Complex<T> operator-(const Complex<T>& o) const {
    return Complex<T>(real - o.real, imag - o.imag);
  }
  inline Complex<T> operator*(const Complex<T>& o) const {
    return Complex<T>(real * o.real - imag * o.imag, real * o.imag + o.real * imag);
  }
  inline void operator/=(T scale) {
    real /= scale;
    imag /= scale;
  }
  inline void init(T _real = 0, T _imag = 0) {
    real = _real;
    imag = _imag;
  }
  inline void initPolar(T r, T theta) {
    real = r * cos(theta);
    imag = r * sin(theta);
  }
  inline void initSub(const Complex<T>& x, const Complex<T>& y) {
    real = x.real - y.real;
    imag = x.imag - y.imag;
  }
  inline Complex<T> conj() const {
    return Complex<T>(real, -imag);
  }
  T real, imag;
};
const long double PI = acos(static_cast<long double>(-1));
template<typename T = double>
struct FFTUtils {
  inline static FFTUtils& instance() {
    static FFTUtils instance;
    return instance;
  }
  inline void initCapacity(int capacity) {
    if (_revs.size() >= capacity) {
      return;
    }
    int pow2 = nextPow2_32(max(capacity, 2));
    _revs.reserve(pow2);
    _roots.reserve(pow2);
    if (_revs.size() < 2) {
      _revs.resize(2);
      _revs[0] = 0;
      _revs[1] = 1;
      _roots.resize(2);
      _roots[0].init(0, 0);
      _roots[1].init(1, 0);
    }
    int oldPow2 = _revs.size(), lgN = __builtin_ctz(pow2);
    _revs.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      _revs[i] = (_revs[i >> 1] >> 1) + ((i & 1) << (lgN - 1));
    }
    _roots.resize(pow2);
    for (int i = oldPow2; i < pow2; i <<= 1) {
      T baseAngle = PI / i;
      for (int j = i, k = 1; j < i << 1; j += 2, k += 2) {
        _roots[j] = _roots[j >> 1];
        _roots[j | 1].initPolar(1, baseAngle * k);
      }
    }
  }
  inline void fft(vector<Complex<T>>& cs, bool inverse, int n = -1) {
    int pow2 = nextPow2_32(n < 0 ? cs.size() : n);
    initCapacity(pow2);
    _expand(cs, pow2);
    if (inverse) {
      reverse(cs.begin() + 1, cs.begin() + pow2);
      for (int i = 0; i < pow2; ++i) {
        cs[i] /= pow2;
      }
    }
    int shift = __builtin_ctz(_revs.size()) - __builtin_ctz(pow2);
    for (int i = 0; i < pow2; ++i) {
      int j = _revs[i] >> shift;
      if (i < j) {
        swap(cs[i], cs[j]);
      }
    }
    for (int l = 1; l < pow2; l <<= 1) {
      for (int i = 0; i < pow2; i += l << 1) {
        for (int j = 0; j < l; ++j) {
          Complex<T> c = cs[i + j + l] * _roots[j + l];
          cs[i + j + l].initSub(cs[i + j], c);
          cs[i + j] += c;
        }
      }
    }
  }
  inline void _expand(vector<Complex<T>>& cs, int pow2) {
    int n = cs.size();
    cs.resize(pow2);
    for (size_t i = n; i < pow2; ++i) {
      cs[i].init(0, 0);
    }
  }
  vector<int> _revs;
  vector<Complex<T>> _roots;
};
template<typename T = double>
struct FFTMulModUtils {
  inline static FFTMulModUtils& instance() {
    static FFTMulModUtils instance;
    return instance;
  }
  template<typename V, typename V_SQR, V MOD>
  inline void mulInlineModInt(
      vector<ModInt<V, V_SQR, MOD>>& xs, const vector<ModInt<V, V_SQR, MOD>>& ys, bool cyclic) {
    if (xs.empty() || ys.empty()) {
      xs.clear();
      return;
    }
    int n = cyclic ? max(xs.size(), ys.size()) : xs.size() + ys.size() - 1;
    int pow2 = nextPow2_32(n);
    static vector<Complex<T>> as, bs, cs, ds;
    as.resize(pow2);
    for (size_t i = 0; i < xs.size(); ++i) {
      as[i].init(xs[i]._v >> 15, xs[i]._v & 32767);
    }
    for (size_t i = xs.size(); i < pow2; ++i) {
      as[i].init(0, 0);
    }
    bs.resize(pow2);
    for (size_t i = 0; i < ys.size(); ++i) {
      bs[i].init(ys[i]._v >> 15, ys[i]._v & 32767);
    }
    for (size_t i = ys.size(); i < pow2; ++i) {
      bs[i].init(0, 0);
    }
    auto& fft = FFTUtils<T>::instance();
    fft.fft(as, false, pow2);
    fft.fft(bs, false, pow2);
    cs.resize(pow2);
    ds.resize(pow2);
    for (int i = 0; i < pow2; ++i) {
      int j = (pow2 - 1) & (pow2 - i);
      Complex<T> v1 = as[i] + as[j].conj();
      v1 /= 2;
      Complex<T> v2 = as[i] - as[j].conj();
      v2 /= 2;
      swap(v2.real, v2.imag);
      v2.imag = -v2.imag;
      Complex<T> v3 = bs[i] + bs[j].conj();
      v3 /= 2;
      Complex<T> v4 = bs[i] - bs[j].conj();
      v4 /= 2;
      swap(v4.real, v4.imag);
      v4.imag = -v4.imag;
      cs[j] = v2 * v4;
      swap(cs[j].real, cs[j].imag);
      cs[j].real = -cs[j].real;
      cs[j] += v1 * v3;
      ds[j] = v1 * v4 + v2 * v3;
    }
    fft.fft(cs, false, pow2);
    fft.fft(ds, false, pow2);
    if (xs.size() < n) {
      xs.resize(n);
    }
    for (int i = 0; i < n; ++i) {
      int64_t v1 = static_cast<int64_t>(cs[i].real / pow2 + 0.5) % MOD;
      int64_t v2 = static_cast<int64_t>(ds[i].real / pow2 + 0.5) % MOD;
      int64_t v3 = static_cast<int64_t>(cs[i].imag / pow2 + 0.5) % MOD;
      xs[i] = (((v1 << 15) + v2) << 15) + v3;
    }
  }
};
template<typename FFT_T, typename V, typename V_SQR, V PRIME>
struct FFTPolyModInt : public vector<ModInt<V, V_SQR, PRIME>> {
  inline FFTPolyModInt(int size = 0, V v = 0) {
    this->assign(size, v);
  }
  inline FFTPolyModInt operator-(const FFTPolyModInt& o) const {
    FFTPolyModInt res(max(this->size(), o.size()));
    for (int i = 0; i < static_cast<int>((*this).size()); ++i) {
      res[i] += (*this)[i];
    }
    for (int i = 0; i < static_cast<int>((o).size()); ++i) {
      res[i] -= o[i];
    }
    return res;
  }
  inline void invInline() {
    static FFTPolyModInt res;
    int n = this->size();
    res.resize(n);
    for (int i = (0); i < (n); ++i) {
      res[i] = (*this)[i];
    }
    res._inv(*this, n);
  }
  inline void _inv(FFTPolyModInt& res, int n) {
    if (n == 1) {
      res.resize(1);
      res[0] = (*this)[0].inv();
      return;
    }
    int nHalf = (n + 1) >> 1;
    _inv(res, nHalf);
    static FFTPolyModInt tmp;
    tmp.resize(n);
    for (int i = (0); i < (n); ++i) {
      tmp[i] = (*this)[i];
    }
    auto& fft = FFTMulModUtils<FFT_T>::instance();
    fft.mulInlineModInt(tmp, res, false);
    tmp.resize(n);
    fft.mulInlineModInt(tmp, res, false);
    for (int i = (0); i < (n); ++i) {
      if (i < res.size()) {
        res[i] *= 2;
      } else {
        res.emplace_back(0);
      }
      res[i] -= tmp[i];
    }
  }
};
} // namespace math
const int MOD = 1000000007;
using ModInt = math::ModInt<int, int64_t, MOD>;
using FFT_T = double;
using FFTPolyModInt = math::FFTPolyModInt<FFT_T, int, int64_t, MOD>;
int main() {
  math::FFTUtils<FFT_T>::instance().initCapacity(1 << 18);
  int taskNumber;
  io::readInt(taskNumber);
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int n, m;
    io::readInt(n);
    io::readInt(m);
    ModInt invM = ModInt(m).inv();
    ModInt cur = invM;
    FFTPolyModInt bases(n + 1);
    for (int i = 1; i < bases.size(); ++i) {
      cur *= invM;
      cur *= m - i + 1;
      bases[i] = cur;
    }
    for (int i = 1; i < bases.size(); ++i) {
      bases[i] *= i;
    }
    bases = FFTPolyModInt(1, 1) - bases;
    bases.invInline();
    ModInt res = 0;
    for (int i = 0; i < n; ++i) {
      res += bases[i];
    }
    io::writeInt(res._v);
    io::writeChar('\n');
  }
  return 0;
}