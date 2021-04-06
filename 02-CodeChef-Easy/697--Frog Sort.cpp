#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
  cin >> t;
  while(t--) {
    int n, r, p, ans = 0;
    cin >> n;
    vector<int> j(n);
    vector<int> l(n);
    
    for(int i = 0; i < n; ++i) {
      cin >> r;
      if(r == 1) {
        p = i;
      }
      j[r-1] = i;
    }
    for(int i = 0; i < n; ++i) {
      cin >> l[i];
    }
    for(int i = 1; i < n; ++i) {
      int m = j[i];
      while(m <= p) {
        ++ans;
        m += l[j[i]];
      }
      p = m;
    }
    cout << ans << "\n";
  }
	return 0;
}
