// what the hell
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 400000 + 10;
const int base = 200000;
char type[maxn];
int px[maxn], py[maxn];
map<pair<int, int>, int> mp;
map<int, pair<int, int> > point;
int newint = 0;
set<pair<int, int> > s[4 * maxn];
int par[maxn];

int get_par(int v){
	return par[v] < 0 ? v : par[v] = get_par(par[v]);
}

void merge(int v, int u){
	if ((v = get_par(v)) == (u = get_par(u)))
		return;
	if (par[v] > par[u])
		swap(v, u);
	par[v] += par[u];
	par[u] = v;
}

void serch(int id, int L, int R, int l, int r, int lo, int hi, int v){
	if (r <= L or R <= l)
		return;
	if (l <= L and R <= r){
		auto it = s[id].lower_bound({lo, -1});
		while (it != s[id].end() and (*it).first < hi){
			merge(v, (*it).second);
			s[id].erase(it);
			it = s[id].lower_bound({lo, -1});
		}
		return;
	}
	int mid = (L + R) >> 1;
	serch(2 * id + 0, L, mid, l, r, lo, hi, v);
	serch(2 * id + 1, mid, R, l, r, lo, hi, v);
}

void add(int id, int L, int R, int idx, int val, int x){
	if (idx < L or R <= idx)
		return;
	s[id].insert({val, x});
	if (L + 1 == R)
		return;
	int mid = (L + R) >> 1;
	add(2 * id + 0, L, mid, idx, val, x);
	add(2 * id + 1, mid, R, idx, val, x);
}

void add(int x, int y){
	if (mp.count({x, y}))
		return;
	mp[{x, y}] = newint;
	point[newint] = {x, y};
	add(1, 0, maxn, x, y, newint ++);
}

int main(){
	ios_base::sync_with_stdio(false);
	int Q, r;
	cin >> Q >> r;
	for (int i = 1; i <= Q; i++){
		cin >> type[i];
		if (type[i] == '+'){
			int x, y;
			cin >> x >> y;
			int newx = (x + y), newy = (x - y);
			x = newx, y = newy;
			x += base, y += base;
			px[i] = x, py[i] = y;
			add(x - r, y - r);
			add(x - r, y + r);
			add(x + r, y - r);
			add(x + r, y + r);
		}
		else{
			cin >> px[i] >> py[i];
		}
	}
	memset(par, -1, sizeof par);
	for (int i = 1; i <= Q; i++){
		if (type[i] == '?'){
			int fi = mp[{px[px[i]] - r, py[px[i]] - r}];
			int se = mp[{px[py[i]] - r, py[py[i]] - r}];
			cout << (get_par(fi) == get_par(se) ? "DA\n" : "NET\n");
			continue;
		}
		merge(mp[{px[i] - r, py[i] - r}], mp[{px[i] - r, py[i] + r}]);
		merge(mp[{px[i] - r, py[i] - r}], mp[{px[i] + r, py[i] - r}]);
		merge(mp[{px[i] - r, py[i] - r}], mp[{px[i] + r, py[i] + r}]);
		serch(1, 0, maxn, px[i] - r, px[i] + r + 1, py[i] - r, py[i] + r + 1, mp[{px[i] - r, py[i] - r}]);
	}
}
