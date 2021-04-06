#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

int MOD;

ll pow_mod(ll x,int k) {
  ll ans=1;
  while (k) {
  	if (k&1) ans=ans*x%MOD;
  	x=x*x%MOD;
  	k>>=1;
  }
  return ans;
}

struct Complex {
  db x,y;
  Complex() {}
  Complex(db a,db b):x(a),y(b) {}
  Complex operator + (Complex b) {return Complex(x+b.x,y+b.y);}
  Complex operator - (Complex b) {return Complex(x-b.x,y-b.y);}
  Complex operator * (Complex b) {return Complex(x*b.x-y*b.y,x*b.y+y*b.x);}
};

namespace FFT {

const db PI=acos(-1.0);
const int Maxn=1<<18;

Complex *w[18];

void fft_init() {
  for(int i=2,t=0;i<=Maxn;i<<=1,t++) {
  	w[t]=new Complex[i>>1];
  	for(int j=0;j<(i>>1);j++) w[t][j]=Complex(cos(2.0*PI*j/i),sin(2.0*PI*j/i));
  }
}

void rev(Complex *p,int len) {
  int j=len>>1;
  for(int i=1;i<len-1;i++) {
  	if (i<j) swap(p[i],p[j]);
  	int k=len>>1;
  	while (j>=k) {
  		j-=k;
  		k>>=1;
	  }
	if (j<k) j+=k;
  }
}

void fft(Complex *p,int len,int check) {
  rev(p,len);
  for(int i=2,t=0;i<=len;i<<=1,t++)
    for(int j=0;j<len;j+=i)
      for(int k=j;k<j+(i>>1);k++) {
      	Complex u=p[k];
      	Complex v=w[t][k-j]*p[k+(i>>1)];
      	p[k]=u+v;
      	p[k+(i>>1)]=u-v;
	  }
  if (check==-1) {
  	reverse(p+1,p+len);
  	for(int i=0;i<len;i++) p[i].x/=len;
  }
}

void mul(ll *a,ll *b,ll *c,int n) {
  static Complex t1[Maxn],t2[Maxn],t3[Maxn],t4[Maxn];
  int len=1;
  while (len<(n<<1)) len<<=1;
  int M=sqrt(MOD);
  for(int i=0;i<n;i++) {
  	t1[i]=Complex(a[i]/M,0);
  	t2[i]=Complex(a[i]%M,0);
  	t3[i]=Complex(b[i]/M,0);
  	t4[i]=Complex(b[i]%M,0);
  }
  for(int i=n;i<len;i++) t1[i]=t2[i]=t3[i]=t4[i]=Complex(0,0);
  fft(t1,len,1);
  fft(t2,len,1);
  fft(t3,len,1);
  fft(t4,len,1);
  for(int i=0;i<len;i++) {
  	Complex u=t1[i]*t3[i],v=t1[i]*t4[i]+t2[i]*t3[i],w=t2[i]*t4[i];
  	t1[i]=u;
  	t2[i]=v;
  	t3[i]=w;
  }
  fft(t1,len,-1);
  fft(t2,len,-1);
  fft(t3,len,-1);
  for(int i=0;i<n;i++) {
  	ll u=(ll)(t1[i].x+0.5)%MOD,v=(ll)(t2[i].x+0.5)%MOD,w=(ll)(t3[i].x+0.5)%MOD;
  	c[i]=(u*M%MOD*M+v*M+w)%MOD;
  }
}

}

struct Matrix {
  int num[2][2],n,m;
  Matrix() {}
  Matrix(int a,int b):n(a),m(b) {memset(num,0,sizeof(num));}
};

Matrix operator * (Matrix a,Matrix b) {
  Matrix c(a.n,b.m);
  for(int i=0;i<c.n;i++)
    for(int j=0;j<c.m;j++)
      for(int k=0;k<a.m;k++) c.num[i][j]=(c.num[i][j]+(ll)a.num[i][k]*b.num[k][j])%MOD;
  return c;
}

Matrix operator ^ (Matrix a,int k) {
  Matrix ans(a.n,a.m);
  for(int i=0;i<a.n;i++) ans.num[i][i]=1;
  while (k) {
  	if (k&1) ans=ans*a;
  	a=a*a;
  	k>>=1;
  }
  return ans;
}

const int Maxn=1e7+1e5;

ll facd[Maxn+5],facv[Maxn+5];

void pre() {
  facd[0]=1;
  for(int i=1;i<=Maxn;i++) facd[i]=facd[i-1]*i%MOD;
  facv[Maxn]=pow_mod(facd[Maxn],MOD-2);
  for(int i=Maxn-1;i>=0;i--) facv[i]=facv[i+1]*(i+1)%MOD;
}

inline ll C(int n,int m) {
  return (n<m)?0:facd[n]*facv[m]%MOD*facv[n-m]%MOD;
}

int calc(int x,int v,int k) {
  Matrix a(2,2),ans(2,1);
  a.num[0][0]=ans.num[0][0]=v;a.num[0][1]=(ll)v*x%MOD;
  a.num[1][0]=ans.num[1][0]=1;
  ans=(a^(k-1))*ans;
  return ans.num[0][0];
}

ll p[100005],q[100005];

void getpoly(int n,int v) {
  for(int i=0;i<n;i++) {
  	p[i]=facv[i];
  	q[i]=((i&1)?MOD-1:1)*facv[i]%MOD*calc((MOD-i-1)%MOD,v,n)%MOD;
  }
  FFT::mul(p,q,p,n);
}

int query(int n,int m,int l,int r) {
  int ans=0;
  for(int i=0;i<n;i++)
    ans=(ans+p[i]*facd[i+m]%MOD*(C(r+i,i+m+1)-C(l+i,i+m+1)+MOD))%MOD;
  return ans*facv[m]%MOD;
}

int main() {
  FFT::fft_init();
  int n,m,k;
  scanf("%d%d%d%d",&n,&m,&MOD,&k);
  n--;
  pre();
  getpoly(n,m);
  for(int i=1;i<=k;i++) {
  	int x,y,z;
  	scanf("%d%d%d",&x,&y,&z);
  	printf("%d\n",query(n,x,y,y+z));
  }
  return 0;
}