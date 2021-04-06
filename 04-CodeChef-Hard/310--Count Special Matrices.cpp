// n!*(n-1)!/(2^{n-1}) * ( n/2 + 2/3 +h[n-1]/3)
#include<bits/stdc++.h>
using namespace std;
#define REP(i,st,ed) for(register int i=st,i##end=ed;i<=i##end;++i)
#define DREP(i,st,ed) for(register int i=st,i##end=ed;i>=i##end;--i)
typedef long long ll;
template<typename T>inline bool chkmin(T &x,T y){return (y<x)?(x=y,1):0;}
template<typename T>inline bool chkmax(T &x,T y){return (y>x)?(x=y,1):0;}
inline int read(){
	int x;
	char c;
	int f=1;
	while((c=getchar())!='-' && (c>'9' || c<'0'));
	if(c=='-') f=-1,c=getchar();
	x=c^'0';
	while((c=getchar())>='0' && c<='9') x=(x<<1)+(x<<3)+(c^'0');
	return x*f;
}
inline ll readll(){
	ll x;
	char c;
	int f=1;
	while((c=getchar())!='-' && (c>'9' || c<'0'));
	if(c=='-') f=-1,c=getchar();
	x=c^'0';
	while((c=getchar())>='0' && c<='9') x=(x<<1ll)+(x<<3ll)+(c^'0');
	return x*f;
}
const int maxn=1e7+10,mod=1e9+7;
inline int ksm(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=(ll)res*x%mod;
		x=(ll)x*x%mod;
		y>>=1;
	}
	return res;
}
int inv[maxn],fac[maxn],ifac[maxn];
inline void init(int n=maxn-10){
	fac[0]=1;
	REP(i,1,n) fac[i]=(ll)i*fac[i-1]%mod;
	ifac[n]=ksm(fac[n],mod-2);
	DREP(i,n,1) ifac[i-1]=(ll)i*ifac[i]%mod;
	REP(i,1,n) inv[i]=(inv[i-1]+(ll)ifac[i]*fac[i-1])%mod;
}
int main(){
	init(maxn-10);
	int T=read();
	int inv_3=ksm(3,mod-2);
	while(T--){
		int n=read();
		int ans=((ll)n*(mod+1)/2-(ll)(2+inv[n-1])*inv_3)%mod;
		ans=(ans+mod)%mod;
		ans=(ll)ans*fac[n]%mod*fac[n-1]%mod*ksm((mod+1)/2,n-1)%mod;
		printf("%d\n",ans);
	}
	return 0;
}
