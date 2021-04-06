#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define pb push_back
#define mp make_pair
#define MOD 1000000007

// For ordered tree
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type , less<T> , rb_tree_tag , tree_order_statistics_node_update> ;

ll reduce(ll n, ll k) {
	vector<int> red;
	while(n) {
		red.pb(n%2);
		n/=2;
	}
	if(red.size() < k) {
		while(red.size()<k) {
			red.pb(0);
		}
	}
	ll res=0,i;
	for(i=k-1;i>=0;i--) res += red[i]*pow(2,k-1-i);
	return res;
}

void solve() {
	ll t,k,i;
	cin >> t;
	while(t--) {
		string s;
		cin >> k >> s;
		vector<char> result(pow(2,k));
		i=0;
		while(s[i]) {
			ll j = reduce(i, k);
			result[j] = s[i];
			i++;
		}
		for(i=0;i<result.size();i++) cout << result[i];
		cout << "\n";
	}
}

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	solve();
	return 0;	
}

