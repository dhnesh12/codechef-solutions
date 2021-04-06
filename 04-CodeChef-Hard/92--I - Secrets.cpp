#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
//using namespace __gnu_pbds;
#define SYNC std::ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
 
typedef    int            ll;
typedef     long double      ld;
typedef    vector<ll>           vi; 
typedef    pair<ll,ll>          ii; 
 
#define    pb                   push_back 
#define    mp                   make_pair
#define    all(c)               (c).begin(),(c).end() 
#define    ff           first
#define    ss           second
//typedef tree<int, null_type, less<int>, rb_tree_tag,
//             tree_order_statistics_node_update>
//    ost;
 
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template <typename T, typename V>
void __print(pair<T, V> x);
template<typename C, typename T = typename C::value_type>
void __print(C x);
template <typename T>
void __print(const T a[]);
template <typename T, typename V>
void __print(pair<T, V> x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename C, typename T = typename C::value_type>
void __print(C x) {int f = 0; cerr << '{'; for (auto i: x) cerr << (f++ ? "," : ""),__print(i) ; cerr << "}";}
template <typename T>
void __print(const T a[]) { cerr << "\n{"; for(int i = 0; i < 10; i++){ __print(a[i]);cerr << ","; } cerr <<  " ... }\n"; }
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "Line " << __LINE__ << ": [" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif
 
// #define     int           long long
const ll MOD = 1e9+7;
const ll MOD1 = 998244353;
const ll N = 2e5+5;

const ld EPS = 1e-12;
const ld PI = 3.141592653589793116;

vector <vi> comps;
vi comp;

vector<bool > vis;

vi g[11];

void dfs(ll s){
	comp.pb(s);
	vis[s] = true;
	for(auto ele:g[s]){
		if(vis[ele] == false){
			dfs(ele);
		}
	}
}

bool srt(vi a, vi b){
	return a.size() < b.size();
}

ll work(vi v){
	ll ret = 0;

	for(int i = 0;i<v.size();i++ ){
		ret*=10;
		ret+=v[i];
	}
	return ret;
}


void solve(int tc){

		ll n;
		cin>>n;

		for(int i = 0;i<=n;i++){
			g[i].clear();
		}
		vis.clear();
		comps.clear();
		vis.resize(n+1,false);


		vi e(n+1),f(n+1);
		for(int i = 1 ;i<=n;i++){
			cin>>e[i];
		}


		
		map<ll,ll> ei;
			vector<pair<ll,ll > > edges; 
		for(int i = 1 ;i<=n;i++){
			cin>>f[i];
			edges.pb({i,f[i]});
			g[i].pb(f[i]);
				if(f[i] < i){
					ei[i] = f[i];
				}
				else {
					ei[i] = i;
				}
			
			}
				for(int i = 1 ;i<=n;i++){
			e[i] = ei[e[i]];
		}





		ll m;
		cin>>m;

	
		for(int i = 0;i<m;i++){
			ll u,v;
			cin>>u>>v;
		edges.pb({u,v});
		edges.pb({v,u});
		g[u].pb(v);
		g[v].pb(u);
		}

		for(int i = 1;i<=n;i++){
			if(vis[i] == false){
				comp.clear();
				dfs(i);
				comps.pb(comp);
			}
		}


		cout<<"Case "<<tc<<": ";

		unordered_map< ll , ll> mmpp;

		sort(all(comps),srt);
		int answer = 0;

		for(auto comp:comps){
			if(answer > 18)break;
			mmpp.clear();

			vi loc(n+1,-1);

			vi compe = comp;
			for(int i = 0;i<compe.size();i++){
				compe[i] = e[comp[i]];
				loc[comp[i]] = i;
			}
			bool found = false;
			queue< pair<ll,vi > > q;
			q.push({answer,compe});
			mmpp[work(compe)]++;
			while(!q.empty()){
				auto cur = q.front();
				q.pop();
				//debug(cur);
				//debug(cur);
				if(cur.ff > 18){answer = 19;break;}
				//if(mmpp.find(cur.ss) != mmpp.end())continue;
				//mmpp[cur.ss]++;
				bool flag = true;
				for(int i = 0;i<cur.ss.size();i++ ){
					if(cur.ss[i] != ei[comp[i]] && cur.ss[i] != ei[f[comp[i]]]){
						flag = false;
						break;
					}
				}
				if(flag){
					answer = cur.ff;
					found = true;
					break;
				}

				vi perm = cur.ss;

				for(int i = 0;i<comp.size();i++){
					for(auto ele:g[comp[i]]){
						if(ele > comp[i]){
							swap(perm[loc[comp[i]]],perm[loc[ele]]);
							if(mmpp.find(work(perm)) == mmpp.end()){
								q.push({cur.ff+1,perm});
								mmpp[work(perm)]++;
							}
							swap(perm[loc[comp[i]]],perm[loc[ele]]);
						}
					}

				}

			}

			if(!found){
				answer = 19;
			}
		}

		if(answer <= 18){
			cout<<answer<<"\n";
		}else 
		cout<<"IMPOSSIBLE"<<"\n";
}

int32_t main()
{
  SYNC   //Disable on interactive problems
  //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
 
    ll t=1;
    int tc = 1;
    cin>>t;
    while(t--){
      solve(tc++);
    }
 
    //cerr<< '\n' << "Time elapsed :" << clock() * 1000.0 / CLOCKS_PER_SEC << " ms\n" ;
  return 0;
}