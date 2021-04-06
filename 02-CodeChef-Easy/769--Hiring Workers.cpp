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

ll sum(vi &arr) {
    ll s = 0;
    for (ll x : arr)
        s += x;
    return s;
}

vi factorise(ll x) {
    vi v;
    for (ll i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            v.pb(i);
            x /= i;
            while (x % i == 0) {
                v[v.size() - 1] *= i;
                x /= i;
            }
        }
    }

    if (x != 1) {
        v.pb(x);
    }

    return v;
}

ll group(vi &arr, vi &factors, ll pos = 0) {
    if (pos == factors.size()) {
        return sum(arr);
    }

    ll ans = inf;
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] *= factors[pos];
        ans = min(ans, group(arr, factors, pos + 1));
        arr[i] /= factors[pos];
    }


    return ans;
}

void solve() {
    ll k, x;
    cin >> k >> x;

    vi factors = factorise(x);
    ll ans = 0;

    if (factors.size() <= k) {
        ans = sum(factors) + k - factors.size();
    }
    else {
        vi arr(k, 1);
        ans = group(arr, factors);
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