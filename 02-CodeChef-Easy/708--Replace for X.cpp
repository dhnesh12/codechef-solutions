// Problem: Replace for X
// Contest: CodeChef - Practice(Easy)
// URL: https://www.codechef.com/problems/REPLESX
// Memory Limit: 256 MB
// Time Limit: 1000 ms

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>

using namespace std;

double pi = acos(-1);
#define tezi                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);                       \
    cout.tie(0);
#define F_OR(i, a, b, s) \
    for (ll i = (a); (s) > 0 ? i < (b) : i >= (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1)
#define FOR(...)       \
    F_ORC(__VA_ARGS__) \
    (__VA_ARGS__)
#define EACH(x, a) for (auto &x : a)
#define itr(it, a) for (auto it = a.begin(); it != a.end(); it++)

#define fill(a, b) memset(a, b, sizeof(a))
#define LOCAL
#define time cout << (0.1 * clock()) / CLOCKS_PER_SEC << endl;
#define countBits(x) __builtin_popcount(ll(x))
#define countZeroesAtBegin(x) __builtin_clz(ll(x))
#define countZeroesAtEnd(x) __builtin_ctz(ll(x))
#define last(x) x[x.end() - x.begin() - 1]
#define pb push_back
#define bg begin
#define ff first
#define ss second
#define pi 3.1415926535897932384626
#define infll 0x3f3f3f3f3f3f3f3f
using ll = long long;
using pl = pair<ll, ll>;
using vll = vector<ll>;
using vpl = vector<pl>;
using mat = vector<vll>;
const ll MAX = 1e5;
const ll mod = 1e9 + 7;
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, 0, sizeof(x))
#define sortall(x) sort(all(x))
static int row[4] = {-1, 0, 0, 1};
static int col[4] = {0, -1, 1, 0};

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    EACH(ele, v) { cout << ele << " "; }
    return os;
}

template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
    return os << '(' << p.ff << "," << p.ss << ')';
}

template <typename T>
istream &operator>>(istream &in, vector<T> &v) {
    EACH(ele, v) { cin >> ele; }
    return in;
}

// Debugging Template
template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string &s) { return '"' + s + '"'; }

string to_string(const char *s) { return to_string((string)s); }

string to_string(bool b) { return (b ? "true" : "false"); }

string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template <size_t N>
string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " +
           to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " +
           to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

void _runtime_terror_() {
    ll N, p, k, x, steps = 0;
    cin >> N >> x >> p >> k;
    vll v(N);
    cin >> v;
    sort(v.begin(), v.end());
    // debug(v);
    k -= 1, p -= 1;
    function<bool()> match_pos = [&]() -> bool {
        if (v[p] == x) {
            return true;
        }
        return false;
    };
    if (match_pos()) {
        cout << "0" << endl;
        return;
    }
    function<ll(ll)> present = [&](ll num) -> ll {
        auto it = find(v.begin(), v.end(), num);
        if (it != v.end()) {
            return (it - v.begin());
        }
        return -1;
    };
    ll pos = present(x);
    if (pos == -1) {
        v[k] = x;
        ++steps;
        sortall(v);
        pos = present(x);
    }
    if (v[p] == x) {
        cout << steps << endl;
        return;
    } else if (pos > p && p >= k) {
        steps += (pos - p);
        cout << steps << endl;
    } else {
        FOR(i, p, 0, -1) {
            if (v[i] == x) {
                pos = i;
                break;
            }
        }
        if (pos < p && p <= k) {
            steps += p - pos;
            cout << steps << endl;
        } else
            cout << -1 << endl;
    }
}

int main() {
    tezi;
    int tc;
    cin >> tc;
    while (tc--) {
        _runtime_terror_();
    }
    return 0;
}
