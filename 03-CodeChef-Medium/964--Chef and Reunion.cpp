/*@author Vipen Loka*/
#include <bits/stdc++.h>
#define endl '\n'
#define ff first
#define ss second
#define ll long long int
#define vi vector<int>
#define vll vector<ll>
#define vvi vector < vi >
#define pii pair<int,int>
#define pll pair<long long, long long>
#define mod 1000000007
#define inf 1000000000000000001;
#define deb(x) cout << #x << ':' << x << '\n';

using namespace std;

ll ans;
void merge(vector<int> &a, int left, int mid, int right) {
	vector<int> x(a.begin() + left, a.begin() + mid);
	vector<int> y(a.begin() + mid, a.begin() + right);

	int i = 0, j = 0;
	int k = left;
	while (i < x.size() && j < y.size()) {
		if (x[i] < y[j]) {
			a[k++] = x[i++];
		}
		else {
			a[k++] = y[j++];
			ans += mid - left - i;
		}
	}
	while (i < x.size()) {
		a[k++] = x[i++];
	}
	while (j < y.size()) {
		a[k++] = y[j++];
	}

}
void mergesort(vector<int> &a, int left, int right) {
	if (right - left < 2)return;
	int mid = left + (right - left) / 2;

	mergesort(a, left, mid);
	mergesort(a, mid, right);
	merge(a, left, mid, right);
}

void solve() {
	int i, j;
	int n;
	ans = 0;
	cin >> n;
	vector<int> a(n);
	vector<pair<int, int>> b(n);

	for (int i = 0; i < n; ++i)
	{
		cin >> b[i].ff >> b[i].ss;
	}
	sort(b.begin(), b.end());

	for (int i = 0; i < n; ++i)
	{
		int t;
		a[i] = b[i].ss;
	}

	mergesort(a, 0, n);
	// for (auto &x : a) {
	// 	cout << x << ' ';
	// }
	// cout << endl;

	cout << ans << endl;






}


int main(int argc, char *argv[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T = 1;
	// cin >> T;
	while (T--) {
		solve();
	}
	cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << " secs" << endl;
}