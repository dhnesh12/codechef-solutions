#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> poly;

const int N=32768,M=50,mod=1000000007;
const double pi=acos(-1);

struct comp{
  double x,y;
  comp(double X=0,double Y=0){x=X;y=Y;}
  comp operator + (const comp &p)const{return comp(x+p.x,y+p.y);}
  comp operator - (const comp &p)const{return comp(x-p.x,y-p.y);}
  comp operator * (const comp &p)const{return comp(x*p.x-y*p.y,x*p.y+y*p.x);}
  comp operator * (const double &p)const{return comp(x*p,y*p);}
  comp operator / (const double &p)const{return comp(x/p,y/p);}
  comp conj(){return comp(x,-y);}
};
typedef vector<comp>cpoly;

int add(int a,int b,int p=mod){return a+b>=p?a+b-p:a+b;}
int sub(int a,int b,int p=mod){return a-b<0?a-b+p:a-b;}
int mul(int a,int b,int p=mod){return 1LL*a*b%p;}
void sadd(int &a,int b,int p=mod){a=add(a,b,p);}
void ssub(int &a,int b,int p=mod){a=sub(a,b,p);}
void smul(int &a,int b,int p=mod){a=mul(a,b,p);}
int Power(int a,int k,int p=mod){int res=1;for (;k;k>>=1,smul(a,a,p)) if (k&1) smul(res,a,p);return res;}
int Get_inv(int a,int p=mod){return Power(a,p-2,p);}

int inv[N+9],fac[N+9],ifac[N+9];

void Get_inv(){
  inv[1]=1;
  fac[0]=fac[1]=1;
  ifac[0]=ifac[1]=1;
  for (int i=2;i<=N;++i){
	inv[i]=mul(mod-mod/i,inv[mod%i]);
	fac[i]=mul(fac[i-1],i);
	ifac[i]=mul(ifac[i-1],inv[i]);
  }
}

int Get_c(int n,int m){return n<m||m<0?0:mul(fac[n],mul(ifac[m],ifac[n-m]));}

comp wn[2][N+9];

void Get_wn(){
  for (int i=0;i<=N;++i){
	wn[0][i]=comp(cos(2*i*pi/N),sin(2*i*pi/N));
	wn[1][i]=comp(cos(2*i*pi/N),-sin(2*i*pi/N));
  }
}

int len,rev[N+9];

void Get_len(int n){
  int l=0;
  for (len=1;len<n;len<<=1) ++l;
  for (int i=0;i<len;++i) rev[i]=rev[i>>1]>>1|(i&1)<<l-1;
}

comp pw[N+9];

void FFT(cpoly &a,int n,int t){
  for (int i=0;i<n;++i)
	if (i<rev[i]) swap(a[i],a[rev[i]]);
  for (int i=1;i<n;i<<=1){
	int tl=N/(i<<1);
	for (int j=0;j<i;++j) pw[j]=wn[t][j*tl];
	for (int j=0;j<n;j+=i<<1)
	  for (int k=0;k<i;++k){
		comp x=a[j+k],y=pw[k]*a[i+j+k];
		a[j+k]=x+y;a[i+j+k]=x-y;
	  }
  }
  if (!t) return;
  for (int i=0;i<n;++i) a[i]=a[i]/n;
}

poly Poly_add(poly a,poly b){int n=a.size();for (int i=0;i<n;++i) sadd(a[i],b[i]);return a;}
poly Poly_sub(poly a,poly b){int n=a.size();for (int i=0;i<n;++i) ssub(a[i],b[i]);return a;}
poly Poly_mul(poly a,int b){int n=a.size();for (int i=0;i<n;++i) smul(a[i],b);return a;}

void Split_FFT(cpoly &a,cpoly &b){
  int n=a.size();
  b[0]=a[0].conj();
  for (int i=1;i<n;++i) b[i]=a[n-i].conj();
  for (int i=0;i<n;++i){
	comp x=a[i],y=b[i];
	a[i]=(x+y)*0.5;b[i]=(y-x)*comp(0,0.5);
  }
}

poly Poly_mul(poly a,poly b,int sk){
  int n=a.size(),m=b.size();
  if (n>sk) n=sk,a.resize(sk);
  if (m>sk) m=sk,b.resize(sk);
  Get_len(n+m-1);
  a.resize(len);b.resize(len);
  cpoly ta(len),tb(len);
  for (int i=0;i<len;++i){
	ta[i]=comp(a[i]>>15,a[i]&(1<<15)-1);
	tb[i]=comp(b[i]>>15,b[i]&(1<<15)-1);
  }
  FFT(ta,len,0);
  FFT(tb,len,0);
  cpoly tc(len),td(len);
  Split_FFT(ta,tc);
  Split_FFT(tb,td);
  for (int i=0;i<len;++i){
	ta[i]=ta[i]*tb[i]+comp(0,1)*ta[i]*td[i];
	tb[i]=tc[i]*tb[i]+comp(0,1)*tc[i]*td[i];
  }
  FFT(ta,len,1);
  FFT(tb,len,1);
  for (int i=0;i<len;++i){
	LL x=(LL)(ta[i].x+0.5)%mod,y=(LL)(ta[i].y+tb[i].x+0.5)%mod,z=(LL)(tb[i].y+0.5)%mod;
	a[i]=((x<<30)+(y<<15)+z)%mod;
  }
  a.resize(sk);
  return a;
}

