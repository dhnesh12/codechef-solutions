#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define pb push_back
#define int long long int
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define rep(i,a,b) for(i=a;i<b;i++)
#define hell 1000000007
#define PI 3.14159265
#define mod 998244353
#define fs first
#define sc second
void solve()
{
    int n,m,i,j;
    cin>>n;
    string s;
    cin>>s;
    int a[n];
    rep(i,0,n)cin>>a[i];
    sort(a,a+n);
    vector<pair<int,int>> adj[n];
    for(i=0;i<n;i++)
    {
      if(i+1<n)
      {
        adj[i].pb({a[i+1]-a[i],i+1});
      }
      if(i-1>=0)
      {
        adj[i].pb({a[i]-a[i-1], i-1});
      }
    }
    priority_queue<pair<int,int>, vector<pair<int,int>> , greater<pair<int,int>>> q;
    for(int i=0;i<n;i++)
    {
      if(s[i]=='1')
        q.push({0,i});
    }
    int cost= 0;
    int vis[n];
    for(i=0;i<n;i++)
      vis[i]=0;
    while(!q.empty())
    {
      pair<int,int> p= q.top();
      q.pop();
      if(vis[p.sc]==0)
      {
        vis[p.sc]=1;
        cost+= p.fs;
        for(auto x: adj[p.sc])
        {
          if(vis[x.sc]==0)
            q.push(x);
        }
      }
    }
    cout<<cost<<"\n";
}
signed main()
{
  fastio
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  int t;
  t=1;
  cin>>t;
  while(t--)
  solve();
  return 0;
}