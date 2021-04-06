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
const int N = 3001;

char s[1000005];
int dp1[15][3001], dp2[15][3001], dp3[15][3001];
int vis[3001];
int main(){
    int n, k;
    scanf("%s%d", s+1, &k);
    n = strlen(s+1);
    int sum1 = 1, sum2 = 0;
    for(int i=n;i>=1;i--){
        s[i] -= '0';
        sum2 = (sum2 + sum1*1ll*s[i])%N;
        for(int d=0;d<=9;d++){
            if(d != s[i]){
                int nt = (d-s[i]+N)%N*sum1%N;
                dp1[s[i]][nt]++;
            }
        }
        sum1 = sum1*10%N;
    }


    memset(vis, -1, sizeof(vis));
    vector<int> path;
    int x = 0, cur = sum2;
    while(vis[cur] == -1){
        path.eb(cur);
        vis[cur] = x;
        cur = (cur*sum1 + sum2)%N;
        x++;
    }

    if(sz(path) >= k){
        sum2 = path[k-1];
    }
    else{
        int k2 = k-sz(path), le = x-vis[cur];
        k2 %= le;
        sum2 = path[vis[cur]+k2-1];
    }
    for(int d=0;d<=9;d++){
        for(int i=0;i<N;i++){
            memset(vis, -1, sizeof(vis));
            vector<int> path;
            int x = 0, cur = i;
            while(vis[cur] == -1){
                path.eb(cur);
                vis[cur] = x;
                cur = cur*sum1%N;
                x++;
            }

            if(sz(path) >= k){
                for(int j=0;j<k;j++){
                    dp2[d][path[j]] = (dp2[d][path[j]] + dp1[d][i])%mod;
                }
            }
            else{
                for(int j=0;j<vis[cur];j++){
                    dp2[d][path[j]] = (dp2[d][path[j]] + dp1[d][i])%mod;
                }
                int k2 = k-vis[cur], le = x-vis[cur];
                for(int j=vis[cur];j<sz(path);j++){
                    dp2[d][path[j]] = (dp2[d][path[j]] + dp1[d][i]*1ll*(k2/le))%mod;
                }
                k2 %= le;
                for(int j=vis[cur];j<vis[cur]+k2;j++){
                    dp2[d][path[j]] = (dp2[d][path[j]] + dp1[d][i])%mod;
                }
            }
        }
    }

    dp3[0][sum2] = 1;
    for(int d=0;d<=9;d++){
        for(int i=0;i<N;i++){
            dp3[d+1][i] = (dp3[d+1][i] + dp3[d][i])%mod;
            for(int j=0;j<N;j++){
                dp3[d+1][(i+j)%N] = (dp3[d+1][(i+j)%N] + dp3[d][i]*1ll*dp2[d][j])%mod;
            }
        }
    }
    printf("%d\n", dp3[10][0]);
}