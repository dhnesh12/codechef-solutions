#include <bits/stdc++.h>
#define IN(a) for(auto &x: a) cin>>x;
#define OUT(a) for(auto x: a) cout<<x<<' '; cout<<'\n';
using namespace std;
const int MOD = 1e9+7;
int solve(){int n, m, K;cin >> n >> m >> K; int a[n]; IN(a); vector<int> dec(n, 0), inc(n, 0);
	while (m--){char t; int l, r; cin >> t >> l >> r;
		if (t == 'I'){inc[l-1]++, inc[r-1]--;} else{dec[l-1]++, dec[r-1]--;}}
	int d[n], rise(0), fall(0);
	for(int i = 0;i < n; i++){rise += inc[i];fall+=dec[i];if(rise && fall){return 0;}else if(rise){d[i] = 1;}
		else if(fall){d[i] = -1;}else{d[i] = 0;}}
	long long ans = 1;
	for (int i = 0;i < n; i++){int l = i, r = i;while(d[r]){r++;}bool all = true;
		for (int j = l; j <= r; j++){if (a[j] != -1){all = false; int val = a[j];
				for (int k = j-1;k >= l; k--){val -= d[k];
					if(val < 1 || val > K || (a[k] != -1 && a[k] != val)) return 0;}val = a[j];
				for (int k = j+1;k <= r; k++){val += d[k-1];
					if(val < 1 || val > K || (a[k] != -1 && a[k] != val)) return 0;}break;}}
		if(all){int cur = 0, mx = 0, mn = 0;
			for (int j = l+1; j <= r; j++){cur += d[j-1]; mx = max(mx, cur); mn = min(mn, cur);
			}if(mx-mn+1 > K)	return 0;ans = (ans * (K-(mx-mn)))%MOD;}i = r;}return ans;}
int main(){ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int t; cin >> t; while(t--){cout << solve() << endl;}}