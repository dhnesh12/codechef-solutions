#include <bits/stdc++.h>
using namespace std;

const long long NIL = 1e18;

namespace {
	double elapsed() {
		static clock_t curr;
		clock_t prev = curr;
		curr = clock();
		return (double)(curr - prev) / CLOCKS_PER_SEC;
	}
}

namespace {
	struct P {
		long long x, y;
		P() : x(0), y(0) {}
		P(long long x, long long y) : x(x), y(y) {}

		bool operator==(const P &r) const {
			return x == r.x && y == r.y;
		}

		bool operator!=(const P &r) const {
			return !(*this == r);
		}

		bool operator<(const P &r) const {
			if (x != r.x) return x < r.x;
			return y < r.y;
		}

		P operator-(const P &r) const {
			return P(x - r.x, y - r.y);
		}
	};

	const P NIL_P(NIL, NIL);

	P subtract(const P &a, const P &b) {
		return P(a.x - b.x, a.y - b.y);
	}

	long long dot(const P &a, const P &b) {
		return a.x * b.x + a.y * b.y;
	}

	long long cross(const P &a, const P &b) {
		return a.x * b.y - a.y * b.x;
	}

	int ccw(P a, P b, P c) {
		b = b - a;
		c = c - a;
		if (cross(b, c) > 0) return 1;
		if (cross(b, c) < 0) return -1;
		return 0;
	}
}

namespace {
	enum { RED, BLACK };

	struct node {
		node *lch, *rch;
		int color, height;
		int size, id;

		long long area = 0;

		P lp, rp;
		P next_lp, prev_rp;
	};

	const int N = 2e5;
	node nodes[N * 2];
	int free_stack[N * 2];
	int sp = 0;

	void init_tree(int n) {
		sp = 0;
		for (int i = n * 2 - 1; i >= 0; i--) {
			free_stack[i] = i;
		}
		sp = n * 2;
	}

	long long area(node *x) {
		if (x == nullptr) return 0;
		return x->area;
	}

	int size(node *x) {
		if (x == nullptr) return 0;
		return x->size;
	}

	bool is_leaf(node *x) {
		return x->lch == nullptr;
	}

	node *update(node *x) {
		if (x == nullptr) return x;
		if (is_leaf(x)) return x;

		x->size = x->lch->size + x->rch->size;
		x->height = max(x->lch->height + (x->lch->color == BLACK), x->rch->height + (x->rch->color == BLACK));

		x->lp = x->lch->lp;
		x->rp = x->rch->rp;

		x->area = x->lch->area + x->rch->area + cross(x->lch->rp, x->rch->lp);

		if (is_leaf(x->lch)) {
			x->next_lp = x->rch->lp;
		} else {
			x->next_lp = x->lch->next_lp;
		}
		if (is_leaf(x->rch)) {
			x->prev_rp = x->lch->rp;
		} else {
			x->prev_rp = x->rch->prev_rp;
		}

		return x;
	}

	node *create() {
		int id = free_stack[--sp];
		node *x = &nodes[id];
		x->id = id;
		return x;
	}

	node *create(node *lch, node *rch) {
		node *x = create();
		x->color = RED;
		x->lch = lch;
		x->rch = rch;
		return update(x);
	}

	node *create(P p) {
		node *x = create();
		x->color = BLACK;
		x->lch = x->rch = nullptr;
		x->lp = x->rp = x->prev_rp = x->next_lp = p;
		x->height = 0;
		x->size = 1;
		return x;
	}

	node *rotL(node *x) {
		node *y = x->rch;
		x->rch = y->lch;
		y->lch = update(x);
		return update(y);
	}

	node *rotR(node *x) {
		node *y = x->lch;
		x->lch = y->rch;
		y->rch = update(x);
		return update(y);
	}

	node *merge_sub(node *u, node *v) {
		if (u->height == v->height) {
			return create(u, v);
		} else if (u->height < v->height) {
			v->lch = merge_sub(u, v->lch);
			if (v->lch->color == RED && v->lch->lch->color == RED && v->color == BLACK) {
				if (v->rch->color == BLACK) {
					v->color = RED;
					v->rch->color = BLACK;
					return rotR(v);
				} else {
					v->color = RED;
					v->lch->color = BLACK;
					v->rch->color = BLACK;
				}
			}
			return update(v);
		} else {
			u->rch = merge_sub(u->rch, v);
			if (u->rch->color == RED && u->rch->rch->color == RED && u->color == BLACK) {
				if (u->lch->color == BLACK) {
					u->color = RED;
					u->rch->color = BLACK;
					return rotL(u);
				} else {
					u->color = RED;
					u->lch->color = BLACK;
					u->rch->color = BLACK;
				}
			}
			return update(u);
		}
	}

	node *merge(node *u, node *v) {
		if (u == nullptr) return v;
		if (v == nullptr) return u;
		node *w = merge_sub(u, v);
		if (w->color == RED) w->color = BLACK;
		return w;
	}