poly Poly_mul(poly a,poly b){return Poly_mul(a,b,a.size());}

int n;
struct matrix{
  
  int a[M+9][M+9];
  
  matrix(){memset(a,0,sizeof(a));}
  int *operator [] (const int &p){return a[p];}
  
  matrix operator * (const matrix &p)const{
	matrix res;
	for (int i=1;i<=n;++i)
      for (int j=1;j<=n;++j)
		for (int k=1;k<=n;++k) res.a[i][k]=(res.a[i][k]+1LL*a[i][j]*p.a[j][k])%mod;
	return res;
  }
  
  int det(){
	int res=1;
	for (int i=1;i<=n;++i){
	  int r=i;
	  for (;!a[r][i]&&r<=n;++r);
	  if (r>n) return 0;
	  if (r^i) swap(a[r],a[i]),res=sub(0,res);
	  smul(res,a[i][i]);
	  int t=Get_inv(a[i][i]);
	  for (int j=i;j<=n;++j) smul(a[i][j],t);
	  for (int j=i+1;j<=n;++j){
		int t=a[j][i];
        for (int k=i;k<=n;++k) ssub(a[j][k],mul(t,a[i][k]));
	  }
	}
	return res;
  }
  
};

poly Lagrange(poly y){
  poly res(n+1);
  for (int i=0;i<=n;++i){
	poly t(n+1);
	int ml=1;
	t[0]=1;
	for (int j=0;j<=n;++j){
	  if (i==j) continue;
	  smul(ml,sub(i,j));
	  for (int k=n;k>=0;--k){
		smul(t[k],sub(0,j));
		if (k) sadd(t[k],t[k-1]);
	  }
	}
	res=Poly_add(res,Poly_mul(t,mul(Get_inv(ml),y[i])));
  }
  return res;
}

int m,K;
matrix a;
poly cnt[M+9],gg[M+9];

poly Get_cnt(int id){
  matrix now=a;
  for (int i=1;i<=n;++i)
	for (int j=1;j<=n;++j) now[i][j]=sub(0,now[i][j]);
  poly b(n+1);
  for (int i=0;i<=n;++i){
	matrix tmp=now;
	b[i]=tmp.det();
	for (int j=1;j<=n;++j) sadd(now[j][j],1);
  }
  gg[id]=b=Lagrange(b);
  now=matrix();
  for (int i=1;i<=n;++i) now[i][i]=1;
  poly res(n+1);
  for (int i=0;i<=n;++i){
	for (int j=1;j<=n;++j) sadd(res[i],now[j][j]);
	now=now*a;
  }
  return res;
}

int cq;
vector<int>ql,qr,qk;

void into(){
  scanf("%d",&m);
  for (int i=1;i<=m;++i){
	int c;
	scanf("%d%d",&n,&c);
	a=matrix();
	for (int j=1;j<=c;++j){
	  int x,y;
	  scanf("%d%d",&x,&y);
	  sadd(a[x][y],1);
	  sadd(a[y][x],1);
	}
	for (int j=1;j<=n;++j) sadd(a[j][j],1);
	cnt[i]=Get_cnt(i);
  }
  scanf("%d",&cq);
  ql.resize(cq);qr.resize(cq);qk.resize(cq);
  for (int i=0;i<cq;++i){
	scanf("%d%d%d",&ql[i],&qr[i],&qk[i]);
	K=max(K,qk[i]+3);
  }
}

void Get_cnt(){
  for (int i=1;i<=m;++i){
	int n=cnt[i].size()-1;
	cnt[i].resize(K);
    for (int j=n+1;j<K;++j){
	  for (int k=0;k<n;++k) ssub(cnt[i][j],mul(gg[i][k],cnt[i][j-n+k]));
  	  smul(cnt[i][j],Get_inv(gg[i][n]));
    }
  }
}

poly ans[M+9][M+9];

void Get_ans(){
  for (int l=1;l<=m;++l){
	poly pre(K);
	for (int i=0;i<K;++i) pre[i]=ifac[i];
	for (int r=l;r<=m;++r){
	  poly t(K);
	  for (int i=0;i<K;++i) smul(pre[i],cnt[r][i]),t[i]=i&1?sub(0,ifac[i]):ifac[i];
	  ans[l][r]=Poly_mul(pre,t);
	  ans[l][r][0]=0;
	  for (int i=0;i<K;++i){
		smul(ans[l][r][i],fac[i]);
		if (i) sadd(ans[l][r][i],ans[l][r][i-1]);
	  }
	}
  }
}

void work(){
  Get_inv();
  Get_wn();
  Get_cnt();
  Get_ans();
}

void getans(){
  for (int i=0;i<cq;++i)
	printf("%d\n",ans[ql[i]][qr[i]][qk[i]]);
}

int main(){
  into();
  work();
  getans();
  return 0;
}