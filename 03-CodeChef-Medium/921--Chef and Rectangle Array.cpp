#include <bits/stdc++.h>
using namespace std;
#define long long long
#define err(a...) fprintf(stderr, a)

template <class T> 
void chmax(T &a, T b) { a = max(a, b); }

constexpr int N = 1010;

int n, m;
int a[N][N];

int row_max[N][N];
long row_sum[N][N];

long query(int c, int d) { // a, b
  memset(row_max, 0, sizeof(row_max));
  memset(row_sum, 0, sizeof(row_sum));

  deque<pair<int, int>> dq;
  auto push = [&](pair<int, int> val) {
    while (!dq.empty() && dq.back().second <= val.second)
      dq.pop_back();
    dq.push_back(val);
  };
  
  for (int i = 0; i < n; ++i) {
    dq.clear();
    for (int j = 0; j < d; ++j) {
      push({j, a[i][j]});
      row_sum[i][0] += a[i][j];
    }
    row_max[i][0] = dq.front().second;

    // err("row_max[%d][0] = %d row_sum[%d][0] = %lld\n", i, row_max[i][0], i, row_sum[i][0]);
    for (int j = 1; j + d <= m; ++j) {
      if (dq.front().first == j - 1)
        dq.pop_front();
      push({j + d - 1, a[i][j + d - 1]});

      row_sum[i][j] = row_sum[i][j - 1] - a[i][j - 1] + a[i][j + d - 1];
      row_max[i][j] = dq.front().second;
      // err("row_max[%d][%d] = %d row_sum[%d][%d] = %lld\n", i, j, row_max[i][j], i, j, row_sum[i][j]);
    }
  }
  
  long ans = LLONG_MAX;
  for (int j = 0; j + d <= m; ++j) {
    dq.clear();
    long sum = 0;
    for (int i = 0; i < c; ++i) {
      push({i, row_max[i][j]});
      sum += row_sum[i][j];
    }
    // err("i = %d j = %d max = %d sum = %lld\n", 0, j, dq.front().second, sum);
    ans = min(ans, 1ll * dq.front().second * c * d - sum);

    for (int i = 1; i + c <= n; ++i) {
      sum -= row_sum[i - 1][j];
      sum += row_sum[i + c - 1][j];

      if (dq.front().first == i - 1)
        dq.pop_front();
      push({i + c - 1, row_max[i + c - 1][j]});
      
      ans = min(ans, 1ll * dq.front().second * c * d - sum);
      // err("i = %d j = %d max = %d sum = %lld\n", i, j, dq.front().second, sum);
    }
  }

  return ans;
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      scanf("%d", &a[i][j]);

  int q;
  scanf("%d", &q);
  while (q--) {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%lld\n", query(a, b));
  }
  return 0;
}
