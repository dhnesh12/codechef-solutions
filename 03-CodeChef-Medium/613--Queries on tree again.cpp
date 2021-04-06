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


vector<vector<int> >adj;
int parent[100005];
void dfs(int ver,int pr)
{
    parent[ver]=pr;
    for(auto i:adj[ver])
    {
        if(i!=pr)
            dfs(i,ver);
    }
}

int ans[100005];
int mm[100005][65];
const int mod=1e9+7;
int pp[65];

void solve(int x,int y)
{
    int ini=x;
    for(int i=0;i<=y && ini;i++)
    {
        ans[ini]+=pp[y-i];
        ini=parent[ini];
        ans[ini]%=mod;
    }
    for(int j=1;j<=y;j++)
    {
        mm[x][j]+=pp[y-j];
        mm[x][j]%=mod;
    }
}

int upd(int x)
{
    int tot=0;
    int ini=parent[x];
    for(int i=1;i<=60&&ini;i++)
    {
        tot+=mm[ini][i];
        ini=parent[ini];
        tot%=mod;
    }
    return tot;
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

    pp[0]=1;
    for(int i=1;i<=63;i++)
        pp[i]=pp[i-1]*2%mod;

    int t;
    cin>>t;
    while(t--)
    {
        int n,q;
        cin>>n>>q;
        for(int i=1;i<=n;i++)
            ans[i]=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<=62;j++)
                mm[i][j]=0;
        }
        adj.clear();
        adj.resize(n+1);
        int x,y;
        for(int i=0;i<n-1;i++)
        {
            cin>>x>>y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        dfs(1,0);
        int z;
        while(q--)
        {
            cin>>z;
            if(z==1)
            {
                cin>>x>>y;
                solve(x,y);
            }
            else
            {
                cin>>x;
                int tot=upd(x);
                tot+=ans[x];
                tot%=mod;
                cout<<tot<<'\n';
            }
        }
    }

}    
