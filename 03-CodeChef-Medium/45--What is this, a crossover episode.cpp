#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define all(x) (x).begin(),(x).end()
const int N = 10010;
int n, m;
int col[N];
vector<int> E[N];
int mex(int x, int y) {
	if(x != 0 && y != 0) return 0;
	if(x != 1 && y != 1) return 1;
	return 2;
}
bool adj(int u, int v) {
	if(u > v) swap(u, v);
	if(u % n + 1 == v) return 1;
	auto it = lower_bound(all(E[u]), v);
	if(it != E[u].end() && *it == v) return 1;
	return 0;
}
void work(int l, int r) {
	if(l + 1 >= r) return;
	int z = -1;
	while(!E[l].empty()) {
		z = E[l].back();
		E[l].pop_back();
		if(z < r) break;
		z = -1;
	}
	if(z == -1) z = l + 1;
	if(adj(z, r)) col[z] = mex(col[l], col[r]);
	else col[z] = mex(col[l], col[l]);
//	cout << l << ' ' << r << ' ' << z << ' ' << col[z] << endl;
	work(l, z); work(z, r);
}
int main() {
#ifdef local
	freopen("in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 0, u, v; i < m; i++) {
		cin >> u >> v;
		if(u > v) swap(u, v);
		E[u].push_back(v);
	}
	for(int i = 1; i <= n; i++) sort(all(E[i]));
	col[1] = 0, col[n] = 1;
	work(1, n);
	cout << *max_element(col + 1, col + 1 + n) + 1 << '\n';
	for(int i = 1; i <= n; i++) cout << col[i] + 1 << " \n"[i == n];
	return 0;
}
