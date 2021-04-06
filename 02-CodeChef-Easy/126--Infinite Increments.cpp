#pragma GCC optimize "trapv"
#include<bits/stdc++.h>

#define int long long
#define pb push_back
#define ppb pop_back
#define ff first
#define ss second
#define sz(s) (int)(s.size())
#define vvi vector<vector<int>>
#define vi vector<int>
#define all(a) (a).begin(),(a).end()
#define pii pair<int,int>
#define trace(x,y) cout<<"Value of "<< x << " = " << y <<endl
#define endl '\n'
#define M 1000000007
const int INF = 1ll << 60;

using namespace std;
//-----------------------------------------//


void solve() {
	int n;
	cin >> n;
	int a[n];
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	int ans = INF;
	for (int i = 0; i < n - 1; ++i) {
		ans = min(ans, a[i] - a[i + 1]);
	}

	cout << ans << endl;
}



signed main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t = 1;
	cin >> t;
	while (t--) {
		solve();
	}
}
