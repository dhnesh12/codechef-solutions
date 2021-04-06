#include "bits/stdc++.h"
using namespace std;
vector<int> bit;
int n, q;
void upd(int k, int x) {
	for(; k <= n; k += k & -k) bit[k] += x;
}
int query(int k) {
	int a = 0;
	for(; k > 0; k -= k & -k) a += bit[k];
	return a;
}
signed main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> q;
	bit.assign(n + 1, 0);
	int inv = 0;
	for(int i = 0; i < n; ++i) {
		int p;
		cin >> p;
		inv += (i - query(p)) & 1;
		upd(p, 1);
	}
	inv %= 2;
	while(q--) {
		int i, j;
		cin >> i >> j;
		inv ^= 1;
		cout << inv << '\n';
	}
	return 0;
}