
#include <bits/extc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll INF = numeric_limits<ll>::max() / 4;
typedef vector<ll> VL;

struct MCMF {
	int N;
	vector<vi> ed, red;
	vector<VL> cap, flow, cost;
	vi seen;
	VL dist, pi;
	vector<pii> par;

	MCMF(int N) :
		N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(cap),
		seen(N), dist(N), pi(N), par(N) {}

	void addEdge(int from, int to, ll cap, ll cost) {
		this->cap[from][to] = cap;
		this->cost[from][to] = cost;
		ed[from].push_back(to);
		red[to].push_back(from);
	}

	void path(int s) {
		fill(all(seen), 0);
		fill(all(dist), INF);
		dist[s] = 0; ll di;

		__gnu_pbds::priority_queue<pair<ll, int>> q;
		vector<decltype(q)::point_iterator> its(N);
		q.push({0, s});

		auto relax = [&](int i, ll cap, ll cost, int dir) {
			ll val = di - pi[i] + cost;
			if (cap && val < dist[i]) {
				dist[i] = val;
				par[i] = {s, dir};
				if (its[i] == q.end()) its[i] = q.push({-dist[i], i});
				else q.modify(its[i], {-dist[i], i});
			}
		};

		while (!q.empty()) {
			s = q.top().second; q.pop();
			seen[s] = 1; di = dist[s] + pi[s];
			for (int i : ed[s]) if (!seen[i])
				relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
			for (int i : red[s]) if (!seen[i])
				relax(i, flow[i][s], -cost[i][s], 0);
		}
		rep(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
	}

	pair<ll, ll> maxflow(int s, int t) {
		ll totflow = 0, totcost = 0;
		while (path(s), seen[t]) {
			ll fl = INF;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
			totflow += fl;
			for (int p,r,x = t; tie(p,r) = par[x], x != s; x = p)
				if (r) flow[p][x] += fl;
				else flow[x][p] -= fl;
		}
		rep(i,0,N) rep(j,0,N) totcost += cost[i][j] * flow[i][j];
		return {totflow, totcost};
	}
};

struct RollbackUF {
	vi e; vector<pii> st;
	RollbackUF(int n) : e(n, -1) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;)
			e[st[i].first] = st[i].second;
		st.resize(t);
	}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		st.push_back({a, e[a]});
		st.push_back({b, e[b]});
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

struct Edge { int a, b; ll w; };
struct Node { /// lazy skew heap node
	Edge key;
	Node *l, *r;
	ll delta;
	void prop() {
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top() { prop(); return key; }
};
Node *merge(Node *a, Node *b) {
	if (!a || !b) return a ?: b;
	a->prop(), b->prop();
	if (a->key.w > b->key.w) swap(a, b);
	swap(a->l, (a->r = merge(b, a->r)));
	return a;
}
void pop(Node*& a) { a->prop(); a = merge(a->l, a->r); }

pair<ll, vi> dmst(int n, int r, vector<Edge>& g) {
	RollbackUF uf(n);
	vector<Node*> heap(n);
	for (Edge e : g) heap[e.b] = merge(heap[e.b], new Node{e});
	ll res = 0;
	vi seen(n, -1), path(n), par(n);
	seen[r] = r;
	vector<Edge> Q(n), in(n, {-1,-1}), comp;
	deque<tuple<int, int, vector<Edge>>> cycs;
	rep(s,0,n) {
		int u = s, qi = 0, w;
		while (seen[u] < 0) {
			if (!heap[u]) return {-1,{}};
			Edge e = heap[u]->top();
			heap[u]->delta -= e.w, pop(heap[u]);
			Q[qi] = e, path[qi++] = u, seen[u] = s;
			res += e.w, u = uf.find(e.a);
			if (seen[u] == s) { /// found cycle, contract
				Node* cyc = 0;
				int end = qi, time = uf.time();
				do cyc = merge(cyc, heap[w = path[--qi]]);
				while (uf.join(u, w));
				u = uf.find(u), heap[u] = cyc, seen[u] = -1;
				cycs.push_front({u, time, {&Q[qi], &Q[end]}});
			}
		}
		rep(i,0,qi) in[uf.find(Q[i].b)] = Q[i];
	}

	for (auto& [u,t,comp] : cycs) { // restore sol (optional)
		uf.rollback(t);
		Edge inEdge = in[u];
		for (auto& e : comp) in[uf.find(e.b)] = e;
		in[uf.find(inEdge.b)] = inEdge;
	}
	rep(i,0,n) par[i] = in[i].a;
	return {res, par};
}

const int MAXN = 50;
string dir = "ULDR";
string dirrev = "DRUL"; 
vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, -1, 0, 1};

