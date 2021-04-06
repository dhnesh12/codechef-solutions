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

char s[305][305];
int sum[305][305];
int dp[2][305][305];
int L[305][305], R[305][305];
int get_sum(int x1, int x2, int y1, int y2){
    return (((sum[x2][y2] - sum[x2][y1-1] + mod)%mod - sum[x1-1][y2] + mod)%mod + sum[x1-1][y1-1])%mod;
}
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        memset(dp, 0, sizeof(dp));
        int n, m, x = 0;
        scanf("%d%d", &n, &m);
        for(int i=1;i<=n;i++) scanf("%s", s[i]+1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s[i][j] == '#') continue;
                for(int k=i;k>=1;k--){
                    if(s[k][j] == '#') break;
                    L[i][j] = k;
                }
                for(int k=i;k<=n;k++){
                    if(s[k][j] == '#') break;
                    R[i][j] = k;
                }
            }
        }
        dp[x][1][n] = 1;
        for(int i=1;i<=m;i++){
            memset(sum, 0, sizeof(sum));
            memset(dp[x^1], 0, sizeof(dp[x^1]));
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    sum[i][j] = (((sum[i-1][j] + sum[i][j-1])%mod - sum[i-1][j-1] + mod)%mod + dp[x][i][j])%mod;
                }
            }
            for(int r1=1;r1<=n;r1++){
                for(int r2=r1+1;r2<=n;r2++){
                    if(s[r1][i] == '#' || s[r2][i] == '#') continue;
                    int x1 = L[r1][i], x2 = min(r2-1, R[r1][i]);
                    int y1 = max(r1+1, L[r2][i]), y2 = R[r2][i];
                    dp[x^1][r1][r2] = (dp[x^1][r1][r2] + get_sum(x1, x2, y1, y2))%mod;
                }
            }
            x ^= 1;
        }
        printf("%d\n", dp[x][1][n]);
    }
}