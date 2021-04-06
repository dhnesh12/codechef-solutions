#include <bits/stdc++.h>
using namespace std;
#define mod 998244353
#define MOD 1000000007
#define inf 0x3f3f3f3f
#define linf 0x3f3f3f3f3f3f3f3fll
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
const int maxn=1100;
const int maxm=10100;
struct Edge
{
	int to,cap,rev,cst;
	Edge(){}
	Edge(int to,int cap,int rev,int cst):to(to),cap(cap),rev(rev),cst(cst){}
};
vector<Edge> g[maxn];
inline void addedge(int a,int b,int c,int d)
{
	g[a].push_back(Edge(b,c,g[b].size(),d));
	g[b].push_back(Edge(a,0,g[a].size()-1,-d));
}
int recans[maxn],lvl[maxn],h[maxn],prevv[maxn],preve[maxn];
void dij(int x)
{
	priority_queue<pii,vector<pii>,greater<pii> > pq;
	memset(lvl,0x3f,sizeof(lvl));
	lvl[x]=0;
	pq.push(make_pair(0,x));
	while(!pq.empty())
	{
		pii cur=pq.top();
		pq.pop();
		x=cur.second;
		if(lvl[x]<cur.first)continue;
		for(int i=0;i<g[x].size();i++)
		{
			Edge &e=g[x][i];
			if(e.cap>0&&lvl[e.to]>lvl[x]+e.cst+h[x]-h[e.to])
			{
				lvl[e.to]=lvl[x]+e.cst+h[x]-h[e.to];
				prevv[e.to]=x;
				preve[e.to]=i;
				pq.push(make_pair(lvl[e.to],e.to));
			}
		}
	}
}
void mincostflow(int s,int t)
{
	int res=0,flow=0;
	for(;;)
	{
		flow++;
		dij(s);
		if(lvl[t]==inf)return;
		for(int i=1;i<=t;i++)h[i]+=lvl[i];
		int f=1;
		for(int i=t;i!=s;i=prevv[i])
		{
			f=min(f,g[prevv[i]][preve[i]].cap);
		}
		res+=f*h[t];
		for(int i=t;i!=s;i=prevv[i])
		{
			Edge &e=g[prevv[i]][preve[i]];
			e.cap-=f;
			g[e.to][e.rev].cap+=f;
		}
		recans[flow]=res;
	}
}
int n,m,q,s,t;
int dist[255][255];
int main()
{
	scanf("%d%d%d",&n,&m,&q);
	memset(dist,0x3f,sizeof(dist));
	for(int i=0;i<m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		dist[a][b]=min(dist[a][b],c);
	}
	for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)if(dist[i][k]<inf)for(int j=1;j<=n;j++)if(i!=j&&dist[k][j])
		dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
	s=n+n+1,t=s+1;
	for(int i=1;i<=n;i++)
	{
		addedge(s,i,1,0);
		addedge(i+n,t,1,0);
		for(int j=1;j<=n;j++)if(dist[i][j]<inf)addedge(i,j+n,1,dist[i][j]);
	}
	memset(recans,0x3f,sizeof(recans));
	mincostflow(s,t);
	while(q--)
	{
		int cc;
		scanf("%d",&cc);
		int res=n*cc;
		for(int i=1;i<=n;i++)if(recans[i]<inf)res=min(res,recans[i]+(n-i)*cc);
		printf("%d\n",res);
	}
	return 0;
}