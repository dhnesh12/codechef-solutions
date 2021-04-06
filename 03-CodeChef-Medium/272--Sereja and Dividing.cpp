#include "bits/stdc++.h"
using namespace std;
#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define rer(i,l,u) for(int (i)=(int)(l);(i)<=(int)(u);++(i))
#define reu(i,l,u) for(int (i)=(int)(l);(i)<(int)(u);++(i))
static const int INF = 0x3f3f3f3f; static const long long INFL = 0x3f3f3f3f3f3f3f3fLL;
typedef vector<int> vi; typedef pair<int, int> pii; typedef vector<pair<int, int> > vpii; typedef long long ll;
template<typename T, typename U> static void amin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> static void amax(T &x, U y) { if(x < y) x = y; }

typedef uint32_t Num;
const Num Digit = 16807;
const int DigitWidth = 5;

Num add(Num *res, const Num *p, const Num *q, int n) {
	Num carry = 0;
	rep(i, n) {
		Num x = p[i] + q[i] + carry;
		carry = 0;
		if(x >= Digit) {
			carry = 1;
			x -= Digit;
		}
		res[i] = x;
	}
	return carry;
}

Num subtract(Num *p, const Num *q, int n) {
	Num borrow = 0;
	rep(i, n) {
		Num x = p[i] - q[i] - borrow;
		borrow = 0;
		if(x >= Digit) {
			borrow = 1;
			x += Digit;
		}
		p[i] = x;
	}
	return borrow;
}

Num add(Num *res, const Num *p, int pn, const Num *q, int qn) {
	assert(pn >= qn);
	Num carry = add(res, p, q, qn);
	if(res != p) {
		for(int i = qn; i < pn; ++ i)
			res[i] = p[i];
	}
	if(carry == 0) return 0;
	for(int i = qn; i < pn; ++ i) {
		if(res[i] ++ != Digit - 1)
			return 0;
		res[i] = 0;
	}
	return 1;
}

Num subtract(Num *p, int pn, const Num *q, int qn) {
	assert(pn >= qn);
	Num borrow = subtract(p, q, qn);
	if(borrow == 0) return 0;
	for(int i = qn; i < pn; ++ i) {
		if(p[i] -- != 0)
			return 0;
		p[i] = Digit - 1;
	}
	return 1;
}

Num muladd_1(Num *p, const Num *q, int n, Num c) {
	Num carry = 0;
	rep(i, n) {
		Num x = p[i] + q[i] * c + carry;
		p[i] = x % Digit;
		carry = x / Digit;
	}
	return carry;
}

Num normalize_carry(Num *p, int n) {
	Num carry = 0;
	rep(i, n) {
		Num x = p[i] + carry;
		p[i] = x % Digit;
		carry = x / Digit;
	}
	return carry;
}

void multipy_basecase(Num *res, const Num *p, int n, const Num *q, int m) {
	/*
	rep(i, n + m)res[i] = 0;
	rep(j, m)
	res[j + n] = muladd_1(res + j, p, n, q[j]);
	return;
	*/
	if(m == 0) {
		rep(i, n)res[i] = 0;
		return;
	}
	{
		Num c0 = q[0];
		rep(i, n) res[i] = p[i] * c0;
		res[n] = 0;
	}
	if(m == 1) {
		res[n] = normalize_carry(res, n);
		return;
	}
	int num = 1;
	reu(j, 1, m) {
		assert(j+n<n+m);
		Num c = q[j];
		rep(i, n)
			res[j + i] += p[i] * c;
		res[j + n] = 0;
		if(++ num == 6 || j == m - 1) {
			res[j + n] = normalize_carry(res + j + 1 - num, n - 1 + num);
			num = 1;
		}
	}
}

void multiply_karatsuba(Num *res, const Num *p, const Num *q, int n, Num *tmpbuf) {
	if(n <= 20) {
		multipy_basecase(res, p, n, q, n);
		return;
	}
	int lo = (n + 1) / 2, hi = n - lo;
	Num *r0 = res, *r1 = tmpbuf, *rinf = res + lo * 2;
	Num *t0 = r1 + (n * 2 - lo), *t1 = t0 + lo + 1;
	Num *nextbuf = tmpbuf + n * 2 + lo + 2;
	assert((lo+1)*2<=n*2-lo);
	t0[lo] = add(t0, p, lo, p + lo, hi);
	t1[lo] = add(t1, q, lo, q + lo, hi);
	multiply_karatsuba(r1, t0, t1, lo + 1, nextbuf);
	reu(i, (lo + 1) * 2, n * 2 - lo) r1[i] = 0;
	multiply_karatsuba(r0, p, q, lo, nextbuf);
	multiply_karatsuba(rinf, p + lo, q + lo, hi, nextbuf);
	subtract(r1, n * 2 - lo, r0, lo * 2);
	subtract(r1, n * 2 - lo, rinf, hi * 2);
	add(res + lo, res + lo, r1, n * 2 - lo);
}

