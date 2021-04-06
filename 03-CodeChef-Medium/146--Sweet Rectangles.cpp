#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

///#define int ll

#define ff first
#define f first
#define ss second
#define s second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define _ << " " <<
#define db(x) //cout << "OK" << x << endl
#define lb lower_bound
#define ub upper_bound

//#define max(x,y) ((x) > (y) ? (x) : (y))
//#define min(x,y) ((x) < (y) ? (x) : (y))

//using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

//template<typename T>
//using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > sp(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> sp[i][j];
        }
    }
    int cnt = 0;
    vector<vector<int> > gor(n, vector<int>(m));
    vector<vector<int> > ver(n, vector<int>(m));
    vector<set<pair<int, int> > > sorted_gor(n);
    vector<set<pair<int, int> > > sorted_ver(m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            sorted_gor[i].insert({sp[i][j], j});
        }
        int cnt = 0;
        for (auto p : sorted_gor[i]) {
            gor[i][p.second] = cnt;
            ++cnt;
        }
    }
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            sorted_ver[j].insert({sp[i][j], i});
        }
        int cnt = 0;
        for (auto p : sorted_ver[j]) {
            ver[p.second][j] = cnt;
            ++cnt;
        }
    }
    long long corners = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            corners += gor[i][j] * ver[i][j];
        }
    }
    //cout << corners << endl;
    long long sq = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            sq += (n - i - 1) * (m - j - 1);
        }
    }
    //cout << sq << endl;
    //cout << endl;
    long long total = corners - sq;
    cout << total << "\n";
    int q;
    cin >> q;
    int x, y, num;
    for (int req = 0; req < q; ++req) {
        cin >> x >> y >> num;
        --x;
        --y;
        long long fst = 0;
        long long scn = 0;
        for (int i = 0; i < n; ++i) {
            fst += gor[i][y] * ver[i][y];
        }
        for (int j = 0; j < m; ++j) {
            fst += gor[x][j] * ver[x][j];
        }
        fst -= gor[x][y] * ver[x][y];
        sorted_gor[x].erase({sp[x][y], y});
        sorted_gor[x].insert({num, y});
        int cnt = 0;
        for (auto p : sorted_gor[x]) {
            gor[x][p.second] = cnt;
            ++cnt;
        }
        sorted_ver[y].erase({sp[x][y], x});
        sorted_ver[y].insert({num, x});
        cnt = 0;
        for (auto p : sorted_ver[y]) {
            ver[p.second][y] = cnt;
            ++cnt;
        }
        sp[x][y] = num;
        for (int i = 0; i < n; ++i) {
            scn += gor[i][y] * ver[i][y];
        }
        for (int j = 0; j < m; ++j) {
            scn += gor[x][j] * ver[x][j];
        }
        scn -= gor[x][y] * ver[x][y];
        //cout << scn << " " << fst << "\n";
        total += scn - fst;
        cout << total << "\n";
    }
}

int32_t main() {
#ifdef LOCAL

#else
    #define cerr if(0) cerr
#endif // LOCAL
    ///freopen(".in", "r", stdin);
    ///freopen(".out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tests = 1;
    ///cin >> tests;
    while (tests--) {
        solve();
    }
    return 0;
}

