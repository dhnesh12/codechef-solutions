#include <bits/stdc++.h>

#define endl '\n'
#define fi first
#define se second
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < int(n); i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 1005;
ll n, a[MX], sum;
ld res[MX];

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);	
	
	cin >> n;
	forn (i, n) {
		cin >> a[i];
		sum += a[i];
	}
	
	forn (i, n) forn (j, n) if (i != j)
		res[i] += 1.0l * a[j] / (a[i] + a[j]);
	
	forn (i, n)
		cout << res[i] + 1 << " ";
	cout << endl;
	
	return 0;
}
