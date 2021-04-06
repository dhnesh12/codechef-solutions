#include <bits/stdc++.h>
using namespace std;
#define N 500001
#define pb push_back
#define all(f) f.begin(),f.end()
#define nl "\n"
#define debug(g) cout<<#g<<" : "<<g<<nl
typedef long long ll;
typedef vector<int> vi;
typedef pair<ll,ll> pii;
const ll mod=(1e9)+7;
const double pi=acos(-1);
ll gcd(ll a,ll b){return (b==0)?a:gcd(b,a%b);}
ll lcm(ll a,ll b){return (a*b)/gcd(a,b);}
vi adj[N],vis(N),ct(N),par(N);
void dfs(int v,int p){
    vis[v]=1;
    par[v]=p;
    ct[p]+=1;
    for(auto x:adj[v]){
        if(vis[x]==0){
            dfs(x,v);
        }
    }
}
void solve(){
    int n,m,u,v,i,k;
    cin>>n>>k;
    for(i=1;i<=n;i++){
        adj[i].clear();
        vis[i]=ct[i]=par[i]=0;
    }
    m=n-1;
    while(m--){
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1,0);
    vi temp;
    for(i=1;i<=n;i++){
        if(ct[i]==0)
        temp.pb(i);
    }
    int nodes=0;
    for(i=1;i<=k;i++){
        vi ans;
        for(auto x:temp){
            if(x==1)
            {
                nodes++;
                continue;
            }
            if(ct[x]==0)
            nodes++;
            ct[par[x]]--;
            if(ct[par[x]]==0)
            ans.pb(par[x]);
        }
        temp.clear();
        for(auto x:ans){
            if(ct[x]==0)
            temp.pb(x);
        }
    }
    cout<<nodes<<nl;
}
int main(){
    //fast io
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #ifndef ONLINE_JUDGE 
        freopen("input.txt", "r", stdin); 
        freopen("output.txt", "w", stdout); 
    #endif
    ll t=1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}