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

int c[100005], f[100005];
ll sum[100005];
int basis[35], idx[35];
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        ll k;
        scanf("%d%lld", &n, &k);
        for(int i=1;i<=n;i++){
            scanf("%d%d", &c[i], &f[i]);
            sum[i] = sum[i-1] + c[i];
        }
        memset(basis, -1, sizeof(basis));
        int l = 1, ans = 0;
        for(int i=1;i<=n;i++){
            while(l <= n && sum[i] - sum[l-1] > k) l++;

            int cur = i, val = f[i];
            for(int j=30;j>=0;j--){
                if((val>>j)&1){
                    if(basis[j] == -1){
                        basis[j] = val;
                        idx[j] = cur;
                        break;
                    }
                    else{
                        if(idx[j] < cur){
                            swap(idx[j], cur);
                            swap(basis[j], val);
                        }
                        val ^= basis[j];
                    }
                }
            }

            int res = 0;
            for(int j=30;j>=0;j--){
                if((res>>j)&1) continue;
                if(basis[j] != -1 && l <= idx[j]) res ^= basis[j];
            }
            ans = max(ans, res);
        }
        printf("%d\n", ans);
    }   
}