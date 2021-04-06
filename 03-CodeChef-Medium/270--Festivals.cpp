#include <cstdio>
#include <vector>
#include <algorithm>
 
using namespace std;
 
#define rep(i,a,n) for(int i=a;i<(int)n;i++)
#define per(i,a,n) for(int i=n-1;i>=a;i--)
 
const int N = 101000, E = 201000;
int n, u, v, w, tot, Q, m, ans1, ans2;
int y[E], nxt[E], c[E], fst[N], d[N], D[N], p[N][20], p2[N][20], f[N], bch[N];
vector<int> cn;
 
void add(int u, int v, int w) 
{
  tot++;
  y[tot] = v;
  nxt[tot] = fst[u];
  c[tot] = w;
  fst[u] = tot;
}
 
bool cmp(int x, int y) { return d[x] > d[y]; }
bool cmp2(int x, int y) { return bch[x] > bch[y]; }
 
void dfs(int u, int f, int dep) 
{
  d[u] = dep; D[u] = D[f] + 1; p[u][0] = f;
  for(int j = fst[u]; j; j = nxt[j]) 
   if(y[j] != f)
    dfs(y[j], u, dep + c[j]), p2[y[j]][0] = c[j];
}
 
int lca(int u,int v) 
{
  if(D[u] > D[v]) swap(u, v);
  per(i, 0, 18) if(D[p[v][i]] >= D[u]) v = p[v][i];
  if(u == v) return u;
  per(i, 0, 18) if(p[v][i] != p[u][i]) u = p[u][i], v = p[v][i];
  return p[u][0];
}
int branch(int u, int v) 
{
  per(i, 0, 18) 
  if(d[p[u][i]] > d[v]) 
   u = p[u][i];
  return u;
}
 
int minv(int u, int v) 
{
  int res = 2000000000;
  per(i, 0, 18) 
  if(d[p[u][i]] > d[v]) 
   res = min(res, p2[u][i]), u = p[u][i];
  if(u != v) 
   res = min(res, p2[u][0]);
  return res;
}
 
int main() 
{
  scanf("%d", &n);
  rep(i,1,n) 
  {
    scanf("%d%d%d", &u, &v, &w);
    add(u, v, w);
    add(v, u, w);
  }
  dfs(1, 0, 0);
  rep(j,1,18) 
   rep(i,1,n+1)
    p[i][j] = p[p[i][j - 1]][j - 1], p2[i][j] = min(p2[i][j - 1], p2[p[i][j - 1]][j - 1]);
  scanf("%d", &Q);
  rep(i,0,Q) 
  {
    scanf("%d", &m);
    rep(j,0,m) scanf("%d", &f[j]);
    sort(f, f + m, cmp);
    int vf = f[0], cl = 1;
    rep(j,1,m) 
    {
      if(d[f[j]] != d[f[j - 1]]) break;
      vf = lca(vf, f[j]);
      cl++;
    }
    ans1 = 2 * (d[f[0]] - d[vf]);
    ans2 = 0;
    rep(j,cl,m) 
     ans2 = max(ans2, d[f[0]] + d[f[j]] - 2 * d[lca(f[0], f[j])]);
    printf("%d ", max(ans1, ans2));
    if(ans1 == ans2) { puts("-1"); continue; }
    if(ans1 < ans2) 
    {
      int cb = 0, v1, v2;
      cn.clear();
      rep(j,cl,m) 
      {
        bch[f[j]] = lca(f[0], f[j]);
        if(d[f[0]] + d[f[j]] - 2 * d[bch[f[j]]] == ans2) cn.push_back(f[j]);
      }
      sort(f, f  + cl, cmp2);
      rep(j,0,cn.size()) 
       if(j == 0 || bch[cn[j]] != bch[cn[j - 1]]) cb++;
      if(cb == 1) 
      {
        v1 = bch[cn[0]];
        v2 = cn[0];
        rep(j,0,cn.size()) 
         v2 = lca(v2, cn[j]);
        printf("%d\n",min(minv(vf,v1),minv(v2,v1)));
      } 
      else 
      {
        v1 = bch[cn[0]];
        rep(j,0,cn.size()) 
         if(d[bch[cn[j]]] > d[v1]) v1 = bch[cn[j]];
        printf("%d\n", minv(vf, v1));
      }
    } 
    else if(ans1 > ans2) 
    {
        rep(j,0,cl) bch[f[j]] = branch(f[j], vf);
      sort(f, f + cl, cmp2);
      int cb = 0, b1, b2, v1, v2;
      rep(j,0,cl) if(j == 0 || bch[f[j]] != bch[f[j - 1]]) cb++;
      if(cb > 2) { puts("-1"); continue; }
      b1 = bch[f[0]]; v1 = f[0];
      rep(j,1,cl) if(bch[f[j]] != bch[f[j - 1]]) { b2 = bch[f[j]]; v2 = f[j];break; }
      rep(j,0,cl) if(bch[f[j]] == b1) v1 = lca(v1, f[j]); else v2 = lca(v2, f[j]);
      printf("%d\n",min(minv(v1,vf),minv(v2,vf)));
    }
  }
}