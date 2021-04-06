#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ui unsigned int
#define ull unsigned long long
#define db long double
#define pii pair<ll,int>
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define vi vector<int>
#define vii vector<vi>
#define lb lower_bound
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,b,a) for(register int i=(b);i>=(a);--i)
#define rep0(i,a,b) for(register int i=(a);i<(b);++i)
#define fore(i,a) for(register int i=0;i<a.size();++i)
#define ls x<<1,l,m
#define rs x<<1|1,m+1,r
#define gc() getchar()
inline ll rd()
{
	ll x=0,w=1;char c=gc();while(!isdigit(c)&&c!='-')c=gc();
	if(c=='-')w=-1,c=gc();while(isdigit(c))x=x*10+c-48,c=gc();return x*w;
}
const int N=30,M=10005,K=100005,G=46,P=1163962801; 
int n,m,t,u[M],v[M],x[M],y[M],w1[N],w2[N],f[N][N][N],ans[N][N]; 
inline int pls(int x,int y){return (1ll*x+y)%P;}
inline int pw(int a,int b){int r=1;for(;b;b>>=1,a=1ll*a*a%P)if(b&1)r=1ll*r*a%P;return r;}
struct mat{int n,m,a[N][N];};
inline mat operator*(const mat&a,const mat&b)
{
	mat c;c.n=a.n;c.m=b.m;rep0(i,0,a.n)rep0(j,0,b.m)c.a[i][j]=0;
	rep0(i,0,a.n)rep0(j,0,b.m)rep0(k,0,a.m)c.a[i][j]=(c.a[i][j]+1ll*a.a[i][k]*b.a[k][j])%P;
	return c;
}
inline mat operator^(mat a,int b)
{
	mat c;c.n=c.m=a.n;
	rep0(i,0,c.n)rep0(j,0,c.m)c.a[i][j]=(i==j);
	for(;b;b>>=1,a=a*a)if(b&1)c=c*a;return c;
}
mat gt(int t1,int t2)
{
	mat a;a.n=a.m=n;rep0(i,0,n)rep0(j,0,n)a.a[i][j]=0;
	rep(i,1,m)a.a[u[i]][v[i]]=(a.a[u[i]][v[i]]+1ll*w1[t1*x[i]%n]*w2[t2*y[i]%(n-1)])%P;
	return a;
}
int main()
{
	n=rd();m=rd();t=rd();
	rep(i,1,m){u[i]=rd()-1;v[i]=rd()-1;x[i]=rd()%n;y[i]=rd()%(n-1);}
	w1[0]=1;w1[1]=pw(G,(P-1)/n);rep0(i,2,n)w1[i]=1ll*w1[i-1]*w1[1]%P;
	w2[0]=1;w2[1]=pw(G,(P-1)/(n-1));rep0(i,2,n-1)w2[i]=1ll*w2[i-1]*w2[1]%P;
	rep0(i,0,n)rep0(j,0,n-1)
	{
		mat a=gt(i,j)^t;
		rep0(k,0,n)f[k][i][j]=a.a[k][k];
	}
	rep0(i,0,n)
	{
		rep0(j,0,n)rep0(k,0,n-1)ans[j][k]=0;
		rep0(j,0,n)rep0(k,0,n-1)rep0(t1,0,n)rep0(t2,0,n-1)
			ans[j][k]=(ans[j][k]+1ll*f[i][t1][t2]*w1[t1*(n-j)%n]%P*w2[t2*(n-1-k)%(n-1)])%P; 
		int iv=pw(n*(n-1),P-2);
		rep0(j,0,n)rep0(k,0,n-1)printf("%d%c",1ll*ans[j][k]*iv%P,k==n-2?'\n':' ');
	}
	return 0;
}
