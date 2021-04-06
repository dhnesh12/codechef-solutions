#include <bits/stdc++.h>
using namespace std;
// #define IOS ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
typedef long long ll;

const int N = 2e3;
const int MOD = 1e9+7;

int n, dp[N][N]; 

inline ll add(ll a, ll b) {
	return (a + b) % MOD;
}

inline ll mul(ll a, ll b) {
	return (a * 1ll * b) % MOD;
}

int main() {

	dp[0][0] = 1;
	for(int i = 1; i < N; i++) 
	for(int j = 1; j < N; j++) {
		dp[i][j] = add(mul(j,dp[i-1][j]), dp[i-1][j-1]);
	}	

	int _; scanf("%d",&_);
	while(_--) {
		scanf("%d",&n);
    	ll ans = 0;
		for(int i = 1; i <= n; i++) {
			ans = add(ans, dp[n][i]);
		}
		printf("%lld\n",ans);
	} 
}	