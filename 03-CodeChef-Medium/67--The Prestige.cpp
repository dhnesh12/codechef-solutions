#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7,maxn=1e6+10;
typedef pair<int,int> pii;
int T,L,R,n,pri[maxn],anses[maxn],vs[maxn],psz,f[maxn],c[maxn];
vector<pii> G[maxn];
int tr[maxn];
int qpow(int a,int b){
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%mod)
		if(b&1)ans=1ll*ans*a%mod;
	return ans;
}
void add(int x,int y){
	for(;x<=n;x+=x&-x)tr[x]=1ll*tr[x]*y%mod;
}
int qry(int x){
	int ans=1;
	for(;x;x-=x&-x)ans=1ll*ans*tr[x]%mod;
	return ans;
}
int main(){
	scanf("%d",&T),n=1e6;
//	scanf("%d%d",&T,&n);
	for(int i=2;i<=n;++i)if(!vs[i]){
		pri[++psz]=i;
		for(int j=i;j<=n;j+=i)
			c[j]=i,vs[j]=1;
	}
	for(int i=1,N,S;i<=T;++i){
		scanf("%d%d",&N,&S);
		R=N,L=N-S+1;
		G[R].push_back(pii(L,i));
		G[L-1].push_back(pii(L,-i));
		anses[i]=1;
	}
	for(int i=0;i<=n;++i)tr[i]=1;
	for(int i=1;i<=n;++i){
		int ni=i;
		while(ni!=1){
			int p=c[ni],cnt=0;
			while(ni%p==0)ni/=p,cnt++;
			for(int j=1,pp=p;j<=cnt;++j,pp*=p){
				add(max(i-pp,1),p);
			}
		}
		for(auto a:G[i]){
			if(a.second>0)anses[a.second]=1ll*anses[a.second]*qry(a.first-1)%mod;
			else anses[-a.second]=1ll*anses[-a.second]*qpow(qry(a.first-1),mod-2)%mod;
		}
	}
	for(int i=1;i<=T;++i)printf("%d\n",(anses[i]-1+mod)%mod);
}