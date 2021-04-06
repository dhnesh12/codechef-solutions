#include <cstdio>
#include <cmath>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <map>
#include <cassert>
#include <string>
#include <cstring>
#include <queue>

using namespace std;

#define rep(i,a,b) for(int i = a; i < b; i++)
#define S(x) scanf("%d",&x)
#define S2(x,y) scanf("%d%d",&x,&y)
#define P(x) printf("%d\n",x)
#define all(v) v.begin(),v.end()
#define FF first
#define SS second
#define pb push_back
#define mp make_pair

typedef long long int LL;
typedef long double LD;
typedef pair<int, int > pii;
typedef vector<int > vi;

const int OFFSET = 200;
const int N = 21;

vector<pii > poly[N];

// Ax + By + C = 0;
struct Line {
  LD A,B,C;
}; 

LD sq(LD x) {
  return x * x;
}

LD dist(pii a, pii b) {
  return sqrt(sq(a.FF - b.FF) + sq(a.SS - b.SS));
}

LD perimeter(int idx) {
  LD res = 0;
  int sz = poly[idx].size();
  rep(i,0,sz) {
    res += dist(poly[idx][i], poly[idx][(i + 1) % sz]);
  }
  return res;
}

pair<LD, LD> centoid(int idx) {
  pair<LD, LD> res = mp(0,0);
  int sz = poly[idx].size();
  rep(i,0,sz) {
    res.FF += poly[idx][i].FF;
    res.SS += poly[idx][i].SS;
  }
  res.FF /= sz;
  res.SS /= sz;
  // printf("%d %Lf %Lf\n",idx, res.FF, res.SS);
  return res;
}

int getSign(Line l, pair<LD, LD> p) {
  LD val = l.A * p.FF + l.B * p.SS + l.C;
  if (val < 0) return -1;
  if (val > 0) return 1;
  // printf("%Lf %Lf\n",p.FF, p.SS);
  assert(0); // centroid should not be on any line.
}

Line getLine(pii a, pii b) {
  Line res;
  res.A = b.SS - a.SS;
  res.B = -b.FF + a.FF;
  res.C = -res.A * a.FF - res.B * a.SS;
  // if (res.A < 0 || (res.A == 0 && res.B < 0)) {
  //   res.A *= -1;
  //   res.B *= -1;
  //   res.C *= -1;
  // }
  if(res.A != 0) {
    res.B /= res.A;
    res.C /= res.A;
    res.A = 1;
  } else if(res.B) {
    res.C /= res.B;
    res.B = 1;
  }
  // printf("%Lfx + %Lfy + %Lf\n",res.A,res.B,res.C);
  return res;
}

//////// ----LP solve taken from stanford notes ...

typedef long double DOUBLE;
typedef vector<DOUBLE> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;

const DOUBLE EPS = 1e-9;

struct LPSolver {
  int m, n;
  VI B, N;
  VVD D;

  LPSolver(const VVD &A, const VD &b, const VD &c) :
    m(b.size()), n(c.size()), N(n + 1), B(m), D(m + 2, VD(n + 2)) {
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
    for (int i = 0; i < m; i++) { B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; }
    for (int j = 0; j < n; j++) { N[j] = j; D[m][j] = -c[j]; }
    N[n] = -1; D[m + 1][n] = 1;
  }

  void Pivot(int r, int s) {
    double inv = 1.0 / D[r][s];
    for (int i = 0; i < m + 2; i++) if (i != r)
      for (int j = 0; j < n + 2; j++) if (j != s)
        D[i][j] -= D[r][j] * D[i][s] * inv;
    for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] *= inv;
    for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] *= -inv;
    D[r][s] = inv;
    swap(B[r], N[s]);
  }

  bool Simplex(int phase) {
    int x = phase == 1 ? m + 1 : m;
    while (true) {
      int s = -1;
      for (int j = 0; j <= n; j++) {
        if (phase == 2 && N[j] == -1) continue;
        if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && N[j] < N[s]) s = j;
      }
      if (D[x][s] > -EPS) return true;
      int r = -1;
      for (int i = 0; i < m; i++) {
        if (D[i][s] < EPS) continue;
        if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
          (D[i][n + 1] / D[i][s]) == (D[r][n + 1] / D[r][s]) && B[i] < B[r]) r = i;
      }
      if (r == -1) return false;
      Pivot(r, s);
    }
  }

  DOUBLE Solve(VD &x) {
    int r = 0;
    for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
    if (D[r][n + 1] < -EPS) {
      Pivot(r, n);
      if (!Simplex(1) || D[m + 1][n + 1] < -EPS) return 1;
      for (int i = 0; i < m; i++) if (B[i] == -1) {
        int s = -1;
        for (int j = 0; j <= n; j++)
          if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && N[j] < N[s]) s = j;
        Pivot(i, s);
      }
    }
    if (!Simplex(2)) return 1;
    x = VD(n);
    for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
    return D[m][n + 1];
  }
};

int main() {
  int n;
  S(n);
  vector<pair<LD, int > > tmp;
  rep(i,0,n) {
    int m;
    S(m);
    rep(j,0,m) {
      int x,y;
      S2(x,y);
      // x += OFFSET;
      // y += OFFSET;
      poly[i].pb(mp(x, y));
    }
    tmp.pb(mp(perimeter(i), i));
  }
  sort(all(tmp));

  // Compute all equations.
  vector<vector<LD > > equations;
  vector<LD > b;
  rep(i,0,n-1) {
    int id1 = tmp[i].SS;
    rep(itr,i+1,n) if(itr != i && tmp[i].FF <= tmp[itr].FF) {
    // int itr = i + 1;
    int id2 = tmp[itr].SS;
    pair<LD, LD > c = centoid(id2);
    // Iterate bigger polynomial and add all equations for all points in smaller polynomial
    rep(j,0,poly[id2].size()) {
      Line l = getLine(poly[id2][j], poly[id2][(j + 1) % poly[id2].size()]);
      int sign = getSign(l, c);
      // P(sign);
      rep(k,0,poly[id1].size()) {
        vector<LD > eq(4 * n, 0);
        eq[4 * i] = sign * -l.A;
        eq[4 * i + 1] = sign * l.A;
        eq[4 * i + 2] = sign * -l.B;
        eq[4 * i + 3] = sign * l.B;

        eq[4 * itr + 0] = sign * l.A;
        eq[4 * itr + 1] = sign * -l.A;
        eq[4 * itr + 2] = sign * l.B;
        eq[4 * itr + 3] = sign * -l.B;
        b.pb(sign * (l.C + l.A * poly[id1][k].FF + l.B * poly[id1][k].SS));
        equations.pb(eq);
      }
    }
    }
  }
  vector<LD > c(4 * n, -1.0);
  LPSolver solver(equations, b, c);
  VD x;
  DOUBLE value = solver.Solve(x);
  // rep(i,0,x.size()) printf("%Lf\n",x[i]);
  // cout << value << "\n";
  if (value < -1e6 || value > 1e6) {
    printf("-1\n");
  } else {
    printf("%0.10Lf\n",-(value));
  }
  return 0;
}
