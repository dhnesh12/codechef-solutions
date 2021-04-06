#include<bits/stdc++.h>
using namespace std;
#define ll long long int
ll n,x;
bool ans[501][100010];
bool marked[100010];
ll d[501];
vector<int> v[501];
ll tree[1000];

void dfs(ll x)
{
    tree[x]=d[x];
    ans[x][d[x]]=1;
    for(ll i=0;i<v[x].size();++i)
    {
        ll to=v[x][i];
        dfs(to);
        tree[x]+=tree[to];
    }
    for(ll i=0;i<v[x].size();++i)
    {
        ll to=v[x][i];
        for(ll j=0;j<=tree[x];++j)
          marked[j]=0;
        marked[d[x]]=1;
        for(ll j=0;j<=tree[to];++j)
          if(ans[to][j]==1)
            marked[j+d[x]]=1;
        for(ll j=0;j<v[x].size();++j)
          if(i!=j){
              ll temp=v[x][j];
              for(ll i1=tree[x];i1>=tree[temp];i1--){
                  if(marked[i1-tree[temp]]==1)
                    marked[i1]=1;
              }
          }
        for(ll j=0;j<=tree[x];++j)
          if(marked[j]==1)
            ans[x][j]=1;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n;
    for(ll i=1;i<=n;++i)
      cin>>d[i];
    for(ll i=2;i<=n;++i)
    {
        cin>>x;
        v[x].push_back(i);
    }
    dfs(1);
    for(ll i=1;i<=tree[1];++i)
      cout<<ans[1][i];
}
