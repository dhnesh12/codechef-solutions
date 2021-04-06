#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 110;
 
int n;
int di[] = {0, 0, -1, 0, 1};
int dj[] = {0, -1, 0, 1, 0};
char s[N];
 
vector<int> gauss(vector<vector<int> > &a) {
  int n = a.size();
  vector<int> x(n, 0);
  for (int i = 0; i < n - 1; ++i) {
    int who = -1;
    for (who = i; who < n; ++who)
      if (a[who][i] == 1) break;
    if (who == n) continue;
    swap(a[who], a[i]);
    for (int j = i + 1; j < n; ++j) {
      if (a[j][i] == 1) {
        for (int k = i; k < (int)a[0].size(); ++k) {
          a[j][k] ^= a[i][k];
        }
      }
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    if (a[i][i] != 0) {
      x[i] = a[i][n];
      for (int k = i + 1; k < n; ++k) {
        x[i] ^= a[i][k] & x[k];
      }
    }
  }
  return x;
}
 
inline bool in(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < n;
}
 
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    vector<int> b(n * n);
    for (int i = 0; i < n; ++i) {
      scanf("%s", s);
      for (int j = 0; j < n; ++j) {
        b[i * n + j] = s[j] - '0';
      }
    }
    vector<vector<int> > a(n * n, vector<int>(n * n + 1, 0));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int p = i * n + j;
        for (int k = 0; k < 5; ++k) {
          int ni = i + di[k];
          int nj = j + dj[k];
          if (!in(ni, nj)) continue;
          a[p][ni * n + nj] = 1;
        }
      }
    }
    for (int i = 0; i < n * n; ++i) {
      a[i][n * n] = b[i];
    }
    vector<int> x = gauss(a);
    printf("%d\n", count(x.begin(), x.end(), 1));
    for (int i = 0; i < x.size(); ++i) {
      if (x[i])
        printf("%d %d\n", i / n + 1, i % n + 1);
    }
  }
  return 0;
}