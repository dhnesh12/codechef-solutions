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
//const ll mod = ;
//const ld error = ;
const ld PI = acosl(-1);

//inline ll MOD(ll x, ll m = mod){
//    ll y = x % m;
//    return (y >= 0) ? y: y+m;
//}

//const int/ll inf = ;
const int nmax = 2e5+10;
///===========================================  template  =======================================================

vector<pair<int, int>> adj[nmax];
int subtree[nmax];
void dfs(int u, int par){
    subtree[u] = 1;
    for(auto p : adj[u]){
        if(p.first == par) continue;
        dfs(p.first, u);
        subtree[u] += subtree[p.first];
    }
}

namespace CD {
    int cdpar[nmax], stk[nmax];
    int sum[nmax];
    int id[nmax];
    pair<int, int> par[nmax];

    void dfs(int u, int p, int x, vector<int> &vec){
        vec.push_back(u);
        par[u] = {p, x};
        for(auto e : adj[u]){
            if(cdpar[e.first] != -1 || e.first == p) continue;
            else{
                id[e.first] = id[u];
                dfs(e.first, u, e.second, vec);
            }

        }
    }


    ll solve(int root, int k){

        int n = subtree[root];
        vector<int> vec{root};
        sum[root] = 0;
        ll ret = 0;

        int cid = 0;
        for(auto e : adj[root]){
            if(cdpar[e.first] != -1) continue;
            id[e.first] = cid++;
            dfs(e.first, root, e.second, vec);
        }

        vector<int> tmp(vec);

        for(int i = 1; i<=k; i++){
            for(int j = 1; j<n; j++){
                int u = tmp[j];
                sum[u] = sum[par[u].first] + (par[u].second == i? 1 : -1);
            }
//            debug(), dbg(range(par+1, par+n+1));
            sort(vec.begin(), vec.end(), [&](int &p, int &q){
                    return sum[p] < sum[q];
                 });
            vector<int> cnt(cid);
            for(int l = 0, r = n; l<n; l++){
                while(r != 0 && sum[vec[r-1]] + sum[vec[l]] > 0){
                    r--;
                    if(vec[r] != root)
                        cnt[id[vec[r]]]++;
                }

                ret += n-r - (vec[l] == root? 0 : cnt[id[vec[l]]]);
            }

        }

        return ret;
    }


    ll decompose(int c, int cpar, int tpar, int k){
        int n = subtree[c], s = 0;
        while(c != tpar){
            stk[s++] = tpar;
            tpar = c;
            for(auto e : adj[tpar])
                if(e.first != stk[s-1] && cdpar[e.first] == -1 && subtree[e.first] > n/2){
                    c = e.first;
                    break;
                }
        }
        for(int i = s-1; i>=1; i--) subtree[stk[i]] -= subtree[c];
        subtree[c] = n;
        cdpar[c] = (cpar == -1)? c : cpar;
        tpar = stk[s-1];

        ll ret = solve(c, k);
        if(s > 1) ret += decompose(stk[1], c, stk[0], k);
        for(auto e : adj[c])
            if(e.first != tpar && cdpar[e.first] == -1)
                ret += decompose(e.first, c, c, k);
        return ret;
    }
}




int main(){
    FASTIO;

    int tc;
    cin>>tc;
    for(int cs = 1; cs <= tc; cs++){
        int n, k;
        cin>>n>>k;

        for(int i = 1; i<=n; i++){
            adj[i].clear();
            CD::cdpar[i] = -1;
        }
        for(int i = 0; i<n-1; i++){
            int u, v, x;
            cin>>u>>v>>x;
            adj[u].emplace_back(v, x);
            adj[v].emplace_back(u, x);
        }

        if(k == 1){
            cout<<ll(n)*(n-1)<<"\n";
            continue;
        }

        dfs(1, -1);
        ll ans = ll(n)*(n-1) - CD::decompose(1, -1, -1, k);
        ans /= 2;


        cout<<ans<<"\n";

    }
    return 0;
}
/*
1
3 2
1 2 1
2 3 2
*/
