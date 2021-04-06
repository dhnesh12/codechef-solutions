#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a;
    for (int i = 0; i < n; i++) {
      if (s[i] == '1') {
        a.emplace_back(i);
      }
    }
    if (a.size() > (n + 1) / 2) {
      cout << "impossible\n";
      continue;
    }
    for (int i = 0; i < n + 5; i++) {
      a.emplace_back(-2 * (i + 1));
      a.emplace_back(n - 1 + 2 * (i + 1));
    }
    sort(begin(a), end(a));
    long long ans = 0;
    priority_queue<long long> pq;
    for (int i = 0; i < (int) a.size(); i++) {
      a[i] -= 2 * i;
      pq.emplace(a[i]);
      pq.emplace(a[i]);
      ans += pq.top() - a[i];
      pq.pop();
    }
    cout << ans << "\n";
  }
  return 0;
}
