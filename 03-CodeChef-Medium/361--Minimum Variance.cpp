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
	ll val[50000 + 1] = {0}, val2[50001] = {0};
	cin >> n;
	rep(i, n) {
		ll last = -1;
		cin >> x;
		v<ll> vec;
		rep(j, x) {
			cin >> y;
			vec.pb(y);
		}
		sortv(vec);
		for (auto y : vec) {
			if (last == -1) {
				val[1] += y * y;
				val2[1] += y;
			}
			else {
				val[(y + last) / 2 + 1] += y * y - last * last;
				val2[(y + last) / 2 + 1] += y - last;
			}
			last = y;
		}
	}

	ll mn = inf;
	for (i = 1; i < 50001; i++) {
		val[i] += val[i - 1];
		val2[i] += val2[i - 1];
		ll sum = n * val[i] - val2[i] * val2[i];
		mn = min(mn, sum);
	}
	cout << mn;

	return 0;




}










