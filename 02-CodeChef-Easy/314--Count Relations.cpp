#include<iostream>
#define ll long long 
#define LL int
const int MAXN = 1001, mod = 100000007, inv = 50000004;
using namespace std;
ll f(ll a, ll p) {
	ll base = 1;
	while(p) {
		if(p & 1) base = (base * a) % mod;
		a = (a * a) % mod; p >>= 1;
	}
	return base % mod;
}
int main() {
	int T;
	cin >> T;
	while(T--) {
	    ll N;
		cin >> N;
		ll ans = ((f(3, N) + 1) * inv - f(2, N) + mod) % mod;
		cout << ans << " ";
		ans = ((-3 * f(3, N) + mod) % mod + f(4, N) - 1 + mod) * inv + f(2, N - 1) * 3 % mod;
		ans %= mod;
		cout << ans << endl;
	}

    return 0;
}
/*
*/