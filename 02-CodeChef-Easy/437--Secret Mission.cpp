#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back
#define pii pair<ll,ll>
#define f first
#define s second

const ll mod = 1e9+7;
ll arr[300005],q[300005],r[300005];
ll adj[201][201],dp[201][201];


int main() {
    int t;
    //cin>>t;
    cin>>t;
    while(t--){
        ll n,m,l;
        cin>>n>>m>>l;
        for(int i=0;i<l;i++) cin>>arr[i],arr[i]--;
        int u,v,w;
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                dp[i][j] = 1e9;
                if(i==j) dp[i][j] = 0;
            }
        }
        for(int i=0;i<m;i++) {
            cin>>u>>v>>w;
            u--,v--;
            adj[u][v] = w;
            adj[v][u] = w;
            dp[u][v] = w;
            dp[v][u] = w;
        }
        for(int k=0;k<n;k++) {
            for(int i=0;i<n;i++) {
                for(int j=0;j<n;j++) {
                    dp[i][j] = min(dp[i][k]+dp[k][j],dp[i][j]);
                }
            }
        }
        int ans = 1;
        bool flg = 0;
        for(int i=0,j=0;i<l-1;i=j) {
            while(j+1<l) {
                ll d = 0;
                for(int k=i;k<=j;k++) {
                    d += adj[arr[k]][arr[k+1]];
                }
                if(d>dp[arr[i]][arr[j+1]]) {
                    break;
                }
                j++;
            }
            if(i==j) {
                flg=1;
                break;
            }
            ans++;
        }
        if(flg) {
            cout<<-1<<endl;
            continue;
        }
        cout<<ans<<endl;
    }
}