#include <bits/stdc++.h>
using namespace std;

#define look6(a,b,c,d,e,f) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d << " | "<<#e<<": "<<e<< " | "<<#f<<": "<<f<< endl;
#define look5(a,b,c,d,e) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d << " | "<<#e<<": "<<e<<endl;
#define look4(a,b,c,d) cerr<<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<" | "<<#d<<": "<<d<<endl;
#define look3(a,b,c) cerr <<#a<<": "<<a<<" | "<<#b<<": "<<b<<" | "<<#c<<": "<<c<<endl;
#define look2(a,b) cerr <<#a<<": "<<a<<" | "<<#b<<": "<<b<< endl;
#define look(a) cerr <<#a<<": "<<a<<endl;

const int MX = 1005;

vector<int> adj[MX];

pair<int, int> dp[MX][25];

pair<int, int> dp_cost[1 << 10][25];

int time_needed[MX];

void dfs(int u, int p, int h) {
    
    for (int i=0; i<adj[u].size(); i++) {
        int v = adj[u][i];
        
        if (v == p) {
            continue;
        }
        
        dfs(v, u, h);
    }
    
    int num_childs = adj[u].size();
    
    // Initalize dp_cost[][] with infinities
	for (int msk = 0; msk < (1 << num_childs); msk++)
		for (int p = 0; p <= h; p++)
			dp_cost[msk][p] = make_pair(MX, h);
			
	
	for (int i=0; i + time_needed[u] <= h; i++)
	    dp_cost[0][i] = make_pair(0, i + time_needed[u]);
	    
	
	for (int i=h+1-time_needed[u]; i<= h; i++)
	    dp_cost[0][i] = make_pair(1, time_needed[u]);
	    
	    
    for (int msk = 0; msk < (1 << num_childs); msk++) {
        
        for (int i=0; i<num_childs; i++) {
            
            if ((msk>>i) & 1 == 1 ) {
                continue;
            }
            
            int v = adj[u][i];
            
            for (int p=0; p<=h; p++) {

                auto& cost = dp_cost[msk][p];
                
                auto& curr_cost = dp_cost[msk | (1 << i)][p];
                
                auto& cost_v = dp[v][cost.second];
                
                auto new_cost = make_pair(cost.first + cost_v.first, cost_v.second);
                
                curr_cost = min(curr_cost, new_cost);
                
            }
        }
    }
    
    for (int p=0; p<=h; p++) {
        
        dp[u][p] = dp_cost[(1<<num_childs) -1][p];
        
        //look4(u, p, dp[u][p].first, dp[u][p].second);
    }
    
}

void solve(){
    int n, h;
    cin >> n >> h;
    
    int u, v;
    
    for (int i=1; i<=n; i++) {
         adj[i].clear();
         cin >> time_needed[i];
    }
    
    int levels, x;
    
    for (int i=1; i<=n; i++) {
        
        cin >> levels;
        
        for (int j=0; j<levels; j++) {
            cin >> x;
            
            adj[i].push_back(x);
           
            //adj[x].push_back(i);
        }
    }
    
    dfs(1, -1, h);
    
    cout << dp[1][h].first << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    cin>>t;
    
    while(t--){
        solve();
    }
    return 0;
}
