#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include<bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
//using namespace __gnu_pbds;
#define SYNC std::ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);
 
typedef    long long            ll;
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
 
#define     int           long long
const ll MOD = 1e9+7;
const ll MOD1 = 998244353;
const ll N = 2e5+5;
const ll INF = 3e9;
const ll BIG_INF = 3e18;
const ld EPS = 1e-12;
const ld PI = 3.141592653589793116;

struct stamp{
	ll t,x1,x2,y1,y2;
	stamp(ll t,ll x1,ll y1,ll x2,ll y2){
		this -> t = t;
		this -> x1 = x1;
		this -> y1 = y1;
		this -> x2 = x2;
		this -> y2 = y2;
	}
};

void solve(int tc){
	ll n;
	cin>>n;

	vector<stamp> v;
	v.pb(stamp(0,1,1,2,1));

	for(int i = 0;i<n;i++){
		ll a,b,c,d,e;
		cin>>a>>b>>c>>d>>e;
		v.pb(stamp(a,b,c,d,e));
	}
	bool  flag = true;
	for(int i = 1;i<=n;i++){
		if(v[i].y1 < v[i-1].y1)flag = false;
		if(v[i].y2 < v[i-1].y2)flag = false;

		if(v[i].x1 == v[i].x2  && v[i].y1 == v[i].y2)flag = false;
		if(v[i].x2 <1 || v[i].x2 > 2 )flag = false;

		ll delta = v[i].t - v[i-1].t;

		if(v[i].y1 - v[i-1].y1 + abs(v[i].x1 - v[i-1].x1) > delta)flag = false;
		if(v[i].y2 - v[i-1].y2 + abs(v[i].x2 - v[i-1].x2) > delta)flag = false;
		if(flag == false)break;

	}

	if(flag){
		cout<<"yes\n";
	} else {
		cout<<"no\n";
	}

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