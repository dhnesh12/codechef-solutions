#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,mo=998244353;
inline void red(int&x){x+=x>>31&mo;}
inline void div2(int&x){x&1?x+=mo:0;x>>=1;}
int T,l,r,ass,a,b,i,j,k,s0[N],s1[N],s2[N],s3[N],s4[N],ans[N],bl;
int fac[N],inv[N],vf[N];
inline int C(int x,int y){return x<y?0:1ll*vf[y]*vf[x-y]%mo*fac[x]%mo;}
struct que{
	int x,y,i,k;
	inline bool operator<(const que&rhs)const{
		int a=x/bl,b=rhs.x/bl;
		return a==b?(a&1?y<rhs.y:y>rhs.y):a<b;
	}
}qu[N*10];int qcnt;
inline void addque(int x,int l,int r,int i,int k){
	r=min(r,x);if(l>r)return;
	qu[++qcnt]=que{x,r,i,k};if(l)qu[++qcnt]=que{x,l-1,i,mo-k};
}
int main(){
	for(i=*vf=*fac=1;i<N;++i)fac[i]=1ll*fac[i-1]*i%mo,
		inv[i]=i==1?1:1ll*(mo-mo/i)*inv[mo%i]%mo,vf[i]=1ll*vf[i-1]*inv[i]%mo;
	for(i=2;i<N;++i)if(!s0[i])for(k=1;1ll*k*i<N;)for(k*=i,j=k;j<N;j+=k)++s0[j];
	for(i=1;i<N;++i){
		for(j=i;!(j&1);j>>=1)--s0[i];
		s1[i]=s1[i-1]+bool(i&1);
		s2[i]=s2[i-1]+bool(i&3);
		s3[i]=s3[i-1]+s0[i];
		s4[i]=s4[i-1]+(i&1?s0[i]:0);
	}
	scanf("%d",&T);
	for(i=1;i<=T;++i){
		scanf("%d%d%d%d",&l,&r,&a,&b);
		addque(r-l,a-1,b-1,i,2*(s3[r]-s3[l-1]));
		addque(s1[r]-s1[l-1]-1,a-1,b-1,i,mo-(s4[r]-s4[l-1]));
		addque(r-l+1,a,b,i,3);
		addque(s1[r]-s1[l-1],a-1,b-1,i,mo-(s2[r]-s2[l-1]-(s1[r]-s1[l-1])));
		addque(s1[r]-s1[l-1],a,b,i,mo-2);
	}
	l=r=0;ass=1;bl=N/sqrt(qcnt);sort(qu+1,qu+qcnt+1);
	for(i=1;i<=qcnt;++i){
		for(;r>qu[i].y;)red(ass-=C(l,r--));
		for(;l<qu[i].x;)red(ass=(ass<<1)-mo),red(ass-=C(l++,r));
		for(;r<qu[i].y;)red(ass+=C(l,++r)-mo);
		for(;l>qu[i].x;)red(ass+=C(--l,r)-mo),div2(ass);
		ans[qu[i].i]=(ans[qu[i].i]+1ll*qu[i].k*ass)%mo;
	}
	for(i=1;i<=T;++i)printf("%d\n",ans[i]);
}