#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;
const int MOD = 1e9 + 7;

int adj[40][40][5];

int solve() {
	unordered_map<int, int> H;
	memset(adj, -1, sizeof adj);
	int n, m;
	cin >> n >> m;
	int tot = 0;
	bool flag = true;
	while (m--) {
		vector<int> al(5);
		int x, y, r;
		cin >> x >> y; if (x > y) swap(x, y);
		for (cin >> r; r--; ) {
			int p, e; cin >> p >> e;
			if (!H.count(p)) H[p] = tot++, assert(tot <= 5);
			int cur = H[p];
			al[cur] += e;
		}
		if (~adj[x][y][0]) {
			for (int i = 0; i < 5; i++) if (adj[x][y][i] != al[i]) {
				flag = false;
				break;
			}
		}
		else for (int i = 0; i < 5; i++) adj[x][y][i] = adj[y][x][i] = al[i];
	}
	
	if (!flag) return 0;
	
	int ans = 1;
	for (int p = 0; p < 5; p++) {
		vector<int> f(n + 1, -1);
		vector<pair<int, pii>> edges;
		for (int x = 1; x <= n; x++) for (int y = x; y <= n; y++) if (~adj[x][y][p]) {
			edges.emplace_back(adj[x][y][p], pii(x, y));
		}
		
		sort(edges.begin(), edges.end());
		for (int l = 0; l < edges.size(); ) {
			int r = l;
			while (r < edges.size() && edges[r].first == edges[l].first) r++;
			int y = edges[l].first;
			
			vector<int> pw(40);
			pw[0] = 1;
			for (int i = 1; i < 40; i++) pw[i] = 1ll * pw[i - 1] * y % MOD;
			
			vector<int> tmp;
			for (int i = l; i < r; i++) {
				pii cur = edges[i].second;
				if (f[cur.first] >= 0 && f[cur.second] >= 0) return 0;
				if (f[cur.first] >= 0) tmp.push_back(cur.second);
				else if (f[cur.second] >= 0) tmp.push_back(cur.first);
				else if (cur.first == cur.second) tmp.push_back(cur.first);
			}
			for (int p : tmp) f[p] = y;
			
			tmp.clear();
			for (int i = l; i < r; i++) {
				pii cur = edges[i].second;
				if (f[cur.first] < 0) tmp.push_back(cur.first);
				if (f[cur.second] < 0) tmp.push_back(cur.second);
			}
			sort(tmp.begin(), tmp.end());
			tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
			
			int sz = tmp.size();
			int h = sz / 2;
			vector<int> le(1 << h), ri(1 << (sz - h));
			le[0] = 1;
			for (int mask = 1; mask < (1 << h); mask++) {
				int i = 31 - __builtin_clz(mask);
				if (le[mask ^ (1 << i)] == false) continue;
				le[mask] = true;
				for (int j = 0; j < i; j++) if ((mask >> j) & 1) {
					if (adj[tmp[i]][tmp[j]][p] == y) {
						le[mask] = false;
						break;
					}
				}
			}
			for (int mask = 0; mask < (1 << h); mask++) {
				if (le[mask]) le[mask] = pw[__builtin_popcount(mask)];
			}
			for (int i = 0; i < h; i++) for (int j = 0; j < (1 << h); j++)
				if ((j >> i) & 1) le[j] = (le[j ^ (1 << i)] + le[j]) % MOD;
				
			vector<int> pos(sz - h);
			
			for (int i = h; i < sz; i++) {
				pos[i - h] = 0;
				for (int j = 0; j < h; j++) if (adj[tmp[i]][tmp[j]][p] != y) {
					pos[i - h] |= (1 << j);
				}
			}
			
			vector<int> go(1 << (sz - h));
			
			ri[0] = 1, go[0] = (1 << h) - 1;
			for (int mask = 1; mask < (1 << (sz - h)); mask++) {
				int i = 31 - __builtin_clz(mask);
				go[mask] = go[mask ^ (1 << i)] & pos[i];
				if (ri[mask ^ (1 << i)] == false) continue;
				ri[mask] = true;
				for (int j = 0; j < i; j++) if ((mask >> j) & 1) {
					if (adj[tmp[i + h]][tmp[j + h]][p] == y) {
						ri[mask] = false;
						break;
					}
				}
			}
			int sum = 0;
			for (int mask = 0; mask < (1 << (sz - h)); mask++) if (ri[mask]) {
				sum = (sum + 1ll * pw[__builtin_popcount(mask)] * le[go[mask]]) % MOD;
			}
			ans = 1ll * ans * sum % MOD;
			for (auto &p : tmp) f[p] = y;
			l = r;
		}
	}
	for (int x = 1; x <= n; x++) {
		bool bad = true;
		for (int y = 1; y <= n; y++) if (adj[x][y][0] != -1) {
			bad = false;
			break;
		}
		if (bad) return -1;
	}
	return ans;
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T; 
	for (cin >> T; T--; ) cout << solve() << endl;
	
	return 0;

}

