/*
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma")
*/
#include<bits/stdc++.h>
using namespace std;
 
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
*/
 
#define ar array 
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define sz(v) int((v).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define rep(i,a,b) for(int i = a; i < b; i++)
#define deb(x) cout << #x << "=" << x << endl
#define PI 3.1415926535897932384626
#define PQ(type) priority_queue<type>
#define PQD(type) priority_queue<type,vector<type>,greater<type> >
#define runtime() ((double)clock() / CLOCKS_PER_SEC)
#define endl '\n'
 
//typedef tree<int,null_type,less<int>,rb_tree_tag, tree_order_statistics_node_update> indexed_set; // use less_equal for multiset
// order_of_key (val): returns the no. of values less than val
// find_by_order (k): returns the iterator to kth largest element.(0-based)
 
typedef long long ll; 
typedef long double ld; 
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
 
 
const  int mxN = 2e5+5;
const  long long INF= 1e18;
const long long mod= 1e9+7;

mt19937_64 RNG(chrono::steady_clock::now().time_since_epoch().count());
#define SHUF(v) shuffle(all(v), RNG);
// Use mt19937_64 for 64 bit random numbers.

ll getrand() {
	uniform_int_distribution<> dis(1, LLONG_MAX);
	return dis(RNG);
}

void solve(int p) {
	int n, q;
	cin >> n >> q;

	vll hash(n + 2);

	for(int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		ll cur = getrand();
		hash[l] += cur;
		hash[r + 1] -= cur;
	}

	for(int i = 1; i <= n; i++) {
		hash[i] += hash[i - 1];
	}

	vi ans(n + 1);

	if(p == 0) {
		rep(i, 1, n + 1) {
			if(hash[i]) cout << i << " ";
			else cout << 1 << " ";
		}
		cout << endl;
		return;
	}

	map<int, vi> m;


	rep(i, 1, n + 1) {
		if(hash[i] != 0)
		m[hash[i]].pb(i);
	}

	for(auto x: m) {
		vi cur = x.se;
		sort(all(cur));

		rep(i, 0, sz(cur)) {
			ans[cur[i]] = cur[sz(cur) - i - 1];
		}
	}

	rep(i, 1, n + 1) {
		if(ans[i] == 0) cout << n << " ";
		else cout << ans[i] << " ";
	}
	cout << endl;
}

int main() {
ios_base::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);

int t = 1, p;
cin >> t >> p;
while(t--) {
solve(p);
}
}


