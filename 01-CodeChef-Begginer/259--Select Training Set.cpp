
#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n;
  cin >> n;
  map<string, int> one, zero;
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    int x; cin >> x;
    if (x) one[s]++;
    else zero[s]++;
  }
  int count = 0;
  for (auto i : one) {
    if (zero.find(i.first) != zero.end())
      count += max(zero[i.first], i.second);
    else
      count += i.second;
  }
  for (auto i : zero) 
    if (one.find(i.first) == one.end())
      count += i.second;

  cout << count << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);
  int t = 1;
  cin >> t;
  for (int tt = 1; tt <= t; ++tt) {
    //cout << "Case #" << tt << ": ";
    solve();
  }
  return 0;
} //Hajimemashite


