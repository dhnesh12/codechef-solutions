#include<bits/stdc++.h>
#define MAX 1000000
#define MOD 1000000007
using namespace std;
int v[MAX+10];
vector<pair<int,int>> q[MAX+10];
int ans[MAX+10];
int mp[MAX+10];
vector<int> g[MAX+10];
int BIT[MAX+10];
int ls[MAX+10];
int pos[MAX+10];
void update(int value, int i, int n)
{
	ls[i++] = value;
	while(i<=n+1)
	{
		BIT[i] = max(BIT[i],value);
		i += i&(-i);
	}
}
int queryMAX(int r, int n)
{
	++r;
	int mx = 0;
	while(r)
	{
		mx = max(mx,BIT[r]);
		r -= r&(-r);
	}
	return mx;
}
stack<pair<int,int>> stk;
void dfs(int x, int lis, int n)
{
	stk.push({x,lis});
	while(!stk.empty())
	{
		x = stk.top().first;
		lis = stk.top().second;
		stk.pop();
		if(++lis>ls[x])
		{
			update(lis,x,n);
			for(int y:g[x])
				stk.push({y,lis});	
		}	
	}
}
int main()
{
	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL);
	set<int> st;
	vector<int> tmp;
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,m;
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n+1;++i)
			BIT[i] = 0;
		st.clear();
		tmp.clear();
		for(int i=1;i<=n;++i)
			scanf("%d",v+i), st.insert(v[i]), mp[v[i]] = INT_MAX, g[i].clear(), q[i].clear(), ls[i] = 0;
		int ii = 0;
		for(int x:st)
		    tmp.push_back(x), pos[x] = ii++;
		for(int i=n;i>=1;--i)
		{
			int last = INT_MAX;
			for(int j = pos[v[i]]+1;j<(int)tmp.size();++j)
				if(mp[tmp[j]]<last)
					last = mp[tmp[j]], g[i].push_back(mp[tmp[j]]);
			mp[v[i]] = i;
		}
		for(int i=1,x,y;i<=m;++i)
			scanf("%d %d",&x,&y),q[x].push_back({y,i});
		for(int i=n;i>=1;--i)
		{
			dfs(i,0, n);
			for(pair<int,int> p:q[i])
				ans[p.second] = queryMAX(p.first,n);
		}
		for(int i=1;i<=m;++i)
			printf("%d\n",ans[i]);
	}
	return 0;
}