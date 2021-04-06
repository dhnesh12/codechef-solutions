#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define ll long long

ll gcd(ll a, ll b){
	if (b == 0) return a;
	return gcd(b, a%b);
}

int main(){
	ll t, N, K, g;
	cin >> t;

	while (t--) {
		cin >> N >> K;
		ll arr[N];
		for (ll i = 0; i < N; i++){
			cin >> arr[i];
		}
		g = arr[0];
		for (ll j = 1; j < N; j++){
			g = gcd(g, arr[j]);
		}

		if (N == 1){cout << "YES" << '\n';}
		else if (g == 1) {cout << "YES" << '\n';}
		
		else {
			map<ll, ll> mp;
			for (ll i = 2; i*i <= g; i++){
				if (g % i == 0){
					while (g % i == 0){
						mp[i]++;
						g /= i;
					}
				}
			}
			if (g > 1) mp[g]++;
			auto it = mp.rbegin();
			ll max = it->first;
			if (max <= K){
				cout << "YES" <<'\n';
			} else {
				cout << "NO" << '\n';
			}
		}
	}
	return 0;
}