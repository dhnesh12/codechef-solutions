 #include <bits/stdc++.h>

using namespace std;

int t, n, m, k, q, x, y, p[9002];
int dp[2][9002];
string s;

const int mod = 1e9 + 7;

void add (int &x, int y) {
  x += y;
  if (x >= mod)
    x -= mod;
}

int main()
{
  cin >> t;
  while (t--) {
    cin >> n >> m >> k;
    memset(p, 0, sizeof(p));
    memset(dp, 0, sizeof(dp));
    vector<vector<int> >G(n + 1);
    for (int i = 1; i <= m; i++) {
      cin >> x >> y;
      G[x].push_back(y);
      G[y].push_back(x);
    }
    cin >> q;
    bool ok = 0;
    while (q--) {
      cin >> y >> x;
      if (p[x] || (y != 1 && x == 0))
        ok = 1;
      p[x] = y;
    }
    if (ok) {
      cout << "0\n";
      continue;
    }
    dp[0][1] = 1;
    int x = 1;
    for (int i = 1; i <= k; i++) {
      for (int j = 1; j <= n; j++) {
        dp[x][j] = dp[x ^ 1][j];
        for (auto it : G[j])
          add(dp[x][j], dp[x ^ 1][it]);
      }
      if (p[i])
        for (int j = 1; j <= n; j++)
          if (j != p[i])
            dp[x][j] = 0;
      x ^= 1;
    }
    x ^= 1;
    int ans = 0;
    for (int i = 1; i <= n; i++)
      add (ans, dp[x][i]);
    cout << ans << "\n";
  }
  return 0;
}
