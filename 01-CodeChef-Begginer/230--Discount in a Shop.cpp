
#include <bits/stdc++.h>

using namespace std;

void solve() {
  string s;
  cin >> s;
  int mini = INT_MAX;
  int n = (int)s.size();
  for (int i = 0; i < n; i++) {
    string res = "";
    for (int j = 0; j < n; j++) 
      if (i != j)
        res += s[j];
    int x = stoi(res);
    mini = min(mini, x);
  }
  cout << mini << '\n';
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


