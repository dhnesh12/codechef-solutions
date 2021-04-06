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
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;


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
const int mod=1e9+7;
int ans[1000004];

void dfs(int ver,int lol)
{
    int sz=adj[ver].size();

    for(int i=0;i<sz;i++)
    {
        ans[adj[ver][i]]=(ans[ver]+(lol*i)%mod)%mod;
        dfs(adj[ver][i],sz*lol%mod);        
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
        adj.clear();
        adj.resize(n+2);
        int sz;
        for(int i=1;i<=n;i++)
        {
            cin>>sz;
            int x;
            for(int j=0;j<sz;j++)
            {
                cin>>x;
                adj[i].push_back(x);
            }
        }
        
        dfs(1,1);

        for(int i=1;i<=n;i++)
            cout<<(ans[i]+1)%mod<<" ";
        cout<<'\n';
    }

}    
    