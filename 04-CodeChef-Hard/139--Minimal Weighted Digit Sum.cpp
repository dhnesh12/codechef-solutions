#include <bits/stdc++.h>
using namespace std;

/*******  All Required define Pre-Processors and typedef Constants *******/
#define mem(a, b) memset(a, (b), sizeof(a))
#define rep(i,k) for(int i=0;i<k;i++)
#define repA(i,a,n) for(int i=a;i<=(n);++i)
#define repD(i,a,n) for(int i=a;i>=(n);--i)
#define all(cont) cont.begin(), cont.end()
#define rall(cont) cont.end(), cont.begin()
#define foreach(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define INF (ll)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define LLINF 1000111000111000111LL
#define sz(a) int(a.size())
#define ff first
#define ss second

typedef long long ll;
typedef vector<int> vi;
typedef vector< vi > vvi;
typedef pair<int,int> ii;
typedef vector< ii > vp;
typedef vector< vp > vvp;

ll mod = (1LL << 32);

inline int pow_(ll x, ll y, ll p = mod){
  int r = 1; while(y){if(y & 1) r = r * x % p; y >>= 1; x = x * x % p;} return r;
}
inline ll inv_(ll x){return pow_(x, mod - 2, mod);}
inline ll add(ll a, ll b){a += b; if(a >= mod) a -= mod; return a;}
inline ll mul(ll a, ll b){return a * 1LL * b % mod;}
inline ll sub(ll a, ll b){a -= b; if(a < 0) a += mod; return a;}

int w[10];
const int M = 3141592;
const int W_MAX = 314 * 7;
int V[M + 5];
int d[M + 5];

ll N[M + 5];

int main(int argc, char const *argv[]) {
        #ifdef LOCAL_TEST
        freopen("in.txt","r",stdin);
        #else
        ios_base::sync_with_stdio(false);cin.tie(NULL);
        #endif
        int t; cin >> t;
        //cout << mod << '\n';
        while(t--){
                int m; cin >> m;
                rep(i, 10) cin >> w[i];

                queue<int> Q[W_MAX + 5];
                Q[0].push(0);

                rep(i, m) V[i] = 0;
                rep(i, m) d[i] = W_MAX + 10;
                d[0] = 0;

                repA(i, 0, W_MAX){
                        while(!Q[i].empty()){
                                int u = Q[i].front();
                                Q[i].pop();
                                if(V[u]) continue;
                                V[u] = 1;

                                rep(j, 10){
                                        int v = (u * 10 + j) % m;
                                        int dv = i + w[j];

                                        if(d[v] > dv){
                                                Q[dv].push(v);
                                                d[v] = dv;
                                        }

                                }
                        }
                }

                rep(i, m) V[i] = 0;
                rep(i, m) N[i] = 0;

                ll ans = 0;
                queue<int> A;
                A.push(0);
                V[0] = 1;

                //rep(i, m) cout << d[i] << ' '; cout << '\n';
                while(!A.empty()){
                        int u = A.front();
                        A.pop();

                        rep(i, 10){
                                int v = (u * 10 + i) % m;
                                //cout << "check " << u << ' ' << v << " " << V[v] << '\n';
                                if(!V[v] && (d[v] == (d[u] + w[i]))){
                                       // cout << "nice\n";
                                        A.push(v);
                                        N[v] = add(mul(N[u], 3141), i);
                                        V[v] = 1;
                                }
                        }
                }

                rep(i, m) ans += N[i];
                //rep(i, m) cout << V[i] << ' '; cout << '\n';
                //rep(i, m) cout << N[i] << ' '; cout << '\n';
                cout << ans << '\n';
        }
        return 0;
 }
