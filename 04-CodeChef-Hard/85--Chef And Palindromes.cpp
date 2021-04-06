#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstring>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
#define REP(i,b) for(int i=0;i<(b);i++)

using namespace std;

#define MAXN 1111
char a[MAXN], b[MAXN], c[MAXN];
int A, B, C;

long long dpB[MAXN][MAXN];
long long solveB(int i1, int i2) {
  if (dpB[i1][i2] >= 0) return dpB[i1][i2];
  if (i1 + 1 >= i2) return dpB[i1][i2] = 1;
  return dpB[i1][i2] = (b[i1 + 1] == b[i2 - 1] && solveB(i1 + 1, i2 - 1));
}
long long dpA[MAXN][MAXN];
long long solveA(int i1, int i2) {
  if (dpA[i1][i2] >= 0) return dpA[i1][i2];
  if (i1 + 1 >= i2) return dpA[i1][i2] = 1;
  return dpA[i1][i2] = (a[i1 + 1] == a[i2 - 1] && solveA(i1 + 1, i2 - 1));
}
long long dpC[MAXN][MAXN];
long long solveC(int i1, int i2) {
  if (dpC[i1][i2] >= 0) return dpC[i1][i2];
  if (i1 + 1 >= i2) return dpC[i1][i2] = 1;
  return dpC[i1][i2] = (c[i1 + 1] == c[i2 - 1] && solveC(i1 + 1, i2 - 1));
}
long long dpA1[MAXN];
long long solveA1(int i1) {
  if (dpA1[i1] >= 0) return dpA1[i1];
  long long ans = 0;
  FOR(i2, i1, A - 1) if (a[i1] == a[i2]) ans += solveA(i1, i2);
  return dpA1[i1] = ans;
}
long long dpC2[MAXN];
long long solveC2(int i2) {
  if (dpC2[i2] >= 0) return dpC2[i2];
  long long ans = 0;
  FOR(i1, 0, i2) if (c[i1] == c[i2]) ans += solveC(i1, i2);
  return dpC2[i2] = ans;
}

long long dpB0;
long long solveB() {
  if (dpB0 >= 0) return dpB0;
  long long ans = 0;
  REP(i, B) REP(j, i + 1) if (b[i] == b[j]) ans += solveB(j, i);
  return dpB0 = ans;
}

long long dpB2[MAXN];
long long solveB2(int i2) {
  if (dpB2[i2] >= 0) return dpB2[i2];
  long long ans = 0;
  FOR(i1, 0, i2) if (b[i1] == b[i2]) ans += solveB(i1, i2);
  return dpB2[i2] = ans;
}

long long dpAB[MAXN][MAXN];
long long solveAB(int ia, int ib) {
  if (dpAB[ia][ib] >= 0) return dpAB[ia][ib];
  long long ans = 1;
  if (ia + 1 < A && ib > 0 && a[ia + 1] == b[ib - 1]) ans += solveAB(ia + 1, ib - 1);
  if (ib > 0) ans += solveB2(ib - 1);
  if (ia + 1 < A) ans += solveA1(ia + 1);
  return dpAB[ia][ib] = ans;
}

long long dpAB1[MAXN];
long long solveAB(int ia) {
  if (dpAB1[ia] >= 0) return dpAB1[ia];
  long long ans = 0;
  REP(ib, B) if (a[ia] == b[ib]) ans += solveAB(ia, ib);
  return dpAB1[ia] = ans;
}

long long dpB1[MAXN];
long long solveB1(int i1) {
  if (dpB1[i1] >= 0) return dpB1[i1];
  long long ans = 0;
  FOR(i2, i1, B - 1) if (b[i1] == b[i2]) ans += solveB(i1, i2);
  return dpB1[i1] = ans;
}

long long dpBC[MAXN][MAXN];
long long solveBC(int ib, int ic) {
  if (dpBC[ib][ic] >= 0) return dpBC[ib][ic];
  long long ans = 1;
  if (ib + 1 < B && ic > 0 && b[ib + 1] == c[ic - 1]) ans += solveBC(ib + 1, ic - 1);
  if (ib + 1 < B) ans += solveB1(ib + 1);
  if (ic > 0) ans += solveC2(ic - 1);
  return dpBC[ib][ic] = ans;
}

long long dpBC1[MAXN];
long long solveBC(int ic) {
  if (dpBC1[ic] >= 0) return dpBC1[ic];
  long long ans = 0;
  REP(ib, B) if (b[ib] == c[ic]) ans += solveBC(ib, ic);
  return dpBC1[ic] = ans;
}

long long dpAC[MAXN][MAXN];
long long solveAC(int ia, int ic) {
  if (dpAC[ia][ic] >= 0) return dpAC[ia][ic];
  long long ans = 0;
  if (ia + 1 < A && ic > 0 && a[ia + 1] == c[ic - 1]) ans += solveAC(ia + 1, ic - 1);
  ans += solveB();
  if (ia + 1 < A) ans += solveAB(ia + 1);
  if (ic > 0)     ans += solveBC(ic - 1);
  // printf("AC: %d %d => %lld\n", ia, ic, ans);
  return dpAC[ia][ic] = ans;
}

int main(int argc, char *argv[]) {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%s%s%s", a, b, c);
    A = strlen(a);
    B = strlen(b);
    C = strlen(c);
    dpB0 = -1;
    REP(i, MAXN) {
      dpBC1[i] = -1;
      dpB1[i] = -1;
      dpAB1[i] = -1;
      dpB2[i] = -1;
      dpA1[i] = -1;
      dpC2[i] = -1;
      REP(j, MAXN) {
        dpAC[i][j] = -1;
        dpBC[i][j] = -1;
        dpAB[i][j] = -1;
        dpB[i][j] = -1;
        dpA[i][j] = -1;
        dpC[i][j] = -1;
      }
    }
    long long ans = 0;
    REP(ia, A) REP(ic, C) if (a[ia] == c[ic]) ans += solveAC(ia, ic);
    printf("%lld\n", ans);
  }
  return 0;
}
