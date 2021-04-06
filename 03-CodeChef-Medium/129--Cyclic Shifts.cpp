#include <bits/stdc++.h>
     
#define all(A) begin(A), end(A)
#define rall(A) rbegin(A), rend(A)
#define sz(A) int(A.size())
#define pb push_back
#define mp make_pair
     
using namespace std;
     
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
typedef vector <int> vi;
typedef vector <ll> vll;
typedef vector <pii> vpii;
typedef vector <pll> vpll;

const int C = 30;

class STree {
private:
  vector <pair <string, int>> st;
  int n;
  void build (int u, int l, int r, const string& s) {
    if (l == r) {
      st[u] = mp(s.substr(l, C), l);
      return;
    }
    int m = (l + r) >> 1;
    int left = u << 1;
    int right = left | 1;
    build(left, l, m, s);
    build(right, m + 1, r, s);
    st[u] = min(st[left], st[right]);
  }
  void update (int u, int l, int r, int L, int R, const string& s) {
    if (r < L or R < l) return;
    if (L <= l and l == r and r <= R) {
      st[u] = mp(s.substr(l, C), l);
      return;
    }
    int m = (l + r) >> 1;
    int left = u << 1;
    int right = left | 1;
    update(left, l, m, L, R, s);
    update(right, m + 1, r, L, R, s);
    st[u] = min(st[left], st[right]);
  }
  pair <string, int> get (int u, int l, int r, int L, int R) {
    if (r < L or R < l) return mp(string(C, 'z'), n);
    if (L <= l and r <= R) return st[u];
    int m = (l + r) >> 1;
    int left = u << 1;
    int right = left | 1;
    return min(get(left, l, m, L, R),
               get(right, m + 1, r, L, R));
  }
public:
  STree (const string& s) {
    st.resize(4 * sz(s));
    n = sz(s) - 1;
    build(1, 0, n, s);
  }
  void update (int L, int R, const string& s) {
    update(1, 0, n, L, R, s);
  }
  pair <string, int> get (int L, int R) {
    return get(1, 0, n, L, R);
  }
};

int main () {
  ios::sync_with_stdio(false); cin.tie(0);
  string s;
  cin >> s;
  STree tree(s);
  int q;
  cin >> q;
  while (q--) {
    int type;
    cin >> type;
    if (type == 0) {
      int pos;
      char ch;
      cin >> pos >> ch;
      pos--;
      s[pos] = ch;
      tree.update(max(0, pos - C + 1), pos, s);
    } else {
      int l, r, p;
      cin >> l >> r >> p;
      l--, r--;
      auto best = mp(string(C, 'z' + 1), -1);
      if (l <= r - C + 1) best = tree.get(l, r - C + 1);
      int from = max(l, r - C + 1);
      int len = r - from + 1;
      string tmp = s.substr(from, len);
      int index = l;
      while (sz(tmp) < C) {
        tmp += s[index];
        index++;
        if (index == r + 1) index = l;
      }
      for (int i = from; i <= r; i++) {
        if (tmp < best.first) {
          best.first = tmp;
          best.second = i;
        }
        tmp = tmp.substr(1) + s[index];
        index++;
        if (index == r + 1) index = l;
      }
      assert(best.second != -1);
      auto get = [&] (int p) {
        p--;
        p += best.second;
        if (p <= r) {
          return s[p];
        }
        p = l + (p - r) - 1;
        assert(l <= p and p <= r);
        return s[p];
      };
      cout << get(p) << '\n';
    }
  }
  return (0);
}
