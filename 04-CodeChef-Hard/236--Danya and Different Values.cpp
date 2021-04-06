#include<bits/stdc++.h>
using namespace std;

#define boost ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);

#define li long long int
#define mod 1000000007

int XX, DD;

const int maxn = 600000, maxk = 200005;
int root[maxn], L[19 * maxn], R[19 * maxn], sum[19 * maxn];
int rt = 1, sz = 1;
int lpos[maxk];

int nn[100006];
set<int> pp;
// function to determine level of each node starting
// from x using BFS
void printLevels(vector<int> graph[], int V, int x) {
	// array to store level of each node
	int level[V];
	memset(level, -1, sizeof(level));
	bool marked[V];
	memset(marked, 0, sizeof(marked));

	// create a queue
	queue<int> que;

	// enqueue element x
	que.push(x);

	// initialize level of source node to 0
	level[x] = 0;

	// marked it as visited
	marked[x] = true;

	// do until queue is empty
	while (!que.empty()) {

		// get the first element of queue
		x = que.front();

		// dequeue element
		que.pop();

		// traverse neighbors of node x
		for (int i = 0; i < graph[x].size(); i++) {
			// b is neighbor of node x
			int b = graph[x][i];

			// if b is not marked already
			if (!marked[b]) {

				// enqueue b in queue
				que.push(b);

				// level of b is level of x + 1
				level[b] = level[x] + 1;

				// mark b
				marked[b] = true;
			}
		}
	}

	// display all nodes and their levels
//	cout << "Nodes" << " " << "Level" << endl;
	for (int i = 0; i < V; i++) {
		if (level[i] != -1 && level[i] <= DD)
			pp.insert(nn[i]);
	}
}

int copy(int v, int &u) {

	L[sz] = L[v];
	R[sz] = R[v];
	sum[sz] = sum[v];
	return u = sz++;
}

void make_root() {

	copy(root[rt - 1], root[rt]);
	rt++;
}

void add(int pos, int x, int v = root[rt - 1], int l = 0,
		int r = maxn) {
	sum[v] += x;
	if (r - l == 1)
		return;
	int m = (l + r) / 2;
	if (pos < m)
		add(pos, x, copy(L[v], L[v]), l, m);
	else
		add(pos, x, copy(R[v], R[v]), m, r);
}

int get(int a, int b, int v, int l = 0, int r = maxn) {
	if (a <= l && r <= b)
		return sum[v];
	if (r <= a || b <= l)
		return 0;
	int m = (l + r) / 2;
	return get(a, b, L[v], l, m) + get(a, b, R[v], m, r);
}

int main() {
	boost
	int t;
	cin >> t;
	while (t--) {
		rt = 1, sz = 1;
		memset(L, 0, sizeof(L));
		memset(R, 0, sizeof(R));
		memset(sum, 0, sizeof(sum));
		memset(root, 0, sizeof(root));
		memset(lpos, 0, sizeof(lpos));

		int n;
		cin >> n;
		if (n <= 1000) {
			vector<int> graph[n];
			int x;
			for (int i = 1; i < n; ++i) {
				cin >> x;
				x--;
				graph[x].push_back(i);
			}
			for (int i = 0; i < n; ++i) {
				cin >> nn[i];

			}

			int q;
			cin >> q;
			int xx, dd, kk = 0;

			while (q--) {
				pp.clear();
				cin >> xx >> dd;

				XX = xx ^ kk;
				XX--;
				//			if (XX < 0) {
				//				while (1)
				//					;
				//			}
				DD = dd ^ kk;

				printLevels(graph, n, XX);
				kk = pp.size();
				cout << kk << "\n";
			}

		} else {
			int y;
			for (int i = 1; i < n; ++i) {
				cin >> y;
			}

			for (int i = 1; i <= n; i++) {
				int tt;
				cin >> tt;

				make_root();
				add(lpos[tt], -1);
				lpos[tt] = i;
				add(lpos[tt], 1);
			}

			int q;
			cin >> q;

			int xx, dd, kk = 0;
			int l, r;
			while (q--) {

				cin >> xx >> dd;

				XX = xx ^ kk;

				DD = dd ^ kk;
				l = XX;
				r = min(XX + DD, n);

				kk = get(l, r + 1, root[r]);
				cout << kk << "\n";

			}

		}
	}

	return 0;
}