void multipy(Num *res, const Num *p, int pn, const Num *q, int qn) {
	if(pn < qn) swap(p, q), swap(pn, qn);
	if(qn <= 10)
		return multipy_basecase(res, p, pn, q, qn);
	vector<Num> tmpbuf(pn * 10 + 10);
	Num *tmpq = tmpbuf.data(), *tmpres = tmpq + pn;
	rep(i, qn) tmpq[i] = q[i];
	multiply_karatsuba(tmpres, p, tmpq, pn, tmpres + pn * 2);
	rep(i, pn + qn)
		res[i] = tmpres[i];
}

Num multiply_1(Num *p, int n, Num q) {
	Num carry = 0;
	rep(i, n) {
		Num x = p[i] * q + carry;
		p[i] = x % Digit;
		carry = x / Digit;
	}
	return carry;
}

int inverse(signed a, const int MOD) {
	a %= MOD;
	if(a < 0) a += MOD;
	signed b = MOD, u = 1, v = 0;
	while(b) {
		signed t = a / b;
		a -= t * b; swap(a, b);
		u -= t * v; swap(u, v);
	}
	if(u < 0) u += MOD;
	return u;
}

vector<Num> invert(const vector<Num> &p, int resn) {
	int pn = (int)p.size();
	vector<Num> res(resn * 2), sq(resn * 2), prod(resn * 4);
	assert(p[0] != 0);
	res[0] = inverse(p[0], Digit);
	int curn = 1;
	//2x-ax^2
	while(curn < resn) {
		int nextn = min(resn, curn * 2);
		multipy(sq.data(), res.data(), curn, res.data(), curn);
		multipy(prod.data(), sq.data(), nextn, p.data(), min(nextn, pn));
		res[curn] = multiply_1(res.data(), curn, 2);
		subtract(res.data(), prod.data(), nextn);
		curn = nextn;
	}
	res.resize(resn);
	return res;
}

int main() {
	int T;
	scanf("%d", &T);
	char *A = new char[1000001], *B = new char[10001];
	for(int ii = 0; ii < T; ++ ii) {
		//rep(i, 1000000+1)A[i] = i== 1000000?0:rand() % 7 + '0';
		scanf("%s", A);
		//rep(i, 10000+1)B[i] = i == 10000 ? 0 :i==9999?rand()%6+'1' :rand() % 7 + '0';
		scanf("%s", B);
		int L;
		//L = 10000;
		scanf("%d", &L);
		//C = A / B
		int n = (int)strlen(A), m = (int)strlen(B);
		while(B[m - 1] == '0') {
			assert(A[n - 1] == '0');
			A[-- n] = '\0';
			B[-- m] = '\0';
		}
		const Num pow7s[DigitWidth] = {1,7,49,343,2401};
		vector<Num> b((m - 1) / DigitWidth + 1);
		rep(i, m)
			b[i / DigitWidth] += (B[m - 1 - i] - '0') * pow7s[i % DigitWidth];
		vector<Num> invb = invert(b, (L - 1) / DigitWidth + 1);
		vector<Num> a((min(L, n) - 1) / DigitWidth + 1);
		rep(i, min(L, n))
			a[i / DigitWidth] += (A[n - 1 - i] - '0') * pow7s[i % DigitWidth];
		vector<Num> prod(a.size() + invb.size());
		multipy(prod.data(), a.data(), a.size(), invb.data(), invb.size());
		vector<uint8_t> prod2(prod.size() * DigitWidth);
		rep(i, prod2.size())
			prod2[i] = prod[i / DigitWidth] / pow7s[i % DigitWidth] % 7;
		int anslen = L;
		while(anslen > 1 && prod2[anslen - 1] == 0) -- anslen;
		string ans(anslen, '?');
		rep(i, anslen) ans[anslen - 1 - i] = '0' + prod2[i];
		puts(ans.c_str());
	}
	return 0;
}
