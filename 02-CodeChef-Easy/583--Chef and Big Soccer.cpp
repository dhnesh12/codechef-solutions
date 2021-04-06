#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int mod = 1e9+7;

ll dp[1001][1001];

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n,m,s;
        cin>>n>>m>>s;
        vector<int>arr(m+1);
        for(int i=1;i<=m;i++) cin>>arr[i];
        memset(dp,0,sizeof(dp));
        dp[s][0] = 1;
        for(int i=1;i<=m;i++) {
            for(int j=1;j<=n;j++) {
                ll temp = 0;
                if(j-arr[i]>=1) temp += dp[j-arr[i]][i-1];
                if(j+arr[i]<=n) temp += dp[j+arr[i]][i-1];
                dp[j][i]=(temp)%mod;
            }
        }
        for(int i=1;i<=n;i++) cout<<dp[i][m]<<" ";
        cout<<endl;
    }
}