#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=2e5+100,mod=1e9+7;
int dp[maxn],a[maxn],n,q,res;
set<int> s;
vector<int> g[maxn];
void dfs(int ss,int p)
{
    dp[ss]=a[ss];
    for(auto it:g[ss])
    {
        if(it==p)
        continue;
        dfs(it,ss);
        dp[ss]+=dp[it];
        s.insert(abs(2LL*dp[it]-res));      //the level of the node include twice 
    }
}
signed main()
{
    res=0;
    cin>>n>>q;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        res+=a[i];
    }
    for(int i=1;i<n;i++)
    {
        int x,y;
        cin>>x>>y;
        --x;
        --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(0,-1);
    while(q--)
    {
        int x;
        cin>>x;
        //--x;
        if(s.find(x)!=s.end())
        cout<<"Yes\n";
        else
        cout<<"No\n";
    }
    return 0;
}