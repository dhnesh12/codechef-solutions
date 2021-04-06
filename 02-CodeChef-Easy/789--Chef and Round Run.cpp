// amit
#include<bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0);cin.tie(NULL); cout.tie(NULL);
#define ll long long int
using namespace std;

#define rep(i,n) for(int i=0;i<n;i++)
#define pi pair<ll,ll>
#define pb push_back

vector<int> a[1000006],ar[1000006];
int vis[1000006];
int val[1000006];

vector<int> order;

void dfs(int node)
{
    vis[node]=1;
    for(int child:a[node])
        if(!vis[child])
        dfs(child);
    order.pb(node);
}
vector<int> scc;
void dfs0(int node)
{
    vis[node]=1;
    for(int child:ar[node])
        if(!vis[child])
        dfs0(child);
    scc.pb(node);
}

int main()

{
   fast;
   int t;cin>>t;
   while(t--)
  {
      int n;cin>>n;
      for(int i=0;i<n;i++)
         a[i].clear(),ar[i].clear(),vis[i]=0,cin>>val[i];
      for(int i=0;i<n;i++)
      {
         
          int b=(i+val[i]+1)%n;
          a[i].pb(b);
          ar[b].pb(i);
      }
      order.clear();
      for(int i=0;i<n;i++)
        if(!vis[i])
      dfs(i);
      rep(i,n)
      vis[i]=0;
      reverse(order.begin(),order.end());
      int ans=0;
      for(int child:order)
      {
          scc.clear();
          if(!vis[child])
            dfs0(child);
          if(scc.size()>1 or scc[0]==a[scc[0]][0])
            ans+=scc.size();
      }
      cout<<ans<<'\n';

  }
   return 0;
}
