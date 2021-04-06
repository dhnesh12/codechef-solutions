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
    ll r, c;
    cin >> r >> c;
    vector<vi> a(r, vi(c));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cin >> a[i][j];
        }
    }

    ll q = 0;

    for (int i = 1; i < r; ++i) {
        for (int j = 1; j < c; ++j) {
            q += (a[i][j] != a[i - 1][j - 1]);
        }
    }


    int queries;
    cin >> queries;
    while (queries--) {
        int x, y, v;
        cin >> x >> y >> v;

        x--; y--;

        if (x - 1 >= 0 and y - 1 >= 0)
            q -= (a[x][y] != a[x - 1][y - 1]);

        if (x + 1 < r and y + 1 < c)
            q -= (a[x][y] != a[x + 1][y + 1]);

        a[x][y] = v;

        if (x - 1 >= 0 and y - 1 >= 0)
            q += (a[x][y] != a[x - 1][y - 1]);

        if (x + 1 < r and y + 1 < c)
            q += (a[x][y] != a[x + 1][y + 1]);

        if (q == 0)
            cout << "Yes";
        else
            cout << "No";
        cout << "\n";
    }
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