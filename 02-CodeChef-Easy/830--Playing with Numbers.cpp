#include <bits/stdc++.h>
using namespace std;
void dfs(long long int  node,long long int gc,vector<vector<long long int>>&g,vector<bool>&visited,long long int *v,long long int *m,long long int *ans)
{
    visited[node]=true;
    gc=__gcd(gc,v[node]);
    for(auto it:g[node])
    {
        if(!visited[it])
        {
            dfs(it,gc,g,visited,v,m,ans);
        }
    }
    if(g[node].size()==1)
    {
        ans[node]=m[node]-__gcd(gc,m[node]);
    }
}
int main() {
	// your code goes here
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	long long int t;
	cin>>t;
	while(t--)
	{
	    long long int n;
	    cin>>n;
	  long long int x,y;
	    vector<vector<long long int>>g(n+1);
	    for(int i=0;i<n-1;i++)
	    {
	        cin>>x>>y;
	        g[x].push_back(y);
	        g[y].push_back(x);
	    }
	    long long int v[n+1],m[n+1],res[n+1];
	    for(int i=1;i<=n;i++)
	    {
	        res[i]=-1;
	        cin>>v[i];
	        
	    }
	    for(int i=1;i<=n;i++)
	    cin>>m[i];
	    vector<bool>visited(n+1,false);
	    dfs(1,v[1],g,visited,v,m,res);
	    for(int i=2;i<=n;i++)
	    {
	        if(res[i]!=-1)
	        cout<<res[i]<<" ";
	    }
	    cout<<endl;
	}
	return 0;
}
