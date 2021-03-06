#include <stdio.h>
#include <string.h>
const int MOD = 1000000007;
long long dp[101][101];
int n, v[101];

long long Solve(int i, int j) {
  if (i >= j)
    return 1;
  if (dp[i][j] != -1)
    return dp[i][j];
  dp[i][j] = Solve(i+1, j);
  if (v[i] < 0) {
    for (int k = i+1; k <= j; k++)
      if (v[k] == -v[i]) {
        dp[i][j] += Solve(i+1, k-1) * Solve(k+1, j);
        dp[i][j] %= MOD;
      }
  }
  return dp[i][j];
}
int main() {
  int i;
  memset(dp, -1, sizeof dp);
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &v[i]);
  }
  printf("%lld\n", Solve(0, n-1));
  return 0;
}