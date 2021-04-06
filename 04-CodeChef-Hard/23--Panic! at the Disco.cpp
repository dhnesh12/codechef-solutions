#include <algorithm>  
#include <iostream>  
#include <sstream>  
#include <string>  
#include <vector>  
#include <queue>  
#include <set>  
#include <map>  
#include <cstdio>  
#include <cstdlib>  
#include <cctype>  
#include <cmath>  
#include <cstring>
#include <list>  
#include <cassert>
#include <climits>
#include <bitset>
#include <chrono>
#include <random>
#include <array>
using namespace std;

#define PB push_back  
#define MP make_pair  
#define SZ(v) ((int)(v).size())  
#define FOR(i,a,b) for(int i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)  
#define REPE(i,n) FORE(i,0,n)  
#define FORSZ(i,a,v) FOR(i,a,SZ(v))  
#define REPSZ(i,v) REP(i,SZ(v))  
std::mt19937 rnd((int)std::chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }

template<const int MOD> struct modint {
	int val;
	int norm(ll x) { int ret = -MOD <= x && x < MOD ? x : x % MOD; if (ret < 0) ret += MOD; return ret; }
	modint() :val(0) {}
	modint(ll val) :val(norm(val)) { }
	modint pow(unsigned long long n) const { modint x = *this, ret = 1; while (true) { if (n & 1) ret *= x; if ((n >>= 1) == 0) return ret; x *= x; } }
	modint inv() const { return pow(MOD - 2); } // MOD must be prime
	modint& operator+=(const modint& other) { val += other.val; if (val >= MOD) val -= MOD; return *this; }
	modint& operator-=(const modint& other) { val -= other.val; if (val < 0) val += MOD; return *this; }
	modint& operator*=(const modint& other) { val = norm((ll)val * other.val); return *this; }
	modint& operator/=(const modint& other) { return *this *= other.inv(); }
	modint operator-() const { return modint(-val); }
	bool operator==(const modint& other) const { return val == other.val; }
	bool operator!=(const modint& other) const { return val != other.val; }
};
template<const int MOD> modint<MOD> operator+(const modint<MOD>& a, const modint<MOD>& b) { return modint<MOD>(a) += b; }
template<const int MOD> modint<MOD> operator-(const modint<MOD>& a, const modint<MOD>& b) { return modint<MOD>(a) -= b; }
template<const int MOD> modint<MOD> operator*(const modint<MOD>& a, const modint<MOD>& b) { return modint<MOD>(a) *= b; }
template<const int MOD> modint<MOD> operator/(const modint<MOD>& a, const modint<MOD>& b) { return modint<MOD>(a) /= b; }


template <class T> struct Mat : vector<vector<T>> {
	int rows, cols;
	Mat() : Mat(0, 0) {}
	Mat(int rows, int cols) : rows(rows), cols(cols), vector<vector<T>>(vector<vector<T>>(rows, vector<T>(cols, 0))) {}
	Mat& operator+=(const Mat& other) { assert(rows == other.rows && cols == other.cols); REP(r, rows) REP(c, cols) (*this)[r][c] += other[r][c]; return *this; }
	Mat& operator*=(const T& other) { REP(r, rows) REP(c, cols) (*this)[r][c] *= other; return *this; }
};
template<class T> Mat<T> operator*(const Mat<T>& A, const T& b) { return Mat<T>(A) *= b; }

template <class T> Mat<T> ident(int n) { Mat<T> ret(n, n); REP(i, n) ret[i][i] = 1; return ret; }
template <class T> Mat<T> operator*(const Mat<T>& A, const Mat<T>& B) {
	assert(A.cols == B.rows);
	Mat<T> C(A.rows, B.cols);
	REP(i, A.rows) REP(j, B.cols) REP(k, A.cols) C[i][j] += A[i][k] * B[k][j];
	return C;
}


template <class T> using Poly = vector<T>;

template<class T> Poly<T> operator*(const Poly<T>& p, const Poly<T>& q) {
	if (SZ(p) == 0 || SZ(q) == 0) return Poly<T>();
	Poly<T> ret(SZ(p) + SZ(q) - 1, 0); REPSZ(i, p) REPSZ(j, q) ret[i + j] += p[i] * q[j]; return ret; // Can be done with FFT
}

// Reduce p modulo q, with q.back()==1
template<class T> void reduce(Poly<T>& p, const Poly<T>& q) {
	assert(SZ(q) >= 1 && q.back() == 1);
	while (SZ(p) >= SZ(q)) {
		T times = p.back();
		int offset = SZ(p) - SZ(q);
		REPSZ(i, q) p[offset + i] -= times * q[i];
		assert(p.back() == 0);
		while (SZ(p) >= 1 && p.back() == 0) p.pop_back();
	}
}

// Calculate x^n mod p, with p.back()=1
template<class T> Poly<T> powerremainder(const vector<int>& bits, Poly<T> p) {
	assert(SZ(p) >= 1 && p.back() == 1);
	Poly<T> ret(1, 1);
	for (int bit = SZ(bits) - 1; bit >= 0; --bit) {
		if (bits[bit]) { ret.insert(ret.begin(), 0); reduce(ret, p); }
		if (bit != 0) ret = ret * ret, reduce(ret, p);
	}
	reduce(ret, p);
	return ret;
}
// Calculate x^n mod p, with p.back()=1
template<class T> Poly<T> powerremainder(ll n, Poly<T> p) {
	assert(SZ(p) >= 1 && p.back() == 1);
	Poly<T> ret(1, 1);
	int bit = 0; while (n >> bit) ++bit;
	for (--bit; bit >= 0; --bit) {
		if ((n >> bit) & 1) { ret.insert(ret.begin(), 0); reduce(ret, p); }
		if (bit != 0) ret = ret * ret, reduce(ret, p);
	}
	reduce(ret, p);
	return ret;
}

