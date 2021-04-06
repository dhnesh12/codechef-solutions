#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
//#include <sys/resource.h>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;
typedef vector<vector<pair<int, int>>> vvpii;
typedef vector<ll> vl;
typedef vector<vector<ll>> vvl;
typedef pair<ll, ll> pll;
typedef vector<vector<pair<ll, ll>>> vvpll;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
pbds;

#define fbo find_by_order
#define ook order_of_key

template<typename T, typename U> static void amin(
  T &x, U y) {
  if(y < x) {
    x = y;
  }
}

template<typename T, typename U> static void amax(
  T &x, U y) {
  if(x < y) {
    x = y;
  }
}

#ifdef loc
template<class T, class U>
  ostream &operator<<(ostream &out, const pair<T, U> &a) {
  out << "[" << a.first << " " << a.second << "]";
  return out;
}
template<class T>
  ostream &operator<<(ostream &out, const vector<T> &a) {
  for(auto &it : a) {
    out << it << " ";
  }
  return out;
}
template<class T>
  ostream &operator<<(ostream &out, const set<T> &a) {
    for(auto &it : a) {
      out << it << " ";
    }
    return out;
  }
template<class T>
  ostream &operator<<(ostream &out, const multiset<T> &a) {
  for(auto &it : a) {
    out << it << " ";
  }
  return out;
}
template<class T, class U>
  ostream &operator<<(ostream &out, const map<T, U> &a) {
  for(auto &it : a) {
    out << it.first << " -> " << it.second << " | ";
  }
  return out;
}
template<class T, class U>
  ostream &operator<<(ostream &out, const multimap<T, U> &a) {
  for(auto &it : a) {
    out << it.first << " -> " << it.second << " | ";
  }
  return out;
}
#define pra(a, n) cerr << #a << " : "; for(int i = 0; i <= n; ++i) cerr << a[i] << " "; cerr << endl;
#define praa(a, n, m) cerr << #a << " : " << endl; for(int i = 0; i <= n; ++i) { for(int j = 0;j <= m; ++j) cerr << a[i][j] << " "; cerr << endl; }
#define pr(...) __f(#__VA_ARGS__, __VA_ARGS__)
#define prl() cerr << __LINE__ << ": " << __PRETTY_FUNCTION__ << endl;
template <typename Arg1>
void __f(const char *name, Arg1 &&arg1) {
  cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char *names, Arg1 &&arg1, Args &&... args) {
  const char *comma = strchr(names + 1, ',');
  cerr.write(names, comma - names) << " : " << arg1 << " | ";
  __f(comma + 1, args...);
}
#else
#define pr(...)
#define pra(a,n)
#define praa(a,n,m)
#define prl()
#endif

#define inc_stack_limit const rlim_t kStackSize = 64 * 1024 * 1024; struct rlimit rl; rl.rlim_cur = kStackSize; setrlimit(RLIMIT_STACK, &rl);
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define sz(a) int(a.size())
#define rep(i, s, n)  for(int i = s; i <= n; ++i)
#define rev(i, n, s)  for(int i = n; i >= s; --i)
#define fore(x, a) for(auto &&x : a)
#define fill(a, x) memset((a), (x), sizeof(a))
#define tcase int __T; cin >> __T; rep(Tc, 1, __T)
#define F first
#define S second
#define gc getchar

const int mod = 1000000007;
const int S = 1000005;
const ll inf = mod * (ll)mod;
const double eps = 1e-12;
const double pi = 4.0 * atan(1.0);

#define y1 aslkdjf
#define y0 kaasdflkj

int x1[S], y1[S], x2[S], y2[S];
int x0, y0;
double d[S];

int main() {
#ifdef loc
  if(!freopen((string(FOLDER) + "inp.txt").c_str(), "r", stdin)) {
    assert(0);
  }
  freopen((string(FOLDER) + "out.txt").c_str(), "w", stdout);
#endif
  fast_io;
  int n;
  cin >> n;
  rep(i, 1, n) {
    cin >> x1[i] >> y1[i];
    x2[i] = x2[i - 1] - x1[i];
    y2[i] = y2[i - 1] - y1[i];
    swap(x2[i], y2[i]);
    x2[i] = -x2[i];
    x2[i] += x1[i];
    y2[i] += y1[i];
    d[i] = pi / 2.0 * sqrt((x1[i] - x2[i]) * (ll)(x1[i] - x2[i]) +
                           (y1[i] - y2[i]) * (ll)(y1[i] - y2[i]));
    d[i] += d[i - 1];
  }
  int q;
  cin >> q;
  while(q-- > 0) {
    cin >> x0 >> y0;
    int lo = 0, hi = n;
    while(lo < hi) {
      int mi = (lo + hi) / 2;
      if(sqrt((x0 - x2[mi]) * (ll)(x0 - x2[mi]) + (y0 - y2[mi]) * (ll)(
                y0 - y2[mi])) <= d[mi]) {
        hi = mi;
      } else {
        lo = mi + 1;
      }
    }
    double ans = 0.0;
    pr(lo);
    if(lo > 0) {
      lo--;
      double l = d[lo], r = d[lo + 1];
      int step = 60;
      double x = x2[lo], y = y2[lo];
      while(step-- > 0) {
        if(abs(r - l) < eps) {
          break;
        }
        double m = (l + r) / 2.0;
        double theta = ((m - d[lo]) / (d[lo + 1] - d[lo])) * pi / 2.0;
        x = x1[lo + 1] + cos(theta) * (x2[lo] - x1[lo + 1]) - sin(theta) *
            (y2[lo] - y1[lo + 1]);
        y = y1[lo + 1] + sin(theta) * (x2[lo] - x1[lo + 1]) + cos(theta) *
            (y2[lo] - y1[lo + 1]);
        if(sqrt((x0 - x) * (x0 - x) + (y0 - y) * (y0 - y)) <= m) {
          r = m;
        } else {
          l = m;
        }
      }
      ans = max(l, sqrt((x0 - x) * (x0 - x) + (y0 - y) * (y0 - y)));
    }
    cout << fixed << setprecision(10) << ans << '\n';
  }
  return 0;
}