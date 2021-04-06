#include <bits/stdc++.h>
using namespace std;

struct BIT {
	vector<long long> arr;
	void init(long long s = 1e6) {
		arr.assign(s+1 , 0);
	}
	long long sum(long long pos) {
		long long ans = 0;
		while(pos > 0) {
			ans += arr[pos];
			pos = pos - (pos & (-pos));
		}
		return ans;
	}
	void update(long long pos, long long val) {
		while((pos > 0) && (pos < arr.size())) {
			arr[pos] += val;
			pos = pos + (pos & (-pos));
		}
	}
	long long rQuery(long long l, long long r) {
		return sum(r) - sum(l-1);
	}
};

int N, K;
vector<vector<int>> graph;
vector<vector<pair<long long, long long>>> updates; // in pair it stores {value to be added, number of times it should be added}.
vector<int> parent, depth;
vector<long long> ans;
BIT sum_depths, count_depths;

void computeDetails(int node, int par, int _depth) { // function is used to compute parent and depth of each node when we root the tree at node 1.
	parent[node] = par;
	depth[node] = _depth;
	for(auto to : graph[node]) {
		if(to == par) continue;
		computeDetails(to, node, _depth+1);
	}
}

void computeAnswer(int node, int par) {
	for(auto i : updates[node]) { // adding the effect of updates for the node, as it will effect the nodes in its subtree.
		long long value = depth[node] + i.first;
		long long count = i.second; 
		sum_depths.update(value, count*value); // as this value will impact only those nodes which have depths < value.
		count_depths.update(value, count);
	}
	// computing the answer for the current node.
	// security value of node = sum_of_updates(with value greater than equal to its depth) - (depth[node] * count_of_updates(with value greater than equal to its depth));
	long long sum_of_updates = sum_depths.rQuery(depth[node], 2*N+5); // as all the lower values do note 
	long long count_of_updates = count_depths.rQuery(depth[node], 2*N+5);
	ans[node] = sum_of_updates - (depth[node] * count_of_updates);

	for(auto to : graph[node]) { // computing answer for nodes in its subtree.
		if(to == par) continue;
		computeAnswer(to, node);
	}

	for(auto i : updates[node]) { // removing the effect of updates for the node, as answer for all nodes in it's subtree is computed.
		long long value = depth[node] + i.first;
		long long count = -i.second; 
		sum_depths.update(value, count*value); // as this value will impact only those nodes which have depths < value.
		count_depths.update(value, count);
	}
}

void solveTestCase() {
	cin >> N >> K;

	updates.clear();
	updates.resize(N+1);
	ans.assign(N+1, 0);
	graph.clear();
	graph.resize(N+1);
	parent.resize(N+1);
	depth.resize(N+1);

	// In the below BIT's the index represent value of update.
	sum_depths.init(2*N+5); // This BIT maintains the sum of security values at each depth for each vertex(it can be maintained for each vertex because we modify it as we go up and down the dfs).
	count_depths.init(2*N+5); // This BIT maintains the count of updates at each depth and is used to count the number of times a vertex is updated(used to compute the answer). It can be maintained for each vertex because we modify it as we go up and down the dfs.

	for(int i = 1; i <= N-1; i ++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	computeDetails(1, -1, 1); // rooting the tree at 1.

	for(int i = 1; i <= K; i ++) {
		int station, radious;  // V_i, R_i
		cin >> station >> radious;
		// Now we have to properly add updates so that we can compute our answer.
		updates[station].push_back({radious, 1}); // as we add values to its subtree.
		while((parent[station] != -1) && (radious > 1)) { 
			radious --; // as its parent is at distance 1 from its child
			updates[parent[station]].push_back({radious, 1}); // as we add values to subtree of parent[station].
			if(radious > 1) { // but we don't want to add the values to subtree of station again as we have already added so to negate the effect of parent flag
				updates[station].push_back({radious-1, -1});
			}
			station = parent[station];
		}
	}

	computeAnswer(1, -1);

	for(int i = 1; i <= N; i ++) {
		cout << ans[i] << " ";
	}
	cout << '\n';
}

int main() {
	ios_base::sync_with_stdio(0); // fast IO
	cin.tie(0);
	cout.tie(0);

	int testCase;
	cin >> testCase;
	for(int i = 1; i <= testCase; i ++) {
		solveTestCase();
	}

}
