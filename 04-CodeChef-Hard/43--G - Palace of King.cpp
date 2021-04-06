#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
	#define eprintf(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
#define mp make_pair

const int INF = (int)1e9 + 7;

const int N = 1024;
struct Node {
	int l, r;
	int val;
	int toAdd;

	Node() : l(), r(), val(), toAdd() {}
	Node(int _l, int _r) : l(_l), r(_r), val(0), toAdd(0) {}
};
Node tree[2 * N];

void push(int v) {
	if (v >= N) throw;
	for (int u = 2 * v; u < 2 * v + 2; u++) {
		tree[u].val += tree[v].toAdd;
		tree[u].toAdd += tree[v].toAdd;
	}
	tree[v].toAdd = 0;
}
void update(int v) {
	tree[v].val = min(tree[2 * v].val, tree[2 * v + 1].val);
}

void buildTree() {
	for (int i = 0; i < N; i++)
		tree[N + i] = Node(i, i + 1);
	for (int i = N - 1; i > 0; i--)
		tree[i] = Node(tree[2 * i].l, tree[2 * i + 1].r);
}

void addOnSegm(int v, int l, int r, int dx) {
	if (l <= tree[v].l && tree[v].r <= r) {
		tree[v].val += dx;
		tree[v].toAdd += dx;
		return;
	}
	if (l >= tree[v].r || tree[v].l >= r) return;
	push(v);
	addOnSegm(2 * v, l, r, dx);
	addOnSegm(2 * v + 1, l, r, dx);
	update(v);
}
int getMin(int v, int l, int r) {
	if (l <= tree[v].l && tree[v].r <= r)
		return tree[v].val;
	if (l >= tree[v].r || tree[v].l >= r)
		return INF;
	push(v);
	return min(getMin(2 * v, l, r), getMin(2 * v + 1, l, r));
}

struct Event {
	int l, r;
	int dx;

	Event() : l(), r(), dx() {}
	Event(int _l, int _r, int _dx) : l(_l), r(_r), dx(_dx) {}
};

int W, H;
int C;
int a[N][5];
int n;
int ans;
vector<Event> b[N], c[N];

void solve() {
	ans = 0;
	scanf("%d%d%d", &W, &H, &C);
	if (W >= N - 4 || H >= N - 4) throw;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d%d%d", &a[i][0], &a[i][1], &a[i][2], &a[i][3], &a[i][4]);
		a[i][2] += a[i][0];
		a[i][3] += a[i][1];
	}
	for (int h = 1; h <= H; h++) {
		buildTree();
		for (int i = 0; i <= W; i++) {
			b[i].clear();
			c[i].clear();
		}
		for (int i = 0; i < n; i++) {
			int l = max(0, a[i][1] - h + 1), r = min(a[i][3], H - h + 1);
			b[a[i][0]].push_back(Event(l, r, a[i][4]));
			c[a[i][2]].push_back(Event(l, r, -a[i][4]));
		}
		int r = 0;
		for (int l = 0; l < W; l++) {
			for (Event e : c[l]) {
				addOnSegm(1, e.l, e.r, e.dx);
			}
			while(r <= W && getMin(1, 0, H - h + 1) <= C) {
				for (Event e : b[r]) {
					addOnSegm(1, e.l, e.r, e.dx);
				}
				r++;
			}
			//printf("%d %d %d --- %d\n", h, l, r, getMin(1, 0, H - h + 1));
			ans = max(ans, (r - l - 1) * h);
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		solve();
		printf("Case %d: %d\n", t, ans);
	}

	return 0;
}
