#include <bits/stdc++.h>

using namespace std;

ifstream fin("heavytask.in");
ofstream fout("heavytask.out");

int t, n, a[100002], ans[100002], f[100002];

struct meh {
  int val, poz1, poz2;
};

void solve () {
  cin >> n;
  vector<meh>f1, f2;
  memset(f, 0, sizeof(f));
  int mx = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    if (f[a[i]]) {
      f2.push_back({a[i], f[a[i]], i});
      f[a[i]] = -1;
    }
    else
      f[a[i]] = i;
  }
  for (int i = 1; i <= 100000; i++)
    if (f[i] > 0)
      f1.push_back({i, f[i], 0});
  for (int i = 0; i < f2.size(); i++) {
    int j = (i + 1) % f2.size();
    ans[f2[i].poz1] = f2[j].val;
    ans[f2[i].poz2] = f2[j].val;
  }
  for (int i = 0; i < f1.size(); i++) {
    int j = (i + 1) % f1.size();
    ans[f1[i].poz1] = f1[j].val;
  }
  if (f1.size() == 1 && f2.size() == 1) {
    swap(ans[f1.back().poz1], ans[f2.back().poz1]);
  }
  else if (f1.size() == 1 && f2.size()) {
    swap(ans[f1.back().poz1], ans[f2.back().poz2]);
  }
  else if (f2.size() == 1 && f1.size()) {
    swap(ans[f2.back().poz1], ans[f1[0].poz1]);
    swap(ans[f2.back().poz2], ans[f1[1].poz1]);
  }
  int cnt =0;
  for (int i = 1; i <= n; i++)
    cnt += (a[i] != ans[i]);
  cout << cnt << "\n";
  for (int i = 1; i <= n; i++)
    cout << ans[i] << " ";
  cout << "\n";
}

int main()
{
  cin >> t;
  while (t--)
    solve();
  return 0;
}