#include<bits/stdc++.h>
#define ll long long int
using namespace std;

int main(){
	ll t;
	cin >> t;
	while(t--){
		ll n;
		cin >> n;
		vector<ll> x(n);
		unordered_map<ll, vector<ll>> y;
		
		for(ll i=0; i<n; i++){
			cin >> x[i];
			y[x[i]].push_back(i);
		}
		
		sort(x.begin(), x.end());
		ll recent = y[x[0]][0];
		ll ans = 1;
		
		for(ll i=1; i<n; i++){
			if(x[i-1] == x[i]){
				continue;
			}
			
			vector<ll> temp = y[x[i]];
			auto it = upper_bound(temp.begin(), temp.end(), recent);
			if(it == temp.end()){
				ans += 1;
				recent = temp[0];
			}
			else{
				recent = *it;
			}
		}
		cout << ans << endl;
	}
	return 0;
}