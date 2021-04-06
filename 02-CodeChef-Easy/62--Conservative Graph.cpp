#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define ul unsigned long int
#define ld long double
#define f(t) for(ll i =0;i<t;i++)
#define vi vector<int>
#define vl vector<ll>
#define pri pair<int,int>
#define mpi map<int,int>
#define prl pair<ll,ll>
#define mp make_pair
#define mpl map<ll,ll>
#define umpl unordered_map<ll,ll>
#define pb push_back
#define ff first
#define ss second
#define MOD 1000000007
#define inf 2e18
#define EPS 1e-3
#define PI 3.1415926535897932385
const double h = 1e-6;
const int MAX_  = 100005;
inline ll mul(ll a, ll b){ return (a * 1ll * b) % MOD; }
inline ll sub(ll a, ll b){ ll c = a - b; if(c < 0) c += MOD; return c; }
inline ll add(ll a, ll b){ ll c = a + b; if(c > MOD) c -= MOD; return c; }
vector <pair<ll,ll> > graph[MAX_];
bool visit[MAX_];
int dist[MAX_];
bool danger;
void dfs (ll start){
    if(danger)
    return;
    visit[start] = true;
    for(auto it:graph[start]){if(visit[it.ff]){if(dist[it.ff] != dist[start] + it.ss){danger = true;return;}}
        else{dist[it.ff] = dist[start] + it.ss;dfs(it.ff);}}return;}
int main(){ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); int t; cin >> t;
    while(t--){int n, m; cin >> n >> m; danger = false;
        f(n){graph[i+1].clear();visit[i+1] = false;dist[i+1] = -1;}
        f(m){ll x, y, w; cin >> x >> y >> w; graph[x].pb({y,w}); graph[y].pb({x,-w});}
        for (int i = 1;i <= n; i++){if (visit[i] == false){dfs(i);}}
        if (danger){cout << "NO" << endl;} else{cout << "YES" << endl;}}}