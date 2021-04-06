#include<bits/stdc++.h>
using namespace std;
//#pragma GCC optimize(2)
typedef double db;
typedef long double ldb;
typedef long long ll;
typedef unsigned long long ull;
typedef pair <int,int> Pii;
#define reg register
#define pb push_back
#define mp make_pair
#define Mod1(x) ((x>=P)&&(x-=P))
#define Mod2(x) ((x<0)&&(x+=P))
#define rep(i,a,b) for(int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(int i=a,i##end=b;i>=i##end;--i)
template <class T> inline void cmin(T &a,const T &b){ ((a>b)&&(a=b)); }
template <class T> inline void cmax(T &a,const T &b){ ((a<b)&&(a=b)); }

char IO;
template <class T=int> T rd(){
	T s=0; int f=0;
	while(!isdigit(IO=getchar())) if(IO=='-') f=1;
	do s=(s<<1)+(s<<3)+(IO^'0');
	while(isdigit(IO=getchar()));
	return f?-s:s;
}

const int N=52,P=1e9+7;

int n,k;

struct Mat{
	int a[N][N];
	Mat(){ memset(a,0,sizeof a); }
	void One(){ rep(i,1,k) a[i][i]=1; }
	Mat operator * (const Mat x) const {
		Mat res;
		rep(i,1,k) rep(j,1,k) rep(d,1,k) res.a[i][d]=(res.a[i][d]+1ll*a[i][j]*x.a[j][d])%P;
		return res;
	}
	Mat operator + (const Mat x) const {
		Mat res;
		rep(i,1,k) rep(j,1,k) res.a[i][j]=a[i][j]+x.a[i][j],Mod1(res.a[i][j]);
		return res;
	}
} A,B;

ll qpow(ll x,ll k=P-2){
	ll res=1;
	for(;k;k>>=1,x=x*x%P) if(k&1) res=res*x%P;
	return res;
}

Mat qpow(Mat x,ll k){
	Mat res; res.One();
	for(;k;k>>=1,x=x*x) if(k&1) res=res*x;
	return res;
}

pair <Mat,Mat> Calc(int n){
	if(n==1) return mp(B,A);
	auto r=Calc(n/2);
	r.first=r.first*r.second+r.second*r.first;
	r.second=r.second*r.second;
	if(n&1) r.first=r.first*A+r.second*B,r.second=r.second*A;
	return r;
}

int main(){
	n=rd(),k=rd();
	int l=rd()+1,r=rd()-1;
	rep(i,1,k) A.a[i][i]=A.a[i][i-1]=A.a[i][i+1]=1;
	rep(i,1,k) rep(j,l,r) if(abs(i-j)<=1) B.a[i][j]++;
	Mat res=Calc(n-2).first*A;
	//rep(i,1,n-2) res=res+qpow(A,i-1)*B*qpow(A,n-2-i);
	//res=res*A;
	int ans=res.a[k/2][k/2]*qpow(n-2)%P;
	printf("%d\n",ans);
}




