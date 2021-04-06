#include<bits/stdc++.h>
using namespace std;
#define si(x) scanf("%d",&x)
#define sll(x) scanf("%lld",&x)
#define pi(x) printf("%d\n",x)
const int N = 200005;
int TIME;
int depth[N], up[19][N], out[N], in[N];
vector<int> edge[N];
int n;
void dfs(int x, int d, int p) {
   in[x] = ++TIME;
   up[0][TIME] = in[p];
   depth[TIME] = d;
   for(auto y : edge[x])
      if(y != p)
         dfs(y,d+1,x);
   out[in[x]] = TIME;
}
int lca(int u, int v) {
   if(depth[u] < depth[v])
      swap(u, v);
   for(int i = 17; i >= 0; i--)
      if(depth[up[i][u]] >= depth[v]) {
         u = up[i][u];
      }
   if(u == v)
      return u;
   for(int i = 17; i >= 0; i--)
      if(up[i][u] != up[i][v]) {
         u = up[i][u];
         v = up[i][v];
      }
   return up[0][u];
}
int BT1[N+1], BT2[N+1];
void update(int BT[], int x, int val) {
   while(x<=n) {
      BT[x] += val;
      x += (x & (-x));
   }
}
int query(int BT[], int id) {
   int ret = 0;
   while(id>0) {
      ret += BT[id];
      id &= (id-1);
   }
   return ret;
}
int query(int BT[], int l, int r) {
   return query(BT,r) - query(BT,l-1);
}
int main() {
   ios_base::sync_with_stdio(0);
//   freopen("TRAVTREE.inp","r",stdin);
   si(n);
   assert(n>0);
   for(int i =0;  i<n-1; i++) {
      int x,y;
      si(x);
      si(y);
      x--;
      y--;
      edge[x].push_back(y);
      edge[y].push_back(x);
   }
   dfs(0,0,0);
   for(int l = 1; l<19; l++)
      for(int i =1; i<=n; i++)
         up[l][i] = up[l-1][up[l-1][i]];
   int q;
   si(q);
   while(q--) {
      int a,b;
      si(a);
      si(b);
      a = in[a-1];
      b = in[b-1];
      int l = lca(a,b);
      int ans =  query(BT1,l,out[l]);
      update(BT1, a, 1);
      update(BT1, b, 1);
      update(BT1, l, -2);
      ans += query(BT2,a) + query(BT2,b) - query(BT2,l) - (l==1  ? 0 : query(BT2, up[0][l]));
      update(BT2,l,1);
      update(BT2,out[l]+1,-1);
      pi(ans);
   }
}
