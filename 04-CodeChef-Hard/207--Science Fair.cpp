#include <bits/stdc++.h>
using namespace std;
const int MXN = 16, MX = MXN + 2, MXV = 1000, md = 1000000007;
const long long INF = 1e18;
vector<pair<int, int>> G[MXV];
int p[MX], t[MXN], m[MXN], n;
void getDistances(int v, long long d[MX]) 
{
  static int special[MXV];
  static long long dist[MXV];
  fill(special, special + MXV, -1);
  fill(dist, dist + MXV, INF);
  for (int i = 0; i < n + 2; i++)
  { 
      special[p[i]] = i;
  }
  priority_queue<pair<long long, int>> q;
  q.emplace(0, v);
  dist[v] = 0;
  while (q.empty() == false) {
    long long d;
    int u;
    tie(d, u) = q.top();
    d *= -1;
    q.pop();
    
    if (dist[u] != d) continue;
    
    for (auto& e : G[u]) {
      if (d + e.second < dist[e.first]) {
        dist[e.first] = d + e.second;
        if (special[e.first] == -1)
          q.emplace(-1 * (d + e.second), e.first);
      }
    }
  }
  
  for (int i = 0; i < n + 2; i++) d[i] = dist[p[i]];
}

long long d[MX][MX], dp[1<<MXN][MX], g[1<<MXN];

int main() 
{
  int v, e, s, f;
  ignore = scanf("%d %d %d %d %d", &v, &e, &s, &f, &n);
  s--; 
  f--;
  for (int i = 0; i < n; i++)
  {
    ignore = scanf("%d %d %d", p+i, t + i, m + i);
    p[i]--;
  }
  
  for (int i = 0, u, v, w; i < e; i++) {
    ignore = scanf("%d %d %d", &u, &v, &w);
    u--;
    v--;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }
  
  p[n] = s;
  p[n + 1] = f;
  
  for (int i = 0; i < n + 2; i++) getDistances(p[i], d[i]);
  
  for (int i = 0; i < (1 << n); i++)
    for (int j = 0; j < n + 2; j++)
      dp[i][j] = INF;
  
  priority_queue<tuple<long long, int, int>> q;
  q.emplace(0, 0, n);
  dp[0][n] = 0;
  while (q.empty() == false) {
    long long dist;
    int mask, last;
    tie(dist, mask, last) = q.top();
    dist *= -1;
    q.pop();
    
    if (dp[mask][last] != dist) continue;
    
    for (int next = 0; next < n + 2; next++) {
      int nextMask = mask | (next < n ? 1 << next : 0);
      long long nextDist = dist + d[last][next];
      if (nextDist < dp[nextMask][next]) {
        dp[nextMask][next] = nextDist;
        q.emplace(-1 * nextDist, nextMask, next);
      }
    }
  }
  
  for (int i = 0; i < (1 << n); i++) {
    long long cost = 1;
    for (int j = 0; j < n; j++)
    {
      if ((i >> j) & 1)
      {
        cost = cost * t[j] % md;
      }
    }
    cost += dp[i][n + 1];
    g[i] = cost;
    for (int j = i; j > 0; j = (j - 1) & i)
    {
      g[j] = min(g[j], cost);
    }
  }
  int ans = 0;
  for (int i = 1; i < (1 << n); i++) 
  {
    int e = g[i] % md;
    for (int j = 0; j < n; j++) 
    {
      e=e*1ll*(((i >> j) & 1)==1 ? m[j]:100-m[j])%md;
      e=e*570000004ll%md;
    }
    ans=((ans+e)%md);
  }
  printf("%d\n", ans);
  return 0;
}

