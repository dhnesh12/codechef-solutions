#include <cmath>
#include <functional>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <math.h>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <chrono>
#include <cstring>

using namespace std;

typedef long long ll;

#ifdef iq
  mt19937 rnd(228);
#else
  mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
#endif

const ll inf = (ll) (1e18) + 7;

const int N = 12000 + 7;

int sz[N];
ll ok[N][5001];

int z = 0;

void solve(int v, int l, int r, vector <int> &a) {
  if (l > r) {
    ok[v][0] = 0;
    sz[v] = 0;
    return;
  }
  if (l == r) {
    sz[v] = 1;
    ok[v][0] = 0;
    ok[v][1] = a[l];
  } else {
    int x = l;
    for (int i = l; i <= r; i++) {
      if (a[i] > a[x]) {
        x = i;
      }
    }
    int vl = z++;
    int vr = z++;
    solve(vl, l, x - 1, a);
    solve(vr, x + 1, r, a);
    sz[v] = sz[vl] + sz[vr] + 1;
    for (int i = 0; i <= sz[v]; i++) ok[v][i] = inf;
    for (int i = 0; i <= sz[vl]; i++) {
      for (int j = 0; j <= sz[vr]; j++) {
        for (int t = 0; t < 2; t++) {
          ok[v][i + j + t] = min(ok[v][i + j + t], ok[vl][i] + ok[vr][j] + (i * j + (t * (i + j + 1))) * (ll) a[x]);
        }
      }
    }
    return;
  }
}

int main() {
#ifdef iq
  freopen("a.in", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    vector <int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    z = 0;
    solve(z++, 0, n - 1, a);
    cout << ok[0][k] << '\n';
  }
}
