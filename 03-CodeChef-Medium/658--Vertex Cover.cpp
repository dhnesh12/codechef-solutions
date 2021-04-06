#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=4e5+100;
int n,m,a,b,cnt,Component[maxn],Test_cases;
vector <int> Main_graph[maxn],Reverse_graph[maxn],tartib_topol_sort;
bool mark[maxn];
void add(int x,int y)
{
	Main_graph[x^1].push_back(y);
	Main_graph[y^1].push_back(x);
	Reverse_graph[y].push_back(x^1);
	Reverse_graph[x].push_back(y^1);
}
void dfs1(int v)
{
	mark[v]=true;
	for(auto NEXT:Main_graph[v])
    {
		if(!mark[NEXT])
        {
			dfs1(NEXT);
        }
    }
	tartib_topol_sort.push_back(v);
}
void dfs2(int v)
{
	Component[v]=cnt;
	for(auto NEXT:Reverse_graph[v])
    {
		if(!Component[NEXT])
        {
			dfs2(NEXT);
        }
    }
}
void solve()
{
	cin>>n>>m;
	for(int i=0;i<2*n;i++)
    {
		mark[i]=false;
		Component[i]=0;
		Main_graph[i].clear();
		Reverse_graph[i].clear();
	}
	tartib_topol_sort.clear();
	for(int i=1;i<=m;i++)
	{
		cin>>a>>b;
		a--;
		b--;
		Main_graph[(2*a)^1].push_back(2*b);
        Main_graph[(2*b)^1].push_back((2*a));
        Reverse_graph[2*b].push_back((2*a)^1);
        Reverse_graph[2*a].push_back((2*b)^1);
	}
	for(int i=0;i<(n/2);i++)
	{
		a=2*i;
		b=2*i+1;
		Main_graph[(2*a)^1].push_back(2*b);
        Main_graph[(2*b)^1].push_back((2*a));
        Reverse_graph[2*b].push_back((2*a)^1);
        Reverse_graph[2*a].push_back((2*b)^1);
		Main_graph[(2*a+1)^1].push_back(2*b+1);
        Main_graph[(2*b+1)^1].push_back((2*a+1));
        Reverse_graph[2*b+1].push_back((2*a+1)^1);
        Reverse_graph[2*a+1].push_back((2*b+1)^1);
	}
	for(int i=0;i<2*n;i++)
    {
		if(!mark[i])
        {
            dfs1(i);
        }
    }
	for(int i=2*n-1;i>=0;i--)
    {
		if(!Component[tartib_topol_sort[i]])
        {
			cnt++;
			dfs2(tartib_topol_sort[i]);
		}
    }
	for(int i=0;i<n;i++)
    {
		if(Component[2*i]==Component[2*i+1])
		{
			cout<<"impossible"<<endl;
			return;
		}
	}
	cout<<"possible"<<endl;
	for(int i=0;i<n;i++)
    {
		cout<<(int)(Component[2*i]>Component[2*i+1]);
	}
	cout<<endl;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>Test_cases;
	while(Test_cases--)
    {
        solve();
    }
	return 0;
}
