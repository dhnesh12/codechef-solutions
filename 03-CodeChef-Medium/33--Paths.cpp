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
//const ld error = ;
const ld PI = acosl(-1);

//inline ll MOD(ll x, ll m = mod){
//    ll y = x % m;
//    return (y >= 0) ? y: y+m;
//}

//const int/ll inf = ;
const int nmax = 1e5+10;
///===========================================  template  =======================================================

int x, y, z;
vector<int> adj[nmax];
int subtree[nmax];

void dfs(int u, int p){
    subtree[u] = 1;
    for(int v : adj[u]){
        if(v == p) continue;
        dfs(v, u);
        subtree[u] += subtree[v];
    }
}
ll ans = 0;

namespace CD{
    int cdpar[nmax];
    ll global[nmax], depth[2*nmax];
    ll XY[nmax], YZ[nmax], ZX[nmax];
    ll XY2[nmax], YZ2[nmax], ZX2[nmax];

    int dfs(int u, int p, int d){
        int ret = d;

        ll xx = depth[d+x], yy = depth[d+y], zz = depth[d+z];
        depth[d]++;
        ll xl = depth[d+x], yl = depth[d+y], zl = depth[d+z];
        ll xy = 0, yz = 0, zx = 0;

        for(int v : adj[u]){
            if(cdpar[v] > -1 || v == p) continue;
            ret = max(ret, dfs(v, u, d+1));

            xy += (depth[d+x] - xl) * (yl - yy) + (depth[d+y] - yl) * (xl-xx);
            yz += (depth[d+y] - yl) * (zl - zz) + (depth[d+z] - zl) * (yl-yy);
            zx += (depth[d+z] - zl) * (xl - xx) + (depth[d+x] - xl) * (zl-zz);

            xl = depth[d+x];
            yl = depth[d+y];
            zl = depth[d+z];
        }

        XY2[d] += xy;
        YZ2[d] += yz;
        ZX2[d] += zx;
//        debug(), dbg(ZX2[d]);

        if(x >= d) ans += global[x-d] * yz;
        if(y >= d) ans += global[y-d] * zx;
        if(z >= d) ans += global[z-d] * xy;

//        debug(), dbg(u), dbg(xy), dbg(yz), dbg(zx), dbg(ans);

        return ret;
    }

    void solve(int root){
        int n = subtree[root];
        global[0] = 1;
        ll xy = 0, yz = 0, zx = 0;

        for(int v : adj[root]){
            if(cdpar[v] > -1) continue;
            int d = dfs(v, root, 1);

            ans += depth[x] * yz + depth[y] * zx + depth[z] * xy;

            xy += depth[x] * global[y] + depth[y] * global[x];
            yz += depth[z] * global[y] + depth[y] * global[z];
            zx += depth[z] * global[x] + depth[x] * global[z];

//            debug(), dbg(xy), dbg(yz), dbg(zx);

//            debug(), dbg(ZX[1]), dbg(depth[2]), dbg(y), dbg(v);

            for(int i = 1; i<=d; i++){
                if(i <= x) ans += YZ[x-i] * depth[i];
                if(i <= y) ans += ZX[y-i] * depth[i];
                if(i <= z) ans += XY[z-i] * depth[i];
                global[i] += depth[i];
                depth[i] = 0;
            }

//            debug(), dbg(v), dbg(ans);

            for(int i = 1; i<=d; i++){
                XY[i] += XY2[i];
                YZ[i] += YZ2[i];
                ZX[i] += ZX2[i];
                XY2[i] = YZ2[i] = ZX2[i] = 0;
            }
        }
        for(int i = 0; i<=n; i++)
            global[i] = XY[i] = YZ[i] = ZX[i] = 0;
    }

    int stk[nmax];
    int decompose(int c, int cpar, int tpar){
        int n = subtree[c], s = 0;
        while(c != tpar){
            stk[s++] = tpar;
            tpar = c;
            for(int v : adj[tpar]){
                if(v != stk[s-1] && cdpar[v] == -1 && subtree[v] > n/2)
                {c = v; break;}
            }
        }
        for(int i = s-1; i>=1; i--) subtree[stk[i]] -= subtree[c];
        subtree[c] = n, cdpar[c] = (cpar == -1)? c : cpar, tpar = stk[s-1];

        solve(c);
//        return 0;
//        debug(), dbg(c), dbg(ans);

        if(s > 1) decompose(stk[1], c, stk[0]);
        for(int v : adj[c]){
            if(v != tpar && cdpar[v] == -1) decompose(v, c, c);
        }
    }
}

int main(){
    FASTIO;

    int tc;
    cin>>tc;
    for(int cs= 1; cs <= tc;cs++){
        int n;
        cin>>n>>x>>y>>z;

        for(int i = 1; i<=n; i++){
            adj[i].clear();
            CD::cdpar[i] = -1;
        }

        int sum = x+y+z;
        for(int i = 1; i<n; i++){
            int u, v;
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        if(sum % 2 == 1){
            cout<<0<<"\n";
            continue;
        }

        x = sum/2 - x;
        y = sum/2 - y;
        z = sum/2 - z;

        if(x < 0 || y < 0 || z < 0){
            cout<<0<<"\n";
            continue;
        }

//        debug(), dbg(x), dbg(y), dbg(z);
//
        dfs(1, -1);

        ans = 0;
        CD::decompose(1, -1, -1);

        cout<<ans<<"\n";



    }


    return 0;
}

/*

1
9 4 3 5
1 2
2 3
3 4
6 5
5 2
6 7
7 8
8 9

1
7 2 2 2
1 2
1 3
1 4
5 4
5 6
5 7


1
4 2 2 2
1 2
1 3
1 4

1
15 4 2 2
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 15

*/
