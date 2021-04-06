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
 

const ll MOD = 1e9+7;
const ll MOD1 = 998244353;
const ll N = 2e5+5;

const ld EPS = 1e-12;
const ld PI = 3.141592653589793116;

void solve(int tc){
	ll n,l,r;
	cin>>n>>l>>r;
	vi v(n);
	for(ll i = 0;i<n;i++){
		cin>>v[i];
	}

	sort(all(v));

	// vi g[n+3],d[n+3];

	// for(ll i = 0;i<n;i++){
	// 	if(v[i] >= 0 && v[i] + r <= l){
	// 		for(ll j = i+1; j < n ;j ++ ){
	// 			if(v[j] >= 0 && v[j] + r <= l){
	// 				if(v[i] + r > v[j])continue;
	// 				g[i+1].pb(j+1);
	// 				d[i+1].pb(v[j] - v[i] - r );
	// 			}
	// 		}
	// 	}
	// }
	// for(int i = 0;i<n;i++){
	// 	if(v[i] >= 0 && v[i] + r <= l){
	// 		g[0].pb(i+1);
	// 		d[0].pb(v[i]);
	// 		g[i+1].pb(n+1);
	// 		d[i+1].pb(l - v[i] - r);
	// 	}
	// }

	// g[0].pb(n+1);
	// d[0].pb(l);

	vector< vector<int> > dp(n+3,vector<int>(n+3,-1));

	// priority_queue< pair<ll,pair<ll,ll> > > pq;
	// pq.push({0LL,{0LL,0LL}});

	// while(!pq.empty()){
	// 	auto cur  = pq.top();
	// 	pq.pop();
	// 	ll s = cur.second.second;
	// 	ll unchanged = cur.second.first;
	// 	ll extra = cur.first;
	// 	if(dp[s][unchanged] >= extra || dp[s][unchanged] + unchanged > n){
	// 		continue;
	// 	}
	// 	dp[s][unchanged] = extra;

	// 	for(int i = 0;i<g[s].size();i++){
	// 		ll nxt = g[s][i];
	// 		ll n_dist = d[s][i];

	// 		if(dp[nxt][unchanged+1] < extra + (n_dist/r)){
	// 			pq.push({extra + (n_dist/r),{unchanged+1,nxt}});
	// 		}
	// 	}
	// }


	vi new_v;
	new_v.pb(-r);

	dp[0][0]=0;
	for(int i = 0;i<n;i++){
		if(v[i]>=0 && v[i] +r <=l){
			new_v.pb(v[i]);
		}
	}
	ll m = new_v.size() -1;
	new_v.pb(l);


	for(int i = 1;i<=m+1;i++){
		for(int j = 0;j<i;j++){
			if(new_v[j] + r <= new_v[i]){
				for(int k = 0;k<=m+1;k++){
					if(dp[j][k] != -1){
						dp[i][k+1] = max(dp[i][k+1],dp[j][k] + (new_v[i] - new_v[j] - r)/r);
					}
				}
			}
		}
	}
	int answer = 0;
	for(int i = 0;i<=m;i++){
		// debug(i,dp[n+1][i+1]);
		if(dp[m+1][i+1] + i >= n){
			answer = i;
		}
	}

	 // debug(dp);
	cout<<n- answer<<"\n";

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