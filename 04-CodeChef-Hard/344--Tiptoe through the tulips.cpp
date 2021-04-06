// I'm going through changes...
// Here we go again...
// It's so insane, 'cause we always end up getting fed up... 
// And then, we always end up trying one more time...
// Despite of the fact, take in mind that...
// At your absolute best, you still won't be good enough for the wrong person... 
// At your worst, you'll still be worth it to the right person...
 
// *********************************0.5*************************************
// El amor siempre va sin razón... y fue así que llegó a mi corazón...
// ¿Como fue?...Aún no se que pasó...
// Aversión o atracción lo que nos unió...
// Discutir por todo pelear... Es una extraña manera de amar...
// ¿Por que no demostrar amor?...
// Un te quiero y ya... con un beso y ya... y así todo podría ser mejor...
// Mira el tiempo... va de deprisa... tal vez te puedas arrepentir...
// Todo se acaba y no avisa... tienes tu vida por vivir...
// Si me vez... oye!, soy de ti... Este amor esta creciendo...
// Por favor... di que sí... y te entregaré mi corazón...
// Oye lo que estoy diciendo... olvida la amargura... y dame tu ternura... 
// Discutir por todo pelear... Es una extraña manera de amar...
// ¿Por que no demostrar amor?...
// Un te quiero y ya... con un beso y ya... y asi todo podría ser mejor...
 
// *************************************************************************
 
 
#pragma GCC optimize ("Ofast,unroll-loops")
// #pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
 
#define pb push_back
#define ff  first
#define ss second
#define tm1 first
#define tm2 second.first
#define tm3 second.second
#define sz(x) ll(x.size())
#define fill(x, v) memset(x, v, sizeof(x))
#define all(v) (v).begin(), (v).end()
#define FER(i,a,b) for(ll i=ll(a); i< ll(b); ++i)
#define IFR(i,a,b) for(ll i=ll(a); i>=ll(b); --i )
#define fastio ios_base::sync_with_stdio(0); cin.tie(0)
 
#define N 400005 
#define mod1 1000000007
// #define mod1 998244353
#define mod2 1000000009
#define bas 987625403
#define sqr(x) (x)*(x)  
#define INF 2e18
 
using namespace std;
using namespace __gnu_pbds;
 
 
typedef long long ll;
typedef pair<ll, ll> ii;
typedef pair<ll, ii > tri;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> S_t;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
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
#define trace(...) fff(#__VA_ARGS__, __VA_ARGS__)
template<typename t> void fff(const char* x, t&& val1) { cout<<x<< " : "<<val1<<"\n";}
template<typename t1, typename... t2> void fff(const char* x, t1&& val1, t2&&... val2){
    const char* xd=strchr(x+1, ',');
    cout.write(x, xd-x)<<" : "<<val1<<" | ";
    fff(xd+1, val2...);
}
 
inline ll add(ll a, ll b, ll mod) { return a+b < mod? a+b : a+b-mod;}
inline ll rem(ll a, ll b, ll mod) { return a >= b? a - b: a- b + mod;}
inline ll mul(ll a, ll b, ll mod) { return (long long) a*b%mod;}
inline void Mul(ll &a, ll b, ll mod) { a = (long long) a*b%mod;}
inline ll bp(ll a, ll p, ll mod){
    ll ret;
    for(ret = 1; p; p>>=1, Mul(a, a, mod)) (p & 1) && (Mul(ret, a, mod), 1);
    return ret;
}
 
static inline void read(ll &result) {
    bool minus = false;
    char ch;
    ch = getchar();
    while (true) {
        if (ch == '-') break;
        if (ch >= '0' and ch <= '9') break;
        ch = getchar();
    }
    (ch == '-')? minus = true: result = ch-'0';
    while (true) {
        ch = getchar();
        if (ch < '0' or ch > '9') break;
        result = (result<<3)+ (result<<1) + (ch - '0');
    }
    if(minus) result = -result;
}

