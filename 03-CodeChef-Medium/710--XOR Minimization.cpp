#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<climits>
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;

const int maxn = 300005;
const int maxnn = 3100;

int N=500,n,m;
int a[maxn],ans1,ans2;
int id[maxn],st[maxnn],f[maxnn],root[maxnn],cnt[maxnn];
int tr[maxn*20][2],sum[maxn*20]; 
void build_(int x)
{
	int tot=cnt[x];
	for(;tot>=root[x];tot--) tr[tot][0]=tr[tot][1]=sum[tot]=0;
	tot++;
	for(int i=st[x];i<st[x+1];i++) a[i]^=f[x]; f[x]=0;
	for(int i=st[x];i<st[x+1];i++)
	{
		int p=root[x];
		for(int j=15;j>=0;j--)
		{
			int y=((a[i]&(1<<j))!=0);
			if(!tr[p][y]) tr[p][y]=++tot;
			p=tr[p][y];
		}
		sum[p]++;
	}
	cnt[x]=tot;
}
void find_(int bel)
{
	int x=root[bel]; int now=0;
	for(int i=15;i>=0;i--)
	{
		int y=((f[bel]&(1<<i))!=0);
		if(tr[x][y])x=tr[x][y];
		else x=tr[x][y^1],now+=1<<i;
		if(now>ans1)return ;
	}
	if(now<ans1) ans1=now,ans2=0;
	if(now==ans1) ans2+=sum[x];
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		id[i]=(i-1)/N+1;
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=id[n];i++)
		st[i]=(i-1)*N+1,cnt[i]=root[i]=st[i]*20;
	st[id[n]+1]=n+1; root[id[n]+1]=cnt[id[n]+1]=(n+1)*20;
	for(int i=1;i<=id[n];i++) build_(i);
	while(m--)
	{
		int l; scanf("%d",&l);
		if(l==1)
		{
			int x,y;scanf("%d%d",&x,&y);
			int t1=id[x],t2=id[y];
			ans1=65536,ans2=0;
			if(t1==t2)
			{
				for(int i=x;i<=y;i++)
				{
					if((a[i]^f[t1])<ans1) ans1=a[i]^f[t1],ans2=0;
					if((a[i]^f[t1])==ans1) ans2++;
				}
			}
			else
			{
				for(int i=x;i<st[t1+1];i++)
				{
					if((a[i]^f[t1])<ans1) ans1=a[i]^f[t1],ans2=0;
					if((a[i]^f[t1])==ans1) ans2++;
				}
				for(int i=st[t2];i<=y;i++)
				{
					if((a[i]^f[t2])<ans1) ans1=a[i]^f[t2],ans2=0;
					if((a[i]^f[t2])==ans1) ans2++;
				}
				for(int i=t1+1;i<t2;i++) find_(i);
			}
			printf("%d %d\n",ans1,ans2);
		}
		else
		{
			int x,y,c;scanf("%d%d%d",&x,&y,&c);
			int t1=id[x],t2=id[y];
			if(t1==t2)
			{
				for(int i=x;i<=y;i++) a[i]^=c;
				build_(t1);
			}
			else
			{	
				for(int i=x;i<st[t1+1];i++) a[i]^=c;
				for(int i=st[t2];i<=y;i++) a[i]^=c;
				build_(t1); build_(t2);
				for(int i=t1+1;i<t2;i++) f[i]^=c;
			}
		}
	}
	
	return 0;
}
