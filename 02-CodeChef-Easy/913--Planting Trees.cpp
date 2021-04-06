#include <bits/stdc++.h>
using namespace std;

void solve() {
 int n, ans = 0; cin >> n;
 int a[n + 2];
 a[0] = a[n+1] = -1;
 for (register int i = 1; i <= n; i++) cin >> a[i];

 sort(a+1, a + n + 1);
 for (register int i = 1; i <= n; i++) 
   if (a[i] + 1 != a[i + 1] and a[i] - 1 != a[i - 1]) {
     ans++; a[i]++;
   }

 cout << ans << "\n";
}

int main() {
 ios_base::sync_with_stdio(false); cin.tie(0);
 register int tc; cin >> tc;
 while (tc--) solve();
 return 0;
}