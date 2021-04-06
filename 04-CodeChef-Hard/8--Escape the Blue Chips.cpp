#include <bits/stdc++.h>
using namespace std;
template <typename T> void read(T &t) {
	t=0; char ch=getchar(); int f=1;
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1; ch=getchar(); }
	do { (t*=10)+=ch-'0'; ch=getchar(); } while ('0'<=ch&&ch<='9'); t*=f;
}
typedef long long ll;
const int maxn=(2e5)+10;
const int maxm=(1e7);
const int INF=maxm;
int T,n,m,K,S,head[maxn],nxt[maxn*2],to[maxn*2],tot;
void add(int x,int y) {
	tot++; nxt[tot]=head[x]; head[x]=tot; to[tot]=y;
}
pair<int,int> dp[maxn];
vector<int> event[maxn],g[maxn];
pair<int,int> rt[maxn];
int ls[maxm],rs[maxm],son[maxn];
int dep[maxn],sz[maxm],tr[maxm],val[maxm],rd[maxm];
void pushup(int root) {
	tr[root]=tr[ls[root]]+tr[rs[root]]+1;
}
int newnode(int x) {
	tot++; val[tot]=x; tr[tot]=1; ls[tot]=rs[tot]=0; rd[tot]=rand(); return tot;
}
bool find(int root,int x) {
	//printf("? %d %d %d %d\n",root,ls[root],rs[root],x);
	if (!root) return 0;
	if (val[root]==x) return 1;
	if (val[root]<x) return find(rs[root],x);
	return find(ls[root],x);
}
pair<int,int> split(int root,int x) {
	if (!root) return make_pair(0,0);
	pair<int,int> res;
	if (val[root]<x) {
		res=split(rs[root],x);
		rs[root]=res.first;
		pushup(root);
		return make_pair(root,res.second);
	}
	res=split(ls[root],x);
	ls[root]=res.second;
	pushup(root);
	return make_pair(res.first,root);
}
void insert2(int &root,int x) {
	if (!root) { root=x; return; }
	pair<int,int> res;
	if (rd[root]<=rd[x]) {
		res=split(root,val[x]);
		ls[x]=res.first,rs[x]=res.second;
		pushup(x);
		root=x;
		return;
	}
	if (val[root]<val[x]) insert2(rs[root],x);
	else insert2(ls[root],x);
	pushup(root);
}

