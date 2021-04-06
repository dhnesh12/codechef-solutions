#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 100005;
const int Mod = 1e9 + 7;
int n, q, mod, posx[maxn], posy[maxn], num[maxn], vis[maxn];
int _pw[maxn << 1], *pw = _pw + 1;
map<int, int> Map[maxn];

inline int mul(int x, int y) {
	return 1ll * x * y % mod;
}
int quick_pow(int x, int y) {
	int res = 1;
	while(y) {
		if(y & 1) res = mul(res, x);
		x = mul(x, x), y >>= 1;
	}
	return res;
}
unordered_map<int, int> Inv;
inline int getinv(int x) { 
	if(Inv.count(x)) return Inv[x]; 
	return Inv[x] = quick_pow(x, mod - 2);
} 

int ans;
set<pair<int, int> > s[maxn];
int fa[maxn], sz[maxn], dis[maxn], len[maxn];

int top;
pair<int, int> st[maxn];
inline int getfa(int x, int r) {
	if(fa[x] == x) return x;
	len[r] = mul(len[r], dis[x]);
	return getfa(fa[x], r);
}
void merge(int x, int y, int z) {// y -> x and y / x = z
	if(ans == -1) return;
	len[x] = len[y] = 1;
	int fx = getfa(x, x), fy = getfa(y, y);
	if(fx == fy) {
		if(len[y] != mul(len[x], z)) ans = -1;
		return;
	}
	ans--;
	if(sz[fx] < sz[fy]) 
		swap(fx, fy), swap(x, y), z = getinv(z);
		
	fa[fy] = fx;
	sz[fx] += sz[fy];
	
	dis[fy] = mul(mul(len[x], getinv(len[y])), z);
	
	st[++top] = make_pair(fx, fy);
}
void recover(int pre_top) {
	while(top != pre_top) {
		int x = st[top].first, y = st[top].second;
		fa[y] = y, dis[y] = 0;
		sz[x] -= sz[y];
		top--;
	}
}

void ins(int x, int y, int z) {
	if(!s[y].size()) ans--;
	auto it = s[y].insert(make_pair(x, z)).first;
	if(it != s[y].begin()) {
		auto pre = prev(it);
		merge(pre -> first, x, mul(z, getinv(pre -> second)));
	}
	if(next(it) != s[y].end()) {
		auto nxt = next(it);
		merge(nxt -> first, x, mul(z, getinv(nxt -> second)));
	}
}
void del(int x, int y, int z) {
	s[y].erase(make_pair(x, z));
}

struct opt {
	int x, y, z;
	opt(int _x = 0, int _y = 0, int _z = 0) { x = _x, y = _y, z = _z; }
};
vector<opt> T[maxn << 2];
void modify(int l, int r, int id, int L, int R, opt x) {
	if(L <= l && r <= R) {
		T[id].push_back(x);
		return;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) modify(l, mid, id << 1, L, R, x);
	if(R > mid) modify(mid + 1, r, id << 1 | 1, L, R, x);
}
void solve(int l, int r, int id) {
	int pre_ans = ans, pre_top = top, endpos = (int)T[id].size() - 1;
	for(int i = 0; i < (int)T[id].size(); i++) {
		opt u = T[id][i];
		ins(u.x, u.y, u.z);
		if(ans == -1) {
			endpos = i;
			break;
		}
	}
	
	auto pushup = [=]() -> void {
		ans = pre_ans;
		for(int i = 0; i <= endpos; i++) {
			opt u = T[id][i];
			del(u.x, u.y, u.z);
		}
		recover(pre_top);
	};
	
	if(ans == -1 || l == r) {
		for(int i = l; i <= r; i++) printf("%d\n", pw[ans]);
		
		pushup();
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid, id << 1);
	solve(mid + 1, r, id << 1 | 1);
	
	pushup();
}

int main() {
	scanf("%d%d%d", &n, &q, &mod);
	for(int i = 1, x, y, z; i <= q; i++) {
		scanf("%d%d%d", &x, &y, &z);
		if(Map[x][y]) {
			int lst = Map[x][y];
			modify(1, q, 1, lst, i - 1, opt(x, y, z));
			
			vis[lst] = -1, Map[x][y] = 0;
		}
		else {
			posx[i] = x, posy[i] = y, num[i] = z;
			vis[i] = 1, Map[x][y] = i;
		}
	}
	for(int i = 1; i <= q; i++)
		if(vis[i] == 1) modify(1, q, 1, i, q, opt(posx[i], posy[i], num[i])); 
	
	pw[0] = 1;	
	for(int i = 1; i <= n * 2 - 1; i++) pw[i] = 1ll * pw[i - 1] * (mod - 1) % Mod;
	
	ans = n * 2 - 1;		
	for(int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
	solve(1, q, 1);
	return 0;
}