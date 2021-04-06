#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>
#include <stack>
#include <iomanip>
using namespace std;
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
typedef double ld;
typedef vector<int> vi;
#define fi first
#define se second
#define fe first
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define Edg int M=0,fst[SZ],vb[SZ],nxt[SZ];void ad_de(int a,int b){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;}void adde(int a,int b){ad_de(a,b);ad_de(b,a);}
#define Edgc int M=0,fst[SZ],vb[SZ],nxt[SZ],vc[SZ];void ad_de(int a,int b,int c){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;vc[M]=c;}void adde(int a,int b,int c){ad_de(a,b,c);ad_de(b,a,c);}
#define es(x,e) (int e=fst[x];e;e=nxt[e])
#define esb(x,e,b) (int e=fst[x],b=vb[e];e;e=nxt[e],b=vb[e])
#define SZ 666666
int n,m,c1[SZ],c2[SZ]; Edgc
bool te[SZ];
void dfs(int x)
{
	for esb(x,e,b) if(c1[b]==-1)
		te[vc[e]]=1,c1[b]=!c1[x],dfs(b);
}
int fa[SZ],t1,t2;
void dfs2(int x)
{
	for esb(x,e,b)
	if(!te[vc[e]])
	{
		if(c2[b]==-1)
			fa[b]=x,c2[b]=!c2[x],dfs2(b);
		else if(c2[b]==c2[x])
		{
			t1=x; t2=b; throw 1;
		}
	}
}
int main()
{
	int T; scanf("%d",&T);
	while(T--)
	{
	scanf("%d%d",&n,&m); M=0;
	for(int i=1;i<=n;++i) fst[i]=0;
	for(int i=1,a,b;i<=m;++i)
		scanf("%d%d",&a,&b),te[i]=0,adde(a,b,i);
	for(int i=1;i<=n;++i) c1[i]=c2[i]=-1;
	c1[1]=0; dfs(1);
	for(int i=1;i<=n;++i)
		if(c1[i]==-1) throw "not connected";
	try
	{
	for(int i=1;i<=n;++i) if(c2[i]==-1)
		c2[i]=0, dfs2(i);
	}
	catch(int)
	{
		vector<int> v;
		for(int x=t1;x!=t2;x=fa[x])
			v.pb(x); v.pb(t2);
		printf("2\n%d",int(v.size()));
		for(unsigned _=0;_<v.size();++_)
			printf(" %d",v[_]);
		puts("");
		continue;
	}
	printf("1\n");
	for(int i=1;i<=n;++i)
		printf("%d ",c1[i]*2+c2[i]+1);
	puts("");
	}
}
