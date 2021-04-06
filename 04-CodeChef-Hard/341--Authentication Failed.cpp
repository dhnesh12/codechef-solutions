#include<bits/stdc++.h>
using namespace std;

#define MOD 1009419529

int n, k;
string pwd;
int last[26];
int jump[10101];
int memo[10101][101];

int dp(int pos, int left) {
	if(!left)
		return 1;
	if(pos >= n + k || left < 0)
		return 0;
	if(memo[pos][left] != -1)
		return memo[pos][left];
	int ret = dp(pos+1, left) + dp(pos+1, left-1);
	ret %= MOD;
	if(jump[pos] + 1 <= n+k) {
		ret -= dp(jump[pos]+1, left - (jump[pos]  - pos));
		ret += MOD;
		ret %= MOD;
	}
	return memo[pos][left] = ret;
}

void solve() {
	cin >> n >> k >> pwd;
	for(int i = 0; i < 26; i++)
		last[i] = n+k;
	for(int i = 0; i < n+k; i++)
		jump[i] = n+k;
	for(int i = n+k-1; i >= 0; i--) {
		jump[i] = last[pwd[i]-'a'];
		last[pwd[i]-'a'] = i;
	}

	for(int i = 0; i <= n+k; i++)
	   for(int j = 0; j <= k; j++)
	  		memo[i][j] = -1;  

	int ans = dp(0, k) - 1 + MOD;
	ans %= MOD;
	/*
	for(int i = 0; i <= n+k; i++) {
		for(int j = 0; j <= k; j++) {
			cout << dp(i, j) << " ";
		}
		cout << endl;
	}
	*/
	cout << ans << endl;
}

int t;
int main() {
	cin >> t;
	while(t-->0)
		solve();
	return 0;
}


