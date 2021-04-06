#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define f(i,a,b) for( ll i = a; i < b ; i++ )
#define af(i,a,b) for( ll i = a; i >= b ; i--)
#define rep(i,a,b,k) for(ll i = a; i < b ; i+= k )
#define arep(i,a,b,k) for( ll i = a; i >= b ; i-= k)
#define ones(ini) (ll) __builtin_popcountll(x)
#define todo(y,val) all_of(all(y),[&val](ll x) {return (x == ((ll)val));})
#define nada(y,val) none_of(all(y),[&val](ll x) {return (x == ((ll)val));})
#define algu(y,val) any_of(all(y),[&val](ll x) {return (x == ((ll)val));})
#define cuantos(a,x) count(all(a),x)
#define fs first
#define sc second
#define pb push_back
#define po pop_back
#define sz(a) (ll) a.size()
#define all(a) a.begin(), a.end()
#define sor(a) sort( a.begin(), a.end() )
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ller ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr)
#define watch(x) cout << (#x) << " is " << (x) <<"\n"
#define test ll deftestcases;cin>>deftestcases;while(deftestcases--)
#define PI acos(-1);
using namespace std;
typedef long long ll;
typedef long double ld; 
typedef pair<ll,ll> ii;
typedef vector<ll>  vi;
typedef vector<ii> vii;
//template<class T> using ordered_set =tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update> ;
const ll inf = 2e18;
const ll mod = 1e9+7;
const ll MAX = 1e5+103;
priority_queue<ii,vii,greater<ii>> pq;
bool id[MAX],vis[MAX];
ll dis[MAX];
vii adj[MAX];
int main(){
    fastio;
        ll n,m,k,ans=inf;cin>>n>>m>>k;
        f(i,0,k){ll lec;cin>>lec;id[lec] = 1;}
        f(i,0,m){
            ll a,b,peso;
            cin>>a>>b>>peso;
            adj[a].pb({b,peso});
            adj[b].pb({a,peso});
        }
        f(i,1,n+1){
            if(!id[i]) continue;
            ll res = 0;
            f(j,1,n+1){
                dis[j]=inf,vis[j]=0;
            }
            dis[i] = 0;
            while(!pq.empty()) pq.pop();
            pq.push({0,i});
            while(!pq.empty()){
                ll u = pq.top().sc;
                pq.pop();
                if(vis[u]) continue;
                vis[u] = true;
                if(id[u]) res++;
                if(dis[u]>ans)break;
                if(id[u]&&res==2){
                    ans=min(ans,dis[u]);break;
                }
                for(auto v : adj[u]){
                    if(dis[u]+v.sc<dis[v.fs]){
                        dis[v.fs] = dis[u]+v.sc;
                        pq.push({dis[v.fs],v.fs});
                    }
                }

            }
        }
        cout<<ans<<"\n";
    return 0;  
}