	pair<node *, node *> split(node *v, int k) {
		if (k == 0) return make_pair(nullptr, v);
		if (k == v->size) return make_pair(v, nullptr);

		free_stack[sp++] = v->id;
		if (k < v->lch->size) {
			auto p = split(v->lch, k);
			return make_pair(p.first, merge(p.second, v->rch));
		} else if (k > v->lch->size) {
			auto p = split(v->rch, k - v->lch->size);
			return make_pair(merge(v->lch, p.first), p.second);
		} else {
			return make_pair(v->lch, v->rch);
		}
	}

	int index_of(node *x, P p) {
		if (is_leaf(x)) return 0;
		if (p < x->rch->lp) {
			return index_of(x->lch, p);
		} else {
			return x->lch->size + index_of(x->rch, p);
		}
	}

	bool contains(P p, P t, P d1, P d2, int sign) {
		p = subtract(p, t);
		return cross(d1, p) * sign > 0 && cross(p, d2) * sign >= 0;
	}

	bool check_L(const P &p, node *x) {
		return contains(p, x->lp, subtract(x->rp, x->lp), subtract(x->next_lp, x->lp), 1) || contains(p, x->rp, subtract(x->rp, x->prev_rp), subtract(x->rp, x->lp), 1);
	}

	bool check_R(const P &p, node *x) {
		return contains(p, x->lp, subtract(x->rp, x->lp), subtract(x->next_lp, x->lp), -1) || contains(p, x->rp, subtract(x->rp, x->prev_rp), subtract(x->rp, x->lp), -1);
	}

	pair<int, P> tangentL(P p, node *x) {
		int pos = 0;
		while (!is_leaf(x)) {
			node *l = x->lch;
			node *r = x->rch;

			bool left = false;
			if (check_L(p, l)) {
				left = true;
			} else if (check_L(p, r)) {
				left = false;
			} else {
				if (is_leaf(l)) {
					if (contains(p, l->rp, subtract(r->lp, l->rp), subtract(l->rp, r->rp), 1) ||
						contains(p, l->lp, subtract(r->lp, l->lp), subtract(l->lp, r->rp), 1)) left = true;
				} else {
					if (contains(p, l->rp, subtract(r->lp, l->rp), subtract(l->rp, l->prev_rp), 1) ||
						contains(p, l->lp, subtract(l->next_lp, l->lp), subtract(l->lp, r->rp), 1)) left = true;
				}
			}

			if (left) {
				x = x->lch;
			} else {
				pos += x->lch->size;
				x = x->rch;
			}
		}
		return make_pair(pos, x->lp);
	}

	pair<int, P> tangentR(P p, node *x) {
		int pos = 0;
		while (!is_leaf(x)) {
			node *l = x->lch;
			node *r = x->rch;

			bool left = false;
			if (check_R(p, l)) {
				left = true;
			} else if (check_R(p, r)) {
				left = false;
			} else {
				if (is_leaf(l)) {
					if (contains(p, l->rp, subtract(l->rp, r->lp), subtract(r->rp, l->rp), 1) ||
						contains(p, l->lp, subtract(l->lp, r->lp), subtract(r->rp, l->lp), 1)) left = true;
				} else {
					if (contains(p, l->rp, subtract(r->lp, l->rp), subtract(l->rp, l->prev_rp), -1) ||
						contains(p, l->lp, subtract(l->next_lp, l->lp), subtract(l->lp, r->rp), -1)) left = true;
				}
			}

			if (left) {
				x = x->lch;
			} else {
				pos += x->lch->size;
				x = x->rch;
			}
		}
		return make_pair(pos, x->lp);
	}

	pair<pair<int, P>, pair<int, P>> common_tangent(node *l, node *r) {
		pair<pair<int, P>, pair<int, P>> p;
		p.first = make_pair(-1, l->rp);
		p.second = make_pair(-1, r->lp);

		while (true) {
			auto prev = p;
			p.second = tangentR(p.first.second, r);
			p.first = tangentL(p.second.second, l);
			if (prev.first.second == p.first.second && prev.second.second == p.second.second) return p;
		}
	}
}

struct SegmentTree {
	int N;

	vector<P> pts;
	vector<node *> hull;
	vector<node *> leaf;
	vector<int> pos;
	vector<pair<P, P>> tangent;

	SegmentTree(vector<P> pts) {
		int n = pts.size();
		N = 1;
		while (N < n) N *= 2;
		hull.resize(N * 2, nullptr);
		pos.resize(N * 2, -1);
		tangent.resize(N * 2, make_pair(NIL_P, NIL_P));

		leaf.resize(n);
		for (int i = 0; i < n; i++) {
			leaf[i] = create(pts[i]);
		}
	}