ll id[1<<20], tsz[1<<20], be[1<<20], boc, n;
vi adj[1<<20];
inline void add(ll a, ll b){
    adj[a].pb(b);
    adj[b].pb(a);
}
inline ll find(ll x){
    while(x != id[x]) id[x] = id[id[x]], x = id[x];
    return x;
}
inline void unir(ll a, ll b){
    a = find(a), b = find(b);
    id[boc] = id[a] = id[b] = boc;
    add(boc, a);
    if(a != b) add(boc, b);
    boc++;
}
inline void dfs(ll u, ll pp){
    tsz[u] = u < n, be[u] = boc;
    if(u < n) boc++;
    for(auto xd: adj[u]) if(xd != pp) 
        dfs(xd, u), tsz[u] += tsz[xd];
}

int main(){
    ll t; read(t);
    while(t--){
        read(n);
        vector<tri> edges;
        vector<pair<ii, ii>> Q;
        FER(i, 0, n) id[i] = i;
        FER(i, 0, n<<1) vi().swap(adj[i]);
        FER(i, 0, n - 1){
            ll a, b, c; read(a), read(b), read(c); a--, b--;
            edges.pb({c, {a, b}});
        }
        ll q, x, d, u, k; read(q), read(x);
        vi rt(q, -1);
        FER(i, 0, q){
            read(d), read(u), read(k); u--;
            Q.pb({{i, d}, {u, k}});
        }
        sort(all(edges)), sort(all(Q), [&](pair<ii, ii> &a, pair<ii, ii> &b){
            return a.ss.ss < b.ss.ss;
        });
        boc = n;
        ll xx = 0, yy = 0;
        for(;yy < q;){
            auto ret = Q[yy];
            ll id = ret.ff.ff, d = ret.ff.ss, u = ret.ss.ff, k = ret.ss.ss;
            while(xx < sz(edges) and edges[xx].tm1 <= k){
                unir(edges[xx].tm2, edges[xx].tm3);
                xx++;
            }
            rt[id] = find(u);
            yy++;
        }
        while(xx < sz(edges)) unir(edges[xx].tm2, edges[xx].tm3), xx++;
        auto root = boc - 1;
        boc = 0;
        dfs(root, -1);
        sort(all(Q), [&](pair<ii, ii> &a, pair<ii, ii> &b){
            return a.ff.ff < b.ff.ff;
        });
        set<tri> s;
        vector<set<tri>::iterator> tnt;
        s.insert({0, {n, 1}});
        auto upd = [&](ll l, ll r, ll valor){
            vector<set<tri>::iterator>().swap(tnt);
            auto it = s.upper_bound({l, {INF, -1}});
            it--;
            ll ans = 0;
            while(1){
                if((*it).tm2 >= r){
                    tnt.pb(it);
                    break;
                }
                tnt.pb(it);
                it++;
            }
            FER(j, 0, sz(tnt)){
                auto cur = *tnt[j];
                if(!j or j == sz(tnt) - 1){
                    if(!j){
                        if(cur.tm2 > r) s.insert({r, {cur.tm2, cur.tm3}});
                        if(cur.tm1 < l) s.insert({cur.tm1, {l, cur.tm3}});
                        if(cur.tm3 <= valor) ans += min(cur.tm2, r) - l;
                        s.erase(tnt[j]);
                        continue;
                    }
                    if(j == sz(tnt) - 1){
                        if(cur.tm2 > r) s.insert({r, {cur.tm2, cur.tm3}});
                        if(cur.tm3 <= valor) ans += r - max(l, cur.tm1);
                        s.erase(tnt[j]);
                        continue;
                    }
                }
                if(cur.tm3 <= valor) ans += cur.tm2 - cur.tm1;
                s.erase(tnt[j]);
            }
            s.insert({l, {r, valor + x}});
            return ans;
        }; 
        FER(i, 0, q){
            auto ret = Q[i];
            ll id = ret.ff.ff, d = ret.ff.ss, u = ret.ss.ff, k = ret.ss.ss;
            auto l = be[rt[id]], r = l + tsz[rt[id]];
            auto BunChan = upd(l, r, d);
            cout<<BunChan<<"\n";
        }
    }
    return 0;
}

// ini: 8:32
// fin: 9:13