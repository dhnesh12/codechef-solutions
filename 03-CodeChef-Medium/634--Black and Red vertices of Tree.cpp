#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define pi 3.141592653589793238
#define int long long
#define ll long long
#define ld long double
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


long long power(long long a, long long b,long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a %mod;
        a = a * a %mod;
        b >>= 1;
    }
    return res;
}


int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b); 
     
}

vector<set<int>> adj;
vector<vector<int> >temp;
const int mod=1e9+7;
int col[100005];
int mm[100005];
int vis[100005];
int deg[100005];
int dp[100005][2];
int ans[100005][3];

void dfs_ways(int ver,int pr)
{
    // cout<<ver<<endl;
    dp[ver][0]=1;   
    dp[ver][1]=1;
    for(auto i:temp[ver])
    {
        if(i!=pr)
        {
            dfs_ways(i,ver);
            dp[ver][0]*=dp[i][0];
            dp[ver][1]*=(dp[i][0]+dp[i][1])%mod;
            dp[ver][0]%=mod;
            dp[ver][1]%=mod;
        }
    }
}

void dfs(int ver,int pr)
{
    vis[ver]=1;
    ans[ver][0]=dp[ver][0];
    ans[ver][1]=dp[ver][1];

    for(auto i:temp[ver])
    {
        if(!vis[i])
        {
            dfs(i,ver);
            ans[ver][0]*=ans[i][0];
            ans[ver][1]*=(ans[i][0]+ans[i][1])%mod;
            ans[ver][0]%=mod;
            ans[ver][1]%=mod;
        }
    }

    for(auto i:temp[ver])
    {
        if(i!=pr)
        {
            ans[ver][2]+=ans[i][1]+ans[i][2];
            ans[ver][2]%=mod;
        }
    }
}

signed main()
{

ios_base::sync_with_stdio(false); 
cin.tie(NULL);  
cout.tie(0);   

#ifndef ONLINE_JUDGE
    if(fopen("INPUT.txt","r"))
    {
        freopen("INPUT.txt","r",stdin);
        freopen("OUTPUT.txt","w",stdout);
    }
#endif          


    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            deg[i]=0;
            mm[i]=0;
            dp[i][0]=0;
            dp[i][1]=0;
            for(int j=0;j<3;j++)
                ans[i][j]=0;
        }

        temp.clear();
        adj.clear();
        adj.resize(n+1);
        temp.resize(n+1);
        int x,y;
        vector<pair<int,int> >pp;
        for(int i=0;i<n-1;i++)
        {
            cin>>x>>y;
            pp.push_back({x,y});
            adj[x].insert(y);
            adj[y].insert(x);
            deg[x]++;
            deg[y]++;
        }
        for(int i=1;i<=n;i++)
            cin>>col[i];
        set<pair<int,int> >s;
        for(int i=1;i<=n;i++)
            s.insert({deg[i],i});
        while(!s.empty())
        {
            pair<int,int>p=*s.begin();
            s.erase(s.begin());
            if(deg[p.second]==1 && col[p.second]==0)
            {
                mm[p.second]=1;
                for(auto j:adj[p.second])
                {
                    adj[j].erase(p.second);
                    s.erase({deg[j],j});
                    deg[j]--;
                    s.insert({deg[j],j});
                }
            }
        }
        for(int i=1;i<=n;i++)
        {
            if(!mm[i]&& !col[i])
            {
                mm[i]=2;
            }
        }
        vector<int>madar;
        for(auto i:pp)
        {
            if(mm[i.first]==1&&mm[i.first]==1)
            {
                temp[i.first].push_back(i.second);
                temp[i.second].push_back(i.first);
            }
            else if(mm[i.first]==1 && mm[i.second]==2)
            {
                temp[i.first].push_back(i.second);
                temp[i.second].push_back(i.first);
            }
            else if(mm[i.second]==1 &&mm[i.first]==2)
            {
                temp[i.first].push_back(i.second);
                temp[i.second].push_back(i.first);
            }
        }

        for(int i=1;i<=n;i++)
        {
            if(mm[i]==2)
                dfs_ways(i,i);
        }
        temp.clear();
        temp.resize(n+1);
        for(auto i:pp)
        {
            if(mm[i.first]!=2||mm[i.second]!=2)
                continue;
            temp[i.first].push_back(i.second);
            temp[i.second].push_back(i.first);
        }
        int kad=0;
        // for(int i=1;i<=n;i++)
        //     cout<<mm[i]<<" ";
        // cout<<'\n';
        for(int i=1;i<=n;i++)
            vis[i]=0;
        // cout<<dp[1][0]<<" "<<dp[1][1]<<endl;
        // cout<<dp[3][0]<<" "<<dp[3][1]<<endl;
        for(int i=1;i<=n;i++)
        {
            if(!vis[i]&&mm[i]==2)
            {
                dfs(i,i);
                kad+=ans[i][1];
                kad+=ans[i][2];
                kad%=mod;
            }
        }
        cout<<kad<<'\n';

    }

}    
