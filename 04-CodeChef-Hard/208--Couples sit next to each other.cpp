#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
 
typedef tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update> order_set;
 
order_set S;
 
#define N 1000005
 
typedef long long ll;
 
int T, n;
int a[N];
int uu[N], vv[N];
int nxt[N], prv[N];
int s[N];
ll ans;
 
ll calc_cross() {
    ll cross = 0;
    S.clear();
    for (int i = 1; i <= 2 * n; i ++) {
        if (prv[i]) {
            cross -= s[prv[i]-1];
            cross += S.order_of_key(prv[i]);
            S.insert(prv[i]);
        }
    }
    return cross;
}
 
int main() {
    scanf("%d", &T);
    while (T --) {
        scanf("%d", &n);
        for (int i = 1; i <= 2 * n; i ++) uu[i] = vv[i] = prv[i] = nxt[i] = 0;
        for (int i = 1; i <= 2 * n; i ++) {
            scanf("%d", &a[i]);
            if (uu[a[i]]) {
                vv[a[i]] = i;
                prv[i] = uu[a[i]];
                nxt[uu[a[i]]] = i;
                s[i] = s[i-1] + 1;
            }
            else { uu[a[i]] = i; s[i] = s[i-1]; }
        }
        ans = -n;
        ans -= calc_cross();
        for (int i = 1; i <= n; i ++) ans += min(vv[i] - uu[i], 2 * n - vv[i] + uu[i]);
        printf("%lld\n", ans);
    }
}  