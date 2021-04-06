#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXn = 1e5 + 10;

ll n, k, q, sum[MAXn], bound[MAXn], lsum[MAXn];

bool isgood(ll l, ll r) {
    ll a = sum[r + 1] - sum[l];
    ll b = r - l - a + 1;
    return a <= k && b <= k;
}

int main() {
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> k >> q;
        
        for (int i = 0; i < n; i++) {
            char c;
            cin >> c;
            sum[i + 1] = sum[i];
            if (c == '1') {
                sum[i + 1]++;
            }
        }
        
        for (int i = 0; i < n; i++) {
            ll left = i;
            ll right = min(n + 1, 2 * k + i + 1);
            while (right - left > 1) {
                ll mid = (right + left) / 2;
                if (isgood(i, mid)) {
                    left = mid;
                } else right = mid;
            }
            bound[i] = left;
            lsum[i + 1] = lsum[i] + left - i + 1;

            //cout << lsum[i + 1] << ' ';
        }

        while (q--) {
            ll l, r;
            cin >> l >> r; l--; r--;

            ll left = l - 1;
            ll right = r;
            while (right - left > 1) {
                ll mid = (right + left) / 2;
                if (bound[mid] < r) left = mid;
                else right = mid;
            }

            cout << (r - right + 1) + (r - right + 1) * (r - right) / 2 + (lsum[left + 1] - lsum[l]) << endl;
        }
    }

    return 0;
}
