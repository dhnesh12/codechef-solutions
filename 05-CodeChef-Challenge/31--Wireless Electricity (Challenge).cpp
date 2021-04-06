#include <bits/stdc++.h>
#define pi acos(-1.0)
#define mod 1000000007
using namespace std;
int a[2505], b[2505], c[2505], d[2505];
int resa[2505], resb[2505];
int ca[2505], cb[2505], cc[2505], cd[2505];
int mcnt;
int treemax;
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    int x, y;
    cin >> x >> y;
  }
  for (int i = 1; i <= m; i++) {
    int x, y;
    cin >> a[i] >> b[i] >> c[i] >> d[i];
  }
  memset(resa,0,sizeof resa);
  memset(resb,0,sizeof resb);
  for (int i = 1; i <= 100; i++) {
    int idx = (i-1) % 50;
    if (idx == 0) {
      if (a[i] < 1000000) {
        resa[i] = -1 - a[i];
        resb[i] = -b[i];
      } else {
        resa[i] = -a[i];
        resb[i] = -1 - b[i];
      }
    } else {
      resa[i] = cc[i - 1] - a[i];
      resb[i] = cd[i - 1] - b[i];
      if (abs(resa[i]) > 1000000||abs(resb[i]) > 1000000)
      if (a[i] < 1000000) {
        resa[i] = -1 - a[i];
        resb[i] = -b[i];
      } else {
        resa[i] = -a[i];
        resb[i] = -1 - b[i];
      }
    }
    ca[i] = resa[i] + a[i];
    cb[i] = resb[i] + b[i];
    cc[i] = resa[i] + c[i];
    cd[i] = resb[i] + d[i];
  }
  for (int i = m / 2 + 1; i <= m / 2 + 100; i++) {
    int idx = (i-1) % 50;
    if (idx == 0) {
      if (c[i] > 0) {
        resa[i] = 1000001 - c[i];
        resb[i] = 1000000 - d[i];
      } else {
        resa[i] = 1000000 - c[i];
        resb[i] = 1000001 - d[i];
      }
    } else {
      resa[i] = ca[i - 1] - c[i];
      resb[i] = cb[i - 1] - d[i];
      if (abs(resa[i]) > 1000000||abs(resb[i]) > 1000000)
      if (c[i] > 0) {
        resa[i] = 1000001 - c[i];
        resb[i] = 1000000 - d[i];
      } else {
        resa[i] = 1000000 - c[i];
        resb[i] = 1000001 - d[i];
      }
    }
    ca[i] = resa[i] + a[i];
    cb[i] = resb[i] + b[i];
    cc[i] = resa[i] + c[i];
    cd[i] = resb[i] + d[i];
  }
  for (int i = 1; i <= m; i++) {
    cout << resa[i] << " " << resb[i] << endl;
  }

  return 0;
}