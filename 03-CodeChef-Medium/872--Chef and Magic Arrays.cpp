#include <iostream>
#include <vector>

using namespace std;

long long n, m, x, ans, t;

vector <long long> a[1000005];

int main()  {
  cin >> t;
  while (t--)  {
    ans = 0;
    cin >> n;
    for (long long i = 1; i <= n; ++i)  {
      cin >> m;
      a[i].clear();
      for (long long j = 1; j <= m; ++j)  {
        cin >> x;
        a[i].push_back(x);
      }
    }
    long long Max = 0, Min = -1e18;
    for (auto it : a[1])  {
      if (it > Max)
        Max = it;
      if (- it > Min)
        Min = - it;
    }
    for (long long i = 2; i <= n; ++i)  {
      long long last = a[i].back();
      long long Max1 = 0;
      long long Min1 = -1e18;
      for (auto it : a[i])  {
        long long dp = max(Max - it * (i - 1), Min + it * (i - 1));
        ans = max(ans, dp);
        Max1 = max(Max1, dp + last * i);
        Min1 = max(Min1, dp - last * i);
        last = it;
      }
      Max = Max1;
      Min = Min1;
    }
    cout << ans << '\n';
  }
	return 0;
}
