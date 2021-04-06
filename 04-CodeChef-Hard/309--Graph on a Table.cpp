#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
typedef pair<pii, int> piipi;
typedef pair<pii, pii> piipii;

#define mp make_pair
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
#define eb emplace_back
const int mod = 1e9+7;

int U[105][105];
int L[105][105];
pii dp[105][105];
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n, m, q;
        scanf("%d%d%d", &n, &m, &q);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                U[i][j] = 1e9;
                L[i][j] = 1e9;
                dp[i][j] = mp(-1e9, 0);
            }
        }
        for(int i=1;i<=q;i++){
            int r1, c1, r2, c2;
            scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
            for(int x=r1;x<=r2;x++) for(int y=c1;y<=c2;y++) dp[x][y] = mp(1, 1);
            for(int x=r1+1;x<=r2;x++){
                for(int y=c1+1;y<=c2;y++){
                    L[x][y] = min(L[x][y], r1);
                    U[x][y] = min(U[x][y], c1);
                }
            }
        }

        int ans = 0, ways = 0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                for(int x=L[i][j];x<=i-1;x++){
                    if(dp[i][j].fi < dp[x][j-1].fi + 1){
                        dp[i][j].fi = dp[x][j-1].fi + 1;
                        dp[i][j].se = dp[x][j-1].se;
                    }
                    else if(dp[i][j].fi == dp[x][j-1].fi + 1){
                        dp[i][j].fi = dp[x][j-1].fi + 1;
                        dp[i][j].se = (dp[i][j].se + dp[x][j-1].se)%mod;
                    }
                    ans = max(ans, dp[i][j].fi);
                }
                for(int y=U[i][j];y<=j-1;y++){
                    if(dp[i][j].fi < dp[i-1][y].fi + 1){
                        dp[i][j].fi = dp[i-1][y].fi + 1;
                        dp[i][j].se = dp[i-1][y].se;
                    }
                    else if(dp[i][j].fi == dp[i-1][y].fi + 1){
                        dp[i][j].fi = dp[i-1][y].fi + 1;
                        dp[i][j].se = (dp[i][j].se + dp[i-1][y].se)%mod;
                    }
                    ans = max(ans, dp[i][j].fi);
                }

                if(L[i][j] <= i-1 && U[i][j] <= j-1){
                    if(dp[i][j].fi == dp[i-1][j-1].fi + 1){
                        dp[i][j].se = (dp[i][j].se - dp[i-1][j-1].se + mod)%mod;
                    }
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(dp[i][j].fi == ans){
                    ways = (ways + dp[i][j].se)%mod;
                }
            }
        }

        printf("%d %d\n", ans, ways);
    }
}