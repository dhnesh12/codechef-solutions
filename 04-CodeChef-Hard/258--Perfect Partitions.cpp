#include<bits/stdc++.h>
using namespace std;
int read() {
	char ch='!'; int res=0, f=0; while(!isdigit(ch)) {ch=getchar(); if(ch == '-') f=1;}
	while(isdigit(ch)) res=res*10+ch-'0', ch=getchar(); return f?-res:res;
}

const int N=(1 << 19)+7;
const int P=998244353; int upd(int x) {return x+(x >> 31 & P);} 
int qpow(int x, int y) {int tms=1; while(y){if(y&1) tms=1ll*tms*x%P; x=1ll*x*x%P, y >>= 1;} return tms;}
int n, m, cnt[N], A[N], B[N], F[N], G[N], inv[N], w[N], L, invL;

void Init(int len) {
	for(L=1;L<len;L <<= 1); invL=qpow(L, P-2);
	w[0]=1, w[1]=qpow(3, (P-1)/L);
	for(int i=2;i<L;++i) w[i]=1ll*w[i-1]*w[1]%P;
}
void DFT(int *p) {
	for(int i=L/2, t=1;i;i >>= 1, t <<= 1)
		for(int j=0;j<L;j += (i << 1)) for(int k=0, o=0;k<i;++k, o += t) {
			int x=p[j+k], y=p[i+j+k];
			p[j+k]=upd(x+y-P), p[i+j+k]=1ll*w[o]*upd(x-y)%P;
		}
}
void IDFT(int *p) {
	for(int i=1, t=L/2;i<L;i <<= 1, t >>= 1)
		for(int j=0;j<L;j += (i << 1)) for(int k=0, o=0;k<i;++k, o += t) {
			int x=p[j+k], y=1ll*w[o]*p[i+j+k]%P;
			p[j+k]=upd(x+y-P), p[i+j+k]=upd(x-y);
		}
	reverse(p+1, p+L); for(int i=0;i<L;++i) p[i]=1ll*p[i]*invL%P;
}

void Exp(int l, int r) {
	if(l == r) {if(l) G[l]=1ll*G[l]*inv[l]%P; return ;}
	int mid=(l+r) >> 1; Exp(l, mid); Init(r-l+3);
	memset(A, 0, (L+1) << 2);
	memset(B, 0, (L+1) << 2);
	for(int i=l;i<=mid;++i) A[i-l]=G[i];
	for(int i=0;i<=r-l;++i) B[i]=F[i]; DFT(A), DFT(B);
	for(int i=0;i<L;++i) A[i]=1ll*A[i]*B[i]%P; IDFT(A);
	for(int i=mid+1;i<=r;++i) G[i]=upd(G[i]+A[i-l-1]-P);
	Exp(mid+1, r);
}

int main() {
	m=read(), n=read();
	for(int i=1;i<=n;++i) {
		int a=read(), b=read();
		++cnt[a]; if(1ll*(b+1)*a <= m) --cnt[(b+1)*a];
	}
	inv[1]=1; for(int i=2;i<=m;++i) inv[i]=P-1ll*P/i*inv[P%i]%P;
	for(int i=1;i<=m;++i) if(cnt[i]=upd(cnt[i]))
		for(int j=i;j<=m;j += i) F[j]=upd(F[j]+1ll*cnt[i]*inv[j/i]%P-P);
	for(int j=0;j<=m;++j) F[j]=1ll*F[j+1]*(j+1)%P;
	G[0]=1; Exp(0, m);
	for(int i=1;i<=m;++i) printf("%d ",G[i]);
	return 0;
}