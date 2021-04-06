#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define endl "\n"
#define ll long long
#define sz(s) (int)(s.size())
#define INF 0x3f3f3f3f3f3f3f3fLL
#define all(v) v.begin(),v.end()
#define watch(x) cout<<(#x)<<" = "<<x<<endl
const int dr[] { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dc[] { 0, 1, 1, 1, 0, -1, -1, -1 };
#if __cplusplus >= 201402L
template<typename T>
vector<T> create(size_t n) {
	return vector<T>(n);
}
template<typename T, typename ... Args>
auto create(size_t n, Args ... args) {
	return vector<decltype(create<T>(args...))>(n, create<T>(args...));
}
#endif
void run() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#else
	//freopen("groups.in", "r", stdin);
#endif
}

pair<int, int> Max(pair<int, int> a, pair<int, int> b) {
	if (a.first == b.first)
		return {a.first,a.second + b.second};
	return max(a, b);
}
struct segment_tree {
#define LEFT (idx<<1)
#define RIGHT (idx<<1|1)
#define MID ((start+end)>>1)
	int n;
	vector<pair<int, int>> tree;
	segment_tree(int n) :
			n(n), tree(n << 2, { -INF, 0 }) {
	}
	void update(int idx, int start, int end, int pos, int val) {
		if (start == end) {
			tree[idx] = { val, 1 };
			return;
		}
		if (pos <= MID)
			update(LEFT, start, MID, pos, val);
		else
			update(RIGHT, MID + 1, end, pos, val);
		tree[idx] = Max(tree[LEFT], tree[RIGHT]);
	}
	pair<int, int> query(int idx, int start, int end, int l, int r) {
		if (r < start || end < l)
			return {-INF,0};
		if (l <= start && end <= r)
			return tree[idx];
		return Max(query(LEFT, start, MID, l, r),
				query(RIGHT, MID + 1, end, l, r));
	}
	void update(int pos, int val) {
		update(1, 1, n, pos, val);
	}
	pair<int, int> query(int l, int r) {
		return query(1, 1, n, l, r);
	}
};

class heavy_light_decomposition {
	int n, is_value_in_edge;
	vector<int> parent, depth, heavy, root, pos_in_array, pos_to_node, size;
	segment_tree seg;
	struct TREE {
		int cnt_edges = 1;
		vector<vector<int>> adj;
		//need for value in edges
		vector<vector<int>> edge_idx;
		//edge_to need for undirected tree //end of edge in directed tree
		vector<int> edge_to, edge_cost;
		TREE(int n) :
				adj(n + 1), edge_idx(n + 1), edge_to(n + 1), edge_cost(n + 1) {
		}
		void add_edge(int u, int v, int c) {
			adj[u].push_back(v);
			adj[v].push_back(u);
			edge_idx[u].push_back(cnt_edges);
			edge_idx[v].push_back(cnt_edges);
			edge_cost[cnt_edges] = c;
			cnt_edges++;
		}
	} tree;
	int dfs_hld(int node) {
		int size = 1, max_sub_tree = 0;
		for (int i = 0; i < (int) tree.adj[node].size(); i++) {
			int ch = tree.adj[node][i], edge_idx = tree.edge_idx[node][i];
			if (ch != parent[node]) {
				tree.edge_to[edge_idx] = ch;
				parent[ch] = node;
				depth[ch] = depth[node] + 1;
				int child_size = dfs_hld(ch);
				if (child_size > max_sub_tree)
					heavy[node] = ch, max_sub_tree = child_size;
				size += child_size;
			}
		}
		return size;
	}
	vector<tuple<int, int, bool>> get_path(int u, int v) { //l,r,must_reverse?
		vector<pair<int, int>> tmp[2];
		bool idx = 1;
		while (root[u] != root[v]) {
			if (depth[root[u]] > depth[root[v]]) {
				swap(u, v);
				idx = !idx;
			}
			//if value in edges ,you need value of root[v] also (connecter edge)
			tmp[idx].push_back( { pos_in_array[root[v]], pos_in_array[v] });
			v = parent[root[v]];
		}
		if (depth[u] > depth[v]) {
			swap(u, v);
			idx = !idx;
		}
		if (!is_value_in_edge || u != v)
			tmp[idx].push_back( { pos_in_array[u] + is_value_in_edge,
					pos_in_array[v] });
		reverse(all(tmp[1]));
		vector<tuple<int, int, bool>> rt;
		for (int i = 0; i < 2; i++)
			for (auto &it : tmp[i])
				rt.emplace_back(it.first, it.second, i == 0);
		return rt; //u is LCA
	}
public:
	heavy_light_decomposition(int n, bool is_value_in_edge) :
			n(n), is_value_in_edge(is_value_in_edge), seg(n + 1), tree(n + 1) {
		heavy = vector<int>(n + 1, -1);
		parent = depth = root = pos_in_array = pos_to_node = size = vector<int>(
				n + 1);
	}
	void add_edge(int u, int v, int c = 0) {
		tree.add_edge(u, v, c);
	}
	void build_chains(int src = 1) {
		parent[src] = -1;
		dfs_hld(src);
		for (int chain_root = 1, pos = 1; chain_root <= n; chain_root++) {
			if (parent[chain_root] == -1
					|| heavy[parent[chain_root]] != chain_root)
				for (int j = chain_root; j != -1; j = heavy[j]) {
					root[j] = chain_root;
					pos_in_array[j] = pos++;
					pos_to_node[pos_in_array[j]] = j;
				}
		}
	}
	void update_node(int node, int value) {
		seg.update(pos_in_array[node], value);
	}
	pair<int, int> query_in_path(int u) {
		pair<int, int> p = { -INF, 0 };
		while (u >= 1) {
			p = Max(p, seg.query(pos_in_array[root[u]], pos_in_array[u]));
			u = parent[root[u]];
		}
		return p;
	}

};

int main() {
	run();
	int n, q;
	cin >> n >> q;
	heavy_light_decomposition hld(n, false);
	vector<int> a(n + 1), p(n + 1), depth(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 2; i <= n; i++) {
		cin >> p[i];
		hld.add_edge(p[i], i);
	}
	hld.build_chains();
	for (int i = 2; i <= n; i++)
		depth[i] = 1 + depth[p[i]];
	for (int i = 1; i <= n; i++)
		hld.update_node(i, a[i] - depth[i]);
	while (q--) {
		int type, x;
		cin >> type >> x;
		if (type == 0) {
			int val;
			cin >> val;
			hld.update_node(x, val - depth[x]);
		} else {
			pair<int, int> p = hld.query_in_path(x);
			cout << p.first + depth[x] << ' ' << p.second << endl;
		}
	}
}
