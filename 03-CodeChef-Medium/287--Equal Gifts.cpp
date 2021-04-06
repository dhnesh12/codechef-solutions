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

const int MX = 100005, SZ = 14, MA = 4782969;
int n, a[MX], s1[MA + 5], s2[MA + 5];
bitset<100000000 * SZ> bs;

int pot (int b, int p) {
	int res = 1;
	while (p) {
		if (p & 1) res *= b;
		b *= b;
		p /= 2;
	}
	return res;
}

void go (int s[], int *ini, int *fin) {
	int len = 1;
	
	while (ini != fin) {
		fin--;
		
		for (int i = len - 1; i >= 0; i--) {
			s[3 * i] = s[i];
			s[3 * i + 1] = s[i] + *fin;
			s[3 * i + 2] = s[i] - *fin;
		}
		
		len *= 3;
	}
}

bool find (int s[], int len, int off) {
	for (int mk = 1, lim = pot(3, len); mk < lim; mk++)
		if (!s[mk]) {
			string res;
			while ((int)res.size() < off) res.pb('N');
			
			forn (j, len) {
				res.pb("NAB"[mk % 3]);
				mk /= 3;
			}
			
			while ((int)res.size() < n) res.pb('N');
			
			cout << "YES" << endl;
			cout << res << endl;
			return 1;
		} 
	
	return 0;
}

void solve () {
	cin >> n;
	forn (i, n)
		cin >> a[i];
	
	go(s1, a, a + min(SZ, n));
	if (find(s1, min(SZ, n), 0))
		return;
	
	if (n <= SZ) {
		cout << "NO" << endl;
		return;
	}
	
	go(s2, a + SZ, a + min(2 * SZ, n));
	if (find(s2, min(SZ, n - SZ), SZ))
		return;
	
	bs.reset();
	for (int mk = 1, lim = pot(3, SZ); mk < lim; mk++)
		if (s1[mk] > 0)
			bs[s1[mk]] = 1;
	
	for (int mk2 = 1, lim = pot(3, min(SZ, n - SZ)); mk2 < lim; mk2++)
		if (s2[mk2] < 0 && bs[-s2[mk2]]) {
			for (int mk1 = 1, _lim = pot(3, SZ); mk1 < _lim; mk1++)
				if (s1[mk1] == -s2[mk2]) {
					string res;
					
					forn (j, SZ) {
						res.pb("NAB"[mk1 % 3]);
						mk1 /= 3;
					}
					
					forn (j, min(SZ, n - SZ)) {
						res.pb("NAB"[mk2 % 3]);
						mk2 /= 3;
					}
					
					while ((int)res.size() < n) res.pb('N');
					
					cout << "YES" << endl;
					cout << res << endl;
					return;
				}
				
				assert(0);
			}
	
	cout << "NO" << endl;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	assert(MA == pot(3, SZ));
	
	int t;
	cin >> t;
	while (t--)
		solve();	
	
	return 0;
}
