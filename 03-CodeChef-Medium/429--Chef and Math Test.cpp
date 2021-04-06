#include <bits/stdc++.h>
using namespace std; 
typedef long long ll; 
typedef pair<ll,ll> pp;
struct Event {
	ll type, mean, med;
	int idx;
	Event(ll type = 0, ll mean = 0, ll med = 0, int idx = 0) : type(type) , mean(mean), med(med), 
	idx(idx){}
	
	bool operator <(const Event&f) {
		if (mean != f.mean) return mean < f.mean; 
		if (med != f.med) return med < f.med; 
		return type < f.type;
	}
	
};
#define N 100005
int n,X,Y;
int a[N];
int meanVal[N], medianVal[N];
int par[N];
bool blocked[N];
int subtree[N];
ll medianSum[N], meanSum[N];
bool vis[N];
vector<int> added; 
vector<int> G[N];
int BIT[3*N]; 
void dfsSize(int u, int p) {
	subtree[u] = 1; 
	par[u] = p;
	for(int i=0; i<(int)G[u].size(); i++) {
		int v = G[u][i]; if (v == p || blocked[v]) continue; 
		dfsSize(v, u);
		subtree[u] += subtree[v];
	}
}

void dfs(int u, int p) {
	added.push_back(u); 
	for(int i=0; i<(int)G[u].size(); i++) {
		int v = G[u][i]; if (v == p || blocked[v]) continue; 
		meanSum[v] = meanSum[u] + (meanVal[v]); 
		medianSum[v] = medianSum[u] + (medianVal[v]); 
		dfs(v, u);
	}
}

void dfs2(int u, int p) {
	added.push_back(u); 
	for(int i=0; i<(int)G[u].size(); i++) {
		int v = G[u][i]; if (v == p || blocked[v]) continue; 
		dfs2(v, u); 
	}
}


void update(int i, int val) {
	while(i <= 2*N) BIT[i] += val, i += (i & (-i)); 
}
int query(int i) {
	int ret = 0; while(i) ret += BIT[i], i -= (i & (-i)); 
	return ret; 
}
int query(int i, int j) {
	return query(j) - query(i-1); 
}

ll calc(vector<int> &added, int centroid) {
	vector<Event> sweep; 
	ll ret = 0; 
	for(int i=0; i<(int)added.size(); i++) {
		int u = added[i]; 
		ll meanCen = meanSum[u] + meanVal[centroid]; 
		ll medCen = medianSum[u] + medianVal[centroid];
		sweep.push_back(Event(0, -meanCen, -medCen, u)); 
		sweep.push_back(Event(1, meanSum[u], medianSum[u], u)); 
	}
	sort(sweep.begin(), sweep.end()); 
	for(int i=0; i<(int)sweep.size(); i++) {
		Event cur = sweep[i]; 
		if (cur.type == 1) {
			update(cur.med + N, +1); 
		}
	}
	
	for(int i=0; i<(int)sweep.size(); i++) {
		Event cur = sweep[i]; 
		if (cur.type == 0) {
			ret += query(cur.med + N, 2 * N); 
			if (!vis[cur.idx]) {
				vis[cur.idx] = true;
				update((-cur.med) - medianVal[centroid] + N, -1); 
			}
		} else {
			if (vis[cur.idx] == 0)
				update(cur.med + N, -1), vis[cur.idx] = true;
		}
	}
	
	for(int i=0; i<(int)added.size(); i++) vis[added[i]] = false; 
	return ret; 
}
ll solve(int centroid) {
	medianSum[centroid] = meanSum[centroid] = 0; 
	added.clear(); 
	dfs(centroid, -1);
	ll ret = calc(added, centroid); 
	
	for(int i=0; i<(int)G[centroid].size(); i++) {
		int v = G[centroid][i]; if (blocked[v]) continue; 
		added.clear(); 
		dfs2(v, centroid); 
		ret -= calc(added, centroid);
	}
	
	return ret; 
}


ll create(int u) {
	dfsSize(u, 0);
	int centroid = u, bestSize = subtree[u] - 1; 
	queue<int> q; q.push(u); 
	while(!q.empty()) {
		int uu = q.front(); q.pop(); 
		int size = subtree[u] - subtree[uu]; 
		for(int i=0; i<(int)G[uu].size(); i++) {
			int v = G[uu][i]; if (v == par[uu] || blocked[v]) continue; 
			size = max(size, subtree[v]); 
			q.push(v);
		}
		
		if (bestSize > size) {
			bestSize = size;
			centroid = uu;
		}
	}
	
	blocked[centroid] = true; 
	ll ret = solve(centroid); 
	for(int i=0; i<(int)G[centroid].size(); i++) {
		int v = G[centroid][i]; if (blocked[v]) continue; 
		ret += create(v); 
	}
	return ret; 
}
int main() {
	int t; scanf("%d",&t); 
//	freopen("out.out", "w", stdout);
	while(t--) {
		scanf("%d%d%d",&n,&X,&Y); 
		for(int i=1; i<=n; i++) {
			scanf("%d",&a[i]); 
			meanVal[i] = a[i] - Y; 
			medianVal[i] = (a[i] <= X) ? +1 : -1;
		}
		for(int i=1; i<=n; i++) G[i].clear(); 
		for(int i=1; i<n; i++) {
			int x,y; scanf("%d%d",&x,&y); 
			G[x].push_back(y); 
			G[y].push_back(x); 
		}
		memset(blocked, 0, sizeof blocked); 
		ll ans = create(1); 
		printf("%lld\n", ans);
	}
	
	
	return 0; 
}