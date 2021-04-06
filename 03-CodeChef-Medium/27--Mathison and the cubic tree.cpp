#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:16000000")
using namespace std;
 
typedef pair <int, int> ii;
typedef long long ll;
 
const int Inf = 1000000000;
const int Maxn = 100005;
const int mod1 = 1000000007;
const int mod2 = 1000000009;
const int arg1 = 461;
const int arg2 = 1688509;
const int Maxm = 1000001;
 
int pw1[Maxm], pw2[Maxm];
int mx[Maxm];
int t;
int n;
int a[Maxn];
vector <ii> seq[Maxn];
vector <int> neigh[Maxn];
bool er[Maxn];
int cnt[Maxn];
map <ii, int> L;
int gcnt[Maxm];
ii H;
int res;
 
void Add(int num, int cnt)
{
	if (cnt == 0) return;
	int add1 = ll(pw1[num]) * cnt % mod1;
	if (add1 < 0) add1 += mod1;
	int add2 = ll(pw2[num]) * cnt % mod2;
	if (add2 < 0) add2 += mod2;
	H = ii((H.first + add1) % mod1, (H.second + add2) % mod2);
}
 
void Modify(const vector <ii> &seq, bool inv)
{
	for (int i = 0; i < seq.size(); i++) {
		Add(seq[i].first, -gcnt[seq[i].first]);
		gcnt[seq[i].first] = (gcnt[seq[i].first] + (inv? 3 - seq[i].second: seq[i].second)) % 3;
		Add(seq[i].first, gcnt[seq[i].first]);
	}
}
 
void Count(int v, int p)
{
	cnt[v] = 1;
	for (int i = 0; i < neigh[v].size(); i++) {
		int u = neigh[v][i];
		if (u == p || er[u]) continue;
		Count(u, v);
		cnt[v] += cnt[u];
	}
}
 
int getCentroid(int v, int p, int need)
{
	for (int i = 0; i < neigh[v].size(); i++) {
		int u = neigh[v][i];
		if (u == p || er[u]) continue;
		if (cnt[u] > need / 2) return getCentroid(u, v, need);
	}
	return v;
}
 
int Get(const ii &p)
{
	map <ii, int>::iterator it = L.find(p);
	if (it != L.end()) return it->second;
	else return -Inf;
}
 
void Upd(const ii &p, int val)
{
	map <ii, int>::iterator it = L.find(p);
	if (it != L.end()) it->second = max(it->second, val);
	else L.insert(make_pair(p, val));
}
 
void Check(int v, int p, int lvl)
{
	Modify(seq[v], false);
	res = max(res, lvl + Get(H));
	for (int i = 0; i < neigh[v].size(); i++) {
		int u = neigh[v][i];
		if (u == p || er[u]) continue;
		Check(u, v, lvl + 1);
	}
	Modify(seq[v], true);
}
 
void Record(int v, int p, int lvl)
{
	Modify(seq[v], true);
	Upd(H, lvl);
	for (int i = 0; i < neigh[v].size(); i++) {
		int u = neigh[v][i];
		if (u == p || er[u]) continue;
		Record(u, v, lvl + 1);
	}
	Modify(seq[v], false);
}
 
void Solve(int v)
{
	Count(v, 0);
	int c = getCentroid(v, 0, cnt[v]);
	L.clear();
	if (seq[c].empty()) res = max(res, 0);
	Upd(ii(0, 0), 0);
	for (int i = 0; i < neigh[c].size(); i++) {
		int u = neigh[c][i];
		if (er[u]) continue;
		Modify(seq[c], false);
		Check(u, c, 1);
		Modify(seq[c], true);
		Record(u, c, 1);
	}
	er[c] = true;
	for (int i = 0; i < neigh[c].size(); i++) {
		int u = neigh[c][i];
		if (er[u]) continue;
		Solve(u);
	}
}
 
int main()
{
	pw1[0] = pw2[0] = 1;
	for (int i = 1; i < Maxm; i++) {
		pw1[i] = ll(pw1[i - 1]) * arg1 % mod1;
		pw2[i] = ll(pw2[i - 1]) * arg2 % mod2;
	}
	for (int i = 2; i < Maxm; i++) if (mx[i] == 0)
		for (int j = i; j < Maxm; j += i)
			mx[j] = i;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			er[i] = false;
			scanf("%d", &a[i]);
			seq[i].clear();
			int num = a[i];
			while (num > 1) {
				int cur = mx[num];
				int cnt = 0;
				while (num % cur == 0) {
					num /= cur;
					cnt++;
				}
				cnt %= 3;
				if (cnt) seq[i].push_back(ii(cur, cnt));
			}
			neigh[i].clear();
		}
		for (int i = 0; i < n - 1; i++) {
			int a, b; scanf("%d %d", &a, &b);
			neigh[a].push_back(b);
			neigh[b].push_back(a);
		}
		res = -2;
		Solve(1);
		printf("%d\n", res + 1);
	}
	return 0;
} 