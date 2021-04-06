#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> poly;
mt19937 Rand(time(0));

const int N=32768,M=100,K=2002,mod=998244353,G=3,invG=332748118;

int add(int a,int b,int p=mod){return a+b>=p?a+b-p:a+b;}
int sub(int a,int b,int p=mod){return a-b<0?a-b+p:a-b;}
int mul(int a,int b,int p=mod){return 1LL*a*b%p;}
void sadd(int &a,int b,int p=mod){a=add(a,b,p);}
void ssub(int &a,int b,int p=mod){a=sub(a,b,p);}
void smul(int &a,int b,int p=mod){a=mul(a,b,p);}
int Power(int a,int k,int p=mod){int res=1;for (;k;k>>=1,smul(a,a,p)) if (k&1) smul(res,a,p);return res;}
int Get_inv(int a,int p=mod){return Power(a,p-2,p);}

struct ncomp{
  int x,y;
  ncomp(int X=0,int Y=0){x=X;y=Y;}
};

ncomp mul(ncomp a,ncomp b,int w){return ncomp(add(mul(a.x,b.x),mul(w,mul(a.y,b.y))),add(mul(a.x,b.y),mul(a.y,b.x)));}

int Cipolla(int c){
  if (!c) return 0;
  if (Power(c,mod>>1)==mod-1) return -1;
  for (;2333;){
	int a=Rand()%(mod-1)+1,w=sub(mul(a,a),c);
	if (Power(w,mod>>1)==1) continue;
	ncomp res=ncomp(1,0),t=ncomp(a,1);
	for (int k=mod+1>>1;k;k>>=1,t=mul(t,t,w))
	  if (k&1) res=mul(res,t,w);
    return res.x;
  }
}

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

poly Poly_sqrt(poly a){
  int n=a.size();
  if (n==1) {int t=Cipolla(a[0]);return poly(1,min(t,mod-t));}
  poly res=Poly_sqrt(poly(a.begin(),a.begin()+(n+1>>1)));
  res.resize(n);
  poly b=Poly_inv(res);
  Get_len(n*2-1);
  a.resize(len);b.resize(len);
  NTT(a,len,0);
  NTT(b,len,0);
  for (int i=0;i<len;++i) smul(a[i],b[i]);
  NTT(a,len,1);
  a.resize(n);
  return Poly_mul(Poly_add(res,a),inv[2]);
}

