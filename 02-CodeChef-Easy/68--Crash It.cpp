#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const int N = 500010;
ll c[N], cc[N];
signed main(){ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q, cnt1 = 0, cnt2 = 0; ll k, C = 0, CC = 0; cin >> n >> q >> k;
    for (int i = 0; i < n; i++){ll x; int d; cin >> d >> x; if (d == 1){c[cnt1++] = x; C++;}
        else{CC++; cc[cnt2++] = x; cc[cnt2++] = x + k;}} sort(c, c + cnt1); sort(cc, cc + cnt2);
    pair<ll,int> p[q]; ll ans[q]; memset(ans, 0, sizeof(ans));
    for (int i = 0; i < q; i++){ll T; cin >> T; T *= 2; ans[i] = C*CC*(T/k); p[i] = {T%k, i};}
    sort(p, p + q); int ptr = 0, nxt[q]; memset(nxt, -1, sizeof(nxt));
    for (int j = 0; j < cnt1; j++){ll u = c[j]; while (ptr < cnt2 && cc[ptr] < u){ptr++;}
        for (int i = 0; i < q; i++){while (nxt[i] + 1 < cnt2 && cc[nxt[i] + 1] - u <= p[i].first){nxt[i]++;}
                ans[p[i].second] += 1LL*(nxt[i]-(ptr-1));}}
    for (int i = 0; i < q; i++){cout << ans[i] << endl;}}