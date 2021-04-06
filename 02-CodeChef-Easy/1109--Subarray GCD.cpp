#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
#define ld long double
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define loop(i,a,b) for(ll i = a; i < b; i++)
#define looprev(i,a,b) for(ll i = a; i >= b; i--)
#define all(x) x.begin(), x.end()
#define V(a) vector<a>
#define P(a, b) pair<a, b>
#define S(a) set<a>
#define M(a, b) map<a, b>
void IO() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}
void IOS() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
}
int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}
int lcm(int a, int b) {
	return (a * b) / gcd(a, b);
}
void solve() {
	int n;
	cin >> n;
	V(int) a(n);
	loop(i, 0, n) cin >> a[i];
	int g = a[0];
	loop(i, 1, n) {
		g = gcd(g, a[i]);
	}
	if (g == 1) cout << n << endl;
	else cout << -1 << endl;
}
int main(int argc, char const *argv[]) {
	IOS(); IO();
	clock_t begin = clock();
	int tc;
	cin >> tc;
	while (tc--) {
		solve();
	}
#ifndef ONLINE_JUDGE
	clock_t end = clock();
	cout << "\n\nExecuted in: " << double(end - begin) * 1000 << " ms.";
#endif
	return 0;
}