#include <cstdio>
#include <algorithm>
#define L 1<<23
#define C (c=*A++)
#define ENS //__attribute__((optimize("-O2")))
#define NES inline//__attribute__((optimize("-O2"))) __inline__ __attribute__((always_inline))
#define T 1048576
#define N 300001

const long long EN=-1ll<<61;using namespace std;struct node{int x,y;bool f;NES bool operator<(const node &b)const{return x<b.x;}}a[N<<1];
int g[T],q[N],u[N],v[N],x[N],y[N],le[T],re[T],ri[T],wt,ss[19];char fl[L],*A=fl,fll[L],*B=fll;long long F[T],f[T],G[T];

NES void read(int &x){char c;bool p=false;x=0;while (C!='-'&&'0'>c||c>'9');if (c=='-') p=true,C;while ('0'<=c&&c<='9') x=(x<<3)+(x<<1)+c-48,C;if (p) x=-x;}NES void print(long long x){if (x<0) *B++='-',x=-x;if (!x) *B++=(48); else {for (wt=0;x;ss[++wt]=x%10,x/=10);for (;wt;*B++=(ss[wt]+48),wt--);}*B++='\n';}
NES void fix(long long &a,long long b){if (a<b) a=b;}
NES void P(int x,long long a,int b)
{
	if (f[x]!=EN)
		if (f[x]<a)
			if (f[x]+(long long)re[x]*g[x]<a+(long long)re[x]*b) f[x]=a,g[x]=b;
			else
				if (f[x]+(long long)ri[x<<1]*g[x]>a+(long long)ri[x<<1]*b) P(x<<1,a,b);
				else P(x<<1|1,f[x]+(long long)g[x]*ri[x<<1],g[x]),f[x]=a,g[x]=b;
		else
		{
			if (f[x]+(long long)re[x]*g[x]<a+(long long)re[x]*b)
				if (f[x]+(long long)ri[x<<1]*g[x]>a+(long long)ri[x<<1]*b) P(x<<1|1,a+(long long)ri[x<<1]*b,b);
				else P(x<<1,f[x],g[x]),f[x]=a,g[x]=b;
		}
	else f[x]=a,g[x]=b;
}

ENS int main()
{
	int n,m,M,i,l,r,S,d,cnt=0;long long X,Y,NE,MAPLE;
	for (*(fl+fread(fl,1,L,stdin))=EOF,read(n),read(m),i=1;i<=m;i++)
		switch (read(q[i]),q[i])
		{
			case 1:read(x[i]),read(y[i]),read(v[i]),read(u[i]),a[++cnt]=(node){x[i],i,true},a[++cnt]=(node){y[i],i,false};break;
			case 2:read(x[i]),read(y[i]),read(v[i]),read(u[i]),a[++cnt]=(node){x[i],i,true},a[++cnt]=(node){y[i],i,false};break;
			case 3:read(x[i]),a[++cnt]=(node){x[i],i,true};break;
		}
	for (sort(a+1,a+cnt+1),a[1].f?x[a[1].y]=S=1:y[a[1].y]=S=1,i=2;i<=cnt;a[i].f?x[a[i].y]=S:y[a[i].y]=S,i++) if (a[i].x!=a[S].x) a[++S].x=a[i].x;
	for (M=1;M<=S;M<<=1);for (i=1;i<=S;le[i+M]=a[i].x,f[i+M]=EN,ri[i+M]=i==S?1:a[i+1].x-a[i].x,i++);for (i=M-1;i;f[i]=EN,re[i]=ri[i<<1]+re[i<<1|1],ri[i]=ri[i<<1]+ri[i<<1|1],le[i]=le[i<<1],i--);
	for (i=1;i<=m;i++)
		switch (q[i])
		{
			case 1:
				for (X=u[i],d=v[i],Y=y[i]==S?u[i]+(long long)(a[y[i]].x-a[x[i]].x+1)*d:u[i]+(long long)(a[y[i]+1].x-a[x[i]].x)*d,l=x[i]+M-1,r=y[i]+M+1;l^r^1;l>>=1,r>>=1)
				{
					if (~l&1) P(l^1,X,d),X+=(long long)ri[l^1]*d;
					if ( r&1) Y-=(long long)ri[r^1]*d,P(r^1,Y,d);
				}break;
			case 2:
				for (X=u[i],d=v[i],Y=y[i]==S?u[i]+(long long)(a[y[i]].x-a[x[i]].x+1)*d:u[i]+(long long)(a[y[i]+1].x-a[x[i]].x)*d,l=x[i]+M-1,r=y[i]+M+1;l^r^1;l>>=1,r>>=1)
				{
					if (~l&1) F[l^1]+=X,G[l^1]+=d,X+=(long long)ri[l^1]*d;
					if ( r&1) Y-=(long long)ri[r^1]*d,F[r^1]+=Y,G[r^1]+=d;
				}break;
			case 3:
				for (MAPLE=0,l=x[i]+M,r=a[x[i]].x,NE=EN;l;MAPLE+=F[l]+(r-le[l])*G[l],fix(NE,f[l]+(long long)(r-le[l])*g[l]),l>>=1);
				if (NE==EN) *B++='N',*B++='A',*B++='\n'; else print(MAPLE+NE);break;
		}fwrite(fll,1,B-fll,stdout);
}