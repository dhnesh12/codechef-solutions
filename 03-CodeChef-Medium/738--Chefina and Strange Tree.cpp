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

struct T{
    ll id, mn;
    T(){}
    T(ll id, ll mn): id(id), mn(mn){}
    inline void clear(){
        mn = INF;
    }
};

struct ST{
    ll n, lazy[1<<20], ar[1<<20];
    T t[1<<20];
    inline T Op(T a, T &b){
        T ty;
        if(a.mn < b.mn){
            ty.id = a.id;
            ty.mn = a.mn;
        }
        else{
            ty.id = b.id;
            ty.mn = b.mn;
        }
        return ty;
    }
    inline void updpro(ll laz, ll id, ll l, ll r){
        if(laz){
            t[id].mn += laz;
            lazy[id] += laz;
        }
    }
    inline void proh(ll id, ll l, ll r){
        ll mid = (l + r)>>1;
        updpro(lazy[id], id<<1, l, mid);
        updpro(lazy[id], id<<1|1, mid, r);
        lazy[id] = 0;
    }
    inline void Upd(ll x, ll y, ll val, ll id, ll l, ll r){
        if(x >= r or y <= l) return;
        if(x <= l and r <= y) {
            updpro(val, id, l, r);
            return;
        }
        proh(id, l, r);
        ll mid = (l + r)>>1;
        Upd(x, y, val, id<<1, l, mid);
        Upd(x, y, val, id<<1|1, mid, r);
        t[id] = Op(t[id<<1], t[id<<1|1]);
    }
    inline T Que(ll x, ll y, ll id, ll l, ll r){
        if(x >= r or y <= l) {T ans; ans.clear(); return ans;}
        if(x <= l and r <= y) return t[id];
        proh(id, l, r);
        ll mid = (l + r)>>1;
        T left, right;
        left = Que(x, y, id<<1, l, mid);
        right = Que(x, y, id<<1|1, mid, r);
        return Op(left, right);
    }
    inline void Build(ll id, ll l, ll r){
        if(l + 1 == r){
            t[id] = T(l, ar[l]);
            return;
        }
        ll mid = (l + r)>>1;
        Build(id<<1, l, mid);
        Build(id<<1|1, mid, r);
        t[id] = Op(t[id<<1], t[id<<1|1]);
    }
    inline void build() { FER(i, 0, n<<1) lazy[i] = 0; Build(1, 0, n);}
    inline void upd(ll x, ll y, ll val) { Upd(x, y, val, 1, 0, n);}
    inline T que(ll x, ll y) { return Que(x, y, 1, 0, n);}
}st;


vi adj[1<<20], graph[1<<20], AdsCFTCorrespondence;
ll id[1<<20], tsz[1<<20], be[1<<20], boc, n;
inline void add(ll a, ll b){
    graph[a].pb(b);
    graph[b].pb(a);
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
    if(u < n) boc++, AdsCFTCorrespondence.pb(u);
    for(auto xd: graph[u]) if(xd != pp)
        dfs(xd, u), tsz[u] += tsz[xd];
}
vi DelEdges[1<<20];

int main(){
    ll t; read(t);
    while(t--){
        read(n);
        vi().swap(AdsCFTCorrespondence);
        FER(i, 0, n) vi().swap(adj[i]), vi().swap(DelEdges[i]), id[i] = i;
        FER(i, 0, n<<1) vi().swap(graph[i]);
        vii edges;
        map<ii, ll> get;
        FER(i, 0, n - 1){
            ll a, b; read(a), read(b); a--, b--;
            edges.pb({a, b});
            get[{a, b}] = i;
            get[{b, a}] = i;
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vi P(n), A(n), B(n), vis(n, 0), rt(n), cost, BunChan(n, -1), rev;
        FER(i, 0, n) read(P[i]), P[i]--;
        FER(i, 0, n) read(A[i]);
        FER(i, 0, n) read(B[i]);
        FER(i, 0, n){
            for(auto xd: adj[P[i]]){
                auto id = get[{P[i], xd}];
                if(!vis[id]){
                    DelEdges[i].pb(id);
                    vis[id]++;
                }
            }
        }
        boc = n;
        IFR(i, n - 1, 0){
            for(auto xd: DelEdges[i]) unir(edges[xd].ff, edges[xd].ss);
            rt[i] = find(P[i]);
        }
        cost.resize(n, INF), rev.resize(n, -1);
        auto root = boc - 1;
        boc = 0;
        dfs(root, -1);
        FER(i, 0, sz(AdsCFTCorrespondence)) if(AdsCFTCorrespondence[i] < n) cost[i] = B[AdsCFTCorrespondence[i]], rev[i] = AdsCFTCorrespondence[i];
        st.n = sz(cost);
        FER(i, 0, st.n) st.ar[i] = cost[i];
        st.build();
        FER(i, 0, n){
            auto l = be[rt[i]], r = l + tsz[rt[i]];
            st.upd(l, r, -A[P[i]]);
            for(;;){
                auto cur = st.que(l, r);
                if(cur.mn > 0) break;
                BunChan[rev[cur.id]] = i + 1;
                st.upd(cur.id, cur.id + 1, INF);
            }
        }
        FER(i, 0, n) cout<<BunChan[i]<<" "; cout<<"\n";
    }
    return 0;
}