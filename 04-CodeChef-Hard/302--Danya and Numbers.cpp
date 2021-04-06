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
const int M = 500;
int t[75005], v[75005];
int a[75005], dp[1<<18], cnt[1<<18];
int n, m, k, mask;
void recal(int idx){
    for(int i=0;i<(1<<k);i++) dp[mask^i] = cnt[i];
    for(int i=idx;i>=1;i--){
        if(t[i] == 1) dp[mask^v[i]]++;
        else if(t[i] == 2) dp[mask^v[i]]--;
    }
    for(int i=0;i<k;i++){
        for(int j=0;j<(1<<k);j++){
            if((j>>i)&1) dp[j] += dp[j^(1<<i)];
        }
    }
}
int main(){
    scanf("%d%d%d", &n, &m, &k);
    for(int i=1;i<=n;i++){
        scanf("%d", &a[i]);
        cnt[a[i]]++;
    }
    mask = (1<<k)-1;
    for(int i=1;i<=m;i++){
        scanf("%d%d", &t[i], &v[i]);
        if(i%M == 1) recal(i);
        if(t[i] == 3){
            int ans = 0;
            for(int j=k-1;j>=0;j--){
                int sum = dp[mask^(ans|(1<<j))];
                for(int l=i;l>=1;l--){
                    if(l%M == 1) break;
                    if(t[l] == 1){
                        if(((ans|(1<<j))&v[l]) == (ans|(1<<j))) sum++;
                    }
                    else if(t[l] == 2){
                        if(((ans|(1<<j))&v[l]) == (ans|(1<<j))) sum--;
                    }
                }
                if(sum >= v[i]) ans |= (1<<j);
            }
            printf("%d\n", ans);
        }
    }
}