
#include <bits/stdc++.h>

#define ln                '\n'
#define all(dat)           dat.begin(), dat.end()
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fm, to)    for (int i = fm; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int nsz = 2e5, lgsz = 18, bsz = 500, samsz = 2 * nsz, alphsz = 26;
int ts, n, q, w[samsz + 5], pre[samsz + 5], at[samsz + 5], rk[samsz + 5], fm[samsz + 5];
int pr[samsz + 5], siz[samsz + 5], dep[samsz + 5], hs[samsz + 5], top[samsz + 5], dfn[samsz + 5];
string s;

struct suffix_automaton {
	bool sf[samsz + 5];
	int rt, sz, lst, pr[samsz + 5], len[samsz + 5], g[samsz + 5][alphsz + 5];
	
	suffix_automaton() { rt = lst = ++sz; }
	
	void inline ins(char ch) {
		int c = isalpha(ch) ? (ch - 'a') : alphsz, p = lst, u = lst = ++sz;
		sf[u] = 1, len[u] = len[p] + 1;
		
		for (; !g[p][c]; g[p][c] = u, p = pr[p]);
		if (!p) { pr[u] = rt; return; }
		int q = g[p][c];
		if (len[q] == len[p] + 1) pr[u] = q;
		else {
			int v = ++sz;
			
			pr[v] = pr[q], len[v] = len[p] + 1, memcpy(g[v], g[q], sizeof(g[q]));
			pr[u] = pr[q] = v;
			for (; g[p][c] == q; g[p][c] = v, p = pr[p]);
		}
	}
	
	void inline ins(const string &s) {
		loop (i, s.size()) ins(s[i]);
	}
};
suffix_automaton sam;

struct graph {
	int sz, hd[samsz + 5];
	
	struct edge {
		int nxt, to;
		
		edge() {}
		edge(int nxt, int to) {
			this->nxt = nxt, this->to = to;
		}
	} e[samsz + 5];
	
	inline edge& operator [] (int id) { return e[id]; }
	
	void inline clear() {
		cont (u, sam.sz) hd[u] = 0;
		sz = 0;
	}
	
	void inline link(int u, int v) {
		e[++sz] = edge(hd[u], v), hd[u] = sz;
	}
};
graph g;

struct query {
	int l, r, id;
	
	query() {}
	query(int l, int r, int id) {
		this->l = l, this->r = r, this->id = id;
	}
	
	friend inline bool operator < (const query a, const query b) { return a.l / bsz != b.l / bsz ? a.l / bsz < b.l / bsz : a.r < b.r; }
};
query qy[nsz + 5];

void dfs1(int u = sam.rt) {
	siz[u] = 1;
	if (sam.sf[u] && sam.len[u]) { at[n - sam.len[u] + 1] = u; return; }
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		pr[v] = u, dep[v] = dep[u] + 1;
		dfs1(v);
		siz[u] = siz[v] + 1;
		if (siz[hs[u]] < siz[v]) hs[u] = v;
	}
}

void dfs2(int u = sam.rt, int tp = sam.rt) {
	static int t = 0, k  = 0;
	if (u == sam.rt) t = k = 0;
	dfn[u] = ++t;
	top[u] = tp;
	if (sam.sf[u]) {
		rk[u] = ++k;
		fm[k] = u;
	}
	if (!hs[u]) return;
	dfs2(hs[u], tp);
	for (int i = g.hd[u]; i; i = g[i].nxt) {
		int v = g[i].to;
		if (v == hs[u]) continue;
		dfs2(v, v);
	}
}

int inline lca(int u, int v) {
	for (; top[u] != top[v]; v = pr[top[v]]) if (dep[top[u]] > dep[top[v]]) swap(u, v);
	if (dep[u] > dep[v]) swap(u, v);
	return u;
}

set<int> cur;
num ans, answer[nsz + 5];

void inline del(int id) {
	int u = at[id], p = -1;
	set<int>::iterator it = cur.lower_bound(rk[u]);
	ans -= pre[u];
	if (it != cur.begin()) {
		--it;
		int v = fm[*it];
		p = lca(u, v);
		++it;
	}
	if (it != cur.end() && (++it != cur.end())) {
		int v = fm[*it], cp = lca(u, v);
		if (p == -1 || dep[cp] > dep[p]) p = cp;
	}
	cur.erase(rk[u]);
	if (p != -1) ans += pre[p];
}

void inline ins(int id) {
	int u = at[id], p = -1;
	set<int>::iterator it = cur.lower_bound(rk[u]);
	ans += pre[u];
	if (it != cur.begin()) {
		--it;
		int v = fm[*it];
		p = lca(u, v);
		++it;
	}
	if (it != cur.end()) {
		int v = fm[*it], cp = lca(u, v);
		if (p == -1 || dep[cp] > dep[p]) p = cp;
	}
	cur.insert(rk[u]);
	if (p != -1) ans -= pre[p];
}

void inline mo_solve() {
	cur.clear(), ans = 0;
	sort(qy + 1, qy + q + 1);
	for (int i = 1; i <= q;) {
		int k = qy[i].l / bsz, cl = qy[i].l, cr = qy[i].l - 1;
		cur.clear(), ans = 0;
		for (; i <= q && qy[i].l / bsz == k; ++i) {
			int l = qy[i].l, r = qy[i].r;
			for (; cl > l; ins(--cl));
			for (; cr < r; ins(++cr));
			for (; cl < l; del(cl++));
			for (; cr > r; del(cr--));
			answer[qy[i].id] = ans;
		}
	}
}

void inline clear() {
	g.clear();
	cont (u, sam.sz) {
		memset(sam.g[u], 0, sizeof(sam.g[u]));
		sam.sf[u] = 0;
		hs[u] = top[u] = 0;
	}
	sam.sz = 0;
	sam.rt = sam.lst = ++sam.sz;
}

int main() {
	ios::sync_with_stdio(0);
	cin >> ts;
	cont (cs, ts) {
		cin >> s;
		n = int(s.size());
		s += '#';
		reverse(all(s));
		sam.ins(s);
		
		cont (u, sam.sz) sam.len[u] -= sam.sf[u], pre[u] = sam.len[u];
		circ (u, 2, sam.sz) {
			w[u] = sam.len[u] - sam.len[sam.pr[u]];
			g.link(sam.pr[u], u);
		}
		
		dfs1(), dfs2();
		
		cin >> q;
		cont (i, q) {
			int l, r;
			cin >> l >> r;
			qy[i] = query(l, r, i);
		}
		
		mo_solve();
		cont (i, q) cout << answer[i] << ln;
		clear();
	}
	return 0;
}