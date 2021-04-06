#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<ctime>
#define ull unsigned long long
#define ll long long
using namespace std;
const int mod=998244353;
const int G=3;
inline int MOD(int x){return x+((x>>31)&mod);}
int read()
{
	int kkk=0,x=1;
	char c=getchar();
	while((c<'0' || c>'9') && c!='-') c=getchar();
	if(c=='-') c=getchar(),x=-1;
	while(c>='0' && c<='9') kkk=kkk*10+(c-'0'),c=getchar();
	return kkk*x;
}
int T,n,K,sum[2000001],inv[2000001],zone[4200000],wn[4200000],f[4200000],ans[4200000],Lim;
ull pro[4200000];
int ksm(int x,int y)
{
	int z=1;
	while(y)
	{
		if(y&1) z=(ll)z*x%mod;
		x=(ll)x*x%mod;
		y>>=1;
	}
	return z;
}
void NTT(int A[],int lim,int flag)
{
	for(int i=0;i<lim;++i) pro[i]=A[zone[i]];
	for(int len=1;len<lim;len<<=1)
		for(int i=0;i<lim;i+=2*len)
			for(int j=0;j<len;++j)
			{
				ull P1=pro[i+j],P2=wn[Lim/len*j]*pro[i+j+len]%mod;
				pro[i+j]=P1+P2;
				pro[i+j+len]=P1+mod-P2;
			}
	for(int i=0;i<lim;++i) A[i]=pro[i]%mod;
	if(!flag)
	{
		int Inv=ksm(lim,mod-2);
		for(int i=0;i<lim;++i) A[i]=(ll)A[i]*Inv%mod;
		reverse(A+1,A+lim);
	}
}
inline int C(int n,int m){return (n<0 || m<0 || n<m)?0:(ll)sum[n]*inv[m]%mod*inv[n-m]%mod;}
int main()
{
	Lim=1; while(Lim<400001) Lim<<=1;
	wn[0]=1,wn[1]=ksm(G,(mod-1)/Lim/2);
	for(int i=2;i<Lim;++i) wn[i]=(ll)wn[i-1]*wn[1]%mod;
	sum[0]=inv[0]=1;
	for(int i=1;i<=2000000;++i) sum[i]=(ll)i*sum[i-1]%mod;
	inv[2000000]=ksm(sum[2000000],mod-2);
	for(int i=1999999;i>=1;--i) inv[i]=(ll)(i+1)*inv[i+1]%mod;
	T=read();
	while(T--)
	{
		n=read(),K=read();
		int N=n-2,tim=n;
		if(K==1)
		{
			int ANS=0;
			for(int i=0,p=1;i<=N;++i,p=(ll)p*n%mod) ANS=MOD(ANS+(ll)C(n,N-i)*inv[i]%mod*p%mod-mod);
			printf("%lld\n",(ll)ANS*sum[N]%mod*ksm(ksm(n,n-2),mod-2)%mod);
			continue;
		}
		for(int i=0;i<=N;++i) f[i]=(ll)ksm(i+1,K)*inv[i]%mod;
		int LOG=0,lim=1; while(lim<2*N+1) lim<<=1,++LOG;
		for(int i=0;i<lim;++i) zone[i]=((zone[i>>1]>>1)|((i&1)<<LOG-1));
		for(int i=N+1;i<lim;++i) f[i]=0;
		for(int i=0;i<lim;++i) ans[i]=0;
		ans[0]=1;
		while(tim)
		{
			NTT(f,lim,1);
			if(tim%2)
			{
				NTT(ans,lim,1);
				for(int i=0;i<lim;++i) ans[i]=(ll)ans[i]*f[i]%mod;
				NTT(ans,lim,0);
				for(int i=N+1;i<lim;++i) ans[i]=0;
			}
			for(int i=0;i<lim;++i) f[i]=(ll)f[i]*f[i]%mod;
			NTT(f,lim,0);
			for(int i=N+1;i<lim;++i) f[i]=0;
			tim>>=1;
		}
		printf("%lld\n",(ll)ans[N]*sum[N]%mod*ksm(ksm(n,n-2),mod-2)%mod);
	}
	return 0;
}