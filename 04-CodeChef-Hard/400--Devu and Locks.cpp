#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> poly;

const int N=32768,M=50,mod=998244353,G=3,invG=332748118;

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

int wn[2][N+9];

void Get_wn(){
  int w0=Power(G,(mod-1)/N),w1=Power(invG,(mod-1)/N);
  wn[0][0]=wn[1][0]=1;
  for (int i=1;i<N;++i){
	wn[0][i]=mul(wn[0][i-1],w0);
	wn[1][i]=mul(wn[1][i-1],w1);
  }
}

int len,rev[N+9];

void Get_len(int n){
  int l=0;
  for (len=1;len<n;len<<=1) ++l;
  for (int i=0;i<len;++i) rev[i]=rev[i>>1]>>1|(i&1)<<l-1;
}

int pw[N+9];

void NTT(poly &a,int n,int t){
  static ULL ntt[N+9];
  for (int i=0;i<n;++i) ntt[i]=a[rev[i]];
  for (int i=1;i<n;i<<=1){
	int tl=N/(i<<1);
    if (i==1){
	  pw[0]=wn[t][0];
	  for (int j=0;j<n;j+=2){
	    ULL y=ntt[i+j]*pw[0]%mod;
	    ntt[i+j]=ntt[j]+mod-y;
	    ntt[j]+=y;
	  }
	}else if (i==2){
	  pw[0]=wn[t][0];pw[1]=wn[t][tl];
	  for (int j=0;j<n;j+=4){
	    ULL y=ntt[i+j]*pw[0]%mod;
	    ntt[i+j]=ntt[j]+mod-y;
	    ntt[j]+=y;
	    y=ntt[i+j+1]*pw[1]%mod;
	    ntt[i+j+1]=ntt[j+1]+mod-y;
	    ntt[j+1]+=y;
	  }
	}else{
	  for (int j=0;j<i;++j) pw[j]=wn[t][j*tl];
	  for (int j=0;j<n;j+=i<<1)
	    for (int k=0;k<i;k+=4){
	      ULL y=ntt[i+j+k]*pw[k]%mod;
	      ntt[i+j+k]=ntt[j+k]+mod-y;
	      ntt[j+k]+=y;
	      y=ntt[i+j+k+1]*pw[k+1]%mod;
	      ntt[i+j+k+1]=ntt[j+k+1]+mod-y;
	      ntt[j+k+1]+=y;
	      y=ntt[i+j+k+2]*pw[k+2]%mod;
	      ntt[i+j+k+2]=ntt[j+k+2]+mod-y;
	      ntt[j+k+2]+=y;
	      y=ntt[i+j+k+3]*pw[k+3]%mod;
	      ntt[i+j+k+3]=ntt[j+k+3]+mod-y;
	      ntt[j+k+3]+=y;
	    }
	}
    if (i==1<<15)
      for (int j=0;j<n;++j) ntt[j]%=mod;
  }
  for (int i=0;i<n;++i) a[i]=ntt[i]%mod;
  if (!t) return;
  t=Get_inv(n);
  for (int i=0;i<n;++i) smul(a[i],t);
}

poly Poly_add(poly a,poly b){int n=a.size();for (int i=0;i<n;++i) sadd(a[i],b[i]);return a;}
poly Poly_sub(poly a,poly b){int n=a.size();for (int i=0;i<n;++i) ssub(a[i],b[i]);return a;}
poly Poly_mul(poly a,int b){int n=a.size();for (int i=0;i<n;++i) smul(a[i],b);return a;}

poly Poly_mul(poly a,poly b){
  int n=a.size();
  if (n<=64){
	for (int i=n-1;i>=0;--i){
	  smul(a[i],b[0]);
	  for (int j=0;j<i;++j) sadd(a[i],mul(a[j],b[i-j]));
	}
	return a;
  }
  Get_len(n*2-1);
  a.resize(len);b.resize(len);
  NTT(a,len,0);
  NTT(b,len,0);
  for (int i=0;i<len;++i) smul(a[i],b[i]);
  NTT(a,len,1);
  a.resize(n);
  return a;
}

poly Poly_mul(poly a,poly b,int sk){
  int n=a.size(),m=b.size();
  if (n>sk) a.resize(sk),n=sk;
  if (m>sk) b.resize(sk),m=sk;
  if (sk<=64){
	a.resize(sk);b.resize(sk);
	for (int i=sk-1;i>=0;--i){
	  smul(a[i],b[0]);
	  for (int j=0;j<i;++j) sadd(a[i],mul(a[j],b[i-j]));
	}
	return a;
  }
  Get_len(n+m-1);
  a.resize(len),b.resize(len);
  NTT(a,len,0);
  NTT(b,len,0);
  for (int i=0;i<len;++i) smul(a[i],b[i]);
  NTT(a,len,1);
  a.resize(sk);
  return a;
}

poly Poly_inv(poly a){
  int n=a.size();
  if (n==1) return poly(1,Get_inv(a[0]));
  poly res=Poly_inv(poly(a.begin(),a.begin()+(n+1>>1)));
  Get_len(n*2-1);
  res.resize(len);a.resize(len);
  NTT(res,len,0);
  NTT(a,len,0);
  for (int i=0;i<len;++i) smul(res[i],sub(2,mul(res[i],a[i])));
  NTT(res,len,1);
  res.resize(n);
  return res;
}

