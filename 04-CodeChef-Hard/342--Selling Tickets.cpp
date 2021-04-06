#include<bits/stdc++.h>
using namespace std;
const int N=210;

int gi() {
	int x=0,o=1;char ch=getchar();
	while(!isdigit(ch)&&ch!='-') ch=getchar();
	if(ch=='-') o=-1,ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return x*o;
}

int n,m,ans,dis[N],fa[N];
vector<int> E[N];

void solve1(int s,int t) {
	memset(dis,0x3f,sizeof(dis));
	queue<int> q;q.push(s);dis[s]=0;
	int rem=3,sum=0;
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(auto v:E[u]) {
			if(v==t) {
				sum+=dis[u]+1;
				if(!(--rem)) { ans=min(ans,sum);return; }
			}
			else {
				if(dis[v]>1e9) dis[v]=dis[u]+1,q.push(v);
			}
		}
	}
}

int lca(int u,int v) {
	while(u!=v) {
		if(dis[u]<dis[v]) swap(u,v);
		u=fa[u];
	}
	return u;
}

void solve2(int s) {
	memset(dis,0x3f,sizeof(dis));
	queue<int> q;q.push(s);dis[s]=fa[s]=0;
	int mn1=1e9,mn2=1e9;
	while(!q.empty()) {
		int u=q.front();q.pop();
		for(auto v:E[u]) {
			if(dis[v]>1e9) dis[v]=dis[u]+1,fa[v]=u,q.push(v);
			else if(dis[v]>dis[u]||(dis[v]==dis[u]&&u<v)) {
				int w=dis[u]+dis[v]-dis[lca(u,v)]+1;
				if(w<mn1) mn2=mn1,mn1=w;
				else mn2=min(mn2,w);
			}
		}
	}
	ans=min(ans,mn1+mn2);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int T=gi();
	while(T--) {
		cin>>n>>m;
		for(int i=1;i<=n;i++) E[i].clear();
		for(int i=1,u,v;i<=m;i++) u=gi(),v=gi(),E[u].push_back(v),E[v].push_back(u);
		ans=m+1;
		for(int i=1;i<=n;i++) {
			solve2(i);
			for(int j=i+1;j<=n;j++) solve1(i,j);
		}
		cout<<ans-1<<'\n';
	}
	return 0;
}
