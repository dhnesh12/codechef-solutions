#include <bits/stdc++.h>
using namespace std;
 
const int MAX = 121;
const int LIM = 1000001;
 
string s, n;
bool PLUS[MAX];
bitset<LIM> dp[MAX];
bitset<LIM> vis[MAX];
 
bool solve(int idx, int rem) {
  if (idx == s.length()) {
    return rem == 0;
  }
  if (vis[idx][rem]) {
    return dp[idx][rem];
  }
  vis[idx][rem] = 1;
  int x = 0;
  for(int i = idx; i < s.length(); ++i) {
    x = x * 10 + s[i] - '0';
    if (x > rem) {
      break;
    }
    if (solve(i + 1, rem - x)) {
      PLUS[i] = 1;
      return (dp[idx][rem] = 1);
    }
  }
  return (dp[idx][rem] = 0);
}
 
int main() {
  int t;
  cin >> t;
  while(t--) {
    cin >> s >> n;
    int N = 0;
    for(int i = 0; i < n.length(); ++i) {
      N = N * 10 + n[i] - '0';
    }
    for(int i = 0; i < s.length(); ++i) {
      PLUS[i] = 0;
      for(int j = 0; j <= N; ++j) {
        dp[i][j] = 0;
        vis[i][j] = 0;
      }
    }
    bool get = solve(0, N);
    for(int i = 0; i < s.length(); ++i) {
      if (i && PLUS[i-1]) {
        cout << "+";
      }
      cout << s[i];
    }
    cout << "\n";
  }
  return 0;
}