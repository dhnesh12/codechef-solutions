#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const int mxn = 1e6+10;
const int mod = 1e9+7;
const int inf = 1e9;

signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int tc; cin>>tc;
	while(tc--) {
		ll n, a, b; cin>>n>>a>>b;
		if(!(a*b>=n and a+b<=n+1)) {
			cout << -1 << '\n';
		}
		else {
			vector<int> sz(a, 0);
			sz[0] = b;
			int cur = n-b; int ind = 1;
			while(cur) {
				sz[ind]++;cur--;ind++;if(ind==a) ind = 1;
			}
			vector<int> ans; int cnt = 1;
			for(int i=0; i<a; i++) {
				vector<int> tmp;
				for(int j=0; j<sz[i]; j++) tmp.push_back(cnt++);
				reverse(begin(tmp), end(tmp));
				for(int x:tmp)ans.push_back(x);
			}
			assert(cnt==n+1);
			for(int x:ans) cout << x << " ";
			cout << '\n';
		}
	}
 
	return 0;
}