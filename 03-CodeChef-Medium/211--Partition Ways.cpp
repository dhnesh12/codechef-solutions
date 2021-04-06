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

const int MX = 2000005, mod = 998244353, g = 3;
ll fac[MX], inv[MX];

int nearestPowerOfTwo(int n){
	int ans = 1;
	while(ans < n) ans <<= 1;
	return ans;
}

ll pot (ll b, ll p, int mod) {
	ll res = 1;
	
	if (p < 0)
		p += mod - 1;
		
	while (p) {
		if (p & 1) (res *= b) %= mod;
		(b *= b) %= mod;
		p /= 2;
	}
	
	return res;
}

void ntt (vi &X, int inv) {
	int n = X.size();
	
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	
	vector<ll> wp(n >> 1, 1);
	for(int k = 1; k < n; k <<= 1) {
		ll wk = pot(g, inv * (mod - 1) / (k << 1), mod);
		
		for(int j = 1; j < k; ++j)
			wp[j] = wp[j - 1] * wk % mod;
		
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = X[i + j], v = X[i + j + k] * wp[j] % mod;
				X[i + j] = u + v < mod ? u + v : u + v - mod;
				X[i + j + k] = u - v < 0 ? u - v + mod : u - v;
			}
		}
	}
	
	if(inv == -1){
		ll nrev = pot(n, mod - 2, mod);
		for (int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % mod;
	}
}

vector<int> convolution(vector<int> A, vector<int> B){
	int sz = A.size() + B.size() - 1;
	int size = nearestPowerOfTwo(sz);
	A.resize(size), B.resize(size);
	ntt(A, 1), ntt(B, 1);
	for(int i = 0; i < size; i++)
		A[i] = 1ll * A[i] * B[i] % mod;
	ntt(A, -1);
	A.resize(sz);
	return A;
}

vector<int> inversePolynomial(const vector<int> & A){
	vector<int> R(1, pot(A[0], mod - 2, mod));
	
	while(R.size() < A.size()){
		int c = 2 * R.size();
		R.resize(c);
		vector<int> R2 = R;
		vector<int> a(min(c, (int)A.size()));
		for(int i = 0; i < (int)a.size(); ++i)
			a[i] = A[i];
		R2 = convolution(R2, R2);
		R2.resize(c);
		R2 = convolution(R2, a);
		for(int i = 0; i < c; ++i){
			R[i] = R[i] + R[i] - R2[i];
			if(R[i] < 0) R[i] += mod;
			if(R[i] >= mod) R[i] -= mod;
		}
	}
	
	R.resize(A.size());
	return R;
}

ll comb (int n, int k) {
	if (n < 0 || k < 0 || n < k) return 0;
	return fac[n] * inv[k] % mod * inv[n - k] % mod;
}

ll f (int n, int k) {
	if (n > k) return 0;
	return comb(k, k - n);
}

int n, k, l, r;

void solve () {
	cin >> n >> k >> l >> r;
	
	vi p(n + 1);
	for (int i = 1; i <= n; i++) {
		p[i] = -(f(i, r) - f(i, l - 1));
		if (p[i] < 0) p[i] += mod;
	}
	p[0] = 1;
	
	vi res = inversePolynomial(p);
	
	ll kinv = pot(k, -1, mod), q = 1;
	
	for (int i = 1; i <= n; i++) {
		(q *= kinv) %= mod;
		cout << res[i] * q % mod << " ";
	}
	cout << endl;
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	fac[0] = inv[0] = 1;
	for (int i = 1; i < MX; i++) {
		fac[i] = fac[i - 1] * i % mod;
		inv[i] = pot(fac[i], -1, mod);
	}
	
	int t;
	cin >> t;
	while (t--)
		solve();
	
	return 0;
}
