//priyomk
#include <bits/stdc++.h>
#define MAXN 100003
#define MAXR 52
using namespace std;
 
vector<pair<int, int> > g[MAXN];
int n, L, R;
int cur_cost;
int dp[MAXN][MAXR];
int cost[MAXN];
 
bool dfs(int u, int p = -1) {
    
    fill(dp[u], dp[u] + R + 1 , INT_MAX);
    
    dp[u][0] = 0;
    
    for(auto e : g[u]) {
        int chld = e.first;
        int w = e.second;
        
        int c = (w <= cur_cost) ? -1 : 1;
        
        if(chld == p) {
            continue;
        }
        
        if(dfs(chld, u)) {
            return true;
        }
        
        for(int l1 = 0; l1 <= R && dp[u][l1] < INT_MAX ; l1++) {
            for(int l2 = 0 ; l1+l2 < R && dp[chld][l2] < INT_MAX ; l2++) {
                int len = l1+l2+1;
                int cc = c + dp[u][l1] + dp[chld][l2];
                
                if(cc < 0 && len >= L && len <= R) {
                    return true;
                }
            }
        }
        
        for(int childLen = 0; childLen < R && 
                    dp[chld][childLen]  < INT_MAX ; childLen++) {
                        
            dp[u][childLen+1] = min(dp[u][childLen+1] ,dp[chld][childLen] + c );
            
        }
    }
    
    
    return false;
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        
        scanf("%d %d %d", &n, &L, &R);
        for(int i = 0 ; i<= n; i++) {
            g[i].clear();
            
        }
        
        
        for(int i = 1; i <= n-1; i++) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            
            g[a].push_back(make_pair(b, c));
            g[b].push_back(make_pair(a, c));
    
    
            cost[i] = c;
        }
        
        
        sort(cost+1, cost + n);
        cur_cost = cost[n-1];
        
        if(dfs(1) == 0) {
            printf("-1\n");
        } else {
            int st = 1;
            int en = n-1;
            int sol = 0;
            
            while(st <= en) {
                int mid = (st + en)/2;
                cur_cost = cost[mid];
                if(dfs(1) ){
                    sol = cost[mid];
                    en = mid - 1;
                } else {
                    st = mid + 1;
                }
            }
            
            
            printf("%d\n", sol);
        }
    }
	return 0;
}