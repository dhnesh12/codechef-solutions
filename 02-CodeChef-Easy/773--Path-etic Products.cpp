#include<iostream>
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define inf 1000000007
#define all(x) (x).begin(), (x).end()
using namespace std;

#define debug(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); deb(_it, args); }
void deb(istream_iterator<string> it) {cout<<endl;}
template<typename T, typename... Args>
void deb(istream_iterator<string> it, T a, Args... args) {
    cerr << *it << " = " << a << ",   ";
    deb(++it, args...);
}

const int MX = 200;
ll cs[MX];

vector<int>adj[MX];


void dfs(int u, int par, int lev){
    cs[u] = 4*lev*lev - 2*lev;

    for(int i=0; i<adj[u].size(); i++){
        int v = adj[u][i];
        if(v!=par){
            dfs(v, u, lev+1);
        }
    }
    return;
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        memset(cs, 0, sizeof cs);

        for(int i=0; i<MX; i++){
            adj[i].clear();
        }

        int n;
        cin>>n;

        for(int i=0; i<n-1; i++){
            int u, v;;
            cin>>u>>v;
            adj[u].pb(v);
            adj[v].pb(u);
        }

        dfs(1, 0, 1);

        for(int i=1; i<=n; i++){
            cout<<cs[i]<<" ";
        }
        cout<<endl;


    }

    return 0;
}