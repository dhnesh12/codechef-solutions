#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 2005
#define ll long long
int T,n,a[N][N],fa[N],siz[N];
ll ans,tot;
struct Node
{
	int x,y;
	Node(){}
	Node(int _x,int _y){
		x=_x,y=_y;
	}
}v[N*N];
int Getbel(int x){return fa[x]==x?x:fa[x]=Getbel(fa[x]);}
bool cmp(Node x,Node y){return a[x.x][x.y]>a[y.x][y.y];}
int main(){
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++){
				scanf("%d",&a[i][j]);
				v[(i-1)*n+j]=Node(i,j);
			}
		sort(v+1,v+n*n+1,cmp);
		for (int i=1;i<=n;i++)
			fa[i]=i,siz[i]=1;
		ans=tot=0;
		for (int i=1;i<=n*n;i++){
			int x=Getbel(v[i].x),y=Getbel(v[i].y);
			if (x==y)
				continue;
			ans+=1ll*a[v[i].x][v[i].y]*siz[x]*siz[y];
			siz[x]+=siz[y],fa[y]=x;
		}
		ans*=2;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				ans-=a[i][j];
		printf("%lld\n",ans);
	}
}
