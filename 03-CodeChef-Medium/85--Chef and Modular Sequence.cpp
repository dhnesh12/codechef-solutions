#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <functional>
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

namespace math {

template<typename T>
inline int ctz(T n) {
  if (!n) {
    return numeric_limits<T>::digits + numeric_limits<T>::is_signed;
  }
  for (int res = 0; n; res += 32, n >>= 16, n >>= 16) {
    uint32_t part = static_cast<uint32_t>(n & 0xFFFFFFFFU);
    if (part) {
      return res + __builtin_ctz(part);
    }
  }
  return -1;
}

} // namespace math

namespace math {

template<typename V>
inline V gcd(V a, V b) {
  if (!a || !b) {
    return a | b;
  }
  int shift = ctz(a | b);
  a >>= ctz(a);
  do {
    b >>= ctz(b);
    if (a > b) {
      swap(a, b);
    }
    b -= a;
  } while (b);
  return a << shift;
}

} // namespace math

namespace collections {

template<typename T>
struct Vector2D {
  inline Vector2D() {}

  inline Vector2D(int n, int valueCap = -1) {
    init(n, valueCap);
  }

  inline void init(int n, int valueCap = -1) {
    _n = n;
    lastOut.assign(n, -1);
    if (valueCap > 0) {
      nxtOut.reserve(valueCap);
      values.reserve(valueCap);
    }
    nxtOut.clear();
    values.clear();
    _edgeIdx = 0;
  }

  template<class... Args>
  inline void emplaceBack(int x, Args&&... args) {
    nxtOut.push_back(lastOut[x]);
    lastOut[x] = _edgeIdx++;
    values.emplace_back(forward<Args>(args)...);
  }

  vector<int> lastOut, nxtOut;
  vector<T> values;
  int _n, _edgeIdx;
};

} // namespace collections

namespace math {

template<typename V = int>
inline void slightFixModInline(V& v, const V& mod) {
  if (v < 0) {
    v += mod;
  }
  if (v >= mod) {
    v -= mod;
  }
}

} // namespace math

namespace math {

template<typename V = int>
inline void fixModInline(V& v, const V& mod) {
  slightFixModInline<V>(v, mod);
  if (v < 0 || mod <= v) {
    v %= mod;
    slightFixModInline<V>(v, mod);
  }
}

} // namespace math

namespace math {

template<typename V = int32_t>
inline V fixMod(const V& v, const V& mod) {
  V res = v;
  fixModInline<V>(res, mod);
  return res;
}

} // namespace math

namespace collections {

template<typename K, typename V>
struct Hashmap {
  inline Hashmap() {}

  inline Hashmap(int size, int keyCap = -1) {
    init(size, keyCap);
  }

  inline void init(int size, int keyCap = -1) {
    _vs.init(size, keyCap);
  }

  inline void set(K key, V value, bool forceEmplaceBack = false) {
    int idx = math::fixMod<K>(key, _vs._n);
    if (forceEmplaceBack) {
      _vs.emplaceBack(idx, key, value);
      return;
    }
    int edgeIdx = _getEdgeIdx(idx, key);
    if (edgeIdx >= 0) {
      _vs.values[edgeIdx].second = value;
    } else {
      _vs.emplaceBack(idx, key, value);
    }
  }

  inline const V* getPtr(K key) const {
    int edgeIdx = _getEdgeIdx(math::fixMod<K>(key, _vs._n), key);
    return edgeIdx >= 0 ? &_vs.values[edgeIdx].second : nullptr;
  }

  inline int _getEdgeIdx(int idx, K key) const {
    for (int edgeIdx = _vs.lastOut[idx]; edgeIdx >= 0;
         edgeIdx = _vs.nxtOut[edgeIdx]) {
      if (_vs.values[edgeIdx].first == key) {
        return edgeIdx;
      }
    }
    return -1;
  }

  Vector2D<pair<K, V>> _vs;
};

} // namespace collections

namespace math {

template<typename V = int32_t, typename V_SQR = int64_t>
inline void mulModInline(V& res, V x, const V& mod) {
  if (!res || !x) {
    res = 0;
  } else if (res < mod / x) {
    res *= x;
  } else {
    res = static_cast<V_SQR>(res) * x % mod;
  }
}

} // namespace math

namespace math {

template<typename V = int32_t, typename EXP = int32_t, typename V_SQR = int64_t>
inline V expMod(V base, EXP exp, const V& mod) {
  V res = 1;
  for (; exp > 0; exp >>= 1) {
    if (exp & 1) {
      mulModInline<V, V_SQR>(res, base, mod);
    }
    mulModInline<V, V_SQR>(base, base, mod);
  }
  return res;
}

} // namespace math

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

} // namespace math

