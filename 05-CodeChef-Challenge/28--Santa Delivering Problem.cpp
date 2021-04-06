#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <queue>
#include <stack>
#include <sstream>
#include <cstring>
#include <numeric>
#include <ctime>
#include <cassert>

#define re return
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int) (x).size())
#define rep(i, n) for (int i = 0; i < (n); i++)
#define rrep(i, n) for (int i = (n) - 1; i >= 0; i--)
#define y0 y32479
#define y1 y95874
#define fill(x, y) memset(x, y, sizeof(x))
#define sqr(x) ((x) * (x))
#define sqrt(x) sqrt(abs(x))
#define unq(x) (x.resize(unique(all(x)) - x.begin()))
#define spc(i,n) " \n"[i == n - 1]
#define next next239
#define prev prev239
#define BIT(x, i) ((x >> i) & 1)

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<string> vs;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;

template<class T> T abs(T x) { return x > 0 ? x : -x;}

int n, m, w;
int x[550], y[550];
int prev[550], cur[550], prev0[550], cur0[550];
int p[55];
int pos;
double dist[550][550];
int dist2[550][550];

D magic = .75;

vi bag;
int cw;
int k;

vs ans;
double dans;

vs bestAns;
double bestDans;

void Clear() {
	bestAns.clear();
}

void trySave() {
	if (!sz(bestAns) || dans < bestDans) {
		bestDans = dans;
		bestAns = ans;
	}
}

void reset() {
	rep(i, n) {
		cur[i] = cur0[i];
		prev[i] = prev0[i];
	}
	bag.clear();
	cw = 0;
	ans.clear();
	dans = 0;
	pos = n;
}

void add(stringstream &s) {
	ans.pb(s.str());
}

void out(int id) {
	stringstream cout;
	int ok = 0;
	cout << "3 " << id + 1 << "\n";
	rep(i, sz(bag)) {
		if (bag[i] == id) {
			swap(bag[i], bag.back());
			bag.pop_back();
			ok = 1;
			break;
		}
	}
	assert(ok);
	cw -= p[id];
	add(cout);
}

void take(int id) {
	stringstream cout;
	cout << "2 " << id + 1 << "\n";
	cw += p[id];
	bag.pb(id);
	add(cout);
}

void home() {
	stringstream cout;
	cout << "1 " << 0 << "\n";
	add(cout);

	dans += dist[pos][n];
	pos = n;
}

void go(int i) {
	stringstream cout;
	cout << "1 " << i + 1 << "\n";
	add(cout);

	dans += dist[pos][i];
	pos = i;
}

void end() {
	for (string s : bestAns)
		cout << s;
	cout << "0" << endl;
}

void clear() {
	while (sz(bag))
		out(bag[0]);
}

void clearChild(int i) {
	go(i);
	out(cur[i]);
	take(prev[i]);
	prev[i] = cur[i];
}

int nearest(int id, ll gift = -1) {
	int ans = -1;
	rep(i, n) {
		if (i == id || cur[i] == prev[i])
			continue;
		if (gift != -1 && !BIT(gift, cur[i]))
			continue;
		//if (cw + prev[i] - cur[i] > w)
		//	continue;
		if (ans == -1 || dist2[id][ans] > dist2[id][i])
			ans = i;
	}
	re ans;
}

void path() {
	//take(cur[id]);
	int id = n;
	while (1) {
		ll mask = 0;
		for (int x : bag)
			mask |= (1ll << x);
		id = nearest(id, mask);
		if (id == -1)
			break;
		clearChild(id);
	}
	home();
	clear();
}

int takeAndPath() {
	vi v;
	rep(i, n)
	if (cur[i] != prev[i])
		v.pb(cur[i]);

	if (!sz(v))
		re 0;

	/*
	if (sz(v) > k) {
		sort(all(v));
		unq(v);
	}*/

	assert(cw == 0);

	random_shuffle(all(v));
	rep(i, sz(v)) {
		int x = v[i];

		if (cw + p[x] > w)
			continue;

		take(x);

		if (i >= k - 1)// && cw + p[x] > w * magic)
			break;
	}

	path();
	re 1;
}

void trySingle() {
	reset();

	/*
	vi v(n);
	rep(i, n)
		v[i] = i;

	random_shuffle(all(v));*/

	/*
	while (1) {
		int p = nearest(n);
		if (p == -1)
			break;
		path(p);
	}*/

	while (takeAndPath());

	/*
	for (int i : v) {
		if (prev[i] == cur[i])
			continue;
		path(i);
	}*/

	trySave();
#ifdef LOCAL_BOBER
	cerr << dans << endl;
#endif
}

void solve() {

	cin >> n >> m >> w >> x[n] >> y[n];
	rep(i, m)
		cin >> p[i];
	rep(i, n) {
		cin >> x[i] >> y[i] >> prev0[i] >> cur0[i];
		prev0[i]--;
		cur0[i]--;
	}
	Clear();
	k = w / *max_element(p, p + m);

	rep(i, n + 1) rep(j, n + 1) {
		dist2[i][j] = sqr(x[i] - x[j]) + sqr(y[i] - y[j]);
		dist[i][j] = sqrt(dist2[i][j]);
	}

	rep(i, 100)
		trySingle();
}

int main() {
#ifdef LOCAL_BOBER
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#else
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
#endif


	int tc = 1;
	cin >> tc;
	rep(tt, tc) {
		solve();
		end();
	}
}









