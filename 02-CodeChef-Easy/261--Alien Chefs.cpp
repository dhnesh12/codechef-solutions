#include<bits/stdc++.h>
using namespace std;

int start[300005],q[5005][25],ans[5005],bit[300005];
vector<pair<pair<int,int>,pair<int,int> > >V;

void update(int x,int value)
{
	for (;x<300005;x+=(x)&(-x))
	{
		bit[x]+=value;
	}
}

int getans(int indx)
{
	int ans=0;
	while(indx)
	{
		ans+=bit[indx];
		indx-=((indx)&(-indx));
	}
	
	return ans;
}

int main()
{
	int N,i,j;
	scanf("%d",&N);
	
	for (i=1;i<=N;i++)
	{
		int st,end;
		scanf("%d%d",&st,&end);
		
		V.push_back(make_pair(make_pair(st,-1),make_pair(1,i)));
		V.push_back(make_pair(make_pair(end,INT_MAX),make_pair(2,i)));
	}
	
	int Q;
	scanf("%d",&Q);
	
	for (i=1;i<=Q;i++)
	{
		int K;
		scanf("%d",&K);
		
		for (j=1;j<=K;j++)
		{
			scanf("%d",&q[i][j]);
		}
		
		sort(q[i]+1,q[i]+1+K);
		
		for (j=1;j<=K;j++)
		{
			V.push_back(make_pair(make_pair(q[i][j],j),make_pair(3,i)));
		}
		
	}
	
	sort(V.begin(),V.end());
	
	int compress=1;
	
	for (i=0;i<V.size();i++)
	{
		if(i>0 && V[i].first.first!=V[i-1].first.first)
		compress++;
		
		if(V[i].second.first==1)
		{
			start[V[i].second.second]=compress;
			update(compress,1);
		}
		
		else if(V[i].second.first==2)
		{
			update(start[V[i].second.second],-1);
		}
		
		else
		{
			q[V[i].second.second][V[i].first.second]=compress;
			ans[V[i].second.second]+=getans(compress)-getans(q[V[i].second.second][V[i].first.second-1]);
		}
		
	}
	
	for (i=1;i<=Q;i++)
	{
		printf("%d\n",ans[i]);
	}
	
}