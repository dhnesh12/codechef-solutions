#include <bits/stdc++.h>
using namespace std;

#define kk first
#define ii second

typedef long long ll;

const int P = 1e9 + 9;
typedef pair<int, int> ii;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> h (n);
        for (int i = 0; i < n; i++) {
            cin >> h[i];
        }

        vector<int> s (n);
        for (int i = 1; i < n; i++) {
            s[i-1] = h[i]-h[i-1];
        }
        s[n-1] = -101;

        vector<int> sk (s.begin(), s.end());

        vector<pair<ii, int>> a(n);
        for (int k = 1; k < n; k *= 2) {
            for (int i = 0; i < n; i++)
                a[i] = { { sk[i], sk[(i+k)%n] }, i };
            sort(a.begin(), a.end());
            sk[a[0].ii] = 0;
            for (int i = 1, r = 0; i < n; i++)
                sk[a[i].ii] = a[i-1].kk == a[i].kk ? r : ++r;
        }

        vector<int> sa (n);
        for (int i = 0; i < n; i++) { sa[i] = a[i].ii; }

        vector<int> lcp (n);
        int k = 0;
        for (int i = 0; i < n-1; i++) {
            int pi = sk[i];
            int j = sa[pi-1];
            // lcp[i] = lcp[s[i..], s[j..])
            while (s[i+k] == s[j+k]) k++;
            lcp[pi] = k;
            k = max(k - 1, 0);
        }

        int ans = ((ll(n-1)*ll(n-1) + ll(n-1))/2) % P;
        for (int i = 0; i < n; i++) {
            ans = (ans - lcp[i] + P) % P;
        }
        cout << ans << "\n";
    }
}
