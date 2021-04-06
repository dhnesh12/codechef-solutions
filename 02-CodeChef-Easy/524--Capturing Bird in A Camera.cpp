#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef long long ll;
typedef long double ld;
typedef unsigned long long Ull;

#define endl "\n"
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define pb push_back
void read(int &sum) {sum = 0; char c = getchar( ); bool f = 0; while (c < '0' || c > '9') {if (c == '-') f = 1; c = getchar( );} while (c >= '0' && c <= '9') {sum = sum * 10 + c - '0'; c = getchar( );} if (f) sum = -sum;}
void read(ll &sum) {sum = 0; char c = getchar( ); bool f = 0; while (c < '0' || c > '9') {if (c == '-') f = 1; c = getchar( );} while (c >= '0' && c <= '9') {sum = sum * 10 + c - '0'; c = getchar( );} if (f) sum = -sum;}
void readarr(ll a[], ll n) {for (int i = 0; i < n; i++)read(a[i]);}
void readarr(int a[], int n) {for (int i = 0; i < n; i++)read(a[i]);}
void readvec(vector<ll> &a, ll n) {for (int i = 0; i < n; i++)read(a[i]);}
void readvec(vector<int> &a, int n) {for (int i = 0; i < n; i++)read(a[i]);}
void aout(ll a[], ll n) {for (int i = 0; i < n; i++)cout << a[i] << " ";}
void aout(int a[], int n) {for (int i = 0; i < n; i++)cout << a[i] << " ";}
const int MAXN = (int)1e6 + 7;
const int MOD = 998244353;
const int INF = (int)2e9 + 7;
const ll LINF = (i64)1e18;
const ld PI = 3.1415926535897932384626433832795;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
	int n;
	read(n);
	vector<double> x(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i];
	}
	sort(all(x));
	double p, q;
	cin >> p >> q;
	double ans = 0;
	for (int i = 0; i < n / 2; i++) {
		double c1 = p - x[i], c2 = p - x[n - i - 1];
		ans += acos((c1 * c2 + q * q) / (sqrt(c1 * c1 + q * q) * sqrt(c2 * c2 + q * q)));
	}
	cout << setprecision(12) << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int t = 1;
	read(t);
	while (t--)
	{
		solve();
	}
}
