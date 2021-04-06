#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set> 
using namespace std;
const int INF = 0x3f3f3f3f;
#define ll long long int
#define ld long double
#define mp make_pair
#define MOD 1000000007
#define maxn 100000
//******************************
vector<pair<int, ll>> adj[maxn];
struct Dinic {
	vector<pair<int, ll>> residue[maxn];
	int rank[maxn], vis[maxn];
	int n;
	void init(int nn) {
		n = nn;
		for (int i = 1;i <= n;i++) {
			residue[i].clear();
			for (auto v : adj[i]) {
				residue[i].push_back(mp(v.first, v.second));
			}
		}
	}
	void ass_set() {
		for (int i = 0;i <= n;i++) { vis[i] = 0; }
	}
	void reset() {
		for (int i = 0;i <= n;i++) { rank[i] = 0; }
	}
	bool bfs(int s, int t) {
		deque<pair<int, int>> lop;
		lop.push_front(mp(s, 0));
		vis[s] = 1;
		while (!lop.empty()) {
			auto v = lop.back();
			for (auto vv : residue[v.first]) {
				if (vv.second>0 && !vis[vv.first] && vv.first != t) {
					vis[vv.first] = 1;
					rank[vv.first] = v.second + 1;
					lop.push_front(mp(vv.first, v.second + 1));
				}
				else if (vv.second>0 && !vis[vv.first]) {
					vis[vv.first] = 1;
					rank[vv.first] = v.second + 1;
				}
			}
			lop.pop_back();
		}
		if (rank[t] > 0) {
			return true;
		}
		else {
			return false;
		}
	}
	vector<pair<int, int>> path, pat;
	ll mini;
	bool hot;
	void dfs(int node, int t, ll mani) {
		if (hot) { return; }
		if (node == t) {
			mini = mani;
			for (auto v : pat) { path.push_back(v); }
			hot = true;return;
		}
		for (int z = 0;z < residue[node].size();z++) {
			auto v = residue[node][z];
			if (hot) { return; }
			if (v.second > 0 && !vis[v.first] && rank[node] < rank[v.first]) {
				vis[v.first] = true;
				pat.push_back(mp(node, z));
				dfs(v.first, t, min(mani, v.second));
				pat.pop_back();
			}
		}
	}
	ll max_flow(int s, int t) {
		ll ans = 0;
		while (1) {
			reset();
			ass_set();
			//do bfs to rank
			bool tool = bfs(s, t);
			if (!tool) { break; }
			//calculate all path_flow(if there are no:break)
			while (1) {
				path.clear();hot = false;mini = 1000000000000000001;pat.clear();
				ass_set();
				dfs(s, t, 1000000000000000001);
				pat.clear();
				if (hot) {
					ans = ans + mini;
					for (auto v : path) {
						int dx = v.second;
						residue[v.first][dx].second -= mini;
						int sec = residue[v.first][dx].first;
						int nmmm = 1;
						if (nmmm) {
							bool ok = true;
							for (int z = 0;z < residue[sec].size();z++) {
								if (residue[sec][z].first == v.first) {
									residue[sec][z].second += mini;
									ok = false;
									break;
								}
							}
							if (ok) {
								residue[sec].push_back(mp(v.first, mini));
							}
						}
						else {//can use this if num of neighbouar is bigg
							residue[sec].push_back(mp(v.first, mini));
						}
					}
				}
				else {
					break;
				}
			}
		}
		return ans;
	}
	vector<int> min_cuts(int s, int t) {
		vector<int> ans;

		return ans;
	}
	vector<int> kth_min_cut(int s, int t) {
		vector<int> ans;

		return ans;
	}
} dnc;
struct Edge
{
	int from, to, cap, flow;
	Edge(int _from, int _to, int _cap, int _flow) :
		from(_from), to(_to), cap(_cap), flow(_flow) {}
};

vector < vector < int > > g;
vector < Edge > e;
vector < int > ptr;
vector < int > dist;
int cnt, st, en;



typedef pair < int, int > pii;
typedef pair < pii, pii > segment;
typedef vector < segment > vs;

bool
isExistX(int l, int r, int y, vs &checks)
{
	for (int i = 0; i < int(checks.size()); ++i) {
		if (checks[i].first.second != checks[i].second.second) {
			continue;
		}
		int a = checks[i].first.first;
		int b = checks[i].second.first;
		if (a > b) {
			swap(a, b);
		}
		if (checks[i].first.second == y && a <= l && b >= r) {
			return true;
		}
	}
	return false;
}

bool
isExistY(int l, int r, int x, vs &checks)
{
	for (int i = 0; i < int(checks.size()); ++i) {
		if (checks[i].first.first != checks[i].second.first) {
			continue;
		}
		int a = checks[i].first.second;
		int b = checks[i].second.second;
		if (a > b) {
			swap(a, b);
		}
		if (checks[i].first.first == x && a <= l && b >= r) {
			return true;
		}
	}
	return false;
}

typedef vector < int > vi;
typedef vector < vi > v2i;
typedef vector < bool > vb;
typedef vector < vb > v2b;

