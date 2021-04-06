#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef long double ld;

#ifdef LOCAL
#define Gene template< class
#define Rics printer& operator,
Gene c> struct rge{c b, e;};
Gene c> rge<c> range(c i, c j){ return {i, j};}
struct printer{
    ~printer(){cerr<<endl;}
    Gene c >Rics(c x){ cerr<<boolalpha<<x; return *this;}
    Rics(string x){cerr<<x;return *this;}
    Gene c, class d >Rics(pair<c, d> x){ return *this,"(",x.first,", ",x.second,")";}
    Gene ... d, Gene ...> class c >Rics(c<d...> x){ return *this, range(begin(x), end(x));}
    Gene c >Rics(rge<c> x){
        *this,"["; for(auto it = x.b; it != x.e; ++it)
            *this,(it==x.b?"":", "),*it; return *this,"]";}
};
#define debug() cerr<<"LINE "<<__LINE__<<" >> ", printer()
#define dbg(x) "[",#x,": ",(x),"] "
#define tham getchar()
#endif

#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define eq(x, y) (fabs((x)-(y))<error)
#define bt(i) (1LL<<(i))

mt19937_64 rng((unsigned)chrono::system_clock::now().time_since_epoch().count());
const ll mod = 1e9+7;
//const ld error = ;
const ld PI = acosl(-1);

//inline ll MOD(ll x, ll m = mod){
//    ll y = x % m;
//    return (y >= 0) ? y: y+m;
//}

//const int/ll inf = ;
const int nmax = 3e5+10;
///===========================================  template  =======================================================

vector<int> adj[nmax];
ll subtree[nmax];

int n;
ll ans1 = 0;

void addself(ll &x, ll y){
    x += y;
    if(x >= mod) x-= mod;
}

ll memo[nmax][4][3];

void dfs(int u, int p){
    subtree[u] = 1;
    for(int v : adj[u]){
        if(v != p){
            dfs(v, u);
            subtree[u] += subtree[v];
        }
    }

    ll sum = n - subtree[u];
    ll paths = n-1;
    for(int v : adj[u]){
        if(v == p) continue;
        paths = (paths + sum * subtree[v]) % mod;
        sum += subtree[v];
        if(sum >= mod) sum -= mod;
    }

    ans1 += paths * (paths-1) % mod * (paths-2);
    ans1 %= mod;

    if(p != -1){
        paths = subtree[u] * (n-subtree[u]) % mod;
        ans1 -= paths * (paths-1) % mod * (paths-2);
        ans1 %= mod;
        if(ans1 < 0) ans1 += mod;
    }

    memo[u][0][0] = 1;
    for(auto v : adj[u]){
        if(v == p) continue;

        ll memo2[4][3] = {1};


        for(int i = 3; i>=0; i--){
            for(int j = 3-i; j>=0; j--){
                if(i+j == 0) continue;

                ll tmp = (memo[v][j][0] + memo[v][j][1] + memo[v][j][2]) % mod;

                memo2[i+j][2] += memo[u][i][1] * memo[v][j][0];
                if(j < 3)
                    memo2[i+j][2] += memo[u][i][1] * memo[v][j+1][1];
                memo2[i+j][2] += memo[u][i][2] * tmp;
                memo2[i+j][2] %= mod;

                if(j > 0)
                    memo2[i+j][1] += memo[u][i][0] * memo[v][j-1][0];
                memo2[i+j][1] += memo[u][i][0] * memo[v][j][1];
                memo2[i+j][1] += memo[u][i][1] * tmp;
                memo2[i+j][1] %= mod;

                memo2[i+j][0] += memo[u][i][0] * tmp;
                memo2[i+j][0] %= mod;

            }
        }

        memcpy(memo[u], memo2, sizeof(memo2));
    }

    return;
}

int main(){
    FASTIO;

    cin>>n;
    for(int i = 1; i<n; i++){
        int u, v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int root = 1;
    dfs(root, -1);

    ll inv3 = (mod+1)/6;
    ans1 = ans1 * inv3 % mod;
//#warning

    ans1 += memo[root][3][0] + memo[root][3][1] + memo[root][3][2];
    ans1 %= mod;

    cout<<ans1<<endl;

    return 0;
}
/*
7
1 2
2 3
1 4
4 5
1 6
6 7
*/
