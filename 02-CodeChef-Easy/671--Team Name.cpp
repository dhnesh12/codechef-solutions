#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
  cin >> t;
  while(t--) {
    int n;
    cin >> n;
    set<string> s;
    string a, b;
    for(int i = 0; i < n; ++i) {
      cin >> a;
      s.insert(a);
    }
    int ans = 0;
    for(string i : s) {
      for(string j : s) {
        if(i!=j) {
          a = i;
          b = j;
          swap(a[0], b[0]);
          if(s.count(a)==0&&s.count(b)==0) {
            ++ans;
          }
        }
      }
    }
    cout << ans << "\n";
  }
	return 0;
}
