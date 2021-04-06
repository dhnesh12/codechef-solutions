#include<bits/stdc++.h>
using namespace std;
#define int long long
void solve(){int n, k; cin >> n >> k;
	if (n == 1){if (!k){cout << 1 << endl;} else{cout << -1 << endl;} return;}
	int mn_sum = n *(n+1)/2-1, diff = k-mn_sum, temp = (n-1)/2, mx_diff = temp*(n-temp-1);
	if (diff < 0 || diff > mx_diff){cout << -1 << endl; return;} int val = n-2, change = 0;
	while (diff > val){change++; diff -= val; val -= 2;} vector<int> v (n+5,0); int ind = -1;
	for (int i = 0; i < change; i++){ind += 2; v[ind] = n - i;} int lim = n-change-diff; ind = 0;
	for (int i = 1 ; i < lim ; i++, ind++){if (!v[ind]){v[ind] = i;} else{v[++ind] = i;}}
	if (v[ind]){ind += 1;} v[ind++] = n-change; while (lim <= n-change-1){v[ind++] = lim++;}
	for (int i = 0 ; i < n; i++){cout << v[i] << " ";} cout << endl;}
signed main(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0); int t; cin >> t; while (t--){solve();}}