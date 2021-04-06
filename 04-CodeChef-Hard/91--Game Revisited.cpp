#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<bitset>
#include<string>
#include<cstdio>
#include<cctype>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<sstream>
#include<numeric>
#include<iostream>
#include<algorithm>
#include<functional>

#define For(i,x,y) for (int i=x;i<y;i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lf else if

#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

typedef long long ll;
typedef double db;
typedef vector<int> Vi;
typedef pair<int,int> pii;

int IN(){
	int c,f,x;
	while (!isdigit(c=getchar())&&c!='-');c=='-'?(f=1,x=0):(f=0,x=c-'0');
	while (isdigit(c=getchar())) x=(x<<1)+(x<<3)+c-'0';return !f?x:-x;
}

const int N=400000+19;

int key[N];

struct QType{
	int x,y;
} Q[N];

struct Edge{
	int x,y,id;
	bool operator < (const Edge &B) const{
		return key[id]<key[B.id];
	}
};

struct Graph{
	Edge E[N];
} G[20];

int fa[N],id[N],vis[N],chk[N],tmp[N];
int n,m,q,x,y,c,Time,Time2;

int getf(int x){
	return fa[x]==x?x:fa[x]=getf(fa[x]);
}
bool Union(int x,int y){
	x=getf(x),y=getf(y);
	if (x!=y) return fa[x]=y,1;
	return 0;
}

void Work(int dep,int n,int m,int l,int r,int res){
	Graph &G=::G[dep];
	For(i,1,m+1) G.E[i]=::G[dep-1].E[i];
	if (l==r){
		key[Q[l].x]=Q[l].y;
		if (l%2==1) return;
		sort(G.E+1,G.E+m+1);
		For(i,1,n+1) fa[i]=i;
		For(i,1,m+1){
			if (Union(G.E[i].x,G.E[i].y)) res=max(res,key[G.E[i].id]);
		}
		printf("%d\n",res);
		return;
	}
	Time++;
	For(i,l,r+1) vis[Q[i].x]=Time;
	//Reduction
	int m2=0;
	sort(G.E+1,G.E+m+1);
	For(i,1,n+1) fa[i]=i;
	For(i,1,m+1){
		if (vis[G.E[i].id]==Time||Union(G.E[i].x,G.E[i].y)) G.E[++m2]=G.E[i];
	}
	m=m2;
	//Contraction
	For(i,1,n+1) fa[i]=i;
	For(i,1,m+1){
		if (vis[G.E[i].id]==Time) Union(G.E[i].x,G.E[i].y);
	}
	Time2++;
	For(i,1,m+1){
		if (vis[G.E[i].id]!=Time&&Union(G.E[i].x,G.E[i].y)) chk[G.E[i].id]=Time2;
	}
	For(i,1,n+1) fa[i]=i;
	For(i,1,m+1){
		if (chk[G.E[i].id]==Time2){
			Union(G.E[i].x,G.E[i].y);
			res=max(res,key[G.E[i].id]);
		}
	}
	//...
	int n2=0;m2=0;
	For(i,1,n+1) if (fa[i]==i) tmp[i]=++n2;
	For(i,1,m+1){
		int x=getf(G.E[i].x),y=getf(G.E[i].y);
		if (x!=y) G.E[++m2]=(Edge){tmp[x],tmp[y],G.E[i].id};
	}
	int mid=(l+r)/2;
	Work(dep+1,n2,m2,l,mid,res);
	Work(dep+1,n2,m2,mid+1,r,res);
}

void Main(){
	n=IN(),m=IN(),q=IN();
	For(i,1,m+1) key[i]=i;
	For(i,1,m+1){
		G[0].E[i]=(Edge){IN(),IN(),i};
		id[i]=i;
	}
	c=0;
	For(i,1,q+1){
		x=IN(),y=IN();
		Q[++c]=(QType){id[x],y};
		Q[++c]=(QType){id[y],x};
		swap(id[x],id[y]);
	}
	Work(1,n,m,1,c,0);
}

int main(){
	for (int T=IN();T--;) Main();
}