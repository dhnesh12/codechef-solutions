#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MOD = 1e9 + 7;

LL ext_gcd(LL a, LL b, LL& x, LL& y) {
	LL g;
	if (b) {
		g = ext_gcd(b, a % b, y, x);
		y -= a / b * x;
	}
	else {
		g = a;
		x = 1, y = 0;
	}
	return g;
}

LL sum_of_floor(LL n, LL m, LL a, LL b) {
	LL ret = 0;
	if (a >= m || a < 0) {
		LL r = (a % m + m) % m;
		ret = ((ret + (n - 1) * n / 2 % MOD * ((a - r) / m) % MOD) % MOD + MOD) % MOD;
		a = r;
	}
	if (b >= m || b < 0) {
		LL r = (b % m + m) % m;
		ret = ((ret + n * ((b - r) / m) % MOD) % MOD + MOD) % MOD;
		b = r;
	}
	LL y = (a * n + b) / m;
	if (y == 0) return ret;
	LL x = y * m - b;
	ret = (ret + (n - (x + a - 1) / a) * y % MOD) % MOD;
	ret = (ret + sum_of_floor(y, a, m, (a - x % a) % a)) % MOD;
	return ret;
}

LL inv(LL a, LL m) {
	LL x, y;
	ext_gcd(a, m, x, y);
	return (x % m + m) % m;
}

LL calc(LL n, LL r, LL p, LL q) {
	p %= r; q %= r;
	if (q == 0) {
		if (p == 0) return n;
		else return 0;
	}
	LL g = abs(__gcd(__gcd(p, q), r));
	r /= g, p /= g, q /= g;
	g = abs(__gcd(p, q));
	p /= g, q /= g;
	if (abs(__gcd(q, r)) != 1) return 0;
	p = (r - p) % r;
	LL i = inv(((q % r) + r) % r, r) * p % r;
	if (i > n - 1) return 0;
	return (n - 1 - i) / r + 1;
}

LL solve() {
	LL x1, y1, x2, y2, a, b, c, d;
	cin >> x1 >> x2 >> y1 >> y2 >> a >> b >> c >> d;
	LL xg, zg, gac, fg, yg, gabc;
	gac = ext_gcd(a, c, xg, zg);
	gabc = ext_gcd(gac, b, fg, yg);
	if (d % gabc) return 0;
	LL f0 = fg * (d / gabc), y0 = yg * (d / gabc), ff = b / gabc, yy = gac / gabc;
	LL r1 = ((y0 - y2) % yy + yy) % yy, r2 = ((y0 - y1) % yy + yy) % yy;
	LL k1 = (y0 - y2 - r1) / yy + (r1 ? 1 : 0), k2 = (y0 - y1 - r2) / yy;
	LL f1 = f0 + k1 * ff, f2 = f0 + k2 * ff;
	LL u = f1, v = ff, n = k2 - k1 + 1;
	LL ret = 0;
	LL p = x2 - xg * u, q = -xg * v, r = c / gac;
	ret = (ret + sum_of_floor(n, r, q, p)) % MOD;
	p = x1 - xg * u;
	ret = (ret + MOD - sum_of_floor(n, r, q, p) % MOD) % MOD;
	ret = (ret + calc(n, r, p, q)) % MOD;
	return ret;
}

int main() {
	
	ios_base::sync_with_stdio(0);
	
	int Tc;
	for (cin >> Tc; Tc--; ) cout << solve() << endl;	
	
}