	enum { DELETE = 0, ADD = 1 };
	void update(int a, int type, int k = 0, int l = 0, int r = -1) {
		if (r == -1) r = N;
		if (r - l == 1) {
			if (type == DELETE) {
				hull[k] = nullptr;
			} else {
				hull[k] = leaf[l];
			}
			return;
		}

		if (hull[k] == nullptr) {
			if (a < (l + r) / 2) {
				update(a, type, k * 2 + 1, l, (l + r) / 2);
			} else {
				update(a, type, k * 2 + 2, (l + r) / 2, r);
			}
		} else {
			node *L, *R;
			tie(L, R) = split(hull[k], pos[k]);

			if (a < (l + r) / 2) {
				hull[k * 2 + 1] = merge(L, hull[k * 2 + 1]);
				update(a, type, k * 2 + 1, l, (l + r) / 2);
				if (tangent[k].first.x != NIL) {
					if (leaf[a]->lp != tangent[k].first) {
						if (ccw(tangent[k].second, tangent[k].first, leaf[a]->lp) >= 0) {
							pos[k] = index_of(hull[k * 2 + 1], tangent[k].first) + 1;
							auto pp = split(hull[k * 2 + 1], pos[k]);
							hull[k * 2 + 1] = pp.second;
							pos[k] = size(pp.first);
							hull[k] = merge(pp.first, R);
							return;
						}
					}
				}
				hull[k * 2 + 2] = merge(hull[k * 2 + 2], R);
			} else {
				hull[k * 2 + 2] = merge(hull[k * 2 + 2], R);
				update(a, type, k * 2 + 2, (l + r) / 2, r);
				if (tangent[k].first.x != NIL) {
					if (leaf[a]->lp != tangent[k].second) {
						if (ccw(tangent[k].first, tangent[k].second, leaf[a]->lp) <= 0) {
							int id = index_of(hull[k * 2 + 2], tangent[k].second);
							auto pp = split(hull[k * 2 + 2], id);
							hull[k * 2 + 2] = pp.first;
							pos[k] = size(L);
							hull[k] = merge(L, pp.second);
							return;
						}
					}
				}
				hull[k * 2 + 1] = merge(L, hull[k * 2 + 1]);
			}
		}

		if (hull[k * 2 + 1] == nullptr) {
			pos[k] = size(hull[k * 2 + 1]);
			hull[k] = hull[k * 2 + 2];
			hull[k * 2 + 2] = nullptr;
			tangent[k] = make_pair(NIL_P, NIL_P);
		} else if (hull[k * 2 + 2] == nullptr) {
			pos[k] = size(hull[k * 2 + 1]);
			hull[k] = hull[k * 2 + 1];
			hull[k * 2 + 1] = nullptr;
			tangent[k] = make_pair(NIL_P, NIL_P);
		} else {
			auto p = common_tangent(hull[k * 2 + 1], hull[k * 2 + 2]);
			tangent[k] = make_pair(p.first.second, p.second.second);
			auto ll = split(hull[k * 2 + 1], p.first.first + 1);
			auto rr = split(hull[k * 2 + 2], p.second.first);
			hull[k * 2 + 1] = ll.second;
			hull[k * 2 + 2] = rr.first;
			pos[k] = size(ll.first);
			hull[k] = merge(ll.first, rr.second);
		}
	}
};

void solve() {
	int n;
	cin >> n;

	vector<char> op(n);
	vector<int> qs(n);

	map<pair<int, int>, stack<int>> mp;

	vector<pair<P, int>> psi;

	for (int i = 0; i < n; i++) {
		int x, y;
		scanf(" %c %d %d", &op[i], &x, &y);
		pair<int, int> p(x, y);

		if (op[i] == '+') {
			qs[i] = psi.size();
			mp[p].push(psi.size());
			psi.emplace_back(P(x, y), psi.size());
		} else {
			int id = mp[p].top(); mp[p].pop();
			qs[i] = id;
		}
	}
	sort(psi.begin(), psi.end());

	vector<int> mm(psi.size());
	vector<P> ps(psi.size());
	for (int i = 0; i < ps.size(); i++) {
		mm[psi[i].second] = i;
		ps[i] = psi[i].first;
	}
	for (int i = 0; i < n; i++) {
		qs[i] = mm[qs[i]];
	}

	int m = ps.size();
	init_tree(m * 2);

	vector<P> ps2(ps);
	for (int i = 0; i < ps2.size(); i++) {
		ps2[i].x *= -1;
		ps2[i].y *= -1;
	}
	sort(ps2.begin(), ps2.end());

	SegmentTree tr1(ps);
	SegmentTree tr2(ps2);

	for (int i = 0; i < n; i++) {
		if (op[i] == '+') {
			tr1.update(qs[i], 1);
			tr2.update(m - 1 - qs[i], 1);
		} else {
			tr1.update(qs[i], 0);
			tr2.update(m - 1 - qs[i], 0);
		}

		long long A = area(tr1.hull[0]) + area(tr2.hull[0]);

		A = abs(A);
		if (A % 2 == 0) {
			printf("%lld.0\n", A / 2);
		} else {
			printf("%lld.5\n", A / 2);
		}
	}
}

int main() {
	int T;
	cin >> T;
	while (T--) solve();
}