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
const int mod = 998244353;

int a[1000005], cnt[1000005];
ll f1[1000005], f2[1000005];
ll pw(ll x, ll y){
    ll ans = 1;
    while(y){
        if(y%2 == 1) ans = ans*x%mod;
        x = x*x%mod;
        y/=2;
    }
    return ans;
}
ll C(int x, int y){
    if(y > x) return 0;
    return f1[x]*1ll*f2[y]%mod*f2[x-y]%mod;
}
int main(){
    f1[0] = f2[0] = 1;
    for(int i=1;i<=1000000;i++){
        f1[i] = f1[i-1]*1ll*i%mod;
        f2[i] = pw(f1[i], mod-2);
    }
    int t;
    scanf("%d", &t);   
    while(t--){
        ll ans = 1;
        int n;
        scanf("%d", &n);
        for(int i=1;i<=n;i++) cnt[i] = 0;
        for(int i=1;i<=n;i++){
            scanf("%d", &a[i]);
            cnt[a[i]]++;
        }
        for(int i=1;i<=n;i++){
            if(cnt[i]%i != 0) ans = 0;
            else{
                for(int j=0;j<cnt[i]/i;j++) ans = ans*1ll*C(cnt[i]-i*j, i)%mod;
                ans = ans*1ll*f2[cnt[i]/i]%mod;
                for(int j=0;j<cnt[i]/i;j++) ans = ans*1ll*f1[i-1]%mod;
            }
        }

        printf("%lld\n", ans);
    }
}