template<class T,class U> struct LinRec {
	vector<U> a;
	vector<T> c; // a[i]=sum(j=0..m,a[i-j-1]*c[j]) 

	U eval(ll n, const U &zero) {
		assert(SZ(c) == SZ(a));
		Poly<T> f(c.begin(), c.end());
		reverse(f.begin(), f.end());
		REPSZ(i, f) f[i] = -f[i];
		f.push_back(1);
		Poly<T> h = powerremainder(n, f);
		U ret = zero; REPSZ(i, h) ret += a[i] * h[i]; return ret;
	}
	U eval(const vector<int> &bits, const U& zero) {
		assert(SZ(c) == SZ(a));
		Poly<T> f(c.begin(), c.end());
		reverse(f.begin(), f.end());
		REPSZ(i, f) f[i] = -f[i];
		f.push_back(1);
		Poly<T> h = powerremainder(bits, f);
		U ret = zero; REPSZ(i, h) ret += a[i] * h[i]; return ret;
	}
};

template<class T> LinRec<T,T> berlekampmassey(vector<T> a) {
	vector<T> c;
	int lasti = -1; T lastdiff; vector<T> lastc;
	REPSZ(i, a) {
		T diff = a[i];
		REPSZ(j, c) diff -= c[j] * a[i - j - 1];
		if (diff == 0) continue;
		if (lasti == -1) { lasti = i, lastdiff = diff, lastc = c; c = vector<T>(i + 1, 0); continue; }
		T mlt = diff / lastdiff;
		vector<T> nc(max(SZ(c), i - lasti + SZ(lastc)), 0);
		REPSZ(j, c) nc[j] = c[j];
		nc[i - lasti - 1] += mlt;
		REPSZ(j, lastc) nc[i - lasti + j] -= mlt * lastc[j];
		if (SZ(c) <= i - lasti + SZ(lastc)) lasti = i, lastdiff = diff, lastc = c;
		c = nc;
	}
	LinRec<T, T> ret; ret.a = vector<T>(a.begin(), a.begin() + SZ(c)); ret.c = c; return ret;
}

template<class T> LinRec<T,Mat<T>> berlekampmassey(vector<Mat<T>> A) {
	assert(SZ(A) >= 1); FORSZ(i, 1, A) assert(A[i].rows == A[0].rows && A[i].cols == A[0].cols);
	while (true) {
		vector<T> l(A[0].rows); REPSZ(i, l) l[i] = T(rnd());
		vector<T> r(A[0].cols); REPSZ(i, r) r[i] = T(rnd());
		vector<T> a(SZ(A), 0); REPSZ(i, A) REPSZ(j, l) REPSZ(k, r) a[i] += l[j] * A[i][j][k] * r[k];
		LinRec<T,T> rec = berlekampmassey(a);
		LinRec<T, Mat<T>> ret; ret.a = vector<Mat<T>>(A.begin(), A.begin() + SZ(rec.c)); ret.c = rec.c; return ret;
	}
}

vector<int> getbits(string s) {
	vector<int> ret;
	reverse(s.begin(), s.end());
	while (true) {
		while (SZ(s) >= 1 && s.back() == '0') s.pop_back();
		if (SZ(s) == 0) return ret;
		int carry = 0; for (int i = SZ(s) - 1; i >= 0; --i) { carry = 10 * carry + s[i] - '0'; s[i] = '0' + carry / 2; carry %= 2; }
		ret.PB(carry);
	}
}

const int MOD = 998244353;
using mint = modint<MOD>;

int dim, fiboffset, fibstep;
string pmx;
Mat<mint> A;
Mat<mint> ans;


void solve() {
	LinRec<mint, mint> fib;
	fib.a = { 0,1 };
	fib.c = { 1,1 };

	int need = 4 * dim + 2;
	vector<Mat<mint>> Apw(need); Apw[0] = ident<mint>(dim); Apw[1] = A; FORSZ(i, 2, Apw) Apw[i] = Apw[i - 1] * A;
	vector<Mat<mint>> S(need); REPSZ(i, S) S[i] = Apw[i] * fib.eval(fiboffset + (ll)i * fibstep, 0); FORSZ(i, 1, S) S[i] += S[i - 1];

	LinRec<mint, Mat<mint>> rec = berlekampmassey(S);
	vector<int> pmxbits = getbits(pmx);
	ans = rec.eval(pmxbits, Mat<mint>(dim, dim));
}

void run() {
	scanf("%d%d%d", &dim, &fiboffset, &fibstep); cin >> pmx;
	A = Mat<mint>(dim, dim); REP(i, dim) REP(j, dim) scanf("%d", &A[i][j].val);
	solve();
	REP(r, ans.rows) { REP(c, ans.cols) { if (c != 0) printf(" "); printf("%d", ans[r][c].val); } puts(""); }
}

int main() {
	int ncase; scanf("%d", &ncase); FORE(i, 1, ncase) run();
	return 0;
}
