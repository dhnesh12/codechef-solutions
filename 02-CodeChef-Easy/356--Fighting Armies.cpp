#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef long long  int ll;
typedef long double db;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define pll pair<ll,ll>
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define ub(v,val) upper_bound(v.begin(),v.end(),val)
#define np(str) next_permutation(str.begin(),str.end())
#define lb(v,val) lower_bound(v.begin(),v.end(),val)
#define sortv(vec) sort(vec.begin(),vec.end())
#define rev(p) reverse(p.begin(),p.end());
#define v vector
#define pi 3.14159265358979323846264338327950288419716939937510
#define len length()
#define repc(i,s,e) for(ll i=s;i<e;i++)
#define fi first
#define se second
#define mset(a,val) memset(a,val,sizeof(a));
#define mt make_tuple
#define repr(i,n) for(i=n-1;i>=0;i--)
#define rep(i,n) for(i=0;i<n;i++)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define at(s,pos) *(s.find_by_order(pos))
#define set_ind(s,val) s.order_of_key(val)
long long int M = 1e9 + 7 ;
long long int inf = 9 * 1e18;
//CLOCK
ll begtime = clock();
#define time() cout << "\n\nTime elapsed: " << (clock() - begtime)*1000/CLOCKS_PER_SEC << " ms\n\n";
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//CLOCK ENDED
ll n, m;
// modular exponentiation
ll binpow(ll val, ll deg)
{
	if (deg < 0)
		return 0;
	if (!deg)
		return 1 % M;
	if (deg & 1)
		return binpow(val, deg - 1) * val % M;
	ll res = binpow(val, deg >> 1);
	return (res * res) % M;
}
//binomial
ll modinv(ll n) {
	return binpow(n, M - 2);
}


int main() {
	// your code goes here
	IOS;
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ll i, j, t, k, x, y, z,  N;

	cin >> t;
	while (t--) {
		cin >> n;
		ll arr[n];
		rep(i, n) cin >> arr[i];
		ll ans = arr[0];
		db an = arr[0];
		ll flg = 0;
		for (ll i = 1; i < n; i++) {
			ans = (((arr[i] * ans)) /
			       (__gcd(arr[i], ans)));
			an = (((arr[i] * an)) /
			      (__gcd(arr[i], ll(an))));
			if (an > 1e18) {
				flg = 1;
			}
		}
		ll l, r;
		cin >> l >> r;
		if (flg) {
			cout << r - l + 1 << '\n';
			continue;
		}
		x = r - l + 1;
		l = ceil(db(l) / ans);
		r = floor(db(r) / ans);
		if (l <= r) x -= (r - l + 1);
		cout << x << '\n';

	}
	return 0;




}










