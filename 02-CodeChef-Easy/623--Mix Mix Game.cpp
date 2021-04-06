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
    LL n, z1, z2;
    read(n, z1, z2);
    vll a(n);
    read(a);
    set <LL> s(all(a));

    int ans = 0;

    bool f = 1;
    REP (i, 0, n-1) {
        f &= (s.find(z1 - a[i]) != s.end() or s.find(z2 - a[i]) != s.end() or s.find(-z1 + a[i]) != s.end() or s.find(-z2 + a[i]) != s.end());
        f &= (s.find(z1 + a[i]) != s.end() or s.find(z2 + a[i]) != s.end() or s.find(-z1 - a[i]) != s.end() or s.find(-z2 - a[i]) != s.end());
    }
    if (f) {
        ans = 2;
    }

    if (s.find(z1) != s.end()) ans = 1;
    if (s.find(-z1) != s.end()) ans = 1;
    if (s.find(z2) != s.end()) ans = 1;
    if (s.find(-z2) != s.end()) ans = 1;

    cout << ans << nl;
}

int main() {
    fast;
    int t;
    cin>>t;
    while(t--)
        solve();
}
