#include <bits/stdc++.h>

#define endl "\n"
#define ll long long
#define pb push_back
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        ll n, m, ans = 0;
        cin >> n >> m;
        int mp[m + 1], a[n + 1] = {0};
        vector<int> inds;

        for (int i = 1; i <= m; i++) {
            int c;
            cin >> c;
            mp[i] = c;
        }

        for (int i = 1; i <= n; i++) {
            int d, f, b;
            cin >> d >> f >> b;
            if (mp[d]) {
                ans += f;
                mp[d]--;
                a[i] = d;
            } else {
                ans += b;
                a[i] = 0;
                inds.pb(i);
            }
         }

        for (int i: inds) {
            if (a[i] == 0) {
                int j = 1;
                while (mp[j] == 0)
                    j++;
                mp[j]--;
                a[i] = j;
            }
        }
        cout << ans << endl;
        for (int i = 1; i <= n; i++) {
            cout << a[i] << " ";
        }
        cout << endl;

    }
    return 0;
}
