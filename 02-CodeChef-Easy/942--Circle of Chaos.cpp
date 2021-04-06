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

ll maxfact(ll g, ll n) {
    ll max_factor = 0;
    for (ll i = 1; i * i <= g; i++)
    {
        if (g % i == 0)
        {
            if (i <= n)
                max_factor = max(max_factor, i);
            if (g / i <= n)
                max_factor = max(max_factor, g / i);
        }
    }
    return max_factor;
}

void solve() {
    ll n, m;
    cin >> n >> m;
    vi p(m);
    for (int i = 0; i < m; ++i) {
        cin >> p[i];
    }

    ll g = 0;
    for (int i = 0; i < m; ++i) {
        g = __gcd(g, p[i]);
    }

    if (g > n) {
        g = maxfact(g, n);
    }

    ll ans = n - g;

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