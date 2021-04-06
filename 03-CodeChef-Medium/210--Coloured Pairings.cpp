#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 300005;
const int magic = 600;

struct Block {
	ll pref, suff, val, sum;
	Block(ll _pref = 0, ll _suff = 0, ll _val = 0, ll _sum = 0) {
		pref = _pref; suff = _suff;
		val = _val; sum = _sum;
	}
} block[N][20];

Block merge(Block a, Block b) {
	Block res;
	res.pref = max(a.pref, a.sum + b.pref);
	res.suff = max(b.suff, a.suff + b.sum);
	res.val = max(max(a.val, b.val), a.suff + b.pref);
	res.sum = a.sum + b.sum;
	return res;
}

int n, q;
ll a[N], c[N];
vector<int> pos[N];
int inDex[N], lg[N];
int cntBig, idBig[N];
int lst[N], nearLef[N][505], nearRig[N][505];
Block prep[505][505];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
//	freopen("40.inp", "r", stdin);
//	freopen("40.out", "w", stdout);
	
	int tc; cin >> tc;
	while (tc--) {
		cin >> n >> q;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= n; i++) cin >> c[i];
		
		for (int i = 1; i <= n; i++) {
			pos[i].clear();
			idBig[i] = 0;
		}
		for (int i = 1; i <= n; i++) pos[c[i]].push_back(i);
		cntBig = 0;
		for (int i = 1; i <= n; i++) { 
			if (pos[i].size() > magic) {
				idBig[i] = ++cntBig;
			}
		}
		
		for (int i = 1; i <= cntBig; i++) {
			for (int j = 1; j <= cntBig; j++) {
				prep[i][j] = Block(); 
			}
		}
		for (int i = 1; i <= n; i++) {
			if (idBig[c[i]] == 0) continue;
			for (int j = 1; j <= cntBig; j++) {
				int x = min(idBig[c[i]], j), y = max(idBig[c[i]], j);
				prep[x][y] = merge(prep[x][y], Block(a[i], a[i], a[i], a[i]));
			}
		}
		
		for (int i = 1; i <= n; i++) lg[i] = log2(i);
		for (int color = 1; color <= n; color++) {
			if (idBig[color] == 0) continue;
			for (int i = 0; i < (int)pos[color].size(); i++) {
				int id = pos[color][i];
				block[id][0] = Block(a[id], a[id], a[id], a[id]);
				inDex[id] = i;
			}
			for (int j = 1; (1 << j) <= (int)pos[color].size(); j++) {
				for (int i = 0; i + (1 << j) - 1 < (int)pos[color].size(); i++) {
					int id1 = pos[color][i], id2 = pos[color][i + (1 << (j - 1))];
					block[id1][j] = merge(block[id1][j - 1], block[id2][j - 1]);
				}
			}
		}
		
		a[n + 1] = c[n + 1] = 0;
		for (int i = 1; i <= cntBig; i++) lst[i] = -1;
		for (int i = 0; i <= n + 1; i++) {
			if (idBig[c[i]] > 0) lst[idBig[c[i]]] = inDex[i];
			for (int j = 1; j <= cntBig; j++) {
				nearLef[i][j] = lst[j];
			}
		}
		for (int i = 1; i <= cntBig; i++) lst[i] = 1e9;
		for (int i = n + 1; i >= 0; i--) {
			if (idBig[c[i]] > 0) lst[idBig[c[i]]] = inDex[i];
			for (int j = 1; j <= cntBig; j++) {
				nearRig[i][j] = lst[j];
			}
		}
		
		while (q--) {
			int x, y; cin >> x >> y;
			if (idBig[x] > 0 && idBig[y] > 0) {
				cout << prep[min(idBig[x], idBig[y])][max(idBig[x], idBig[y])].val << "\n";
				continue;
			}
			
			if (idBig[x] == 0 && idBig[y] == 0) {
				Block ans = Block();
				int ptr = -1;
				for (int i : pos[x]) {
					while (ptr + 1 < (int)pos[y].size() && pos[y][ptr + 1] < i) {
						ptr++;
						ll tmp = a[pos[y][ptr]];
						ans = merge(ans, Block(tmp, tmp, tmp, tmp));
					}
					ans = merge(ans, Block(a[i], a[i], a[i], a[i]));
				}
				while (ptr + 1 < (int)pos[y].size()) {
					ptr++;
					ll tmp = a[pos[y][ptr]];
					ans = merge(ans, Block(tmp, tmp, tmp, tmp));
				}
				cout << ans.val << "\n";
				continue;
			}
			
			if (idBig[x] > 0) swap(x, y);
			Block ans = Block();
			for (int i = 0; i <= (int)pos[x].size(); i++) {
				int pre, cur;
				pre = (i == 0 ? 0 : pos[x][i - 1]);
				cur = (i == (int)pos[x].size() ? n + 1 : pos[x][i]);
				int L = nearRig[pre][idBig[y]], R = nearLef[cur][idBig[y]];
				while (L <= R) {
					int len = R - L + 1;
					ans = merge(ans, block[pos[y][L]][lg[len]]);
					L += (1 << lg[len]);
				}
				if (cur >= 1 && cur <= n) {
					ans = merge(ans, Block(a[cur], a[cur], a[cur], a[cur]));
				}
			}
			
			cout << ans.val << "\n";
		}
	}
}
