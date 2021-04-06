#include <bits/stdc++.h>
#define spd ios::sync_with_stdio(false),cin.tie(0)
using namespace std;
using ll = long long;

vector<ll> primes;
bool prime[10010] = {false};
void PrimeGenerator() {
    prime[1] = true;
    primes.push_back(2);
    for(ll i = 4; i <= 10010; i += 2) prime[i] = true;
    for (ll i = 3; i*i <= 10010; i += 2) {
        if(!prime[i]) {
            for(ll j = i*i; j <= 10010; j += 2*i)
                prime[j] = true;
        }
    }
    for (ll i = 3; i < 10010; i += 2) {
        if (!prime[i])
            primes.push_back(i);
    }
}

ll res[10010] = {};

int main() {
    spd; PrimeGenerator();
	for(ll i = 0; i < primes.size(); i++) {
		for(ll j = 0; j < primes.size(); j++) {
			if(primes[i] + 2 * primes[j] < 10010) res[primes[i] + 2 * primes[j]]++;
		}
	}
    ll t; cin >> t;
    while(t--) {
            ll n; cin >> n;
            cout << res[n] << endl;
    }
}