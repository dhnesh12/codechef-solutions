#include <bits/stdc++.h>

#define pb push_back

using namespace std;

const int N = 1e5 + 5;

bool f[N];
vector < int > cycle, od;
vector < pair < int , int >  > v[N];

void dfs(int x) {
	for (int i = 0; i < v[x].size(); ++i) {
		int to = v[x][i].first, id = v[x][i].second;
		if (!f[id]) {
			f[id] = true;
			dfs(to);
			cycle.pb(id);
		}
	}
}

void solve() {
	int n, m, st;
	cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int r, c;
		cin >> r >> c; c += n;
		v[r].pb({c, i});
		v[c].pb({r, i});
		st = r;
	}
	
	for (int i = 1; i <= 2 * n; ++i) 
		if (v[i].size() % 2 == 1) od.push_back(i);
	
	if (od.size() == 2) {
		++m;
		v[od[0]].pb({od[1], m});
		v[od[1]].pb({od[0], m});
	}
	
	dfs(st);
	if (od.size() == 2) {
		int id = -1;
		for (int i = 0; i < cycle.size(); ++i) 
			if (cycle[i] == m) id = i;

		for (int i = id + 1; i < cycle.size(); ++i)
			cout << cycle[i] << " ";
			
		for (int i = 0; i < id; ++i)
			cout << cycle[i] << " ";
	}
		else {
		for (int i = 0; i < cycle.size(); ++i)
			cout << cycle[i] << " ";		
	}
		
	cout << "\n";
	od.clear();
	cycle.clear();
	for (int i = 1; i <= 2 * n; ++i) {
		v[i].clear();
	}
	
	for (int i = 1; i <= m; ++i) {
		f[i] = false;
	}
}

main () {
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}