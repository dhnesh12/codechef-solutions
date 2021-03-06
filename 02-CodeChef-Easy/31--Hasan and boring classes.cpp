#include <bits/stdc++.h>
using namespace std;
const int MAX = 3e5 + 5;
const int MOD = 1e9 + 7;
int p2[MAX], p24[MAX], p25[MAX], fact[MAX], invp[MAX], f1[MAX];
int power(int a, int b){int x = 1, y = a;
	while(b){if (b & 1){x = ((long long)x * y) % MOD;}y = ((long long)y * y) % MOD;b >>= 1;}return x;}
void pre(){fact[0] = 1; invp[0] = 1;
	for(int i = 1; i < MAX; ++i){fact[i]=((long long)fact[i-1]*i)%MOD;}invp[MAX-1]=power(fact[MAX-1], MOD-2);
	for (int i = MAX - 2; i >= 1; i--){invp[i] = ((long long)invp[i+1] * (i+1)) % MOD;
		assert(((long long)fact[i] * invp[i]) % MOD == 1);}p2[0] = 1; p24[0] = 1; p25[0] = 1;
	for(int i = 1; i < MAX; ++i){p2[i]=((long long)p2[i-1]*2)%MOD; p24[i] = ((long long)p24[i-1] * 24) % MOD;
		p25[i] = ((long long)p25[i-1] * 25) % MOD;}}
int ncr(int n, int r){if (n < r){return 0;}
	int ans = ((long long)fact[n] * invp[n-r]) % MOD;ans = ((long long)ans * invp[r]) % MOD;return ans;}
int solve(int n, int k, int fixed, int non_fixed){if (k < 0){return 0;}int ans = 0; f1[0] = 1;
	for (int i = 1; i <= k; i++){f1[i] = f1[i-1];
		if (i % 2 == 0){f1[i] = (f1[i] + ((long long)ncr(fixed, i/2) * p25[i/2])) % MOD;}}
	for (int x = 0; x <= k; x++){int r = x + 2 * (non_fixed - x);
		if (r <= k && non_fixed >= x){int f2 = ((long long)ncr(non_fixed, x) * p2[x]) % MOD;
			f2 = ((long long)f2 * p24[non_fixed - x]) % MOD;
			ans = (ans + ((long long)f2 * f1[k - r])) % MOD;}}return ans;}
int main(){ios_base::sync_with_stdio(false); pre(); int T, n, k; string s; cin >> T;
	while(T--){cin >> n >> k >> s; int fixed = 0, non_fixed = 0;
		for (int i = 0; i < n/2; i++){if (s[i] == s[n-1-i]){fixed += 1;}else{non_fixed += 1;}}int ans;
		if (n & 1){ans = solve(n, k, fixed, non_fixed);
			ans = (ans + ((long long)25 * solve(n, k-1, fixed, non_fixed))) % MOD;}
		else{ans = solve(n, k, fixed, non_fixed);}cout << ans << endl;}}