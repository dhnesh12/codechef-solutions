#include<bits/stdc++.h>
using namespace std;
#define ll int
int ctr=0;
class graph{
	ll v;
	list<ll> *g;
	public:
	graph(int x){
		this->v=x;
		g=new list<int>[v];
	}
	void add(int v,int w)
	{
		g[v].push_back(w);
		g[w].push_back(v);
	}
	void DFSUtil(int V, bool visited[],int ans[])
	{
	//	cout<<ctr<<' ';
    	visited[V] = true;
	//	cout << V << " ";
    	ans[ctr++]=V;
		list<int>::iterator i;
		for (i = g[V].begin(); i != g[V].end(); ++i)
        if (!visited[*i])
	    {
	  //  	cout<<"G";
			DFSUtil(*i, visited,ans);
	    }
	}
	void DFS(int V,int ans[])
	{
    	bool *visited = new bool[v];
    	for (int i = 0; i < v; i++)
    	visited[i] = false;
    	DFSUtil(V, visited,ans);
	}
	void BFS(int s,int color[])
	{
		for(ll i=0;i<v;i++)
		{
			//cout<<"S ";
			color[i]=-1;
		}
		//return;
	//	bool visited[v];
	//	for(i=0;i<v;i++)
	//	visited[i]=false;
		list<int> q;
	//	visited[s]=false;
		q.push_back(s);
		list<int>::iterator it;
		color[s]=1;
		while(q.empty()==0)
		{
			s=q.front();
			q.pop_front();
			for(it=g[s].begin();it!=g[s].end();it++)
			{
				if(color[*it]==-1)
				{
					color[*it]=1-color[s];
					q.push_back(*it);
				}
			}
		}
	}
};
int main()
{
	ll t,n,u,v,i;
	cin>>t;
	while(t--)
	{
		ctr=0;
		cin>>n;
		graph G(n);
		int color[n];
		int ans[n];
		for(i=0;i<n-1;i++)
		{
			cin>>u>>v;
			G.add(u-1,v-1);
		}
		G.BFS(0,color);
	//	for(i=0;i<n;i++)
	//	cout<<color[i]<<' ';
	//	cout<<endl;
		ll c0=0,c1=0;
		for(i=0;i<n;i++)
		if(color[i]==1)
		c1++;
		else
		c0++;
		if(c1==n/2)
		{
			cout<<1<<endl;
			for(i=0;i<n;i++)
			if(color[i]==0)
			cout<<i+1<<' ';
			cout<<endl;
			for(i=0;i<n;i++)
			if(color[i]==1)
			cout<<i+1<<' ';
			cout<<endl;
		}
		else
		{
			cout<<2<<endl;
			G.DFS(1,ans);
			//cout<<"EF";
			for(i=0;i<n;i++)
			if(i%2==0)
			cout<<ans[i]+1<<' ';
			cout<<endl;
			for(i=0;i<n;i++)
			if(i%2==1)
			cout<<ans[i]+1<<' ';
			cout<<endl;
		}
	}
}