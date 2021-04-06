#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned ll
#define uint unsigned int
#define db double
#define pint pair<int,int>
#define mk make_pair
#define pb push_back
#define eb emplace_back
#define ins insert
#define fi first
#define se second
#define Rep(x,y,z) for(int x=y;x<=z;x++)
#define Red(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
const int Mod=998244353,MAXN=6e5+5;
char buf[1<<12],*pp1=buf,*pp2=buf,nc;int ny;
inline char gc() {return pp1==pp2&&(pp2=(pp1=buf)+fread(buf,1,1<<12,stdin),pp1==pp2)?EOF:*pp1++;}
//inline char gc(){return getchar();}
inline int read(){
	int x=0;for(ny=1;nc=gc(),(nc<48||nc>57)&&nc!=EOF;)if(nc==45)ny=-1;if(nc<0)return nc;
	for(x=nc-48;nc=gc(),47<nc&&nc<58&&nc!=EOF;x=(x<<3)+(x<<1)+(nc^48));return x*ny;
}
inline int Fp(int x,int k){int ans=1;for(;k;k>>=1,x=1ll*x*x%Mod)if(k&1)ans=1ll*ans*x%Mod;return ans;}
typedef vector<int> Poly;
int r[20][MAXN],wi[2][MAXN],Lg[MAXN],Max,inv[MAXN],iFac[MAXN],Fac[MAXN];
inline void Init(){
	int N=1,c=0;
	for(;N<MAXN;N<<=1,c++){
		for(int i=0;i<N;i++)r[c][i]=(r[c][i>>1]>>1)|((i&1)<<(c-1));Lg[N]=c;
	}Max=N>>1,wi[0][0]=wi[1][0]=1;int w1=Fp(3,(Mod-1)/Max),w2=Fp(w1,Mod-2);
	for(int i=1;i<Max;i++)wi[0][i]=1ll*wi[0][i-1]*w1%Mod,wi[1][i]=1ll*wi[1][i-1]*w2%Mod;
	inv[1]=1;Rep(i,2,MAXN-1)inv[i]=1ll*(Mod-Mod/i)*inv[Mod%i]%Mod;
	Fac[0]=iFac[0]=1;Rep(i,1,MAXN-1)Fac[i]=1ll*Fac[i-1]*i%Mod,iFac[i]=1ll*iFac[i-1]*inv[i]%Mod;
}
inline int C(int n,int m){return n<0||m<0||n<m?0:1ll*Fac[n]*iFac[m]%Mod*iFac[n-m]%Mod;}
inline void NTT(int*f,int len,int opt){
	int c=Lg[len];for(int i=0;i<len;i++)if(i<r[c][i])swap(f[i],f[r[c][i]]);
	for(int i=1,t=Max>>1;i<len;i<<=1,t>>=1)for(int j=0;j<len;j+=i<<1)for(int k=0,o=0;k<i;k++,o+=t){
		int x=1ll*wi[opt][o]*f[i+j+k]%Mod,y=f[j+k];f[i+j+k]=(y-x+Mod)%Mod,f[j+k]=(x+y)%Mod;
	}if(opt)for(int i=0;i<len;i++)f[i]=1ll*f[i]*inv[len]%Mod;
}
inline int Trans(int x){return 1<<(int)(ceil(log2(x+1)));}
inline Poly operator*(Poly a,Poly b){
	static int A[MAXN],B[MAXN];int len=Trans(a.size()+b.size()-2);
	copy(a.begin(),a.end(),A),copy(b.begin(),b.end(),B),fill(A+a.size(),A+len,0),fill(B+b.size(),B+len,0);
	NTT(A,len,0),NTT(B,len,0);for(int i=0;i<len;i++)A[i]=1ll*A[i]*B[i]%Mod;NTT(A,len,1);
	return Poly(A,A+a.size()+b.size()-1);
}
inline Poly operator-(Poly a,Poly b){int len=max(a.size(),b.size());a.resize(len);for(int i=0;i<b.size();i++)a[i]=(a[i]-b[i]+Mod)%Mod;return a;}
inline Poly Inv(Poly F,int len){
	F.resize(len);Poly G(1);G[0]=Fp(F[0],Mod-2);
	for(int m=2;m<=len;m<<=1){
		static int A[MAXN],B[MAXN];int len=Trans(m+(m>>1));
		copy(F.begin(),F.begin()+m,A),copy(G.begin(),G.end(),B),fill(A+m,A+len,0),fill(B+G.size(),B+len,0);
		NTT(A,len,0),NTT(B,len,0);for(int i=0;i<len;i++)A[i]=(2-1ll*A[i]*B[i]%Mod+Mod)%Mod*B[i]%Mod;NTT(A,len,1);G=Poly(A,A+m);
	}return G;
}
inline Poly Der(Poly f){int len=f.size();if(len==1){f[0]=0;return f;}for(int i=0;i<len-1;i++)f[i]=1ll*f[i+1]*(i+1)%Mod;f.resize(len-1);return f;}
inline Poly Inte(Poly f){int len=f.size();f.resize(len+1);for(int i=len-1;i>=0;i--)f[i+1]=1ll*f[i]*inv[i+1]%Mod,f[i]=0;return f;}
inline Poly Ln(Poly F,int len){Poly Ans=Inte(Der(F)*Inv(F,len));return Ans.resize(len),Ans;}
inline Poly Exp(Poly F,int len){
	F.resize(len);Poly G(1);G[0]=1;
	for(int m=2;m<=len;m<<=1){
		Poly A(F.begin(),F.begin()+m),B=(A-Ln(G,m));
		(B[0]==Mod-1?B[0]=0:B[0]++),G=G*B,G.resize(m);
	}return G;
}
Poly B,A,H,F;int n,k,m;
inline Poly calc(int n){
	Rep(i,0,k+1)A[i]=1ll*Fp(n+1,i)%Mod*iFac[i]%Mod;
	Poly Ans=A*B;Ans.resize(k+2);
	Rep(i,0,k)Ans[i]=(Ans[i+1]-B[i+1]+Mod)%Mod;
	Ans[0]=(Ans[0]-1+Mod)%Mod;
	Ans.resize(k+1);
	return Ans;
}
int main(){
//	freopen("std.in","r",stdin);
//	freopen("std.out","w",stdout);
	k=read(),read(),n=read(),Init();int len=Trans(k+1);
	B.resize(len);Rep(i,0,len-1)B[i]=iFac[i+1];
	B=Inv(B,len),B.resize(k+2),A.resize(k+2);
	F.resize(k+1);F[0]=1;
	Rep(i,1,n){
		int a=read(),b=read(),c=read();
		if(a!=b){
			H=calc(b)-calc(a-1);int tt=Fp(b-a+1,Mod-2);
			Rep(i,0,k)H[i]=1ll*H[i]*tt%Mod;H=Ln(H,len);
			for(int i=0;i<len;i++)H[i]=1ll*H[i]*c%Mod;
			H=Exp(H,len),H.resize(k+1);
			Rep(i,0,k)H[i]=1ll*H[i];
		}else {H.resize(k+1);Rep(i,0,k)H[i]=1ll*Fp(1ll*c*a%Mod,i)*iFac[i]%Mod;}
		F=F*H;F.resize(k+1);
	}cout<<1ll*F[k]*Fac[k]%Mod;
	return 0;
}


