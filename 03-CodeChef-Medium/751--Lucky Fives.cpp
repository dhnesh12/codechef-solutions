#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

void update(ll *bit, ll n, ll counter, ll val) {
	ll idx = n;
	while (idx <= counter) {
		bit[idx] += val;
		idx += (idx & (-idx));
	}
}

ll query(ll *bit, ll n, ll counter) {
	ll idx = n, sum = 0;
	while (idx > 0) {
		sum += bit[idx];
		idx -= (idx & (-idx));
	}
	return sum;
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll a, b;
	cin >> a >> b;
	vector<pair<ll, ll> > x;
	for (ll  j = 0; j < a; j++) {
		ll k;
		cin >> k;
		x.push_back({k, j});
	}
	sort(x.begin(), x.end());
	ll counter = 0;
	vector<ll> y(a + 1, 0);
	ll prev =  -1;
	for (ll j = 0; j < a; j++) {
		pair<ll, ll> z = x[j];
		if (z.first == prev) {
			y[z.second] = counter;
		}
		else {
			counter++;
			y[z.second] = counter;
		}
		prev = z.first;
	}
	ll bit_j[counter + 1] = {0};
	ll bit_l[counter + 1] = {0};
	ll bit_k[counter + 1] = {0};
	ll ans[a + 1][a + 1];
	memset(ans, 0, sizeof(ans));
	for (ll i = 0; i < a; i++) {
		memset(bit_j, 0, sizeof(bit_j));
		memset(bit_l, 0, sizeof(bit_l));
		memset(bit_k, 0, sizeof(bit_k));
		for (ll j = i; j < a; j++) {
			if (y[i] > y[j]) {
				update(bit_l, y[j], counter, 1);
			}
			ll k = query(bit_l, y[j] - 1, counter);
			update(bit_j, y[j],counter,k);
			k = query(bit_j, counter, counter) - query(bit_j, y[j], counter);
			update(bit_k, y[j], counter, k);
			ans[i][j] = query(bit_k, y[j] - 1, counter);
		}
	}
	for (ll i = 0; i < b; i++) {
		ll l, r;
		cin >> l >> r;
		cout << ans[l - 1][r - 1] << "\n";
	}
}