void insert(int &root,int x) {
	if (find(root,x)) {
	//	puts("find");
		return;
	}
//	puts("OK");
	insert2(root,newnode(x));
	//puts("OK");
}
void dfs(int root,vector<int> &res) {
	if (!root) return;
	dfs(ls[root],res);
	res.push_back(val[root]);
	dfs(rs[root],res);
}
int small(int root,int x) {
	if (!root) return 0;
	if (val[root]>x) return small(ls[root],x);
	return small(rs[root],x)+1+tr[ls[root]];
}
int big(int root,int x) {
	if (!root) return 0;
	if (val[root]<x) return big(rs[root],x);
	return big(ls[root],x)+1+tr[rs[root]];
}
int ycl;
void dfs(int u,int p) {
	bool leaf=1; sz[u]=1; son[u]=0; int mid;
	for (int i=head[u],v;i;i=nxt[i]) {
		v=to[i]; if (v==p) continue;
		leaf=0;
		dep[v]=dep[u]+1;
		dfs(v,u); sz[u]+=sz[v];
		if (!son[u]||sz[v]>sz[son[u]]) son[u]=v;
		dp[u].second=min(dp[u].second,dp[v].second+K);
	}
	if (leaf) {
		for (int t : g[u]) {
		//	printf("HI %d %d\n",t,rt[u].first);
			insert(rt[u].first,t);
			insert(rt[u].second,t),insert(rt[u].second,t+2);
		}
		int l=-dep[u],r=INF,mid;
		ycl=tr[rt[u].first]-small(rt[u].first,-1-dep[u]);
		while (l<r-1) {
			mid=(l+r)>>1;
			if (ycl-big(rt[u].first,mid)!=mid+dep[u]) r=mid;
			else l=mid;
		}
		dp[u]=make_pair(dep[u]+l,dep[u]+l);
		//printf("?? %d %d\n",rt[u].first,rt[u].second);
		//printf("%d %d %d\n",u,dp[u].first,dp[u].second);
        return;
	}
	vector<int> all;
	for (int i=head[u],v;i;i=nxt[i]) {
		v=to[i];
		if (v==p||v==son[u]) continue;
		dfs(rt[v].first,all);
	}
	all.push_back(INF),all.push_back(-INF);
	sort(all.begin(),all.end());
	all.resize(unique(all.begin(),all.end())-all.begin());
	///printf("all : "); for (int x :all) printf("%d ",x); puts("");
	for (int i=0;i<(int)all.size()-1;i++) {
        if (all[i+1]<=dp[son[u]].first-dep[u]) continue;
		int L=max(dp[son[u]].first-dep[u],all[i]),R=all[i+1];
		if (L>R) continue;
		ycl=tr[rt[son[u]].second]-small(rt[son[u]].second,L);
		if (ycl-big(rt[son[u]].second,R)!=R-L-1) {
			int l=L,r=R;
			while (l<r-1) {
				mid=(l+r)>>1;
				if (ycl-big(rt[son[u]].second,mid)!=mid-L-1) r=mid;
				else l=mid;
			}
			//printf("%d %d , %d %d\n",L,R,l,tr[rt[son[u]].second]);
			dp[u].first=min(dp[u].first,l+dep[u]);
			break;
		}
	}
    rt[u]=rt[son[u]];
   // printf("?? %d %d\n",dp[u].first,dp[u].second);
    for (int t : all) {
    	insert(rt[u].first,t);
    //	printf("?? %d %d\n",rt[u].first,rt[u].second);
    	insert(rt[u].second,t),insert(rt[u].second,t+2);
    }
    for (int i=head[u],v;i;i=nxt[i]) {
		v=to[i]; if (v==p||v==son[u]) continue;
		vector<int> now; now.push_back(-INF);
		dfs(rt[v].first,now); now.push_back(INF);
        //for (int x : now) printf("%d ",x); puts("");
		for (int j=0;j<(int)now.size()-1;j++) {
			if (now[j+1]+2<=dp[v].first-dep[u]) continue;
			int L=max(now[j]+2,dp[v].first-dep[u]),R=now[j+1]+2;
			ycl=tr[rt[u].first]-small(rt[u].first,L);
			if (ycl-big(rt[u].first,R)!=R-L-1) {
				int l=L,r=R;
				while (l<r-1) {
					mid=(l+r)>>1;
					if (ycl-big(rt[u].first,mid)!=mid-L-1) r=mid;
					else l=mid;
				}
				dp[u].first=min(dp[u].first,l+dep[u]);
				break;
			}
		}
	}
	//printf("%d %d %d\n",u,dp[u].first,dp[u].second);
	int l=dp[u].second-dep[u],r=dp[u].first+2-dep[u];
	ycl=tr[rt[u].first]-small(rt[u].first,dp[u].second-dep[u]-1);
	//printf("%d %d\n",l,r);
	while (l<r-1) {
		mid=(l+r)>>1;
		if (ycl-big(rt[u].first,mid)!=mid-dp[u].second+dep[u]) r=mid;
		else l=mid;
	}
	dp[u].first=min(dp[u].first,l+dep[u]);
	dp[u].second=min(dp[u].second,dp[u].first);
//	printf("%d %d %d\n",u,dp[u].first,dp[u].second);
}

int main() {
	//freopen("1.txt","r",stdin);
	read(T);
	while (T--) {
		read(n),read(m),read(K),read(S);
		tot=0;
		for (int i=1;i<=n;i++) {
			head[i]=0;
			dp[i]=make_pair(INF,INF);
			rt[i]=make_pair(0,0);
			g[i].clear();
		}
		int x,y;
		for (int i=1;i<n;i++) {
			read(x),read(y);
			add(x,y),add(y,x);
		}
		tot=0;
		while (m--) {
			read(y),read(x);
			y-=S;
			if (y<-3*n||y>3*n) continue;
			g[x].push_back(y);
		}
		dfs(1,0);
		printf("%d\n",dp[1].first+S);
	}
	return 0;
}
/*
  0. Enough array size? Enough array size? Enough array size? Integer overflow?
  
  1. Think TWICE, Code ONCE!
  Are there any counterexamples to your algo?
    
  2. Be careful about the BOUNDARIES!
  N=1? P=1? Something about 0?
    
  3. Do not make STUPID MISTAKES!
  Time complexity? Memory usage? Precision error?
*/
