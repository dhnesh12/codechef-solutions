#include<bits/stdc++.h>
using namespace std;


#define int             long long
#define pb              push_back
#define ppb             pop_back
#define pf              push_front
#define ppf             pop_front
#define all(x)          (x).begin(), (x).end()
#define uniq(v)         (v).erase(unique(all(v)), (v).end())
#define sz(x)           (int)((x).size())
#define ff              first
#define ss              second
#define rep(i, a, b)    for(int i = a; i <= b; i++)
#define mem1(a)         memset(a, -1, sizeof(a))
#define mem0(a)         memset(a, 0, sizeof(a))
#define endl            "\n"
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;


const long long INF = 1e18;
const int32_t M = 1e9 + 7;
const int32_t MM = 998244353;









int binpow(int a, int b) {
	int res = 1;
	while (b > 0) {
		if (b & 1) {
			res = a * res;
		}
		a = a * a;
		b >>= 1;
	}
	return res;
}




void fast_io()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
}


const int N = 10005;
// int dp[N][N];

// int func(int i, int j) {
// 	if (i == 0 && j == 0) return dp[i][j] = 0;
// 	if (i == 0 && j == 1) return dp[i][j] = 0;
// 	if (i == 1 && j == 1) return dp[i][j] = 0;

// 	if (i == 1 && j == 2) return dp[i][j] = 1;
// 	if (i == 2 && j == 1) return dp[i][j] = 1;

// 	if (dp[i][j] != -1) return dp[i][j];
// 	int ans1, ans2;
// 	ans1 = 0; ans2 = 0;
// 	for (int k = 1; k <= j / 2; k++) {
// 		ans1 = ans1 || !func(k, j - k);
// 	}
// 	for (int k = 1; k <= i / 2; k++) {
// 		ans2 = ans2 || !func(k, i - k);
// 	}
// 	return dp[i][j] = ans1 || ans2;

// }

void solve() {
	// memset(dp, -1, sizeof(dp));
	int a, b; cin >> a >> b;


	// Generating the pattern

	// for (int i = 1; i <= a; i++) {
	// 	for (int j = 1; j <= b; j++) {
	// 		cout << i << ' ' << j << ' ' << func(i, j) << endl;
	// 	}
	// 	cout << endl;
	// }


	// after Generating the pattern i observed that both odd is a losing position otherwise winning

	if (a % 2 == 1 && b % 2 == 1) {

		cout << "Vanka" << endl;
	}
	else {
		cout << "Tuzik" << endl;
	}













}

signed main()
{
	fast_io();
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int t = 1;

	cin >> t;


	while (t--) {

		solve();


	}
	return 0;


}