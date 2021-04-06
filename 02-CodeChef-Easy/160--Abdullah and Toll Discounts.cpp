#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define rep(i,s,f) for(i=s;i<f;i++)
#define print(v) for(auto &z:v) cout<<z<<' ';cout<<'\n'
#define db cout<<"db: "
#define pb push_back
#define pii pair<int,int>
#define F first
#define S second
#define B begin()
#define E end()
#define all(v) v.B,v.E
#define sz(v) (int)((v).size())
#define vi vector<int>
#define vii vector<pair<int,int>>
#define boost ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define clk1 clock_t start_time=clock()
#define clk2 cout<<(clock()-start_time)/(double)CLOCKS_PER_SEC
#define clean(arr) memset(arr,0,sizeof(arr))
#define mod 1000000007
#define mod2 998244353
#define space 10005
//<<fixed << setprecision(9)
int k,arr[space],mx[space],cost;
vi G[space];

int dfs(int n,int p)
{
    mx[n]=0;
    for(auto z:G[n])
    {
        if(z!=p) mx[n]=max(mx[n],dfs(z,n));
    }
    mx[n]+=arr[n];
    return mx[n];
}

void dfs2(int n,int p)
{
    if(mx[n]>k)
    {
        int sub = min(mx[n]-k,arr[n]);
        cost+=sub;
    }
    for(auto z:G[n]) if(z!=p) dfs2(z,n);
}

int32_t main()
{
    int n,i,j,t;
    boost;

    cin>>t;
    while(t--)
    {
        int root;
        cin>>n>>root>>k;
        rep(i,1,n+1)cin>>arr[i], G[i].clear();
        rep(i,0,n-1)
        {
            int u,v;
            cin>>u>>v;
            G[u].pb(v);
            G[v].pb(u);
        }
        dfs(root,-1);
        cost=0;
        dfs2(root,-1);
        cout<<cost*2<<'\n';
    }

    return 0;
}