namespace math {

template<typename V = int32_t>
inline V invMod(V a, const V& mod) {
  V x0, x1, gcd = extGcd(a, mod, x0, x1);
  if (gcd != 1) {}
  slightFixModInline(x0, mod);
  return x0;
}

} // namespace math

namespace math {

template<typename V = int32_t, typename V_SQR = int64_t>
inline V mulMod(V a, const V& b, const V& mod) {
  mulModInline<V, V_SQR>(a, b, mod);
  return a;
}

} // namespace math

namespace math {

template<typename V = int32_t, typename V_SQR = int64_t>
struct LogModCoPrime {
  inline LogModCoPrime() {}

  inline LogModCoPrime(
      int hashMapSize, bool positiveResultOnly = false, int keyCap = -1) {
    init(hashMapSize, positiveResultOnly, keyCap);
  }

  inline void
  init(int hashMapSize, bool positiveResultOnly = false, int keyCap = -1) {
    _hashMapSize = hashMapSize;
    _positiveResultOnly = positiveResultOnly;
    _keyCap = keyCap;
  }

  inline void precomputeFixedBaseMod(V base, V mod, int step, V k = 1) {
    _mod = mod;
    _step = step;
    _maxStepCnt = _mod / _step + 5;

    fixModInline(base, mod);
    _invBase = invMod<V>(base, mod);
    _invBasePowStep = expMod<V, V, V_SQR>(_invBase, step, mod);
    _vals.init(_hashMapSize, _keyCap);
    V cur = fixMod<V>(k, mod);
    int totalStep = _step + !_positiveResultOnly;
    for (int q = 0; q < totalStep; ++q) {
      _vals.set(cur, q, true /* forceEmplaceBack */);
      cur = mulMod<V, V_SQR>(cur, _invBase, mod);
    }
  }

  inline V calcFixedBaseMod(V remainder, bool& exist) {
    exist = false;
    fixModInline(remainder, _mod);
    V cur = remainder;
    for (int p = 1; p <= _maxStepCnt; ++p) {
      cur = mulMod<V, V_SQR>(cur, _invBasePowStep, _mod);
      auto* pos = _vals.getPtr(cur);
      if (pos) {
        exist = true;
        return _step * p - *pos;
      }
    }
    return 0;
  }

  inline V calc(V base, V remainder, V mod, bool& exist, V k = 1) {
    precomputeFixedBaseMod(base, mod, static_cast<int>(sqrt(mod) + 1), k);
    return calcFixedBaseMod(remainder, exist);
  }

  collections::Hashmap<V, int> _vals;
  int _hashMapSize, _keyCap, _step, _maxStepCnt;
  bool _positiveResultOnly;
  V _invBase, _invBasePowStep, _mod;
};

} // namespace math

const int HASH_SIZE = 1000003;
const int HASH_KEY_CNT = 2000000;
const int BOUND = 10000;

const int MOD = 100000007;
const int PHI = MOD - 1;
const int ROOT = 5;

math::LogModCoPrime<> logMod;
vector<int> logs;
vector<pair<int, int>> vs;

inline int64_t calc(int base) {
  int64_t res = 0;
  int curMin = MOD;
  for (int curV = base; curMin >= BOUND; curV = math::mulMod(curV, base, MOD)) {
    if (curMin <= curV) {
      continue;
    }
    curMin = curV;
    res += curV;
  }
  if (curMin == 1) {
    return res;
  }
  bool exist;
  int logBase = logMod.calcFixedBaseMod(base, exist);
  int gcd = math::gcd(logBase, PHI);
  int rLogBase = logBase / gcd;
  int phi = PHI / gcd;
  int invRLogBase = math::invMod(math::fixMod(rLogBase, phi), phi);
  int pos = MOD;
  for (int i = 1; i < curMin; ++i) {
    if (logs[i] % gcd) {
      continue;
    }
    int newPos =
        math::mulMod(math::fixMod(logs[i] / gcd, phi), invRLogBase, phi);
    if (!newPos) {
      newPos = phi;
    }
    if (pos > newPos) {
      pos = newPos;
      res += i;
    }
  }
  return res;
}

int main() {
  int taskNumber;
  scanf("%d", &taskNumber);
  vs.reserve(HASH_KEY_CNT);
  logMod.init(HASH_SIZE, true, HASH_KEY_CNT);
  logMod.precomputeFixedBaseMod(
      ROOT, MOD, static_cast<int>(sqrt(MOD) * sqrt(BOUND) + 1));
  logs.assign(BOUND, 0);
  for (int i = 1; i < BOUND; ++i) {
    bool exist;
    logs[i] = logMod.calcFixedBaseMod(i, exist);
  }
  for (int taskIdx = 0; taskIdx < taskNumber; ++taskIdx) {
    int base;
    scanf("%d", &base);
    printf("%lld\n", calc(base));
  }
  return 0;
}
