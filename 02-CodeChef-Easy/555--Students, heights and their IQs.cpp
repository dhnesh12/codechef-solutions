#include <bits/stdc++.h>
using namespace std;
int n;
const int N = 1001;
int h[N], iq[N], dp[N][N];

int solve(int cur, int prev) {
    if(cur>=n)      return 0;
    int incld = 0, excld = 0;
    if(prev!=-1 && dp[cur][prev]!=-1) {
        return dp[cur][prev];
    }
    if(prev==-1 || (h[cur]>h[prev] && iq[cur]<iq[prev])) {
        incld = 1+solve(cur+1, cur);
    }
    excld = solve(cur+1, prev);
    dp[cur][prev] = max(incld,excld);
    return dp[cur][prev];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    int t;      cin >> t;
    while(t--) {
        memset(dp, -1, sizeof(dp));
        cin >> n;
        for(int i=0; i<n; i++) {
            cin >> h[i];
        }
        for(int i=0; i<n; i++) {
            cin >> iq[i];
        }
        cout << solve(0, -1) << endl;
    }
}