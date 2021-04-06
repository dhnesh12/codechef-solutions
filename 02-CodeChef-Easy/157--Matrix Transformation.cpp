#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N, M;
  cin >> N >> M;

  vector<vector<long long>> C(N, vector<long long>(M));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j) cin >> C[i][j];

  for (int x, i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      cin >> x;
      C[i][j] -= x;
    }
  }

  bool is_possible = true;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < M; ++j)
      is_possible &= (C[i][j] - C[0][j]) == (C[i][0] - C[0][0]);
  if (!is_possible) {
    cout << -1 << '\n';
    return;
  }

  vector<long long> v;
  v.reserve(N + M);
  for (int i = 0; i < M; ++i) v.push_back(C[0][i]);
  for (int i = 0; i < N; ++i) v.push_back(C[0][0] - C[i][0]);
  sort(v.begin(), v.end());
  
  long long ans = 0;
  for (const auto &x : v) ans += abs(x - v[(N + M) / 2]);
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) solve();
}