int n, p[4], pr[4], cost[2], X[MAXN][MAXN], Y[MAXN][MAXN], eq[MAXN][MAXN], vis[MAXN][MAXN];
char ans[MAXN][MAXN];

int encode(int x, int y) {
	return x*n + y;
}

pair<int, int> decode(int g) {
	return {g/n, g%n};
}

bool valid(int x, int y) {
	if (x < 0) return 0;
	if (x >= n) return 0;
	if (y < 0) return 0;
	if (y >= n) return 0;
	return 1;
}

void prim(int sx, int sy) {
	queue<pair<int, int>> pq;
	pq.push({sx, sy});
	vis[sx][sy] = 1;

	vector<Edge> e;
	int cnt = 0;

	vector<int> xt;

	while (pq.size()) {
		auto [x, y] = pq.front(); pq.pop(); cnt++;
		xt.push_back(encode(x, y));

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (valid(nx, ny) && X[nx][ny] == X[x][y] && Y[nx][ny] == Y[x][y]) {
				e.push_back({encode(x, y), encode(nx, ny), (ll)pr[i]});
				if (!vis[nx][ny]) {
					vis[nx][ny] = 1;
					pq.push({nx, ny});
				}
			}
		}
	}

	sort(xt.begin(), xt.end());
	vector<Edge> actual_edges;
	for (auto [u, v, w]: e) {
		actual_edges.push_back({lower_bound(xt.begin(), xt.end(), u) - xt.begin(), lower_bound(xt.begin(), xt.end(), v) - xt.begin(), (ll)w});
	}

	int rt = lower_bound(xt.begin(), xt.end(), encode(sx, sy)) - xt.begin();
	auto [w, par] = dmst(cnt, rt, actual_edges);

	for (int i = 0; i < cnt; i++) {
		if (i == rt) continue;

		int u = xt[i], v = xt[par[i]];
		auto [x, y] = decode(u);
		auto [nx, ny] = decode(v);

		for (int f = 0; f < 4; f++) {
			if (x+dx[f] == nx && y+dy[f] == ny) {
				ans[x][y] = dir[f];
			}
		}	
	}
}

signed main() {
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n;
	for (int i = 0; i < 4; i++) {
		cin >> p[i];
		cost[i % 2] += p[i];
		pr[(i+2) % 4] = p[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> X[i][j] >> Y[i][j];
			X[i][j]--; Y[i][j]--;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (X[i][j] == i && Y[i][j] == j && !vis[i][j]) {
				eq[i][j] = 1;
				prim(i, j);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!vis[i][j]) {
				cout << "-1\n"; exit(0);
			}
		}
	}

	MCMF mc(n*n + 2);
	int eqcnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!eq[i][j]) continue;
			eqcnt++;

			if ((i+j) % 2) {
				// to sink
				mc.addEdge(encode(i, j), n*n + 1, 1, 0);
			} else {
				// source to
				mc.addEdge(n*n, encode(i, j), 1, 0);

				// cost[0]: up-down
				// cost[1]: left-right
				for (int f = 0; f < 4; f++) {
					int nx = i+dx[f], ny = j+dy[f];
					if (valid(nx, ny) && eq[nx][ny]) {
						mc.addEdge(encode(i, j), encode(nx, ny), 1, cost[f % 2]);
					}
				}
			}
		}
	}

	if (mc.maxflow(n*n, n*n + 1).first*2 != eqcnt) {
		cout << "-1\n"; exit(0);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!eq[i][j]) continue;
			if ((i+j) % 2) continue;
				
			// cost[0]: up-down
			// cost[1]: left-right
			for (int f = 0; f < 4; f++) {
				int nx = i+dx[f], ny = j+dy[f];
				if (valid(nx, ny) && eq[nx][ny]) {
					if (mc.flow[encode(i, j)][encode(nx, ny)] > 0) {
						ans[i][j] = dir[f];
						ans[nx][ny] = dirrev[f];
					}
				}
			}		
		}
	}

	int sumcost = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int f = 0; f < 4; f++) {
				if (ans[i][j] == dir[f]) {
					sumcost += p[f];
				}
			}	
		}
	}

	cout << sumcost << '\n';
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << ans[i][j];	
		}
		cout << '\n';
	}
	
	return 0;
}
