#include<iostream>
#include<cstdio>
#pragma GCC optimize(2)

#define fo(i,j,l) for(int i=j;i<=l;++i)
#define fd(i,j,l) for(int i=j;i>=l;--i)

using namespace std;
typedef long long ll;
const ll N=32e5,K=1500000,mo=1e9+7;

ll s1[N],s2[N];
int bh[N],phi[N];
int ss[N];
bool bz[N];
int zh,oo,yu;
ll A,B,n;
int t;

inline void prepare()
{
	phi[1]=1;
	fo(i,2,K){
		if(!bz[i])ss[++oo]=i,phi[i]=i-1;
		fo(j,1,oo)if(i*ss[j]<=K){
			bz[i*ss[j]]=true;
			phi[i*ss[j]]=phi[i]*(ss[j]-1);
			if(i%ss[j]==0){
				phi[i*ss[j]]=phi[i]*ss[j];
				break;
			}
		} else break;
	}
	fo(i,1,K)s1[i]=(s1[i-1]+phi[i])%mo;
	fo(i,1,K)s1[i]=(s1[i]*2+mo-1)%mo;
}

inline ll ksm(ll o,ll t)
{
	ll y=1;
	for(;t;t>>=1,o=o*o%mo)
	if(t&1)y=y*o%mo;
	return y;
}

inline ll get(ll s,ll d1,ll d2)
{return (s==1)?(d2-d1+1):(ksm(s,d2+1)-ksm(s,d1)+mo)%mo*(ksm(s-1,mo-2))%mo;}

inline ll get(int n)
{
	if(n<=K)return s1[n];
	if(bh[zh/n]==yu)return s2[zh/n];
	int l=2;
	ll ans=0;
	while(l<=n){
		int k=n/l,r=(n/k);
		ans=(ans+get(k)*(ll)(r-l+1)%mo)%mo;
		l=r+1;
	}
	ans=((ll)n*n-ans)%mo;
	bh[zh/n]=yu; s2[zh/n]=ans;
	return ans;
}

int main()
{
	prepare();
	cin>>t;
	fo(tt,1,t){
		scanf("%lld%lld%lld",&A,&B,&n);
		zh=n; ll ans=0; yu=tt;
		for(int l=1;l<=n;){
			int k=n/l,r=n/k;
			ans=(ans+get(k)*(get(A,l,r)-get(B,l,r)+mo))%mo;
			l=r+1;
		}
		printf("%lld\n",ans);
	}
}