#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define repi(i, a, b) for(int i=(a); i>(b); i--)
#define db(x) (cerr << #x << ": " << (x) << '\n')
#define sync ios_base::sync_with_stdio(false), cin.tie(NULL)
#define tests(t) int t; cin >> t; while(t--)
#define iceil(n, x) (((n) + (x) - 1) / (x))
#define ll long long
#define gcd __gcd
#define eb emplace_back
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define sz size()
#define all(v) (v).begin(), (v).end()
#define uni(v) sort(all(v)); (v).erase(unique(all(v)), (v).end())
#define pii pair<int, int>
#define vi vector<int>
#define vpii vector<pii>
#define vvi vector<vi>
#define fi first
#define se second
#define pqueue priority_queue
#define bitcount(x) __builtin_popcount(x)
#define cps CLOCKS_PER_SEC
#define PI acos(-1.0)
#define EPS 1e-9
#define mod 1000000007
using namespace std;
 
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    cerr << name << " : " << arg1 << '\n';
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ','); cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}

template<typename T1, typename T2>
ostream& operator << (ostream& os, const pair<T1, T2>& p) { return os << '(' << p.fi << ", " << p.se << ')'; }

template<typename T>
void printv(const T& v) { for(auto i : v) cerr << i << ' '; cerr << '\n'; }

template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;
 
template<typename T>
using maxpq = priority_queue<T>;
 
//All indexing is 0-based
using namespace __gnu_pbds;
template<class key, class cmp = std::less<key>>
using ordered_set = tree<key, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;
//methods: find_by_order(k); & order_of_key(k);
//To make it an ordered_multiset, use pairs of (value, time_of_insertion)
//to distinguish values which are similar
 
template<class key, class value, class cmp = std::less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;
 
//Returns no. of values x for which ceil(n / x) == y (y must be > 1).
inline ll CC(ll n, ll y) { return iceil(n, y-1) - iceil(n, y); }
 
//Returns no. of values x for which floor(n / x) == y
inline ll FF(ll n, ll y) { return n / y - n / (y+1); }
 
//a and b are assumed to be taken modulo p
inline int add(int a, int b, int p = mod){ int c = a + b; if(c >= p) c -= p; return c; }
inline int sub(int a, int b, int p = mod){ int c = a - b; if(c < 0) c += p; return c; }
inline int mul(int a, int b, int p = mod){ return (a * 1ll * b) % p; }

#define N 100005
#define int ll
// #define trace(...) 42

#define x first
#define y second
#define y1 Y1

int x1, y1, r1, x2, y2, r2;

int dist2(pii p, pii q) {
    p.x -= q.x;
    p.y -= q.y;
    return p.x * p.x + p.y * p.y;
}

double dist(pii p, pii q) {
    return sqrt(dist2(p, q));
}

bool contains() {
    // trace(r2, r1, dist2({x1, y1}, {x2, y2}), (r2 - r1) * (r2 - r1));
    return r2 >= r1 && dist2({x1, y1}, {x2, y2}) <= (r2 - r1) * (r2 - r1);
}

main()
{   
    #ifndef ONLINE_JUDGE
        freopen("/home/tarun/Desktop/input.txt", "r", stdin);
     // freopen("/home/tarun/Desktop/output.txt", "w", stdout);
    #endif
    sync;
    clock_t clk = clock();
    cerr << "I will return...\n";

    cout << fixed << setprecision(12);

    tests(t) {
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

        if(contains()) {
            cout << "NO\n"; continue;
        }

        pii c1, c2;
        c1 = {x1, y1};
        c2 = {x2, y2};
        cout << "YES\n";
        if(dist2(c1, c2) == 0 || dist2(c1, c2) > (r1 + r2) * (r1 + r2)) {
            cout << c1.x + r1 << ' ' << c1.y << '\n'; continue;
        }

        pair<double, double> vec = c1;
        vec.x -= c2.x;
        vec.y -= c2.y;
        // vec.x = -vec.x, vec.y = -vec.y;

        double d = sqrt(vec.x * vec.x + vec.y * vec.y);

        vec.x /= d;
        vec.y /= d;
        // trace(vec.x, vec.y);

        //vec: Unit vector in the direction of c2c1

        vec.x = c1.x + r1 * vec.x;
        vec.y = c1.y + r1 * vec.y;
        cout << vec.x << ' ' << vec.y << '\n';
    }

    cerr << "...don't you ever hang your head.\n";
    cerr << "Time (in ms): " << (double)(clock() - clk) * 1000.0 / cps << '\n';
}
 
//Compile using:
//g++ -o filename.exe --std=c++11 filename.cpp
//Use -D CP for defining a macro CP in the local environment


