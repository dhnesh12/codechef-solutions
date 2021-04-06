#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const int mod = 10007;
 
int fac[mod], inv[mod];
int t;
ll r, c, n;
 
int Inv(int x)
{
	int p = mod - 2;
	int res = 1;
	while (p) {
		if (p & 1) res = res * x % mod;
		p >>= 1; x = x * x % mod;
	}
	return res;
}
 
int simpleC(int n, int k)
{
	if (n < 0 || k < 0 || k > n) return 0;
	return fac[n] * inv[k] % mod * inv[n - k] % mod;
}
 
int C(ll n, ll k)
{
	if (n < 0 || k < 0 || k > n) return 0;
	if (n < mod && k < mod) return simpleC(n, k);
	return C(n / mod, k / mod) * simpleC(n % mod, k % mod) % mod;
}
 
int main()
{
	fac[0] = inv[0] = 1;
	for (int i = 1; i < mod; i++) {
		fac[i] = i * fac[i - 1] % mod;
		inv[i] = Inv(fac[i]);
	}
	scanf("%d", &t);
	while (t--) {
		scanf("%lld %lld %lld", &r, &c, &n);
		int tot = C(n + r - 1, r - 1) * C(n + c - 1, c - 1) % mod;
		if (r >= n && c >= n) {
			int byr = (C(n + r, n) - C(n + r, n - 1) + mod) % mod;
			int byc = (C(n + c, n) - C(n + c, n - 1) + mod) % mod;
			tot = (tot - byr * byc % mod + mod) % mod;
		}
		printf("%d\n", tot);
	}
	return 0;
}