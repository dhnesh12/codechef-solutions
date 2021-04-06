#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define s(x) scanf("%d", &x)
#define mod 1000000007
map <int,ll> m;
map <int,ll> :: iterator it;
int main(){int t, n, x, last, cnt; ll ans; s(t);
    while (t--){s(n); last = 0; m.clear(); while (n--){s(x); if (x == last){cnt++;}
            else{if (last){m[last] = (m[last] + (cnt*1LL*(cnt+1))/2)%mod;} cnt = 1;} last = x;}
        m[last] = (m[last]+(cnt*1LL*(cnt+1))/2)%mod;
        ans = 1; for (it=m.begin();it!=m.end();it++){ans = (ans * it->second)%mod;} printf("%lld\n", ans);}}