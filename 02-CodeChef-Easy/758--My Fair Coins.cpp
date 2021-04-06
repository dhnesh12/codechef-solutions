#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
 
using namespace std;
//using namespace __gnu_pbds;
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define fp(i,a,b) for(int i=a ; i<b ; i++)
#define fn(i,a,b) for(int i=a ; i>=b ; i--)
#define ones(x) __builtin_popcount(x)
#define pb push_back
#define ff first
#define ss second
#define all(x) x.begin(),x.end()
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;/*
typedef tree<
pii,
null_type,
less<pii>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;*/
const int M=53;
const int inf=2e9;
const int mod=1e9+7;

ll inv2;

ll bp(ll a,int b){
	if (b == 0) return 1;
	ll x = bp(a, b>>1);
	x *= x;
	x %= mod;
	if (b&1) return (a*x) % mod;
	return x;
}

pll fib(int n){
	if (n == 1) return {2, 1};

	pll f = fib(n>>1);
	ll a = 2 * f.ss * f.ss + f.ff * f.ff; a %= mod;
	ll b = 2 * f.ff * f.ff + 4 * f.ff * f.ss; b %= mod;

	if (n&1) return {b, a};
	return {a, ((b + 2*mod - 2*a) * inv2) % mod};
}

void go(){
	int t; cin >> t;
	inv2 = bp(2, mod - 2);

	while (t--){
		int n; cin >> n;
		cout << (fib(n).ff * inv2) % mod << "\n";
	}
}

int main(){	
 
	fastio;	
	int tst=1;
	//cin >> tst;
	while (tst--) go();
 
	return 0;
}