#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math,inline")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define mod         1000000007
#define pi          3.1415926535898
#define eps         1e-9


#define fast       ios::sync_with_stdio(0); cin.tie(0);cout.tie(0)
#define vt vector
#define ar array
#define fs          first
#define sc          second
#define pb         push_back
#define sp          printf(" ")
#define nl          '\n'
#define all(a) a.begin(),a.end()
#define unique(c) (c).resize(unique(all(c)) - (c).begin())
#define sz(x) (int)(x).size()
#define revsort(x) sort(all(x));reverse(all(x))

#define REP(i,start,end) for (int i = start; i <=end; i++)
#define RREP(i,end,start) for (int i=end; i>=start ;i--)
#define EACH(x, a) for (auto& x: a)

typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<LL> vll;
typedef vector<double> vd;
typedef vector<vector<LL> > matrix;
typedef vector<vector<int> > graph;


 
template<class A> void read(vt<A>& v);
template<class A, size_t S> void read(ar<A, S>& a);
template<class T> void read(T& x) {
    cin >> x;
}
void read(double& d) {
    string t;
    read(t);
    d=stod(t);
}
void read(long double& d) {
    string t;
    read(t);
    d=stold(t);
}
template<class H, class... T> void read(H& h, T&... t) {
    read(h);
    read(t...);
}
template<class A> void read(vt<A>& x) {
    EACH(a, x)
        read(a);
}
template<class A, size_t S> void read(array<A, S>& x) {
    EACH(a, x)
        read(a);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
int getRand(int l, int r)
{
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int add (LL var1, LL var2) {
    return ( (var1 % mod) + (var2 % mod) + mod) % mod;
}

int mul (LL var1, LL var2) {
    return (var1*var2) % mod;
}

int powm (LL x, LL y) {
    int ans = 1;
    while (y) {
        if (y & 1) {
            ans = mul(ans, x);
        }
        x = mul(x, x);
        y /= 2;
    }
    return ans;
}

int inv(LL x) {
    return powm(x, mod-2);
}

LL INF=1e9;

void solve() {
    int n, m;
    read(n, m);
    vector <string> grid(n);
    read(grid);
    string s;
    read(s);

    function <void()> up = [&] () {
        REP (j, 0, m-1) {
            int cnt = 0;
            REP (i, 0, n-1) cnt += grid[i][j] - '0';
            REP (i, 0, cnt-1) grid[i][j] = '1';
            REP (i, cnt, n-1) grid[i][j] = '0';
        }
    };

    function <void()> down = [&] () {
        REP (j, 0, m-1) {
            int cnt = 0;
            REP (i, 0, n-1) cnt += grid[i][j] - '0';
            REP (i, n-cnt, n-1) grid[i][j] = '1';
            REP (i, 0, n-cnt-1) grid[i][j] = '0';
        }
    };

    function <void()> left = [&] () {
        REP (i, 0, n-1) {
            int cnt = 0;
            REP (j, 0, m-1) cnt += grid[i][j] - '0';
            REP (j, 0, cnt-1) grid[i][j] = '1';
            REP (j, cnt, m-1) grid[i][j] = '0';
        }
    };

    function <void()> right = [&] () {
        REP (i, 0, n-1) {
            int cnt = 0;
            REP (j, 0, m-1) cnt += grid[i][j] - '0';
            REP (j, 0, cnt-1) grid[i][j] = '1';
            REP (j, cnt, m-1) grid[i][j] = '0';
            reverse(all(grid[i]));
        }
    };

    
    map <int, int> mp;
    REP (i, 0, sz(s)-1) {
        mp[s[i]] = i+1;
    }
    if (s[0] == 'U') {
        up();
    } else if (s[0] == 'D') {
        down();
    } else if (s[0] == 'L') {
        left();
    } else {
        right();
    }
    int m1 = 0;
    m1 = max(mp['U'], mp['D']);
    vector <char> op;
    if (m1) op.pb(s[m1-1]);

    int m2 = 0;
    m2 = max(mp['L'], mp['R']);
    if (m2) op.pb(s[m2-1]);

    if (m1 and m2 and m1 > m2) {
        swap(op[0], op[1]);
    }
    if (sz(op) > 0) {
        if (op[0] == 'U') {
            up();
        } else if (op[0] == 'D') {
            down();
        } else if (op[0] == 'L') {
            left();
        } else {
            right();
        }
    }

    if (sz(op) > 1) {
        if (op[1] == 'U') {
            up();
        } else if (op[1] == 'D') {
            down();
        } else if (op[1] == 'L') {
            left();
        } else {
            right();
        }
    }

    REP (i, 0, n-1) {
        REP (j, 0, m-1) {
            cout << grid[i][j];
        }
        cout << nl;
    }
    

}

int main() {
    fast;
    int t;
    cin>>t;
    while(t--)
        solve();
}
