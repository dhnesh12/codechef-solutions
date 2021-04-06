#include <bits/stdc++.h>

using namespace std;



int get(string s, int n){
    int res = 0;
    for(int i=1;i<n;i++){
        if(s[i] != s[i-1])
            res++;
    }
    return res;
}

void solve(){
    int n,m;
    cin>>n>>m;
    string a,b;
    cin>>a>>b;
    
    int dp[n+1][m+1][2];
    memset(dp, 0, sizeof(dp));
    
    for(int j=1;j<=m;j++){
        if(b[j-1] == a[0]){
            dp[0][j][0] = dp[0][j-1][1];
        }
        else{
            dp[0][j][0] = 1 + dp[0][j-1][1];
        }
        
        if(j != m && b[j-1] == b[j]){
            dp[0][j][1] = dp[0][j-1][1];
        }else{
            dp[0][j][1] = 1 + dp[0][j-1][1];
        }
    }
    dp[0][m][1] = get(b, m);
    
    for(int i=1;i<=n;i++){
        if(a[i-1] == b[0]){
            dp[i][0][0] = dp[i-1][0][1];
        }
        else{
            dp[i][0][0] = 1 + dp[i-1][0][1];
        }
        
        if(i != n && a[i-1] == a[i]){
            dp[i][0][1] = dp[i-1][0][1];
        }else{
            dp[i][0][1] = 1 + dp[i-1][0][1];
        }
    }
    dp[n][0][1] = get(a, n);
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            
            dp[i][j][0] = INT_MAX;
            dp[i][j][1] = INT_MAX;
            char prev = 'A';
            if(i != n)
                prev = a[i];
            
            if(a[i-1] == prev)
                dp[i][j][0] = min(dp[i][j][0], dp[i-1][j][0]);
            else
                dp[i][j][0] = min(dp[i][j][0], 1 + dp[i-1][j][0]);
            
            if(b[j-1] == prev)
                dp[i][j][0] = min(dp[i][j][0], dp[i][j-1][1]);
            else
                dp[i][j][0] = min(dp[i][j][0], 1 + dp[i][j-1][1]);
            
            if(i != m)
                prev = b[j];
            
            if(a[i-1] == prev)
                dp[i][j][1] = min(dp[i][j][1], dp[i-1][j][0]);
            else
                dp[i][j][1] = min(dp[i][j][1], 1 + dp[i-1][j][0]);
            
            if(b[j-1] == prev)
                dp[i][j][1] = min(dp[i][j][1], dp[i][j-1][1]);
            else
                dp[i][j][1] = min(dp[i][j][1], 1 + dp[i][j-1][1]);
        }
    }
    cout<<min(dp[n][m][0],dp[n][m][1])<<endl;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        solve();
    }
}
