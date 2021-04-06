#include <bits/stdc++.h>
#define X first
#define Y second
#define pb push_back
#define sz(a) (int)a.size()

using namespace std;

void solve();

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}


bitset <42000> b, a;

bool cmp(pair <int, int> a, pair <int, int> b) {
    if (a.X > 0 && b.X > 0)
        return a.Y > b.Y;
    else if (a.X > 0)
        return true;
    else if (b.X > 0)
        return false;
    return a.Y > b.Y;
}

vector <pair <int, int>> f;

vector <pair <int, int>> v;

void pol(string &s) {
    int p = 0;
    int mn = 1e9;
    for (int i = 0; i < sz(s); ++i) {
        if (s[i] == '(') {
            p++;
        } else
            p--;
        mn = min(mn, p);
    }
    f.pb({mn, p});
}

bool get() {
    sort(v.begin(), v.end(), cmp);
    b = 0;
    b[21000] = 1;
    for (auto i : v) {
        a = (b >> (21000 - i.X));
        a <<= (21000 - i.X);
        if (i.Y < 0) {
            a >>= (-i.Y);
        } else {
            a <<= i.Y;
        }
        if (a[21000])
            return true;
        b |= a;
    }
    return false;
}

void solve() {
    int n, x;
    f.clear();
    string s;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        pol(s);
    }
    int l = 0, r = n + 1;
    while (r - l > 1) {
        int mid = (r + l) / 2;
        v.clear();
        for (int i = 0; i < min(mid, n); ++i)
            v.pb(f[i]);
        if (get()) {
            r = mid;
        } else {
            l = mid;
        }
    }
    if (l == n)
        cout << -1 << '\n';
    else
        cout << r << '\n';
}
