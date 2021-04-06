#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
//#pragma GCC optimize(3)
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma GCC target("sse3","sse2","sse")
//#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
//#pragma GCC target("f16c")
//#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
//#pragma GCC diagnostic error "-fwhole-program"
//#pragma GCC diagnostic error "-fcse-skip-blocks"
//#pragma GCC diagnostic error "-funsafe-loop-optimizations"
//#pragma GCC diagnostic error "-std=c++14"
#include "bits/stdc++.h"
#include "ext/pb_ds/tree_policy.hpp"
#include "ext/pb_ds/assoc_container.hpp"

#define PB push_back
#define PF push_front
#define LB lower_bound
#define UB upper_bound
#define fr(x) freopen(x,"r",stdin)
#define fw(x) freopen(x,"w",stdout)
#define REP(x, l, u) for(ll x = l;x<u;x++)
#define RREP(x, l, u) for(ll x = l;x>=u;x--)
#define complete_unique(a) a.erase(unique(begin(a),end(a)),end(a))
#define mst(x, a) memset(x,a,sizeof(x))
#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define MP make_pair
#define lowbit(x) ((x)&(-(x)))
#define bitcnt(x) (__builtin_popcountll(x))
#define lson (ind<<1)
#define rson (ind<<1|1)
#define se second
#define fi first
#define sz(x) ((int)x.size())
#define EX0 exit(0);

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ld;
using namespace __gnu_pbds; //required
using namespace std;
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef vector<ll> VLL;
typedef vector<int> VI;
const ll mod = 1e9 + 7;


string to_string (string s) { return '"' + s + '"'; }

string to_string (const char *s) { return to_string ((string) s); }

string to_string (bool b) { return (b ? "true" : "false"); }

template<typename A, typename B>
string to_string (pair<A, B> p) { return "(" + to_string (p.first) + ", " + to_string (p.second) + ")"; }

template<typename A>
string to_string (A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) { res += ", "; }
        first = false;
        res += to_string (x);
    }
    res += "}";
    return res;
}

void debug_out () { cerr<<endl; }

template<typename Head, typename... Tail>
void debug_out (Head H, Tail... T) {
    cerr<<" "<<to_string (H);
    debug_out (T...);
}

#ifdef LOCAL
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define dbg(...) {}
#endif

template<typename T, typename S>
inline bool upmin (T &a, const S &b) { return a > b ? a = b, 1 : 0; }

template<typename T, typename S>
inline bool upmax (T &a, const S &b) { return a < b ? a = b, 1 : 0; }


ull twop (ll x) { return 1ULL<<x; }

ll MOD (ll a, ll m) {
    a %= m;
    if (a < 0)a += m;
    return a;
}

ll inverse (ll a, ll m) {
    a = MOD (a, m);
    if (a <= 1)return a;
    return MOD ((1 - inverse (m, a) * m) / a, m);
}

template<typename T>
T sqr (T x) { return x * x; }

ll gcd (ll a, ll b) {
    a = abs (a), b = abs (b);
    while (b != 0) {
        a %= b;
        swap (a, b);
    }
    return a;
}

ll fast (ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b & 1)ans *= a;
        a *= a;
        b /= 2;
    }
    return ans;
}

ll fast (ll a, ll b, ll mod) {
    if (b < 0)a = inverse (a, mod), b = -b;
    ll ans = 1;
    while (b) {
        if (b & 1)ans = ans * a % mod;
        a = a * a % mod;
        b /= 2;
    }
    return ans % mod;
}

namespace CircleSquareTree {
    struct Edge {
        ll from, to, id;
        
        Edge (ll from, ll to, ll id) : from (from), to (to), id (id) {}
    };
    
    
    const ll N = 500010 * 2; //开两倍
    
    ll low[N], dfn[N], cnt = 1, square;
    vector<Edge> adj[N];
    vector<Edge> stack;
    
    VLL realAdj[N]; // 点双树边
    
    void addRealEdge (int a, int b) {
        realAdj[a].PB (b);
        realAdj[b].PB (a);
    }
    
    void addEdge (int a, int b, int id) {
        adj[a].PB (Edge (a, b, id));
        adj[b].PB (Edge (b, a, id));
    }
    
    void tarjan (ll cur, Edge edge) {
        dfn[cur] = low[cur] = cnt++;
        for (auto e:adj[cur]) {
            if (e.id != edge.id) {
                auto to = e.to;
                if (!dfn[to]) {
                    stack.PB (e);
                    tarjan (to, e);
                    upmin (low[cur], low[to]);
                    if (low[to] >= dfn[cur]) {
                        vector<Edge> components;
                        while (true) {
                            auto cur = stack.back ();
                            stack.pop_back ();
                            components.PB (cur);
                            if (cur.id == e.id)break;
                        }
                        if (sz(components) == 1) {
                            // bridge
                            addRealEdge (cur, e.to);
                        } else {
                            // bcc
                            auto center = square++;
                            for (auto edge:components) {
                                addRealEdge (center, edge.from);
                                addRealEdge (center, edge.to);
                            }
                        }
                    }
                } else {
                    upmin (low[cur], dfn[to]);
                }
            }
        }
    }
    