int
weight(int cx, int cy, v2b &used, v2i &col, vi &x, vi &y, int cur_num, vs &segs)
{
	int sum = (y[cy + 1] - y[cy]) * (x[cx + 1] - x[cx]);
	used[cx][cy] = true;
	col[cx][cy] = cur_num;
	if (cx != 0) {
		if (!isExistY(y[cy], y[cy + 1], x[cx], segs) && !used[cx - 1][cy]) {
			sum += weight(cx - 1, cy, used, col, x, y, cur_num, segs);
		}
	}
	if (cx != int(x.size()) - 2) {
		if (!isExistY(y[cy], y[cy + 1], x[cx + 1], segs) && !used[cx + 1][cy]) {
			sum += weight(cx + 1, cy, used, col, x, y, cur_num, segs);
		}
	}
	if (cy != 0) {
		if (!isExistX(x[cx], x[cx + 1], y[cy], segs) && !used[cx][cy - 1]) {
			sum += weight(cx, cy - 1, used, col, x, y, cur_num, segs);
		}
	}
	if (cy != int(y.size()) - 2) {
		if (!isExistX(x[cx], x[cx + 1], y[cy + 1], segs) && !used[cx][cy + 1]) {
			sum += weight(cx, cy + 1, used, col, x, y, cur_num, segs);
		}
	}
	return sum;
}

void
dsu_dfs(int x, vb &used, vi &col, int ccol, v2b &sm)
{
	used[x] = true;
	int cnt = int(sm[x].size());
	col[x] = ccol;
	for (int i = 0; i < cnt; ++i) {
		if (!used[i] && sm[x][i]) {
			dsu_dfs(i, used, col, ccol ^ 1, sm);
		}
	}
}

void
process()
{
	int n, m;
	cin >> n >> m;
	vector < int > xd, yd;
	vs segs;
	xd.push_back(0);
	xd.push_back(n);
	yd.push_back(0);
	yd.push_back(n);
	for (int i = 0; i < m; ++i) {
		int cp;
		cin >> cp;
		vector < pair < int, int > > points(cp);
		for (int i = 0; i < cp; ++i) {
			cin >> points[i].first >> points[i].second;
			xd.push_back(points[i].first);
			yd.push_back(points[i].second);
		}
		for (int i = 0; i < cp; ++i) {
			segs.push_back(make_pair(points[i], points[(i + 1) % cp]));
		}
	}
	sort(xd.begin(), xd.end());
	sort(yd.begin(), yd.end());
	xd.resize(unique(xd.begin(), xd.end()) - xd.begin());
	yd.resize(unique(yd.begin(), yd.end()) - yd.begin());
	int dx = int(xd.size()) - 1;
	int dy = int(yd.size()) - 1;
	vector < vector < bool > > used(dx, vector < bool >(dy, false));
	vector < vector < int > > col(dx, vector < int >(dy, 0));
	int cur_cnt = 0;
	vi dsu_w;
	for (int i = 0; i < dx; ++i) {
		for (int j = 0; j < dy; ++j) {
			if (!used[i][j]) {
				int sum = weight(i, j, used, col, xd, yd, cur_cnt, segs);
				++cur_cnt;
				dsu_w.push_back(sum);
			}
		}
	}
	v2b matrix(cur_cnt, vb(cur_cnt, false));
	for (int i = 0; i < dx; ++i) {
		for (int j = 0; j < dy; ++j) {
			if (i && isExistY(yd[j], yd[j + 1], xd[i], segs)) {
				//assert(col[i][j] != col[i - 1][j]);
				matrix[col[i][j]][col[i - 1][j]] = true;
			}
			if (j && isExistX(xd[i], xd[i + 1], yd[j], segs)) {
				//assert(col[i][j] != col[i][j - 1]);
				matrix[col[i][j]][col[i][j - 1]] = true;
			}
			if (i != dx - 1 && isExistY(yd[j], yd[j + 1], xd[i + 1], segs)) {
				//assert(col[i][j] != col[i + 1][j]);
				matrix[col[i][j]][col[i + 1][j]] = true;
			}
			if (j != dy - 1 && isExistX(xd[i], xd[i + 1], yd[j + 1], segs)) {
				//assert(col[i][j] != col[i][j + 1]);
				matrix[col[i][j]][col[i][j + 1]] = true;
			}
		}
	}
	vb dsu_used(cur_cnt, false);
	vi dsu_col(cur_cnt, 0);
	for (int i = 0; i < cur_cnt; ++i) {
		if (!dsu_used[i]) {
			dsu_dfs(i, dsu_used, dsu_col, 0, matrix);
		}
	}
	cnt = cur_cnt + 2;
	st = 0;
	en = cnt - 1;
	e.clear();
	g.clear();
	g.resize(cnt);
	int masi = 0;
	for (int i = 0; i < cur_cnt; ++i) {
		if (dsu_col[i]) {
			adj[i + 2].push_back(mp(en + 1, dsu_w[i]));
			masi = max(masi, i + 2);
			masi = max(masi, en + 1);
		}
		else {
			adj[st + 1].push_back(mp(i + 2, dsu_w[i]));
			masi = max(masi, i + 2);
			masi = max(masi, st + 1);
		}
	}
	for (int i = 0; i < cur_cnt; ++i) {
		if (dsu_col[i]) {
			continue;
		}
		for (int j = 0; j < cur_cnt; ++j) {
			if (matrix[i][j]) {
				adj[i + 2].push_back(mp(j + 2, INF));
				masi = max(masi, i + 2);
				masi = max(masi, j + 2);
			}
		}
	}
	dnc.init(masi);
	int res = dnc.max_flow(st + 1, en + 1);;
	cout << n * n - res << '\n';
	for (int i = 0;i <= masi;i++) { adj[i].clear(); }
}
//just for check my dinic
int
main(int argc, char **argv)
{
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for (; t; --t) {
		process();
	}
	return 0;
}