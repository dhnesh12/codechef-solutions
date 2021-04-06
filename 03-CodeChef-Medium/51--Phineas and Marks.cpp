#include <bits/stdc++.h>
#define pb push_back
#define X first
#define Y second
#define sz(a) (int)a.size()
#define int long long

using namespace std;

void solve();

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t > 0) {
        solve();
        t--;
    }
    return 0;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    int nn = n % k;
    int ans = m;
    int past = n % k;
    while (true) {
        if (nn + k > n)
            break;
        if (2 * m >= 2 * past - nn - k) {
            ans = min(m - (2 * past - nn - k + 1) / 2, m);
            past = nn + k;
            nn += k;
            int l = 0, r = (n - nn) / k;
            while (r - l > 1) {
                int mid = (r + l) / 2;
                if (2 * m >= 2 * (past + k * mid) - (nn + k * mid) - k)
                    l = mid;
                else
                    r = mid;
            }
            nn += k * l;
            past += k * l;
        } else {
            nn += (abs(2 * m - 2 * past + nn + k) + k - 1) / k * k;
            //cout << (abs(2 * m - 2 * past + nn + k) + k - 1) / k * k << endl;
        }
    }
    cout << past << " " << ans << '\n';
    return;
}

/*/
1
1000000000 1000000000 10
/*/
