#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

///#define int ll

#define ff first
#define ss second
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define _ << " " <<
#define lb lower_bound
#define ub upper_bound

//#define max(x,y) ((x) > (y) ? (x) : (y))
//#define min(x,y) ((x) < (y) ? (x) : (y))

#ifdef LOCAL
    #define err cerr
#else
    #define err if(0) cerr
#endif // LOCAL

//using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ld, ld> pld;

//template<typename T>
//using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O3")
//#pragma GCC optimize("fast-math")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")

const int MXN = 1e5 + 101;
const int K = 320;

int a[MXN];
int p[MXN];

int n;

vector<pii> d;

void spefbuild(int l, int r) {
    vector<pii> e;
    int x = 1;
    for (int i = 0; i < d.size(); ++i) {
        if (x < l && l < x + (d[i].ss - d[i].ff + 1)) {
            //err << "L" _ d[i].ff _ d[i].ss _ ": " << endl;
            e.push_back({d[i].ff, d[i].ff + (l - x) - 1});
            //err << ">" _ d[i].ff _ d[i].ff + (l - x) - 1 << endl;
            d[i] = {d[i].ff + (l - x), d[i].ss};
            //err << ">" _ d[i].ff + (l - x) _ d[i].ss << endl;
            x += (l - x);
        }
        if (x <= r && r + 1 < x + (d[i].ss - d[i].ff + 1)) {
            //err << "R" _ d[i].ff _ d[i].ss _ ": " << endl;
            e.push_back({d[i].ff, d[i].ff + (r - x)});
            //err << ">" _ d[i].ff _ d[i].ff + (r - x) << endl;
            d[i] = {d[i].ff + (r - x) + 1, d[i].ss};
            //err << ">" _ d[i].ff + (r - x) + 1 _ d[i].ss << endl;
            x += (r - x) + 1;
        }
        x += d[i].ss - d[i].ff + 1;
        e.push_back(d[i]);
    }
    d = e;
}

void init() {
    d.clear();
    int lst = 1;
    for (int i = 1; i <= n; ++i) {
        if (i - lst + 1 == K) {
            d.push_back({lst, i});
            lst = i + 1;
        }
    }
    if (lst <= n) {
        d.push_back({lst, n});
    }
    p[0] = 0;
    for (int i = 1; i <= n; ++i) {
        p[i] = p[i - 1];
        if (i + 1 <= n && a[i] != a[i + 1]) ++p[i];
    }
}

void rebuild() {
    vector<int> v;
    for (auto p: d) {
        for (int i = p.ff; i <= p.ss; ++i) {
            v.push_back(a[i]);
        }
    }
    for (int i = 0; i < v.size(); ++i) {
        a[i + 1] = v[i];
    }
    init();
}

void prnt() {
    cout << "--v--" << endl;
    for (int i = 1; i <= n; ++i) {
        cout << i << " ";
    } cout << endl;
    for (int i = 1; i <= n; ++i) {
        cout << a[i] << " ";
    } cout << endl;
    cout << "p:" << endl;
    for (int i = 1; i <= n; ++i) {
        cout << p[i] << " ";
    } cout << endl;
    for (auto p: d) {
        cout << "[" << p.ff << ";" << p.ss << "] ";
    } cout << endl;
    cout << "--^--" << endl;
}

void mov(int l, int r) {
    spefbuild(l, r);
    vector<pii> e;
    int x = 1;
    for (int i = 0; i < d.size(); ++i) {
        if (l <= x && x + (d[i].ss - d[i].ff) <= r) {
            e.push_back(d[i]);
        }
        x += d[i].ss - d[i].ff + 1;
    }
    x = 1;
    for (int i = 0; i < d.size(); ++i) {
        if (!(l <= x && x + (d[i].ss - d[i].ff) <= r)) {
            e.push_back(d[i]);
        }
        x += d[i].ss - d[i].ff + 1;
    }
    d = e;
}

int get(int l, int r) {
    //err << "get" _ l _ r << endl;
    spefbuild(l, r);
    //prnt();
    int ans = 0;
    int lst = -1;
    int x = 1;
    for (int i = 0; i < d.size(); ++i) {
        if (l <= x && x + (d[i].ss - d[i].ff) <= r) {
            //err << "!" _ d[i].ff _ d[i].ss << endl;
            ans += p[d[i].ss - 1] - p[d[i].ff - 1];
            if (lst != -1 && lst != a[d[i].ff]) {
                ++ans;
            }
            lst = a[d[i].ss];
        }
        x += d[i].ss - d[i].ff + 1;
    }
    //err << "get(" << l << "," << r << ") =" _ ans + 1 << endl;
    return ans + 1;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    init();
    //prnt();
    int m;
    cin >> m;
    int x, y, z;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> z;
    //    err << x _ y _ z << endl;;
        if (x == 1) {
            cout << get(y, z) << endl;
        } else {
            mov(y, z);
        }
        if (d.size() >= 1.1 * K) {
            rebuild();
        }
    //    prnt();
    }
    //prnt();
}

int32_t main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    #ifdef STRESS
        {};
    #else
        ///freopen(".in", "r", stdin);
        ///freopen(".out", "w", stdout);
    #endif // STRESS
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tests = 1;
    cin >> tests;
    while (tests--) {
        solve();
    }
    return 0;
}

