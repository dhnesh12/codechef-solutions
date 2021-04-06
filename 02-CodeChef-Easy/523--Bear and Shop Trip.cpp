#include<iostream>
#include<bits/stdc++.h>
#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<stack>
#include<queue>
#include<list>
#include<vector>
#include<bitset>
using namespace std;


// #include "boost/algorithm/string.hpp"
// using namespace boost;

#define FastIO ios_base::sync_with_stdio(false)
#define mod 1000000007
#define ll int
#define pub push_back
#define fi first
#define sec second
#define read_i(x) scanf("%d",&x)
#define read_s(x) scanf("%s",x)
#define read_l(x) scanf("%ld",&x)
#define INFI 1000000000000000000
#define NINFI -1000000000000000000




#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")


#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) {
	cout << name << " : " << arg1 << std::endl;
	//use cerr if u want to display at the bottom
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
	const char* comma = strchr(names + 1, ','); cout.write(names, comma - names) << " : " << arg1 << " | "; __f(comma + 1, args...);
}
#else
#define trace(...)
#endif


long double distance(pair<ll, ll> p1, pair<ll, ll> p2) {

	ll dx = (p1.first - p2.first);
	ll dy = (p1.second - p2.second);

	return (sqrt((dx * dx) + (dy * dy)));

}

long double dist[50][50] = {0};


ll n, k;
vector<pair<ll, ll>> coordinates;
vector<ll> ingredients;
long double dp[(1 << 13) + 1][40];

long double solve(ll mask, ll pos) {

	if ((mask == ((1 << k) - 1)) && (pos == 0))
		return 0;

	if (dp[mask][pos] != -1)
		return dp[mask][pos];

	dp[mask][pos] = INT_MAX;


	for (ll i = 0; i <= n; i++) {
		if (((mask | ingredients[i]) != mask) || (i == 0))
			dp[mask][pos] = min(dp[mask][pos], dist[pos][i] + solve(mask | ingredients[i], i));
	}

	return dp[mask][pos];

}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	ll t;
	string temp;
	cin >> t;
	while (t--) {

		cin >> n >> k;
		coordinates.clear();
		ingredients.clear();

		coordinates.pub({0, 0});

		for (ll i = 0; i < n; i++) {
			ll x, y;
			cin >> x >> y;
			coordinates.pub({x, y});
		}

		ingredients.pub(0);
		ll possible = 0;
		for (ll i = 0; i < n; i++) {
			cin >> temp;
			reverse(temp.begin(), temp.end());


			ll temp_mask = 0;
			for (ll j = 0; j < temp.length(); j++) {
				temp_mask |= (1 << j) * (temp[j] - '0');
			}
			possible |= temp_mask;
			ingredients.pub(temp_mask);

		}

		ll mask_of_all_set_ingredients = ((1 << k) - 1);
		if (possible != mask_of_all_set_ingredients) {

			cout << -1 << '\n';
			continue;
		}
		memset(dist, 0, sizeof dist);
		for (ll i = 0; i <= n; i++) {
			for (ll j = 0; j <= n; j++) {
				dist[i][j] = distance(coordinates[i], coordinates[j]);
			}
		}

		for (ll i = 0; i < (1 << k); i++) {
			for (ll j = 0; j <= n; j++) {
				dp[i][j] = -1;
			}
		}

		long double ans = solve(0, 0);

		cout << fixed << setprecision(9) << ans << '\n';

	}

	return 0;
}