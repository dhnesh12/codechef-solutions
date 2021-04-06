#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5;
int n, m, rt;

bool rnd(int x, int y) {
	return rand() % (x + y) < x;
}

namespace bst {
	int lc[maxn + 10], rc[maxn + 10], sz[maxn + 10];
	bool rev[maxn + 10];

	void apply(int p) {
		rev[p] ^= 1; swap(lc[p], rc[p]);
	}

	void push(int p) {
		if (rev[p]) {
			if (lc[p]) apply(lc[p]);
			if (rc[p]) apply(rc[p]);
			rev[p] = 0;
		}
	}

	void update(int p) {
		sz[p] = sz[lc[p]] + sz[rc[p]] + 1;
	}

	int merge(int x, int y) {
		if (!x || !y) return x + y;
		if (rnd(sz[x], sz[y])) {
			push(x); rc[x] = merge(rc[x], y);
			update(x); return x;
		} else {
			push(y); lc[y] = merge(x, lc[y]);
			update(y); return y;
		}
	}

	void split(int p, int k, int &x, int &y) {
		if (!p) x = y = 0;
		else {
			push(p);
			if (k <= sz[lc[p]]) {
				y = p; split(lc[p], k, x, lc[p]);
			} else {
				x = p; split(rc[p], k - sz[lc[p]] - 1, rc[p], y);
			}
			update(p);
		}
	}

	void dfs(int p) {
		if (!p) return;
		push(p);
		dfs(lc[p]); printf("%d ", p);
		dfs(rc[p]);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		bst::update(i); rt = bst::merge(rt, i);
	}
	while (m--) {
		int a, b, c; scanf("%d%d%d", &a, &b, &c);
		int p, q;
		bst::split(rt, a, p, rt);
		bst::split(rt, b, q, rt);
		rt = bst::merge(p, rt);
		bst::split(rt, c, p, rt);
		bst::apply(q);
		rt = bst::merge(q, rt);
		rt = bst::merge(p, rt);
	}
	bst::dfs(rt);
}
