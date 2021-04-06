#include <bits/stdc++.h>
 
#define endl '\n'
#define fi first
#define se second
#define forn(i,n) for (int i = 0; i < n; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define all(v) v.begin(), v.end()
#define pb push_back
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define var(x) #x << " = " << x

using namespace std;
 
typedef long long lli;
typedef long double ld;
typedef pair<lli, lli> plli;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<vector<lli>> vvlli;
typedef vector<lli> vlli;
typedef vector<pii> vpii;

const int MAXN = 1005;

int n, m;
vector<bool> vis;
vi link_a, link_b;
vvi adj;
pii coord[MAXN];

bool try_khun(int u){
	vis[u] = true;
	for(auto v:adj[u]){
		if(link_b[v] == -1){
			link_b[v] = u;
			link_a[u] = v;
			return true;
		}
	}
	for(auto v:adj[u]){
		if(vis[link_b[v]]) continue;
		if(try_khun(link_b[v])){
			link_b[v] = u;
			link_a[u] = v;
			return true;
		}
	}
	return false;
}

int max_matching(){
	link_a.assign(n, -1);
	link_b.assign(m, -1);
	vis.resize(n);
	int mx_match = 0;
	forn(i, n){
		fill(all(vis), false);
		if(try_khun(i))
			mx_match++;
	}
	return mx_match;
}

int main () {
	fastIO();
	int t;
	cin >> t;
	while(t--){
		int N;
		cin >> N;
		set<int> sx, sy;
		forn(i, N){
			cin >> coord[i].fi >> coord[i].se;
			sx.insert(coord[i].fi);
			sy.insert(coord[i].se);
		}
		int _id = 0;
		map<int, int> idx, idy;
		for(auto i:sx) idx[i] = _id++;
		_id = 0;
		for(auto i:sy) idy[i] = _id++;
		n = sx.size();
		m = sy.size();
		adj.clear();
		adj.resize(n);
		forn(i, N)
			adj[idx[coord[i].fi]].pb(idy[coord[i].se]);
		cout << max_matching() << endl;
	}
	return 0;
}
