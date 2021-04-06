#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5, mod = 1e9 + 7;
ll dp[N], dp2[N], arr[N];
ll mul(ll a, ll b, ll m) {
    return ((a % m) * (b % m)) % m;
}
ll add(ll a, ll b, ll m) {
    return (((a + b) % m) + m) % m;
}
ll fp(int b, int p, ll m) {
    if (p == 0) return 1;
    ll ret = fp(b, p / 2, m);
    ret = mul(ret, ret, m);
    if (p & 1) ret = mul(ret, b, m);
    return ret;
}
ll solve(int idx) {
    ll &ret = dp2[idx];
    if (ret != -1) return ret;
    ret = add(fp(2, dp[idx], mod - 1), -1, mod - 1);
    for (int i = idx * 2; i < N; i += idx)
        ret = add(ret, -solve(i), mod - 1);
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        memset(arr, 0, sizeof arr);
        memset(dp, 0, sizeof dp);
        memset(dp2, -1, sizeof dp2);
        int n;
        cin >> n;
        vector<ll> v;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            arr[x]++;
        }
        for (int i = 1; i < N; i++) {
            for (int j = i; j < N; j += i)
                dp[i] += arr[j];
        }
        ll ans = 1;
        for (int i = 1; i < N; i++) {
            ans = mul(ans, fp(i, solve(i), mod), mod);
        }
        cout << ans << '\n';
    }
    return 0;
}