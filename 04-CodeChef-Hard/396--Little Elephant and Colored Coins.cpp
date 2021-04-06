#include<bits/stdc++.h>
#define ll long long
#define re register
#define ull unsigned ll
using namespace std;
inline ll read(){
	ll s=0,t=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')t=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*t;
}
const int M=31;
const int N=2e5+5;
int n,m,P,id,w[M],c[M],q[N],vis[N];
ll f[M][N],g[M][N];
vector<int> G[M];
unordered_map<int,int> mp;
void Upd(ll &x,ll y){x>y?x=y:0;}
void Solve(int n,int v){
	for(int i=0;i<n;i++)
	for(int r=0;r<P;r++)Upd(g[i+1][(r+v)%P],f[i][r]+v);
	memset(vis,0,sizeof(vis));
	for(int r=0;r<P;r++)if(!vis[r]){
		int top=0,t=r;
		while(!vis[t])vis[t]=1,q[++top]=t,t=(t+v)%P;
		for(int i=1;i<=n;i++){
			ll tp=9e18;int p=0;
			for(int j=1;j<=top;j++)if(g[i][q[j]]<tp)tp=g[i][q[j]],p=j;
			for(int j=p,k=0;;j=k){
				k=j%top+1,Upd(g[i][q[k]],g[i][q[j]]+v);
				if(k==p)break;
			}
		}
	}
}
int main(){
//	freopen("coin32.in","r",stdin);
//	freopen("data.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		w[i]=read(),c[i]=read();
		if(!mp[c[i]])mp[c[i]]=++m;
		c[i]=mp[c[i]];
	}
	P=2e9;for(int i=1;i<=n;i++)if(w[i]<P)P=w[i],id=c[i];
	for(int i=1;i<=n;i++){
		if(c[i]==id)c[i]=m;
		else if(c[i]==m)c[i]=id;
		G[c[i]].push_back(w[i]);
	}
	memset(f,0x3f,sizeof(f)),f[0][0]=0;
	for(int i=1;i<=m;i++){
		memset(g,0x3f,sizeof(g));
		sort(G[i].begin(),G[i].end());
		for(int j=(i==m);j<G[i].size();j++)Solve(i,G[i][j]);
		if(i<m){
			for(int j=0;j<=i;j++)
			for(int r=0;r<P;r++)Upd(f[j][r],g[j][r]);
		}
	}
	for(int T=read();T;T--){
		ll S=read();int res=-1;
		for(int i=m;i>=0;i--){
			if(g[i][S%P]<=S)res=max(res,i);
			
			if(f[i][S%P]==S)res=max(res,i);
			else if(f[i][S%P]<S)res=max(res,i+1);
		}printf("%d\n",res);
	}
	return 0;
}