poly Poly_power(poly a,int k){
  int n=a.size();
  poly res(n);
  if (!k) {res[0]=1;return res;}
  int m=0;
  for (;m<n&&!a[m];++m);
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

pair<poly,poly>Poly_div(poly a,poly b){
  int n=a.size(),m=b.size();
  if (n<m) {a.resize(m-1);return make_pair(poly(),a);}
  poly ta=a,tb=b;
  reverse(ta.begin(),ta.end());
  reverse(tb.begin(),tb.end());
  tb.resize(n-m+1);
  poly res=Poly_mul(ta,Poly_inv(tb),n-m+1);
  reverse(res.begin(),res.end());
  a=Poly_sub(a,Poly_mul(b,res,n));
  a.resize(m-1);
  return make_pair(res,a);
}

poly prod[N+9];

void Divide_prod(poly &x,int l,int r,int k){
  if (l==r) {prod[k].resize(2);prod[k][0]=1;prod[k][1]=sub(0,x[l]);return;}
  int mid=l+r>>1,ls=k<<1,rs=k<<1|1;
  Divide_prod(x,l,mid,ls);
  Divide_prod(x,mid+1,r,rs);
  prod[k]=Poly_mul(prod[ls],prod[rs],r-l+2);
}

poly Poly_mulT(poly a,poly b){
  int n=a.size(),m=b.size();
  if (n<=64){
	for (int i=0;i<n;++i){
	  smul(a[i],b[0]);
	  for (int j=1;j<m&&i+j<=n;++j) sadd(a[i],mul(a[i+j],b[j]));
	}
	a.resize(n-m+1);
	return a;
  }
  reverse(b.begin(),b.end());
  Get_len(n);
  a.resize(len);b.resize(len);
  NTT(a,len,0);
  NTT(b,len,0);
  for (int i=0;i<len;++i) smul(a[i],b[i]);
  NTT(a,len,1);
  for (int i=0;i<=n-m;++i) a[i]=a[i+m-1];
  a.resize(n-m+1);
  return a;
}

poly polynow[N+9];

void Divide_polynow(int l,int r,int k,poly &res){
  if (l==r) {res[l]=polynow[k][0];return;}
  int mid=l+r>>1,ls=k<<1,rs=k<<1|1;
  polynow[ls]=Poly_mulT(polynow[k],prod[rs]);
  polynow[rs]=Poly_mulT(polynow[k],prod[ls]);
  Divide_polynow(l,mid,ls,res);
  Divide_polynow(mid+1,r,rs,res);
}

poly Poly_val(poly a,poly x){
  int n=x.size();
  Divide_prod(x,0,n-1,1);
  poly t=prod[1];
  reverse(t.begin(),t.end());
  a=Poly_div(a,t).second;
  t=Poly_inv(prod[1]);
  t.resize(n);
  reverse(t.begin(),t.end());
  a=Poly_mul(a,t,n*2-1);
  polynow[1].resize(n);
  for (int i=0;i<n;++i) polynow[1][i]=a[i+n-1];
  a.resize(n);
  Divide_polynow(0,n-1,1,a);
  return a;
}

void Divide_inter(int l,int r,int k,poly &res){
  if (l==r) return;
  int mid=l+r>>1,ls=k<<1,rs=k<<1|1;
  Divide_inter(l,mid,ls,res);
  Divide_inter(mid+1,r,rs,res);
  poly a=poly(res.begin()+l,res.begin()+mid+1),b=poly(res.begin()+mid+1,res.begin()+r+1);
  poly c=prod[ls],d=prod[rs];
  Get_len(r-l+1);
  a.resize(len);b.resize(len);c.resize(len);d.resize(len);
  NTT(a,len,0);
  NTT(b,len,0);
  NTT(c,len,0);
  NTT(d,len,0);
  for (int i=0;i<len;++i) a[i]=add(mul(a[i],d[i]),mul(b[i],c[i]));
  NTT(a,len,1);
  for (int i=l;i<=r;++i) res[i]=a[i-l];
}

poly Poly_inter(poly x,poly y){
  int n=x.size();
  Divide_prod(x,0,n-1,1);
  poly a=prod[1];
  reverse(a.begin(),a.end());
  for (int i=1;i<=n;++i) a[i-1]=mul(i,a[i]);
  a.resize(n);
  poly t=Poly_inv(prod[1]);
  t.resize(n);
  reverse(t.begin(),t.end());
  a=Poly_mul(a,t,n*2-1);
  polynow[1].resize(n);
  for (int i=0;i<n;++i) polynow[1][i]=a[i+n-1];
  polynow[1].resize(n+1);
  a.resize(n);
  Divide_polynow(0,n-1,1,a);
  for (int i=0;i<n;++i) a[i]=mul(y[i],Get_inv(a[i]));
  Divide_inter(0,n-1,1,a);
  reverse(a.begin(),a.end());
  return a;
}

int n,m,e[M+9][M+9];

void into(){
  scanf("%d%d",&n,&m);
  for (int i=1;i<=n;++i)
	for (int j=1;j<=n;++j) e[i][j]=-1;
  for (int i=1;i<=m;++i){
	int x,y,v;
	scanf("%d%d%d",&x,&y,&v);++x;++y;
	if (x==y) continue;
	e[x][y]=e[y][x]=v;
  }
}

int rnd[M+9][M+9];

void Get_rnd(){
  for (int i=1;i<=n;++i)
	for (int j=i+1;j<=n;++j) rnd[i][j]=rnd[j][i]=Rand()%mod;
}

int mat[M+9][M+9],pwx[29];

void Get_mat(int x){
  pwx[0]=1;
  for (int i=1;i<=20;++i) pwx[i]=mul(pwx[i-1],x);
  for (int i=1;i<=n;++i){
	mat[i][i]=0;
	for (int j=i+1;j<=n;++j)
	  if (e[i][j]==-1) mat[j][i]=mat[i][j]=0;
      else{
		int t=1LL*rnd[i][j]*pwx[e[i][j]]%mod;
		mat[i][j]=t;mat[j][i]=t?mod-t:0;
	  }
  }
}

int Mat_det(){
  int res=1;
  for (int i=1;i<=n;++i){
	int r=i;
	for (;r<=n&&!mat[r][i];++r);
	if (r>n) return 0;
    if (r^i) swap(mat[r],mat[i]),res=sub(0,res);
	for (int j=i+1;j<=n;++j)
	  for (int x=mat[i][i],y=mat[j][i];y;swap(x,y),swap(mat[i],mat[j]),res=sub(0,res)){
		int t=x/y;x%=y;
		for (int k=i;k<=n;++k) ssub(mat[i][k],mul(t,mat[j][k]));
	  }
	if (!mat[i][i]) return 0;
	smul(res,mat[i][i]);
  }
  return res;
}

poly Sqrt(poly a){
  int n=a.size(),m=0;
  for (;m<n&&!a[m];++m);
  if (m>=n) return poly(n,0);
  poly res(n-m);
  for (int i=m;i<n;++i) res[i-m]=a[i];
  res.resize(n);
  res=Poly_sqrt(res);
  m>>=1;
  for (int i=n-1;i>=m;--i) res[i]=res[i-m];
  for (int i=0;i<m;++i) res[i]=0;
  return res;
}

vector<int>ans;

void Get_ans(){
  poly x(K+1),y(K+1);
  for (int i=0;i<=K;++i){
	Get_mat(x[i]=i);
	y[i]=Mat_det();
  }
  x=Sqrt(Poly_inter(x,y));
  for (int vs=x.size(),i=0;i<vs;++i)
	if (x[i]) ans.push_back(i);
}

void work(){
  Get_inv();
  Get_wn();
  Get_rnd();
  Get_ans();
}

void outo(){
  if (ans.empty()) {puts("YOU ARE IN TROUBLE");return;}
  printf("%d\n",ans.size());
  for (int vs=ans.size(),i=0;i<vs;++i)
	printf("%d ",ans[i]);
  puts("");
}

int main(){
  into();
  work();
  outo();
  return 0;
}
