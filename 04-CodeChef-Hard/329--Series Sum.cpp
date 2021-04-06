#include<bits/stdc++.h>
#define ll long long
#define vi vector< int >
#define pii pair< vi, vi >
#define fi first
#define se second
using namespace std;
int read() {
	char ch='!'; int res=0, f=0; while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=res*10+ch-'0', ch=getchar(); return res;
}

const int N=(1 << 18)+7, P=1e9+7;
const double pi=acos(-1.0);
int upd(int x) {return x+(x >> 31 & P);}
int qpow(int x, ll y) {int tms=1; while(y){if(y&1) tms=1ll*tms*x%P; x=1ll*x*x%P, y >>= 1;} return tms;}

namespace Poly {
int L, Lm, r[N]; struct comp { double x, y; } w[N];
inline comp operator + (const comp &a, const comp &b)
	{ return {a.x + b.x, a.y + b.y}; }
inline comp operator - (const comp &a, const comp &b)
	{ return {a.x - b.x, a.y - b.y}; }
inline comp operator * (const comp &a, const comp &b)
	{ return {a.x * b.x - a.y * b.y, a.y * b.x + a.x * b.y}; }
inline comp conj(const comp &a) { return {a.x, -a.y}; }
void Init(int n) {
	for (L = 1, Lm = -1; L < n; L <<= 1, ++Lm);
	for (int i = 0; i < L; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << Lm);
	for (int i = 1; i < L; i <<= 1) 
		for (int j = 0; j < i; j++) w[i + j] = (comp){cos(j * pi / i), sin(j * pi / i)};
}
void FFT(comp *p) {
	for (int i = 0; i < L; i++) if (i < r[i]) swap(p[i], p[r[i]]);
	for (int i = 1, s = 2; i < L; i <<= 1, s <<= 1)
		for (int j = 0; j < L; j += s) for (int k = 0, o = i; k < i; ++k, ++o) {
			auto x = p[j + k], y = w[o] * p[i + j + k];
			p[j + k] = x + y, p[i + j + k] = x - y;
		}
}
void Mul(int *f, int *g, int *h, int n, int m) {
	static comp a[N], b[N], A[N], B[N], C[N], D[N]; Init(n + m + 1);
	for (int i = 0; i < L; i++) a[i] = b[i] = (comp){0, 0};
	for (int i = 0; i < n; i++) a[i] = (comp){(double)(f[i] & 0x7fff), (double)(f[i] >> 15)};
	for (int i = 0; i < m; i++) b[i] = (comp){(double)(g[i] & 0x7fff), (double)(g[i] >> 15)};
	FFT(a), FFT(b);
	for (int i = 0, j; i < L; i++) {
		j = (L - i) & (L - 1);
		auto da = (a[i] + conj(a[j])) * (comp) {0.5, 0}, db = (a[i] - conj(a[j])) * (comp) {0, -0.5};
		auto dc = (b[i] + conj(b[j])) * (comp) {0.5, 0}, dd = (b[i] - conj(b[j])) * (comp) {0, -0.5};
		A[j] = da * dc, B[j] = da * dd, C[j] = db * dc, D[j] = db * dd;
	}
	for (int i = 0; i < L; i++) a[i] = A[i] + B[i] * (comp) {0, 1};
	for (int i = 0; i < L; i++) b[i] = C[i] + D[i] * (comp) {0, 1};
	FFT(a), FFT(b);
	for (int i = 0; i < n+m-1; i++)	{
		ll da = (ll) (a[i].x / L + 0.5) % P, db = (ll) (a[i].y / L + 0.5) % P;
		ll dc = (ll) (b[i].x / L + 0.5) % P, dd = (ll) (b[i].y / L + 0.5) % P;
		h[i] = (da + (db + dc << 15) + (dd << 30)) % P;
	}
}
void Inv(int *a, int *b, int n) {
	if(n == 1) return (void)(b[0]=qpow(a[0], P-2));
	static int f[N], g[N]; 
	Inv(a, b, (n+1) >> 1);
	memcpy(f, b, n << 2), memcpy(g, a, n << 2);
	Mul(f, f, f, (n+1)/2, (n+1)/2), Mul(f, g, f, n+1, n);
	for(int i=(n+1) >> 1;i<n;++i) b[i]=upd(-f[i]);
}
void Mul(vi &f, vi &g, vi &h) {Poly::Mul(&f[0], &g[0], &h[0], f.size(), g.size());}
}

int n, K, A[N], fac[N], ifac[N], F[N], G[N], ans[N], S[N], spw[N]; ll T;
pii Prod(int l, int r) {
	if(l == r) return pii({1, 0}, {1, upd(-A[l])});
	int mid=(l+r) >> 1; pii L=Prod(l, mid), R=Prod(mid+1, r);
	vi now(r-l+2), now1(r-l+2), now2(r-l+2);
	Poly::Mul(L.se, R.se, now);
	Poly::Mul(L.se, R.fi, now1);
	Poly::Mul(L.fi, R.se, now2);
	for(int i=0;i<now1.size();++i) now1[i]=upd(now1[i]+now2[i]-P);
	return pii(now1, now);
}

int main() {
	n=read(), K=read(); cin >> T;
	fac[0]=1; for(int i=1;i<=1e5;++i) fac[i]=1ll*fac[i-1]*i%P;
	ifac[100000]=qpow(fac[100000], P-2); for(int i=100000-1;~i;--i) ifac[i]=1ll*ifac[i+1]*(i+1)%P;
	for(int i=1;i<=n;++i) A[i]=read();
	pii tmp=Prod(1, n); tmp.se.resize(K+1), tmp.fi.resize(K+1);
	Poly::Inv(&tmp.se[0], spw, K+1);
	Poly::Mul(&tmp.fi[0], spw, spw, K+1, K+1); for(int i=K+1;i<Poly::L;++i) spw[i]=0;
	for(int i=1;i<=K+1;++i) F[i-1]=upd(-ifac[i]);
	Poly::Inv(F, G, K+1); 
	for(int i=1, tms=upd(-1);i<=K+1;++i, tms=1ll*tms*(T+1)%P) F[i-1]=1ll*ifac[i]*upd(-qpow((T+1)%P, i))%P;
	Poly::Mul(F, G, S, K+1, K+1); for(int i=K+1;i<Poly::L;++i) S[i]=0;
	for(int i=0;i<=K;++i) spw[i]=1ll*spw[i]*ifac[i]%P;
	Poly::Mul(spw, S, ans, K+1, K+1);
	for(int i=0;i<=K;++i) printf("%lld ", 1ll*ans[i]*fac[i]%P); puts(""); return 0;
}