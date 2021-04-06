#include<bits/stdc++.h>
#define pb push_back
//#define mp make_pair
#define fastread ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define openfile ifstream cin; ofstream cout; cin.open("input.txt"); cout.open("output.txt");
#define f(i, x, y) for(int i = x; i < y; i++)
#define all(X) X.begin(), X.end()
#define int long long
#define ll long long
#define key pair<int, int>
#define keyd pair<double, double>
#define ff first
#define ss second
#define double long double
int mod = 1e9+7;
const int inf = 1e18;
using namespace std;

vector<key> g[100001];
int lca[100001][20];
int tin[100001], tout[100001];
int up[100001], down[100001], dep[100001];

void dfs(int s, int p, int sum, int ds)
{
    static int t = 0;
    tin[s] = t++;
    down[s] = 0;
    dep[s] = ds;
    up[s] = max(0ll, sum);
    lca[s][0] = p;
    f(i, 1, 20) lca[s][i] = lca[lca[s][i-1]][i-1];
    for(key i : g[s])
    {
        if(i.ff == p) continue;
        dfs(i.ff, s, max(sum + i.ss, i.ss), ds + i.ss);
        down[s] = max(down[s], down[i.ff] + i.ss);
    }
    tout[s] = t++;        
}

bool upper(int a, int b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int LCA(int a, int b)
{
    if(upper(a, b)) return a;
    if(upper(b, a)) return b;
    for(int i = 19; i >= 0; i--)
        if(!upper(lca[a][i], b))
            a = lca[a][i];
    return lca[a][0];        
}

main()
{
    fastread;
    int n, Q; cin>>n>>Q; 
    f(i, 1, n)
    {
        int s, d, w; cin>>s>>d>>w; 
        g[s].pb({d, w}); g[d].pb({s, w});
    }
    dfs(1, 1, 0, 0);
    
    //  f(i, 1, n+1) cout<<up[i]<<" "; cout<<"\n"; f(i, 1, n+1) cout<<down[i]<<" "; cout<<"\n";
    //  f(i, 1, n+1) cout<<dep[i]<<" "; cout<<"\n";
    
    while(Q--)   
    {
        int a, b; cin>>a>>b;
        int t = LCA(a, b); 
        int ans = 0;
        if(t == b)
            ans = dep[a] - dep[b] + max(up[b], down[a]) * 2;
        else if(t == a)
            ans = dep[b] - dep[a] + max(down[b], up[a]) * 2;
        else
            ans = dep[a] + dep[b] + 2 *(up[t] - dep[t]) ;
        cout<<ans<<"\n";
    }
}