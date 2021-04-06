// BX

#include <stdio.h>
#include <math.h>
#include <vector>

using std::vector;

#define pb push_back
#define INFD 10000000000.0

struct P {
  int g;
  double x,y;
  vector<int> n;
};

P a[1000];

double dist(int i, int j){
  return sqrt((a[i].x-a[j].x)*(a[i].x-a[j].x) +
              (a[i].y-a[j].y)*(a[i].y-a[j].y));
}

int main(){
  int N, i,j,k, ii,jj,mi,mj;
  double m,t;
  vector<vector<int> > g;

  scanf("%d", &N);
  for(i = 0; i < N; ++i)
    scanf("%lf %lf", &a[i].x, &a[i].y), a[i].g = -1, a[i].n.clear();

  // Connect each to closest
  for(i = 0; i < N; ++i){
    if(a[i].g != -1) continue;
    m = INFD;
    for(j = 0; j < N; ++j){
      if(i == j) continue;
      t = dist(i, j);
      if(t < m) m = t, k = j;
    }

    a[i].n.pb(k), a[k].n.pb(i);
    if(a[k].g == -1){
      a[i].g = a[k].g = g.size();
      vector<int> gn;
      gn.pb(i), gn.pb(k), g.pb(gn);
    }else
      a[i].g = a[k].g, g[a[k].g].pb(i);
  }

  // Combine groups
  for(i = g.size()-1; i > 0; --i){
    m = INFD;
    for(j = i-1; j >= 0; --j){
      for(ii = 0; ii < g[i].size(); ++ii){
        for(jj = 0; jj < g[j].size(); ++jj){
          t = dist(g[i][ii], g[j][jj]);
          if(t < m) m = t, k = j, mi = ii, mj = jj;
        }
      }
    }
    a[g[i][mi]].n.pb(g[k][mj]), a[g[k][mj]].n.pb(g[i][mi]);
    for(j = 0; j < g[i].size(); ++j)
      a[g[i][j]].g = k, g[k].pb(g[i][j]);
  }

  for(k = i = 0; i < N; ++i)
    for(j = 0; j < a[i].n.size(); ++j)
      if(a[i].n[j] > i) ++k;
  printf("0\n%d\n", k);
  for(i = 0; i < N; ++i)
    for(j = 0; j < a[i].n.size(); ++j)
      if(a[i].n[j] > i)
        printf("%d %d\n", i, a[i].n[j]);
  return 0;
}
