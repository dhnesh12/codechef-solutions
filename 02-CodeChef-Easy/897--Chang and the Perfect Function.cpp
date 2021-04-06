#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	ll a, b; cin >> a >> b;

	ll maxNum = a * a + b;
	ll tot = 0;
	for(ll i = 2; i * i <= maxNum; i++) {
		tot += max(0LL, (ll)sqrt(i * i - 1) - (ll)sqrt(max(0LL, i * i - b - 1)));
	}

	cout << tot << endl;
}