poly Poly_der(poly a){int n=a.size();for (int i=1;i<n;++i) a[i-1]=mul(a[i],i);a[n-1]=0;return a;}
poly Poly_int(poly a){int n=a.size();for (int i=n-1;i>=1;--i) a[i]=mul(a[i-1],inv[i]);a[0]=0;return a;}

poly Poly_ln(poly a){
  int n=a.size();
  if (n==1) return poly(1,0);
  poly res=Poly_inv(a);
  for (int i=1;i<n;++i) a[i-1]=mul(a[i],i);
  Get_len(n*2-1);
  res.resize(len);a.resize(len);
  NTT(res,len,0);
  NTT(a,len,0);
  for (int i=0;i<len;++i) smul(res[i],a[i]);
  NTT(res,len,1);
  for (int i=n-1;i>=1;--i) res[i]=mul(res[i-1],inv[i]);
  res[0]=0;
  res.resize(n);
  return res;
}

void Poly_exp(poly &a,int l,int r,poly &res){
  if (r-l+1<=64){
	for (int i=l;i<=r;++i){
	  if (i) smul(res[i],inv[i]);
	  for (int j=1;i+j<=r;++j) sadd(res[i+j],mul(res[i],a[j]));
	}
    return;
  }
  int c=r-l+1>>4;
  poly ta[15],tb[16];
  Get_len(c*2-1);
  for (int i=0;i<16;++i){
	tb[i].resize(len);
	if (i<15){
	  ta[i]=poly(a.begin()+i*c,a.begin()+(i+2)*c);
	  NTT(ta[i],len,0);
	}
  }
  for (int i=0;i<16;++i){
	int nl=l+i*c,nr=nl+c-1;
	if (i){
	  NTT(tb[i],len,1);
	  for (int j=nl;j<=nr;++j) sadd(res[j],tb[i][j-nl+c]),tb[i][j-nl+c]=0;
	}
	Poly_exp(a,nl,nr,res);
    Get_len(c*2-1);
	if (i<15){
	  for (int j=nl;j<=nr;++j) tb[i][j-nl]=res[j];
	  NTT(tb[i],len,0);
	  for (int j=i+1;j<16;++j)
	    for (int k=0;k<len;++k) sadd(tb[j][k],mul(ta[j-i-1][k],tb[i][k]));
	}
  }
}

poly Poly_exp(poly a){
  int n=a.size();
  Get_len(n);
  a.resize(len);
  for (int i=0;i<n;++i) smul(a[i],i);
  poly res(len);
  res[0]=1;
  Poly_exp(a,0,len-1,res);
  res.resize(n);
  return res;
}

poly Poly_power(poly a,int k){
  int n=a.size();
  poly res(n);
  if (!k) {res[0]=1;return res;}
  int m=0;
  for (;!a[m]&&m<n;++m);
  if (m>(n-1)/k) return res;
  int mk=m*k,t=Get_inv(a[m]);
  for (int i=0;i<n-mk;++i) res[i]=mul(a[i+m],t);
  res.resize(n-mk);
  res=Poly_exp(Poly_mul(Poly_ln(res),k));
  res.resize(n);
  t=Power(a[m],k);
  for (int i=n-mk-1;i>=0;--i) res[i+mk]=mul(res[i],t);
  for (int i=0;i<mk;++i) res[i]=0;
  return res;
}

int n,p,m;

void into(){
  scanf("%d%d%d",&n,&p,&m);
}

int cnt[M+9],last[M+9],num[M+9];

void Get_cnt(){
  int now=1%p;
  for (int i=1;i<=n;++i){
	if (last[now]){
	  int l=last[now],r=i-1,c=r-l+1,s=n-i+1;
	  for (int j=l;j<=r;++j) cnt[num[j]]+=(s+c-1-j+l)/c;
	  return;
	}
    ++cnt[now];
	last[now]=i;
	num[i]=now;
	smul(now,10,p);
  }
  //printf("%d\n",cnt[0]);
}

poly a[M+9],b[M+9],ans[M+9];

void Get_ans(){
  Get_len(m*2+1);
  for (int i=0;i<p;++i) ans[i].resize(len);
  ans[0][0]=1;
  for (int i=0;i<p;++i){
	poly c(10,1);
	c.resize(m+1);
	c=Poly_power(c,cnt[i]);
    Get_len(m*2+1);
	for (int j=0;j<p;++j) a[j].clear(),a[j].resize(len);
	for (int j=0,s=0;j<=m;++j,sadd(s,i,p)) a[s][j]=c[j];
	for (int j=0;j<p;++j){
	  NTT(a[j],len,0);
	  b[j]=ans[j];
	  ans[j].clear();ans[j].resize(len);
	  NTT(b[j],len,0);
	}
	for (int j=0;j<p;++j)
	  for (int k=0;k<p;++k)
		for (int t=0;t<len;++t){
		  int s=j+k>=p?j+k-p:j+k;
		  ans[s][t]=(ans[s][t]+1LL*a[j][t]*b[k][t])%mod;
		}
	for (int j=0;j<p;++j){
	  NTT(ans[j],len,1);
	  ans[j].resize(m+1);
	  ans[j].resize(len);
	}
  }
}

void work(){
  Get_inv();
  Get_wn();
  Get_cnt();
  Get_ans();
}

void outo(){
  for (int i=0;i<=m;++i){
	if (i) sadd(ans[0][i],ans[0][i-1]);
	printf("%d ",ans[0][i]);
  }
  puts("");
}

int main(){
  into();
  work();
  outo();
  return 0;
}