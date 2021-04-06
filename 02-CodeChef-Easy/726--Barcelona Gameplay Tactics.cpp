#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll mod = 1e9 + 7;
ll K;
unordered_map<ll, unordered_map<bool, ll>> dp;
ll solve(int N, bool messi) {
    if (dp.count(N) && dp[N].count(messi)) return dp[N][messi];
    if (N == 1) {
        if (messi) {
            return 0;
        } else {
            return 1;
        }
    }

    ll ans = 0;
    if (messi) {
        ans = K * solve(N - 1, false);
    } else {
        ans = (K - 1) * solve(N - 1, false) + solve(N - 1, true);
    }

    return dp[N][messi] = ans % mod;
}

int main() {
    int t; cin >> t;
    while (t--) {
        int N;
        cin >> N >> K;

        dp.clear();
        cout << solve(N, true) << endl;
    }
    return 0;
}