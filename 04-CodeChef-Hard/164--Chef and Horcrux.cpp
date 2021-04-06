#include<bits/stdc++.h>
typedef int LL;
typedef long long ll;
#define opt operator
const LL maxn=1e7+9;
const LL mod=330301441,G=22;
LL Read(){
	LL x(0),f(1); char c=getchar();
	while(c<'0' || c>'9'){
		if(c=='-') f=-1; c=getchar();
	}
	while(c>='0' && c<='9'){
		x=(x<<3ll)+(x<<1ll)+c-'0'; c=getchar();
	}return x*f;
}
LL add(LL x,LL y){
	x+=y; return x>=mod?x-mod:x;
}
LL dec(LL x,LL y){
	x-=y; return x<0?x+mod:x;
}
LL mul(LL x,LL y){
	return 1ll*x*y%mod;
}
LL Pow(LL base,ll b){
	LL ret(1); while(b){
		if(b&1ll) ret=mul(ret,base); base=mul(base,base); b>>=1ll;
	}return ret;
}
namespace Getroot{
	void Solve(){
		static LL a[maxn];
		LL nw(mod-1),tot(0);
		for(LL i=2;i*i<=nw;++i){
			if(nw%i==0){
				a[++tot]=i;
				while(nw%i==0) nw/=i;
			}
		}
		if(nw>1) a[++tot]=nw;
		for(LL i=1;;++i){
			LL flag(1);
			for(LL j=1;j<=tot && flag;++j) flag&=(Pow(i,nw)!=1);
			if(flag){
				//printf("%lld\n",i);
				return;
			}
		}
	}
}
namespace Getmex{
	LL Solve(LL *a,LL *cnt,LL n){
		std::sort(a+1,a+1+n);
		LL pre(1);
		LL inv(Pow(2,n)); inv=Pow(inv,mod-2);
		for(LL i=0;i<=n;++i) cnt[i]=0;
		for(LL i=0,j=1;i<=n;++i){
			if(j>n || a[j]!=i){
				cnt[i]=1ll*pre*Pow(2,n-j+1)%mod*inv%mod;
				return i;
			}
			LL Tmp(j);
			while(j<n && a[j+1]==i) ++j;
			LL len(j-Tmp+1);
			//printf("%lld(%lld,%lld)\n",len,pre,Pow(2,n-j));
			cnt[i]=1ll*pre*Pow(2,n-j)%mod*inv%mod;
			pre=1ll*pre*dec(Pow(2,len),1)%mod;
			++j;
		}
		//puts("");
	}
}
namespace Fwt{
	struct Mat{
		LL n,m;
		LL a[11][11];
		Mat opt * (const Mat A){
			Mat ret; ret.n=n; ret.m=A.m;
			for(LL i=1;i<=n;++i){
				for(LL j=1;j<=A.m;++j){
					LL Tmp(0);
					for(LL k=1;k<=m;++k) Tmp=add(Tmp,mul(a[i][k],A.a[k][j]));
					ret.a[i][j]=Tmp;
				}
			}
			return ret;
		}
	};
	Mat Construct(LL K,LL op){
		Mat ret; ret.n=ret.m=K; //ret.Init(K);
		LL wn(Pow(G,(mod-1)/K));
		for(LL i=1;i<=K;++i){
			LL w(Pow(wn,i-1));
			for(LL j=1;j<=K;++j){
				ret.a[i][j]=Pow(w,j-1);
			}
		}
		if(op==-1){
			for(LL i=1;i<=K;++i){
				for(LL j=1;j<=K;++j){
					ret.a[i][j]=Pow(ret.a[i][j],mod-2);
				}
			}
		}
		return ret;
	}
	void Fwt(LL *A,LL op,LL limit,LL K){
		Mat M(Construct(K,op));
		for(LL len=1;len<limit;len*=K){
			for(LL j=0;j<limit;j+=len*K){
				for(LL k=0;k<len;++k){
					Mat Tmp; Tmp.n=1; Tmp.m=K;
					for(LL i=0;i<K;++i) Tmp.a[1][i+1]=A[j+k+i*len];
					Tmp=Tmp*M;
					for(LL i=0;i<K;++i) A[j+k+i*len]=Tmp.a[1][i+1];
				}
			}
		}
		if(op==-1){
			LL Tmp(Pow(limit,mod-2));
			for(LL i=0;i<limit;++i) A[i]=mul(A[i],Tmp);
		}
	}
	LL pow(LL *a,LL n,LL K,ll X){
		LL limit(1);
		while(limit<=n) limit*=K;
		//printf("#:");for(LL i=0;i<limit;++i) printf("%lld ",a[i]); puts("");
		//exit(0);
		for(LL i=n+1;i<limit;++i) a[i]=0;
		Fwt(a,1,limit,K);
		//printf("#:");for(LL i=0;i<=limit;++i) printf("%lld ",a[i]); puts("");
		for(LL i=0;i<limit;++i) a[i]=Pow(a[i],X);
		Fwt(a,-1,limit,K);
		//printf("#:");for(LL i=0;i<=limit;++i) printf("%lld ",a[i]); puts("");
		return limit;
	}
}
LL n,K;
ll X;
LL a[maxn],cnt[maxn],p[maxn];
void Solve(){
	n=Read(); K=Read(); //X=Read();
	scanf("%lld",&X);
	for(LL i=1;i<=n;++i) a[i]=Read();
	LL limit=Getmex::Solve(a,cnt,n);
	//printf("    ");
	//for(LL i=0;i<=n;++i) printf("%lld ",cnt[i]); puts("");
	//printf("%lld\n",n);
	LL N=Fwt::pow(cnt,limit,K,X);
	//for(LL i=0;i<=n;++i) printf("%lld ",cnt[i]); puts("");
    for(LL i=0;i<=N;++i) p[i]=cnt[i];
	LL ret(0);
	//printf("%lld\n",N);
	for(LL i=0;i<N;++i){
		LL Tmp(1ll*Pow(i,2)*Pow(p[i],3)%mod);
		//printf("%lld\n",Tmp);
		Tmp=Pow(Tmp,i);
		//printf("%lld\n",Tmp);
		ret=add(Tmp,ret);
	}
	//puts("");
	printf("%d\n",ret);
}
int main(){
	//Getroot::Solve();
	double ret1(clock());
	LL T=Read();
	while(T--){
		Solve();
	}
    double ret2(clock());
	//printf("%.10lf\n",(ret2-ret1)/CLOCKS_PER_SEC);
	return 0;
}