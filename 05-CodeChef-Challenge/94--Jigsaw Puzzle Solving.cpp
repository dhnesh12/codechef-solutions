#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

int n,m,K,i,j,k,u,v;
int mx[200005],my[200005],id[200005];
int qx[1000005],qy[1000005],ban[1000005],r;
int col[1005][1005];
vector<int> x[200005],y[200005];

inline bool cmp(const int &a,const int &b)
{
	int Sa=mx[a]*my[a],Sb=mx[b]*my[b],na=x[a].size(),nb=x[b].size();
	return (long long)na*Sb>(long long)nb*Sa;
}

void add(int x_,int y_)
{
	if(x_>=n||y_>=m)return;
	++r;qx[r]=x_;qy[r]=y_;ban[r]=0;
}

bool check(int x_,int y_,int d)
{
	int i,num=x[d].size(),x__,y__;
	for(i=0;i<num;++i)
	{
		x__=x_+x[d][i];
		y__=y_+y[d][i];
		if(x__>n||y__>m)return false;
		if(col[x__][y__])return false;
	}
	for(i=0;i<num;++i)
	{
		x__=x_+x[d][i];
		y__=y_+y[d][i];
		col[x__][y__]=d;
	}
	add(x_+mx[d],y_);
	add(x_,y_+my[d]);
	return true;
}

int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for(i=1;i<=K;++i)
	{
		id[i]=i;
		scanf("%d",&k);
		for(;k;--k)
		{
			scanf("%d%d",&u,&v);
			x[i].push_back(u);if(u>mx[i])mx[i]=u;
			y[i].push_back(v);if(v>my[i])my[i]=v;
		}
	}
	sort(id+1,id+K+1,cmp);
	r=1;
	for(i=1;i<=K;++i)
	for(j=1;j<=r;++j)
	if(check(qx[j],qy[j],id[i]))
	{
		qx[j]=qx[r];qy[j]=qy[r];ban[j]=ban[r];
		--r;break;
	}
	else
	{
		++ban[j];
		if(ban[j]>10&&rand()%10)
		{
			qx[j]=qx[r];qy[j]=qy[r];ban[j]=ban[r];
			--r;--j;
		}
	}
	for(i=1;i<=n;++i)
	{
		for(j=1;j<=m;++j)printf("%d ",col[i][j]);
		printf("\n");
	}
}