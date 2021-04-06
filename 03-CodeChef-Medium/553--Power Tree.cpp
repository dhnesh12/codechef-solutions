#include <bits/stdc++.h>
#define int long long
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL)
#define pb push_back
#define F first
#define S second

using namespace std;
const int N = 256 + 1;
const int md = 1e9 + 7;
int g[N][N];
queue<int> q;
void checkmate() 
{
  int n;
  cin >> n;
  int ec = n * (n - 1) / 2;
  for (int i = 1, u, v; i <= ec; i++) {
    cin >> u >> v;
    g[u][v] = i;
    g[v][u] = 0;
  }
  if ((n & n - 1) != 0) {
    cout << -1 << '\n';
    return;
  }
  for (int i = 1; i <= n; i++) 
    q.push(i);
  while (q.size() > 1) {
    int u = q.front(); q.pop();
    int v = q.front(); q.pop();
    if (g[u][v]) {
      q.push(u);
      g[u][v] = 0;
    }
    else {
      q.push(v);
      g[v][u] = 0;
    }
    --ec;
  }
  q.pop();
  cout << ec << '\n';
  for (int i = 1; i <= n; i++) 
    for (int j = 1; j <= n; j++)
      if (g[i][j])
        cout << g[i][j] << " ";
  cout << '\n';
}
int32_t main() 
{
  faster;
  int t = 1;
  cin >> t;
  while (t--) 
    checkmate();
  return 0;
}
