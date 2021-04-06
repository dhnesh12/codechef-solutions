#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define sync ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define MOD 1000000007
#define inf 2000000000

#define ff first
#define ss second

#define ll  long long int
#define pii pair<ll, ll>
#define vi  vector<ll>

#define hmap  unordered_map
#define hset  unordered_set
#define maxpq priority_queue<ll>
#define minpq priority_queue<ll,vi,greater<ll>>

template<typename T, typename U>
inline bool operator&(const T &s, U x) {return (s.find(x) != s.end());}

ostream& operator<<(ostream &cout, vi &v) {cout << "["; for (int i = 0; i < v.size(); ++i) {cout << v[i]; cout << (i < v.size() - 1 ? ", " : "]\n");}}

void solve() {
    ll n, m;
    cin >> n >> m;
    vi a(n), b(m);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll p = 0, q = 0;

    for (int i = 0; i < n; ++i) {
        p += a[i];
    }

    for (int i = 0; i < m; ++i) {
        q += b[i];
    }

    if (p > q) {
        cout << 0;
        return;
    }

    ll ans = 0;
    ll i = 0, j = b.size() - 1;

    while (p <= q and i < a.size() and j >= 0) {
        if (a[i] >= b[j]) {
            ans = -1;
            break;
        }
        ans++;

        p += b[j];
        p -= a[i];

        q -= b[j];
        q += a[i];

        i++;
        j--;
    }

    if (p <= q) {
        cout << -1;
        return;
    }
    cout << ans;
}

void precompute() {}

int main() {
    sync;
    precompute();
    int testCases = 1, t = 1;
    cin >> testCases;
    while (testCases--) {
        // cout << "Case #" << t++ << ": ";
        solve();
        cout << '\n';
    }

    return 0;
}