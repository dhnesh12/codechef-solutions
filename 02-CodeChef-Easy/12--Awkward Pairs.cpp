#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
#define ll long long int
#define MAXN 100005
ll mod = 1000000007, ct[185][2], coprime[185][185], fact[2004], dp[20][185];
void init(){
	fact[0] = 1; for (ll i = 1; i <= 2000; i++){fact[i] = (fact[i-1] * i) % mod;}for (int i = 1; i <= 180; i++){
		for (int j = 1; j <= 180; j++){if (__gcd(i, j) == 1){coprime[i][j] = coprime[j][i] = 1;}}}
	for (ll i = 0; i <= 9; i++){dp[1][i] = 1;}
	for (ll i = 2; i <= 19; i++){for (ll j = 0; j <= 180; j++){
			for (ll k = 0; k <= j && k <= 9; k++){dp[i][j] = (dp[i][j] + dp[i-1][j-k]) % mod;}}}}
ll solve (ll x, ll num){vector<ll> v; ll y = x;
	while (y > 0){v.push_back(y % 10); y /= 10;} if (v.size() == 0){v.push_back(0);}
	reverse (v.begin(), v.end()); int sz = v.size(), ans;
	for (int s = 0; s <= 180; s++){ll left = s; ans = 0;
		for (int i = 0; i < sz; i++){if (i == sz-1){if (left <= v[i]){ans += 1;}continue;}
			for (int j = 0; j < v[i] && j <= left; j++){ans = (ans + (dp[sz-i-1][left-j])) % mod;}
			left -= v[i]; if (left < 0){break;}}ct[s][num] = ans;}}
int main(){init(); ll t; cin >> t;
	while (t--){ll l, r, c1, c2, ans = 0; cin >> l >> r; solve (l-1, 0); solve (r, 1);
		for (int i = 1; i <= 180; i++){
			for (int j = i; j <= 180; j++){c1 = (ct[j][1]-ct[j][0]); c2 = (ct[i][1]-ct[i][0]);
				if (i == j){continue;}if (coprime[i][j]){ans = (ans + (c1 % mod) * (c2 % mod)) % mod;}}}
		cout << ans << endl;}}