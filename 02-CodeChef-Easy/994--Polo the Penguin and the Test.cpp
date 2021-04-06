#include "bits/stdc++.h"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long int
#define mod 1000000007
#define deb(x) cout << #x << " " << x << "\n";
#define fo(i, n) for(ll i = 0; i < n; i++)
#define Fo(i, k, n) for(ll i = k; i < n; i++)
#define ordered_set tree < ll ,  null_type ,  less<ll> ,  rb_tree_tag ,  tree_order_statistics_node_update >
using namespace std;
using namespace __gnu_pbds;

int dp[101][101];
ll knapsack(vector<ll>& c, vector<ll>& p, vector<ll>& t, ll n, ll w) {
	
	if(n == -1 or w == 0) {
		return 0;
	}
	
	if(dp[n][w] != -1) {
		return dp[n][w];
	}
	
	if(t[n] <= w) {
		return dp[n][w] = max(
			c[n] * p[n] + knapsack(c, p, t, n-1, w-t[n]),
			knapsack(c, p, t, n-1, w)
		);
	}
	
	return dp[n][w] = knapsack(c, p, t, n-1, w);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	ll T;
	cin >> T;
	while(T--) {
		ll n, w;
		cin >> n >> w;
		vector<ll> c(n), p(n), t(n);
		
		for(int i = 0; i < n; i++) {
			cin >> c[i] >> p[i] >> t[i];
		}
		
		memset(dp, -1, sizeof(dp));
		ll res = knapsack(c, p, t, n-1, w);
		cout << res << "\n";
	}
	
	return 0;
}












