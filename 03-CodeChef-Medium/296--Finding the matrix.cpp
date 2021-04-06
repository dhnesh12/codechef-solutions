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
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define sz size()
#define all(v) (v).begin(), (v).end()
#define uni(v) sort(all(v)); (v).erase(unique(all(v)), (v).end());
#define pii pair<int, int>
#define vi vector<int>
#define vpii vector<pii>
#define vvi vector<vi>
#define fi first
#define se second
#define umap unordered_map
#define uset unordered_set
#define pqueue priority_queue
#define si(a) scanf("%d", &a)
#define sll(a) scanf("%lld", &a)
#define bitcount(x) __builtin_popcount(x)
#define cps CLOCKS_PER_SEC
#define PI acos(-1.0)
#define EPS 1e-9
#define mod 1000000007
#define MOD 1000000007
#define N 1005
using namespace std;

#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    cerr << name << " : " << arg1 << '\n';
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}

template<typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;

template<typename T>
using maxpq = priority_queue<T>;

//All indexing is 0-based
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update> ordered_set;
//methods: find_by_order(k); & order_of_key(k);
//To make it an ordered_multiset, use pairs of (value, time_of_insertion)
//to distinguish values which are similar Or
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, 
             tree_order_statistics_node_update> ordered_multiset;

template<class key, class value, class cmp = std::less<key>>
using ordered_map = tree<key, value, cmp, rb_tree_tag, tree_order_statistics_node_update>;
//ordered_map<int, int> my_map;

template<typename T>
void printv(const vector<T>& v) { for(auto i : v) cerr << i << ' '; cerr << '\n'; }

//Returns no. of values x for which ceil(n / x) == y (y must be > 1).
inline ll CC(ll n, ll y) { return iceil(n, y-1) - iceil(n, y); }

//Returns no. of values x for which floor(n / x) == y
inline ll FF(ll n, ll y) { return n / y - n / (y+1); }

//a and b are assumed to be taken modulo p
inline int add(int a, int b, int p = mod){ int c = a + b; if(c >= p) c -= p; return c; }
inline int sub(int a, int b, int p = mod){ int c = a - b; if(c < 0) c += p; return c; }
inline int mul(int a, int b, int p = mod){ return (a * 1ll * b) % p; }

#define int ll
// #define trace(...) 42

int n, a[N][N], b[N][N];
int cnt; //Count of components
auto &num = cnt;
vvi comp;
vi adj[N]; 
bool adjM[N][N];

bool check_symmetric() {
    bool ok = 1;
    rep(i, 0, n) rep(j, i+1, n)
        ok &= b[i][j] == b[j][i];
        
    return ok;
}

bool check_diagonals() {
    bool ok = 1;
    rep(i, 0, n) ok &= b[i][i] >= 0;
    return ok;
}

bool ek_aur_check() {
    bool ok = 1;
    rep(i, 0, n) 
        rep(j, 0, n)
            if(!b[i][i] || !b[j][j])
                ok &= !b[i][j];
    return ok;
}

bool vis[N];

void dfs(int i) {
    vis[i] = 1;
    comp[num].pb(i);
    for(int j : adj[i]) {
        if(!vis[j]) {
            dfs(j);
        }
    }
}
        
void find_components() {
    comp.clear();
    fill(vis, vis + n, 0);
    rep(i, 0, n) adj[i].clear();
    rep(i, 0, n) rep(j, 0, n) adjM[i][j] = 0;

    rep(i, 0, n) {
        rep(j, i + 1, n) {
            if(b[i][j]) {
                adj[i].pb(j); adj[j].pb(i);
                adjM[i][j] = adjM[j][i] = 1;
            }
        }
    }

    rep(i, 0, n) {
        if(b[i][i] == 0 || vis[i]) continue;
        comp.pb({});
        dfs(i);
        // sort(all(comp[num]));
        //printv(comp[num]);
        num++;
    }
}

//Checks for every component to be completely connected.
bool check_complete() {
    bool ok = 1;
    for(auto& v : comp) {
        for(int i : v) {
            for(int j : v) {
                if(i == j) continue;
                ok &= adjM[i][j];
            }
        }
    }
    return ok;
}

void init() {
    rep(i, 0, n) rep(j, 0, n) a[i][j] = 0;
    cnt = 0;
}

bool dfs1(int i, int col) {
    vis[i] = 1;
    for(int j : adj[i]) {
        if(!vis[j]) {
            a[j][col] = b[i][j] * a[i][col];
            if(!dfs1(j, col)) return 0;
        }
        else {
            if(a[j][col] != b[i][j] * a[i][col]) 
                return 0;
        }
    }
    return 1;
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

    tests(t) {
        cin >> n;
        init();
        rep(i, 0, n) rep(j, 0, n) 
              cin >> b[i][j];
        if(!check_symmetric() || !check_diagonals() || !ek_aur_check()) {
            cout << -1 << '\n'; continue;
        }
        //db(0);
        find_components();
        //db(1);
        if(!check_complete()){
            cout << -1 << '\n'; continue;
        }
        //db(2);
        bool ok = 1;
        fill(vis, vis + n, 0);
        //Assign ith component to ith column
        for(int col = 0; col < cnt; col++) {
            a[comp[col][0]][col] = -1;
            ok &= dfs1(comp[col][0], col);
        }
        if(!ok) {cout << -1 << '\n'; continue;}
        else {
            rep(i, 0, n) {
                rep(j, 0, n) {
                    cout << a[i][j] << ' ';
                } cout << '\n';
            }
        }
    }

    cerr << "...don't you ever hang your head.\n";
    cerr << "Time (in ms): " << double(clock() - clk) * 1000.0 / cps << '\n';
}

//Compile using:
//g++ -o filename.exe --std=c++11 filename.cpp
//Use -D CP for defining a macro CP in the local environment





