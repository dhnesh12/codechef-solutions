#include <bits/stdc++.h>
using namespace std;
int main(){ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0); int t; cin >> t;
    while (t--){int n, k; cin >> n >> k; vector<int> a(k), others; for (auto &i : a){cin >> i;}
        if (n == 0){cout << "YES" << endl; continue;}
        if (n == 1){cout << "YES" << endl; cout << "1" << endl; continue;}
        else if (k == 1){cout << "NO" << endl; continue;}
        else if (k == 2 && n > 2){bool impossible = false; if (a[0] != a[1] - 1){impossible = true;}
            if (impossible){cout << "NO" << endl; continue;}}
        cout << "YES" << endl; int mx = n; vector<int> ans (n+1, 0);
        for (int i = 1; i < a[0]; i++){ans[i] = mx--;} for (int i = a[0]+1; i < a[1]; i++){ans[i] = mx--;}
        for (int i = k-1; i >= 0; i--){ans[a[i]] = mx--;}
        for (int i = a[0]; i <= n; ++i){if (!ans[i]){ans[i] = mx--;}}
        for (int i = 1; i <= n; i++){cout << ans[i] << " ";}cout << endl;}}