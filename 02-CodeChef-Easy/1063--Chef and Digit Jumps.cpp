
// SACXY

#include<bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
using namespace std;


#define ff              first
#define ss              second
#define int             long long int
#define pb              push_back
#define mp              make_pair
#define pii             pair<int,int>
#define vi              vector<int>
#define mii             map<int,int>
#define repp(i, a, b)   for(int i = a; i <= b; i++)
#define rep(i, a, b)    for(int i = a; i < b; i++)
#define rrep(i, b, a)   for(int i = b; i >= a; i--)
#define all(v)          v.begin(),v.end()
#define rall(v)         v.rbegin(),v.rend()
#define lb              lower_bound
#define ub              upper_bound
#define endl            "\n"
#define setbits(x)      __builtin_popcountll(x)
#define zrobits(x)      __builtin_ctzll(x)
#define mod             1000000007
#define inf             1e18
#define ps(x,y)         fixed<<setprecision(y)<<x
#define w(x)            int x; cin>>x; while(x--)
mt19937                 rng(chrono::steady_clock::now().time_since_epoch().count());
#define MAX             1000004
  
  
void c_p_c()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

int vis[MAX];
int dis[MAX];
vector<int> adj[10];

int32_t main()
{
    c_p_c();
    string s;
    cin >> s;
    memset(vis,0,sizeof(vis));
    rep(i,1,s.size()) {
        int val = s[i]-'0';
        adj[val].pb(i);
    }
    queue<int> q;
    
    dis[0] = 0;
    q.push(0);
    vis[0] = 1;
    
    while(!q.empty()) {
        int idx = q.front();
        
        if(idx == s.size()-1) break;
        
        q.pop();
        
        int val = s[idx]-'0';
        int n = adj[val].size(); 
        for(int i = 0 ; i < n ; i++) {
            int id = adj[val][i];
            if(!vis[id]) {
                q.push(id);
                vis[id] = 1;
                dis[id] = dis[idx] + 1;
            }
        }
        adj[val].clear();
        
        if(idx-1 >=0 && !vis[idx-1]) {
            q.push(idx-1);
            vis[idx-1] = 1;
            dis[idx-1] = dis[idx] + 1;
        }
        
        if(idx+1 <= s.size() && !vis[idx+1]) {
            q.push(idx+1);
            dis[idx+1] = dis[idx] + 1;
            vis[idx+1] = 1;
        }
        // for(int i = )
    }
    
    cout << dis[s.size()-1] << endl;
    
    return 0;
}
