#include <bits/stdc++.h>

#ifdef _MSC_VER
#include <agents.h>
#endif

#define FOR(i, a, b) for(int i = (a); i < (int)(b); ++i)
#define rep(i, n) FOR(i, 0, n)
#define ALL(v) v.begin(), v.end()
#define REV(v) v.rbegin(), v.rend()
#define MEMSET(v, s) memset(v, s, sizeof(v))
#define UNIQUE(v) (v).erase(unique(ALL(v)), (v).end())
#define MP make_pair
#define MT make_tuple

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> P;

const int N = 1e5 + 10;

struct Edge{
	int from, to, cost, id;
};

struct state{
	ll cost;
	int edge;
	bool operator < (const state &rhs) const{
		return cost > rhs.cost;
	}
};

vector<vector<int>> G;

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	cout.setf(ios::fixed);
	cout.precision(20);

	int t;
	cin >> t;
	while (t--){
		int n, m;
		cin >> n >> m;
		G.assign(n, vector <int>());
		vector<Edge> edge(m*2+1);
		int k = 1;
		rep(i, m){
			int x, y, z;
			cin >> x >> y >> z;
			--x, --y;
			G[x].push_back(k);
			G[y].push_back(k + 1);
			edge[k] = { x, y, z, k };
			edge[k+1] = { y, x, z, k+1 };
			k += 2;
		}
		int s, t;
		cin >> s >> t;
		--s, --t;

		edge[0] = { s, s, 0, 0 };

		vector<ll> dist(2*k, 1e18);
		dist[0] = 0;
		priority_queue<state> q;
		q.push({0, 0});

		auto check = [&](int s, int t, int nxt){
			if (nxt) return edge[s].cost > edge[t].cost;
			return edge[s].cost < edge[t].cost;
		};

		ll ans = -1;
		while (!q.empty()){
			auto st = q.top();
			q.pop();

			int nxt = st.edge / k; // 0 => pos, 1 => neg
			int e = st.edge % k;

			int v = edge[e].to;
			if (v == t){
				ans = st.cost;
				break;
			}
			if (dist[st.edge] < st.cost) continue;

			for (auto num : G[v]){
				if (!check(e, num, nxt)) continue;
				ll ncost = st.cost + edge[num].cost;
				int ne = (!nxt)*k + num;
				if (dist[ne] <= ncost) continue;
				dist[ne] = ncost;
				q.push({ncost, ne});
			}
		}
		if(ans >= 0) cout << ans << '\n';
		else cout << "No Solution" << '\n';
	}
}