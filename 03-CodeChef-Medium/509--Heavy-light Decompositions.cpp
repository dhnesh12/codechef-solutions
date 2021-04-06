/**
 * Problem: HLDOTS (Codechef)
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h> // using GCC/G++
// #include "custom/prettyprint.hpp" // G++11 only
using namespace std;

static const int MOD = 19101995;
static const int INF = 0x3f3f3f3f;
static const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
#define pb push_back
#define eb emplace_back
#define mp make_pair

#define debug(x) cerr << #x << " : " << x << endl;
#define whole(func, x, ...) ([&](decltype((x)) var) { return (func)(begin(var), end(var), ##__VA_ARGS__); })(x)

unordered_map<int, unordered_set<int>> g;
queue<int> que;
int n, ans, x, y;

int main() {
  ios_base::sync_with_stdio(false); // for fast I/O

  cin >> n;

  for(int i=0; i<n; i++) {
    cin >> x >> y;
    g[x].insert(y);
    g[y].insert(x);
  }

  que.push(1);
  ans = 1;

  while(!que.empty()) {
    int top = que.front();
    que.pop();

    ans = (ans * (max(1, (int)g[top].size()) % MOD)) % MOD;

    // debug(ans)
    // debug(top)

    for(auto&& val: g[top]) {
      g[val].erase(top);
      que.push(val);
    }
  }

  cout << ans << endl;

  return 0;
}
