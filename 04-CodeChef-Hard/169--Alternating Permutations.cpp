#include <bits/stdc++.h>
#define MOD 1000000007
typedef long long ll;
using namespace std;

ll a[26];
ll n, k, tc;

ll fac[50000];
ll facinv[50000];

ll modpow(ll b, ll e) {
    if (!e) return 1;
    if (e % 2) return (b * modpow(b, e - 1)) % MOD;
    ll tmp = modpow(b, e / 2);
    return (tmp * tmp) % MOD;
}

ll nCr(ll n, ll k) {
    if (k < 0 || n < 0 || k > n) return 0;
    if (k == 0 || n == k) return 1;
    ll rs = (fac[n] * facinv[k]) % MOD;
    return (rs * facinv[n - k]) % MOD;
}

ll dp[26][20001];

// left: exklusive
// right: inclusive
ll solve(ll leftIdx, ll rightPos) {
    ll leftPos = a[leftIdx];
    if (leftIdx > 0) {
        ++leftPos;
    }

    if (rightPos < 1 || rightPos > n || leftPos > 1 + rightPos) return 0; // invalid
    if (leftPos >= rightPos || rightPos <= a[leftIdx + 1]) return 1;

    if (dp[leftIdx][rightPos] != -1) return dp[leftIdx][rightPos];

    ll rs = 0;
    ll last = 0;
    for (ll i = leftIdx + 1; i < k && a[i] < rightPos; i += 2) {
        ll cur = (solve(leftIdx, a[i] - 1) * solve(i, rightPos)) % MOD;
        cur = (cur * nCr(rightPos - leftPos, a[i] - leftPos)) % MOD;
        rs = (rs + cur) % MOD;
        last = i;
    }

    if (last + 1 < k && a[last + 1] < rightPos) {
        rs = (rs + solve(leftIdx, rightPos - 1)) % MOD;
    }

    return dp[leftIdx][rightPos] = rs;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    fac[0] = facinv[0] = 1;
    for (ll i = 1; i <= 50000; ++i) {
        fac[i] = (i * fac[i - 1]) % MOD;
        facinv[i] = modpow(fac[i], MOD - 2);
    }

    cin >> tc;
    while (tc-- > 0) {
        cin >> n >> k;
        for (ll i = 0; i < k; ++i) {
            cin >> a[i];
        }

        fill(dp[0], dp[0] + 26 * 20001, -1);
        cout << solve(0, n) << endl;
    }

    return 0;
}