    // 圆方树在realAdj，编号为 [1,square)
    void run (int n, vector<PLL > edges) {
        fill (low, low + n + 1, 0);
        fill (dfn, dfn + n + 1, 0);
        cnt = 1, square = n + 1;
        REP(i, 0, (n + 1) * 2)adj[i].clear ();
        REP(i, 0, (n + 1) * 2)realAdj[i].clear ();
        stack.clear ();
        REP(i, 0, sz (edges)) {
            addEdge (edges[i].fi, edges[i].se, i);
        }
        tarjan (1, Edge (0, 0, -1));
        REP(i, 1, square) {
            sort (all(realAdj[i]));
            complete_unique(realAdj[i]);
        }
    }
    
    vector<VI> getStartNodes (int n) {
        vector<VI> nodes;
        REP(i, 1, n + 1) {
            if (sz(realAdj[i]) == 1 and realAdj[i][0] <= n) {
                nodes.PB ({static_cast<int>(i)});
            }
        }
        REP(i, n + 1, square) {
            int cnt = 0;
            VI tmp;
            for (auto son:realAdj[i]) {
                if (sz(realAdj[son]) > 1) {
                    cnt++;
                } else {
                    tmp.PB (son);
                }
            }
            if (cnt <= 1) {
                nodes.PB (tmp);
            }
        }
        return nodes;
    }
    
    
}

namespace BipolarOrientation {
    const ll N = 500010;
    VLL adj[N], tree[N];
    ll n, m;
    list<int> order;
    list<int>::iterator ptr[N];
    ll dfn[N], low[N], dfnToID[N], cnt = 1;
    int sign[N];
    
    
    void dfs (int cur, int fa) {
        dfn[cur] = low[cur] = cnt++;
        dfnToID[dfn[cur]] = cur;
        for (auto nxt:adj[cur]) {
            if (nxt == fa)continue;
            if (!dfn[nxt]) {
                dfs (nxt, cur);
                tree[cur].PB (nxt);
                upmin (low[cur], low[nxt]);
            } else {
                upmin (low[cur], dfn[nxt]);
            }
        }
    }
    
    
    void dfs2 (int cur, int fa) {
        dbg(cur, fa);
        if (cur != order.front () and cur != order.back ()) {
            if (sign[dfnToID[low[cur]]]) {
                ptr[cur] = order.insert (ptr[fa], cur);
            } else {
                ptr[cur] = order.insert (next (ptr[fa]), cur);
            }
            sign[fa] = !sign[dfnToID[low[cur]]];
        }
        for (auto nxt:tree[cur]) {
            dfs2 (nxt, cur);
        }
    }
    
    
    void clean () {
        cnt = 1;
        order.clear ();
        fill (sign, sign + n + 1, 0);
        fill (low, low + n + 1, 0);
        fill (dfn, dfn + n + 1, 0);
        fill (dfnToID, dfnToID + n + 1, 0);
        fill (tree, tree + n + 1, VLL ());
        fill (adj, adj + n + 1, VLL ());
    }
    
    void construct (int s, int t) {
        sign[s] = true;
        adj[s].insert (begin (adj[s]), t);
        adj[t].insert (begin (adj[t]), s);
        order.push_back (s);
        ptr[s] = prev (order.end ());
        order.push_back (t);
        ptr[t] = prev (order.end ());
        dfs (s, 0);
        dfs2 (s, 0);
        for (auto i:order)cout<<i<<" ";
    }
    
    void main (int _n, vector<PLL > edges, int s, int t) {
        n = _n;
        m = sz(edges);
        clean ();
        for (auto e:edges) {
            adj[e.fi].PB (e.se);
            adj[e.se].PB (e.fi);
        }
        construct (s, t);
    }
}


namespace SOLVE {
    int v[500100];
    
    void main () {
        int n, m;
        cin>>n>>m;
        REP(i, 1, n + 1)cin>>v[i];
        vector<PLL > edges (m);
        for (auto &e:edges) {
            cin>>e.first>>e.second;
        }
        CircleSquareTree::run (n, edges);
        auto nodes = CircleSquareTree::getStartNodes (n);
        VI leaves;
        for (auto &array:nodes) {
            leaves.PB (*min_element (all(array), [] (const int a, const int b) { return v[a] < v[b]; }));
        }
        sort (all(leaves), [] (const int a, const int b) { return v[a] < v[b]; });
        if (leaves.size () == 1)leaves.PB (leaves[0] == 1 ? n : 1);
        
        
        cout<<sz(leaves) - 1<<endl;
        int s = leaves[0], t = leaves.back ();
        REP(i, 1, sz (leaves) - 1)cout<<leaves[i]<<" ";
        set<int> front_nodes;
        REP(i, 0, sz (leaves) - 1) {
            front_nodes.insert (leaves[i]);
        }
        dbg(leaves);
        for (auto &e:edges) {
            auto &a = e.fi, &b = e.se;
            if (front_nodes.count (a))a = s;
            if (front_nodes.count (b))b = s;
        }
        dbg(edges);
        
        BipolarOrientation::main (n, edges, s, t);
        cout<<endl;
        
    }
}


signed main () {
#ifdef LOCAL
    fr("/Users/zhangqingchuan/Desktop/cp/cp/input.txt");
    fw("/Users/zhangqingchuan/Desktop/cp/cp/output.txt");
#endif
    
    
    int t = 1;
    cin>>t;
    for (int i = 1; i <= t; i++) {
//        cout<<"Case #"<<i<<": ";
        SOLVE::main ();
        
    }








//    clock_t st = clock();
//    while(clock() - st < 3.0 * CLOCKS_PER_SEC){
//
//    }
    
    
    
    
    
    
    return 0;
}
