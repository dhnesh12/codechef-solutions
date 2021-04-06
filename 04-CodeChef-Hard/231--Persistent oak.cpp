#include<bits/stdc++.h>
#define N 100050
using namespace std;
int n,m;
int fa[N],w[N];
int he[N],ne[N],to[N],bs;
inline void addedge(int x,int y){to[++bs]=y;ne[bs]=he[x];he[x]=bs;}
int L[N],R[N],pos[N],cnt;
int sz[N],hs[N],tp[N];
inline void dfs1(int g){
	sz[g]=1;hs[g]=N-1;
	for(int i=he[g];i;i=ne[i]){
		dfs1(to[i]);sz[to[i]]+=sz[g];
		if(sz[to[i]]>sz[hs[g]])hs[g]=to[i];
	}
}
inline void dfs2(int g,int t){
	L[g]=++cnt;pos[cnt]=g;
	tp[g]=t;
	if(hs[g]!=N-1)dfs2(hs[g],t);
	for(int i=he[g];i;i=ne[i])
		if(to[i]!=hs[g])dfs2(to[i],to[i]);
	R[g]=cnt;
}

//////segment
unordered_map<int,int>h[N];
int rt[N],lc[N*1000],rc[N*1000],sum[N*1000],tag[N*1000],mi[N*1000],tot,las;
inline int newd(int x){
	++tot;tag[tot]=tag[x];
	lc[tot]=lc[x];rc[tot]=rc[x];
	sum[tot]=sum[x];mi[tot]=mi[x];
	return tot;
}
inline void upd(int g){
	sum[g]=sum[lc[g]]+sum[rc[g]];
	mi[g]=min(mi[lc[g]],mi[rc[g]])-tag[g];
}
inline void build(int &g,int l,int r){
	h[l][r]=g=newd(0);
	if(l==r){mi[g]=w[pos[l]];return;}
	const int m=l+r>>1;
	build(lc[g],l,m);build(rc[g],m+1,r);
	upd(g);
}

inline void add(int &g,int l,int r,int pos,int v){
	if(g<=las)g=newd(g);
	if(l==r){sum[g]+=v;return;}
	const int m=l+r>>1;
	if(pos<=m)add(lc[g],l,m,pos,v);
	else add(rc[g],m+1,r,pos,v);
	upd(g);
}
inline void addtag(int &g,int l,int r,int x,int y,int t){
	if(l>y||r<x)return;
	if(g<=las)g=newd(g);
	if(l>=x&&r<=y){
//		printf("addtag:g:%d l:%d r:%d t:%d\n",g,l,r,t);
		tag[g]+=t;mi[g]-=t;return;}
	const int m=l+r>>1;
	addtag(lc[g],l,m,x,y,t);addtag(rc[g],m+1,r,x,y,t);
	upd(g);
}
inline int ask(int g,int l,int r,int x,int y,int val){
	if(l>y||r<x||mi[g]-val>=0)return 0;
	if(l==r)return pos[l];
	const int m=l+r>>1;
	int ret=ask(rc[g],m+1,r,x,y,val+tag[g]);
	if(ret)return ret;
	return ask(lc[g],l,m,x,y,val+tag[g]);
}
inline void down(int g){
	if(lc[g]<=las)lc[g]=newd(lc[g]);
	if(rc[g]<=las)rc[g]=newd(rc[g]);
	tag[lc[g]]+=tag[g];tag[rc[g]]+=tag[g];
	mi[lc[g]]-=tag[g];mi[rc[g]]-=tag[g];
	tag[g]=0;
}
inline int del(int &g,int l,int r,int x,int y){
	if(l>y||r<x)return 0;
	if(g<=las)g=newd(g);
	int ret=0;
	if(l>=x&&r<=y){ret=sum[g];g=h[l][r];return ret;}
	if(tag[g])down(g);
	const int m=l+r>>1;
	ret+=del(lc[g],l,m,x,y);
	ret+=del(rc[g],m+1,r,x,y);
	upd(g);return ret;
}
////

inline void add(int id,int x,int val){
	add(rt[id],1,cnt,L[x],val);
	while(1){
		addtag(rt[id],1,cnt,L[tp[x]],L[x],val);
		if(!tp[x])break;x=fa[tp[x]];
	}
}
inline int check(int id,int x){
	int ret=0;
	while(!ret){
		ret=ask(rt[id],1,cnt,L[tp[x]],L[x],0);
		if(!tp[x])break;x=fa[tp[x]];
	}
	if(ret){
		x=ret;
		int val=del(rt[id],1,cnt,L[x],R[x]);
		x=fa[x];
		while(1){
			addtag(rt[id],1,cnt,L[tp[x]],L[x],-val);
			if(!tp[x])break;x=fa[tp[x]];
		}
	}
	return ret;
}
inline void work(){
	scanf("%d%d",&n,&m);
	w[0]=0;
	for(int i=1;i<=n;++i){
		scanf("%d%d",&fa[i],&w[i]);
		addedge(fa[i],i);
	}
	dfs1(0);dfs2(0,0);
	build(rt[0],1,cnt);
	for(int i=1,f,op,u,x;i<=m;++i){
		scanf("%d%d%d",&f,&op,&u);
		las=tot;rt[i]=rt[f];
		if(op==1){
			scanf("%d",&x);
			add(i,u,x);
			printf("%d\n",check(i,u));
		}
		else{
			int ans=del(rt[i],1,cnt,L[u],R[u]);
			u=fa[u];
			while(1){
				addtag(rt[i],1,cnt,L[tp[u]],L[u],-ans);
				if(!tp[u])break;u=fa[tp[u]];
			}
			printf("%d\n",ans);
		}
	}
	tot=rt[0]=cnt=bs=0;
	for(int i=1;i<=cnt;++i)h[i].clear();
	memset(he,0,sizeof(int)*(n+1));
}
int main(){
	int T;cin>>T;while(T--)work();
}