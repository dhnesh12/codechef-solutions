//HYBRYDO RAAAAAAAAAAA
#include<bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0); cin.tie(nullptr)
#define rall(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>
#define pb push_back
#define ss second
#define ff first
#define endl '\n'
using namespace std;
typedef long long ll;
const int INF=1e9;
const int N=3e5+15;
const ll MOD=998244353;
int color[N], anc[N];
vector<int> topo;
vector<int> adj[N];
int pdre[N];
int vis[N];
int tim;
pii cor[N];
void dfs(int v){
    vis[v]=1;
    cor[v].ff=tim;
    tim++;
    for(int u: adj[v]){
        if(vis[u]==0){
            pdre[u]=v;
            dfs(u);
        }
    }
    vis[v]=2;
    cor[v].ss=tim;
    tim++;
}

void solve(){
    int n, k; cin>>n>>k;
    int cmb=((n-1)*n)/2;
    int cnb=((n-2)*(n-1))/2;
    if(k==cmb){
        cout<<cmb<<endl;
        for(int i=1; i<=n; ++i){
            for(int j=i+1; j<=n; ++j){
                cout<<i<<" "<<j<<endl;
            }
        }
        return;
    }
    if(k>cnb && k<cmb){
        cout<<-1<<endl;
        return;
    }
    int a=cnb-k;
    cout<<cnb-k+n-1<<endl;
    for(int i=1; i<n; ++i){
        cout<<n<<" "<<i<<endl;
    }
    for(int i=1; i<n; ++i){
        for(int j=i+1; j<n; ++j){
            if(a==0) return;
            cout<<i<<" "<<j<<endl;
            a--;
        }
    }
}

int main(){
    FAST_IO;
    int t; cin>>t;
    while(t--) solve();
}