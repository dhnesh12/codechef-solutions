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

vi primes;
vector<bool> is_prime;
ll least_divisor[600000];
ll grundy[600000];

void sieve(ll n){
	is_prime.resize(n+1,true);
	for(int i = 2;i<=n;i++){
		if(is_prime[i]){
			for(int j = i*i;j<=n;j+=i){
				is_prime[j] = false;
				least_divisor[j] = i;
			}
			primes.pb(i);
			grundy[i] = primes.size();
			least_divisor[i] = i;
		} 
	}



}

void solve(int tc){
	ll n;
	cin>>n;
	vi v(n);
	for(int i = 0;i<n;i++){
		cin>>v[i];
	}

	int xorr = 0;

	for(int i = 0;i<n;i++){
		while(v[i]>1){

			ll div = least_divisor[v[i]];
			// debug(i,v[i],div,grundy[div]);
			v[i]/=div;
			xorr^=grundy[div];
		}
	}
	if(xorr){
		cout<<"Alice\n";
	} else {
		cout<<"Bob\n";
	}

}

int32_t main()
{
  SYNC   //Disable on interactive problems
  //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);

  sieve(500100);
 
    ll t=1;
    int tc = 1;
    cin>>t;
    while(t--){
      solve(tc++);
    }
 
    //cerr<< '\n' << "Time elapsed :" << clock() * 1000.0 / CLOCKS_PER_SEC << " ms\n" ;
  return 0;
}