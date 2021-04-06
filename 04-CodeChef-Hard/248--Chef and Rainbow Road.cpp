#include<bits/stdc++.h>
#define ll long long
#define vi vector< int >
using namespace std;
int read() {
	char ch='!'; int res=0, f=0; while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=res*10+ch-'0', ch=getchar(); return res;
}
const int N=(1 << 18)+7, P=998244353; int upd(int x){return x+(x >> 31 & P);}
int qpow(int x, ll y){int tms=1; while(y){if(y&1) tms=1ll*tms*x%P; x=1ll*x*x%P, y >>= 1;} return tms;}
namespace Poly {
	int L, invL, w[N];
	void Init(int len) {
		for(L=1;L<len;L <<= 1); invL=qpow(L, P-2);
		w[0]=1, w[1]=qpow(3, (P-1)/L);
		for(int i=2;i<L;++i) w[i]=1ll*w[i-1]*w[1]%P;
	}
	void DFT(int *p) {
		for(int i=L/2,t=1;i;i >>= 1, t <<= 1)
			for(int j=0;j<L;j+=(i << 1)) for(int k=0,o=0;k<i;++k,o+=t) {
				int x=p[j+k], y=p[i+j+k];
				p[j+k]=upd(x+y-P), p[i+j+k]=1ll*w[o]*upd(x-y)%P;
			}
	}
	void IDFT(int *p) {
		for(int i=1,t=L/2;i<L;i <<= 1, t >>= 1)
			for(int j=0;j<L;j+=(i << 1)) for(int k=0,o=0;k<i;++k,o+=t) {
				int x=p[j+k], y=1ll*w[o]*p[i+j+k]%P;
				p[j+k]=upd(x+y-P), p[i+j+k]=upd(x-y);
			}
		reverse(p+1, p+L); for(int i=0;i<L;++i) p[i]=1ll*p[i]*invL%P;
	}
	void Inv(int *a, int *b, int n) {
		if(n == 1) return (void)(b[0]=qpow(a[0], P-2));
		static int f[N], g[N]; 
		Inv(a, b, (n+1) >> 1); Init(n+n);
		for(int i=0;i<L;++i) f[i]=g[i]=0;
		for(int i=0;i<n;++i) f[i]=a[i];
		for(int i=0;i<(n+1)/2;++i) g[i]=b[i];
		DFT(f), DFT(g);	for(int i=0;i<L;++i) f[i]=1ll*g[i]*(2+P-1ll*f[i]*g[i]%P)%P;
		IDFT(f); for(int i=0;i<L;++i) b[i]=0; for(int i=0;i<n;++i) b[i]=f[i];
	}
	void Mul(int *a, int *b, int *c, int n, int m) {
		static int f[N], g[N]; Init(n+m-1);
		for(int i=0;i<L;++i) f[i]=g[i]=0;
		for(int i=0;i<n;++i) f[i]=a[i]; 
		for(int i=0;i<m;++i) g[i]=b[i]; 
		DFT(f), DFT(g); for(int i=0;i<L;++i) f[i]=1ll*f[i]*g[i]%P; IDFT(f);
		for(int i=0;i<n+m-1;++i) c[i]=f[i];
	}
	void MulT(int *a, int *b, int *c, int n, int m, int k) {
		static int f[N], g[N], h[N]; 
		for(int i=0;i<n;++i) f[i]=a[i]; for(int i=0;i<m;++i) g[i]=b[m-1-i];
		Mul(f, g, h, n, m);
		for(int i=0;i<k;++i) c[i]=h[i+m-1];
	}
}
void Mul(vi &f, vi &g, vi &h) {Poly::Mul(&f[0], &g[0], &h[0], f.size(), g.size());}
void MulT(vi &f, vi &g, vi &h) {Poly::MulT(&f[0], &g[0], &h[0], f.size(), g.size(), h.size());}
namespace Evaluate {
	#define lch (k << 1)
	#define rch (k << 1 | 1)
	vi w[N << 2], v[N << 2]; 
	void getPoly(int *a, int k, int l,int r) {
		if(l == r) {w[k]={0}, v[k]={1, upd(-a[l])}; return ;}
		int mid=(l+r) >> 1;
		getPoly(a, lch, l, mid), getPoly(a, rch, mid+1, r);
		v[k].resize(r-l+2), w[k].resize(r-l+1), Mul(v[lch], v[rch], v[k]);
	}
	void divide(int *ans, int k, int l, int r) {
		if(l == r) return (void)(ans[l]=w[k][0]);
		int mid=(l+r) >> 1;
		MulT(w[k], v[rch], w[lch]), MulT(w[k], v[lch], w[rch]);
		divide(ans, lch, l, mid), divide(ans, rch, mid+1, r);
	}
	void solve(int *f, int *a, int *ans, int n) {
		static int g[N];
		getPoly(a, 1, 1, n-1);Poly::Inv(&v[1][0], g, n);
		Poly::MulT(f, g, &w[1][0], n, n, w[1].size());
		divide(ans, 1, 1, n-1);
	}
}

ll M, K; int n, Q, A[N], val[N << 1], F[N << 1], B[N << 1], coef=1;
vi Prod(int l, int r) {
	if(l == r) return {1, upd(-A[l])};
	int mid=(l+r) >> 1;
	vi L=Prod(l, mid), R=Prod(mid+1, r), now(r-l+2);
	Mul(L, R, now); return now;
}
namespace Subtask1 {
	void main() {
		vi tmp=Prod(1, n); tmp.resize(max(n, (int)M)+1); Poly::Inv(&tmp[0], F, M+1);
		while(Q--) printf("%lld\n",1ll*coef*F[read()-1]%P);
	}
}
namespace Subtask2 {
	void main() {
		vi tmp=Prod(1, n); 
		for(int i=0;i+1<tmp.size();++i) F[i]=1ll*tmp[i+1]*(i+1)%P;
		for(int i=1;i<=n;++i) B[i]=qpow(A[i], P-2);
		Evaluate::solve(F, B, val, n+2);
		for(int i=1;i<=n;++i) val[i]=1ll*upd(-A[i])*qpow(val[i], P-2)%P;
		while(Q--) {
			cin >> K; --K; int ans=0;
			for(int i=1;i<=n;++i) ans=(ans+1ll*val[i]*qpow(A[i], K)%P)%P;
			cout << 1ll * ans * coef%P << endl;
		}
	}
}

int main() {
	cin >> M >> n >> Q; for(int i=1;i<=n;++i) A[i]=read(), coef=1ll*coef*A[i]%P;
	if(M <= 1e5) Subtask1::main(); else Subtask2::main(); return 0;	
}