#include<bits/stdc++.h>
using namespace std;
const int N=2510;
typedef vector<int> vi;
#define pb push_back
#define sz(a) int(a.size())

mt19937 rng(20020415);
vi E[N];
int vis[N],tim,n,m,tt,mat[N],fa[N],dx[8]={-1,-1,-1,0,0,1,1,1},dy[8]={-1,0,1,-1,1,-1,0,1},id[55][55],new_id[N];
char str[55][55];

bool dfs(int u) {
	shuffle(E[u].begin(),E[u].end(),rng);
	vis[u]=tim;
	for(auto v:E[u]) {
		int w=mat[v];
		if(vis[w]==tim) continue;
		mat[u]=v;mat[v]=u;mat[w]=0;
		if(!w||dfs(w)) return 1;
		mat[u]=0;mat[v]=w;mat[w]=v;
	}
	return 0;
}

void adde(int u,int v) {
	E[u].pb(v);E[v].pb(u);
}

int getf(int x) {
	return x==fa[x]?x:fa[x]=getf(fa[x]);
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	ios::sync_with_stdio(0);cin.tie(0);
	int T;cin>>T;
	while(T--) {
		for(int i=0;i<N;i++) E[i].clear();
		memset(id,0,sizeof(id));
		memset(vis,0,sizeof(vis));
		memset(mat,0,sizeof(mat));
		tim=tt=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>(str[i]+1);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++) {
				if(str[i][j]!='.') continue;
				bool fl=1;
				for(int d=0;d<8;d++) {
					int x=i+dx[d],y=j+dy[d];
					if(1<=x&&x<=n&&1<=y&&y<=m&&str[x][y]!='.') { fl=0;break; }
				}
				if(fl) id[i][j]=++tt,fa[tt]=tt;
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(id[i][j]) 
					for(int d=0;d<8;d++) {
						int x=i+dx[d],y=j+dy[d];
						if(id[x][y]) fa[getf(id[i][j])]=getf(id[x][y]);
					}
		int cnt=0;
		for(int i=1;i<=tt;i++)
			if(getf(i)==i) new_id[i]=++cnt;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(id[i][j]) id[i][j]=new_id[getf(id[i][j])];
		tt=cnt;
		int ans=tt;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(!id[i][j]) {
					set<int> s;
					for(int d=0;d<8;d++) {
						int x=i+dx[d],y=j+dy[d];
						if(id[x][y]) s.insert(id[x][y]);
					}
					if(s.empty()) ++ans;
					else if(sz(s)==2) adde(*s.begin(),*s.rbegin());
				}
		for(int T=1;T<=5;T++) {
			memset(vis,0,sizeof(vis));
			for(int i=1;i<=tt;i++)
				if(!mat[i]) tim=i,ans-=dfs(i);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
