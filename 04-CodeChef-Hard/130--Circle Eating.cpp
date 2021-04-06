#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vl = vector<ll>;
using vvl = vector<vl>;


void solve() {
    ll n;
    cin >> n;
    vl a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll sum = a[0];
    ll minimum = sum;
    ll l = 1, r = n-1;
    bool resetl = true, resetr = true;
    ll leftsum = 0;//a[l];
    ll leftmin = 0;//a[l];
    ll i = l;//l + 1;
    ll rightsum = 0;//a[r];
    ll rightmin = 0;//a[r];
    ll j = r;//r - 1;
    while (l <= r) {
        if (resetl) {
            leftsum = a[l];
            leftmin = leftsum;
            i = l + 1;
            while (leftsum < 0 && i <= r) {
                leftsum += a[i];
                leftmin = min(leftmin, leftsum);
                i++;
            }
            resetl = false;
        }
        if (resetr) {
            rightsum = a[r];
            rightmin = rightsum;
            j = r - 1;
            while (rightsum < 0 && j >= l) {
                rightsum += a[j];
                rightmin = min(rightmin, rightsum);
                j--;
            }
            resetr = false;
        }
        if (leftmin >= rightmin) {
            minimum = min(minimum, sum + leftmin);
            sum += leftsum;
            l = i;
            resetl = true;
            if (l > j) {
                resetr = true;
                // cerr << "oeps ";
            }
        } else {
            minimum = min(minimum, sum + rightmin);
            sum += rightsum;
            r = j;
            resetr = true;
            if (r < i) {
                resetl = true;
                // cerr << "oeps! ";
            }
        }
    }
    cout << minimum << endl;
}

int main() {
    int testcases;
    cin >> testcases;
    for (int i = 0; i < testcases; i++) {
        // cerr << "Testcase " << i << ": ";
        solve();
    }
    return 0;
}
