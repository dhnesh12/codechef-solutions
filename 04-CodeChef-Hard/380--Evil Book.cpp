#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;
typedef double DB;
const double eps=1e-10;
int n,X,C[10],M[10];
bool used[10];
DB ans,r;
void dfs(int t,DB k,int l,DB m,DB c)
{
	if(m+eps>666){ans=min(ans,c);return;}
	if(c+eps>ans||m+r/k+eps<666||m+eps<t*X)return;
	for(int i=l;i<n;i++)
		if(!used[i]&&t*X+eps<M[i]/k)
		{
			used[i]=1,r-=M[i];
			dfs(t,k,i+1,m+M[i]/k-t*X,c+C[i]/k);
			used[i]=0,r+=M[i];
		}
	dfs(t+1,k*3,0,m,c);
}
int main()
{
	int CT;
	for(scanf("%d",&CT);CT--;)
	{
		scanf("%d%d",&n,&X);
		r=0;
		for(int i=0;i<n;i++)
			scanf("%d%d",C+i,M+i),r+=M[i];
		if(r+eps<666)puts("impossible");
		else
			ans=1e18,dfs(0,1,0,0,0),printf("%.0lf\n",ans);;
	}
	return 0;
}