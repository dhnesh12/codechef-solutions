#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y,z;
}E[50005];
struct node2{
	int fa;
	bool fla;
}a[10005];
int getfa(int x)
{
	if(x==a[x].fa)
	{
		return x;
	}
	return a[x].fa=getfa(a[x].fa);
}
//bool getflag(int x)
//{
//	if(x==a[x].fa||a[x].fla)
//	{
//		return a[x].fla;
//	}
//	return a[x].fla=getflag(a[x].fa);
//}
vector <int> G[10005];
bool vis[10005];
int n,m,ans;
bool dfs(int x,int pre)
{
	if(vis[x])
	{
		return true;
	}
	vis[x]=true;
	bool flag=false;
	for(int i=0;i<(int)G[x].size();i++)
	{
		int to=G[x][i];
		if(to==pre)
			continue;
		flag=flag||dfs(to,x);
	}
	return flag;
}
bool cmp(node x,node y)
{
	return x.z>y.z;
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--)
	{
		ans=0;
		fill(vis+1,vis+n+1,false);
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			G[i].clear();
			a[i].fa=i;
			a[i].fla=false;
		}
		for(int i=1,x,y,z;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			G[x].push_back(y);
			G[y].push_back(x);
			E[i]=(node){x,y,z};
		}
		sort(E+1,E+m+1,cmp);
		bool flag=true;
		for(int i=1;i<=n;i++)
		{
			if(!vis[i])
			{
				flag=flag&&dfs(i,0);
				if(!flag)
				{
					break;
				}
			}
		}
		if(!flag)
		{
			printf("impossible\n");
			continue;
		}
		for(int i=1;i<=m;i++)
		{
			int fx=getfa(E[i].x),fy=getfa(E[i].y);
			if(a[fx].fla&&a[fy].fla)
				continue;
//			cout<<fx<<" "<<fy<<endl;
			if(fx==fy)
			{
				if(a[fx].fla)
				{
					
				}
				else
				{
//					cout<<i<<endl;
					ans+=E[i].z;
					a[fx].fla=true;
				}
			}
			else
			{
//				cout<<i<<endl;
				ans+=E[i].z;
				if(a[fx].fla)
					a[fy].fa=fx;
				else
					a[fx].fa=fy;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}