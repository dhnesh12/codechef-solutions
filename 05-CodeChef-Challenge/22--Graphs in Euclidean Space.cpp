#include<bits/stdc++.h>

using namespace std;
/*
*
*arun nainwal
*
*/
const int MAXN = 300, MAXD = 20, MAXV = 1000000;

int g[MAXN][MAXN], x[MAXN][MAXD], best[MAXN][MAXN], bestD;
double dist[MAXN][MAXN];

double eval(int n, int d) {
    for (int i = 0; i < n; ++i) {
      dist[i][i] = 0;

      for (int j = 0; j < i; ++j) {
	dist[i][j] = 0;
	for (int k = 0; k < d; ++k) {
	  double dx = x[j][k]-x[i][k];
	  dist[i][j] += dx*dx;
	}
	dist[j][i] = dist[i][j] = sqrt(dist[i][j]);
      }
    }


    double K = g[0][1]/dist[0][1];
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < i; ++j)
	K = max(g[i][j]/dist[i][j], K);

    double L = K*dist[0][1]/g[0][1];
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < i; ++j)
	L = max(K*dist[i][j]/g[i][j], L);

    return d*L;
}

void perturb(int n, int d) {
  for (int i = 0; i < n; ++i) {
    bool ok = false;
    while (!ok) {
      ok = true;
      for (int j = 0; j < i && ok; ++j) {
	bool same = true;
	for (int k = 0; k < d && same; ++k)
	  same &= (x[j][k] == x[i][k]);
	if (same) ok = false;
      }
      if (!ok) --x[i][0];
    }
  }
}

double solve(int n, int d) {
  int a[MAXN];

  for (int i = 0, p2 = 2; i < d; ++i, p2 *= 2) {
    int num = (n/p2)+1;
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) a[k] = k;
      for (int k = n-1; k > 0; --k)
	swap(a[k], a[rand()%(k+1)]);
      x[j][i] = MAXV;
      for (int k = 0; k < n && k < num; ++k)
	x[j][i] = min(x[j][i], g[i][a[k]]);

    }
  }

  perturb(n,d);
  return eval(n,d);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
	scanf("%d", &g[i][j]);

    double val = solve(n, bestD = 1);
    for (int i = 0; i < n; ++i)
      best[i][0] = x[i][0];

    //skip by 2 for the sake of time
    for (int d = 2; (1<<d) <= n; d += 2) {
      double tmp = solve(n, d);
      if (tmp < val) {
	bestD = d;
	for (int i = 0; i < n; ++i)
	  for (int j = 0; j < d; ++j)
	    best[i][j] = x[i][j];
      }
    }

    printf("%d\n", bestD);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < bestD; ++j)
	printf("%d%c", best[i][j], (j+1==bestD?'\n':' '));
  }
}