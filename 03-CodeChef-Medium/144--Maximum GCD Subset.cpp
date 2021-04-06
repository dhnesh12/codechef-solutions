#include <bits/stdc++.h>

using namespace std;

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
  return '"' + s + '"';
}

string to_string(const char* s) {
  return to_string((string) s);
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}

template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

#define end END

const int N = 100010;

vector<int> divs[N];
vector<int> who[N];
int when[N];
int tt;
vector<int> ds;

vector<int> g[N];
int pos[N];
int end[N];
int tau;

inline bool Anc(int x, int y) {
  return (pos[x] <= pos[y] && end[y] <= end[x]);
}

int x[N];
int v[N];

void Dfs(int vv, int pr) {
  for (int j : divs[x[vv]]) {
    if (when[j] != tt) {
      when[j] = tt;
      who[j].clear();
      ds.push_back(j);
    }
    who[j].push_back(vv);
  }
  pos[vv] = tau++;
  for (int u : g[vv]) {
    if (u != pr) {
      Dfs(u, vv);
    }
  }
  end[vv] = tau - 1;
}

long long dp[N];
vector<int> children[N];
int st[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  for (int i = 2; i < N; i++) {
    for (int j = i; j < N; j += i) {
      divs[j].push_back(i);
    }
  }
  memset(when, -1, sizeof(when));
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
      g[i].clear();
    }
    for (int i = 0; i < n - 1; i++) {
      int xx, yy;
      cin >> xx >> yy;
      --xx; --yy;
      g[xx].push_back(yy);
      g[yy].push_back(xx);
    }
    for (int i = 0; i < n; i++) {
      cin >> x[i] >> v[i];
    }
    ds.clear();
    tau = 0;
    Dfs(0, -1);
    long long ans = -1;
    int ans_d = -1;
    vector<int> ans_v;
    x[n] = 1;
    v[n] = 0;
    st[0] = n;
    for (int d : ds) {
      int ns = 1;
      dp[n] = 0;
      for (int it = 0; it <= (int) who[d].size(); it++) {
        int ver = (it < (int) who[d].size() ? who[d][it] : -1);
        while (ns > 0 && (ver == -1 || (st[ns - 1] != n && !Anc(st[ns - 1], ver)))) {
          int u = st[ns - 1];
          dp[u] = max(dp[u], (long long) v[u]);
          --ns;
          if (ns == 0) {
            assert(ver == -1 && u == n);
            long long cur = dp[u] * d;
            if (cur > ans) {
              ans = cur;
              ans_d = d;
            }
          } else {
            dp[st[ns - 1]] += dp[u];
          }
        }
        if (ver == -1) {
          break;
        }
        dp[ver] = 0;
        st[ns++] = ver;
      }
    }
    {
      int d = ans_d;
      int ns = 1;
      dp[n] = 0;
      children[n].clear();
      for (int it = 0; it <= (int) who[d].size(); it++) {
        int ver = (it < (int) who[d].size() ? who[d][it] : -1);
        while (ns > 0 && (ver == -1 || (st[ns - 1] != n && !Anc(st[ns - 1], ver)))) {
          int u = st[ns - 1];
          dp[u] = max(dp[u], (long long) v[u]);
          --ns;
          if (ns == 0) {
            assert(ver == -1 && u == n);
            ans_v.clear();
            function<void(int)> DfsRe = [&](int w) {
              if (w != n && dp[w] == v[w]) {
                ans_v.push_back(w);
                return;
              }
              for (int j : children[w]) {
                DfsRe(j);
              }
            };
            DfsRe(u);
          } else {
            dp[st[ns - 1]] += dp[u];
          }
        }
        if (ver == -1) {
          break;
        }
        dp[ver] = 0;
        if (ns > 0) {
          children[st[ns - 1]].push_back(ver);
        }
        st[ns++] = ver;
        children[ver].clear();
      }
    }
    int sz = (int) ans_v.size();
    cout << ans << " " << ans_d << '\n';
    cout << sz << '\n';
    for (int i = 0; i < sz; i++) {
      if (i > 0) {
        cout << " ";
      }
      cout << ans_v[i] + 1;
    }
    cout << '\n';
  }
  debug(clock());
  return 0;
}
