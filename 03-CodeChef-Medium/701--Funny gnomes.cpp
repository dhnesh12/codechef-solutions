#include "bits/stdc++.h"

using namespace std;

const int N = 505;
const int LN = 30;

bitset < N > dp[LN][N];
bitset < N > who;
bitset < N > who_next;

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      int yes;
      scanf("%d", &yes);
      dp[0][i][j] = yes;
    }
  }
  for (int bit = 1; bit < LN; ++bit) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (dp[bit - 1][i][j]) {
          dp[bit][i] |= dp[bit - 1][j];
        }
      }
    }
  }
  int q;
  scanf("%d", &q);
  while (q--) {
    int k, x;
    scanf("%d %d", &k, &x);
    who.reset();
    who[x - 1] = 1;
    for (int bit = 0; bit < LN; ++bit) {
      if ((k >> bit) & 1) {
        who_next.reset();
        for (int i = 0; i < n; ++i) {
          if (who[i]) {
            who_next |= dp[bit][i];
          }
        }
        who = who_next;
      }
    }
    printf("%d\n", who.count());
    bool no = 1;
    for (int i = 0; i < n; ++i) {
      if (who[i]) {
        printf("%d ", i + 1);
        no = 0;
      }
    }
    if (no) {
      printf("-1");
    }
    puts("");
  }
  return 0;
}
