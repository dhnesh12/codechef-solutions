#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
 
typedef vector<int> vi;
 
#define range(v, f, t) for (int v = (f); v < (t); ++v)
#define repeat(n) range (_, 0, (n))
#define sq(x) ((x) * (x))
 
#define MAXN 205
#define MAXK 105
 
int T;
int N, K;
int x[MAXN], y[MAXN];
double d[MAXN][MAXN];
int order[MAXN];
bool is_rpr[MAXN];
double dist_to_rpr[MAXN];
int grp[MAXK][MAXN], grp_sz[MAXK];
int grp_of[MAXN], best_grp_of[MAXN];
 
void solve();
 
int main(int argc, char const *argv[])
{
  srand(time(0));
  scanf("%d\n", &T);
  range (t, 1, T + 1) {
    
    scanf("%d %d\n", &N, &K);
    range (p, 0, N) {
      scanf("%d %d\n", &x[p], &y[p]);
    }

    if (K == 1) {
      
      printf("case %d Y\n", t);
      printf("%d", N);
      range (p, 0, N) {
        printf(" %d", p + 1);
      }
      printf("\n");
    }
    else {
      solve();
      
      printf("case %d Y\n", t);
      range (g, 0, K) {
        printf("%d", (int) grp_sz[g]);
        range (i, 0, grp_sz[g]) {
          printf(" %d", grp[g][i] + 1);
        }
        printf("\n");
      }
    }
  }
  return 0;
}
 
inline void solve()
{
  
  range (p1, 0, N) {
    range (p2, 0, p1 + 1) {
      d[p1][p2] = d[p2][p1] = sqrt(sq(x[p1] - x[p2]) + sq(y[p1] - y[p2]));
    }
  }
  
  range (p, 0, N) order[p] = p; random_shuffle(order, order + N);
  
  double min_diam = 1e9;
  range (o, 0, min(N, 1)) { 
    
    range (p, 0, N) is_rpr[p] = (p == order[o]);
    range (p, 0, N) dist_to_rpr[p] = d[p][order[o]];

    repeat (K - 1) {
      
      double max_dist = -1.0; int best_p = -1;
      range (p, 0, N) if (!is_rpr[p] && max_dist < dist_to_rpr[p]) {
        max_dist = dist_to_rpr[p], best_p = p;
      }
    
      is_rpr[best_p] = true;
      range (p, 0, N) if (!is_rpr[p]) {
        dist_to_rpr[p] = min(dist_to_rpr[p], d[p][best_p]);
      }
    }
    
    range (g, 0, K) grp_sz[g] = 0;
    fill(grp_of, grp_of + N, -1);
    
    int i = 0;
    range (g, 0, K) {
      while (i < N && !is_rpr[i]) ++i;
      grp[g][grp_sz[g]] = i, ++grp_sz[g], grp_of[i] = g;
      ++i;
    }
    range (g, 0, K) {
      double min_dist = 1e9; int best_p = -1;
      range (p, 0, N) if (grp_of[p] == -1 && d[grp[g][0]][p] < min_dist) {
        min_dist = d[grp[g][0]][p];
        best_p = p;
      }
      grp[g][grp_sz[g]] = best_p, ++grp_sz[g], grp_of[best_p] = g, is_rpr[best_p] = true;
    }
    
    repeat (1 * K)
    {
      int g1 = rand() % K, g2 = rand() % K;
      while (g1 == g2) g2 = rand() % K;
      double max_dist = max(d[grp[g1][0]][grp[g1][1]], d[grp[g2][0]][grp[g2][1]]);
      if (max(d[grp[g1][0]][grp[g2][0]], d[grp[g1][1]][grp[g2][1]]) < max_dist) {
        swap(grp[g1][0], grp[g2][1]);
        swap(grp_of[grp[g1][0]], grp_of[grp[g2][1]]);
      }
      else if (max(d[grp[g1][0]][grp[g2][1]], d[grp[g1][1]][grp[g2][0]]) < max_dist) {
        swap(grp[g1][0], grp[g2][0]);
        swap(grp_of[grp[g1][0]], grp_of[grp[g2][0]]);
      }
    }
    bool done = false; int it = 0;
    while (!done && it < 5) {
      done = true; ++it;
      range (p, 0, N) if (!is_rpr[p]) {
        
        double min_dist_to_grp = 1e9; int best_g = -1;
        range (g, 0, K) {
          double max_dist_to_pt = -1.0;
          range (i, 0, grp_sz[g]) {
            max_dist_to_pt = max(max_dist_to_pt, d[p][grp[g][i]]);
          }
          if (max_dist_to_pt < min_dist_to_grp) {
            min_dist_to_grp = max_dist_to_pt;
            best_g = g;
          }
        }
        
        if (best_g != grp_of[p]) {
          done = false;
          remove(grp[grp_of[p]], grp[grp_of[p]] + grp_sz[grp_of[p]], p), --grp_sz[grp_of[p]];
          grp[best_g][grp_sz[best_g]] = p, ++grp_sz[best_g], grp_of[p] = best_g;
        }
      }
    }

    double diam = -1.0;
    range (g, 0, K) {
      range (i, 0, grp_sz[g]) {
        range (j, 0, i) {
          diam = max(diam, d[grp[g][i]][grp[g][j]]);
        }
      }
    }
    
    if (diam < min_diam) {
      min_diam = diam;
      copy(grp_of, grp_of + N, best_grp_of);
    }
  }

  copy(best_grp_of, best_grp_of + N, grp_of);
  range (g, 0, K) grp_sz[g] = 0;
  range (p, 0, N) grp[grp_of[p]][grp_sz[grp_of[p]]] = p, ++grp_sz[grp_of[p]];
} 
