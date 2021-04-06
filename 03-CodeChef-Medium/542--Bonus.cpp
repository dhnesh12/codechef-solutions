#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const double PI=acos(-1.0);
#define t1(x)             cerr<<#x<<"="<<x<<endl
#define t2(x, y)          cerr<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl
#define t3(x, y, z)       cerr<<#x<<"=" <<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl
#define t4(a,b,c,d)       cerr<<#a<<"="<<a<<" "<<#b<<"="<<b<<" "<<#c<<"="<<c<<" "<<#d<<"="<<d<<endl
#define t5(a,b,c,d,e)     cerr<<#a<<"="<<a<<" "<<#b<<"="<<b<<" "<<#c<<"="<<c<<" "<<#d<<"="<<d<<" "<<#e<<"="<<e<<endl
#define t6(a,b,c,d,e,f)   cerr<<#a<<"="<<a<<" "<<#b<<"="<<b<<" "<<#c<<"="<<c<<" "<<#d<<"="<<d<<" "<<#e<<"="<<e<<" "<<#f<<"="<<f<<endl
#define GET_MACRO(_1,_2,_3,_4,_5,_6,NAME,...) NAME
#define t(...) GET_MACRO(__VA_ARGS__,t6,t5, t4, t3, t2, t1)(__VA_ARGS__)
//freopen("output.txt","w",stdout);
//freopen("input.txt","r",stdin);
/*-------------------------------------------------------------------------------------------------------------------------------------*/
#define MOD 1000000007
#define endl "\n" 
#define int long long // remove when constraints are tight.
/*-------------------------------------------------------------------------------------------------------------------------------------*/

const int N=105;

vector<vector<int>> adj;
vector<vector<int>> adjtranspose;

vector<bool> visited1;
vector<bool> visited2;
stack<int> st;
vector<int> color;
vector<vector<int>> SCC;

int n,m,l;
void dfs1(int node)
{
	visited1[node]=true;
	for(auto x: adj[node])
	{
		if(!visited1[x])
		{
			dfs1(x);
		}
	}
	st.push(node);
}

void dfs2(int node,int c)
{
	visited2[node]=true;
	color[node]=c;
	for(auto x: adjtranspose[node])
	{
		if(!visited2[x])
		{
			dfs2(x,c);
		}
	}
}

void condense_directed_graph()// adj and adjtranspose should already be constructed before calling this function
{
    for(int i=1;i<=n;i++)
    {
        if(!visited1[i])
        {
            dfs1(i);
        }
    }
    int c=0;
    while(!st.empty())
    {
        int x=st.top();
        st.pop();
        if(!visited2[x])
        {
            dfs2(x,c++);
        }
    }
    SCC.resize(c);
    for(int i=1;i<=n;i++)
    {
        for(auto x: adj[i])
        {
            if(color[i]!=color[x])
            {
                SCC[color[i]].push_back(color[x]);
            }
        }
    }   
}
int32_t main()
{
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>m>>l;
		adj.clear();
		adjtranspose.clear();
		visited1.clear();
		SCC.clear();
		visited2.clear();

		adj.resize(n+1);
		adjtranspose.resize(n+1);
		visited1.resize(n+1,false);
		visited2.resize(n+1,false);
		color.resize(n+1);

		struct edges{
			int x,y,c;
		};	
		vector<edges> v;
		for(int i=1;i<=m;i++)
		{
			int x,y,c;
			cin>>x>>y>>c;
			v.push_back({x,y,c});
			if(c==0)
			{
				adj[y].push_back(x);
				adjtranspose[x].push_back(y);
			}
		}
		condense_directed_graph();
		int flag=1;
		for(edges i: v)
		{
			if(color[i.x]==color[i.y] && i.c!=0)
			{
				flag=0;
				break;
			}
		}
		if(flag==0)
		{
			cout<<"Inconsistent analysis.\n";
			continue;
		}
		vector<pair<int,int>> out[SCC.size()];
		int indegree[SCC.size()];
		memset(indegree,0,sizeof(indegree));
		for(auto i: v)
		{
			if(color[i.x]!=color[i.y])
			{
				out[color[i.y]].push_back({color[i.x],i.c});
				indegree[color[i.x]]++;
			}
		}
		int c=SCC.size();
		set<pair<int,int>> se;
		for(int i=0;i<c;i++)
		{
			se.insert({indegree[i],i});
		}
		flag=1;
		int ans[c];
		memset(ans,0,sizeof(ans));
		for(int i=0;i<c;i++)
		{
			ans[i]=l;
		}
		while(se.size())
		{
			pair<int,int> tmp=*se.begin();
			se.erase(tmp);
			if(tmp.first>0)
			{
				flag=0;
				break;
			}	
			for(auto x: out[tmp.second])
			{
				ans[x.first]=max(ans[x.first],ans[tmp.second]+x.second);
				se.erase({indegree[x.first],x.first});
				indegree[x.first]--;
				se.insert({indegree[x.first],x.first});
			}
		}
		if(flag)
		{
			int sum=0;
			for(int i=1;i<=n;i++)
			{
				sum+=ans[color[i]];
			}
			cout<<sum<<endl;
			for(int i=1;i<=n;i++)
			{
				cout<<ans[color[i]]<<" ";
			}
			cout<<endl;
		}
		else
		{
			cout<<"Inconsistent analysis.\n";
		}
	}
}
