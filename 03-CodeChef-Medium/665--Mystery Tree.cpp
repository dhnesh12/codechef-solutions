#include <bits/stdc++.h>
using namespace std;

// =============================================================================
// BEGIN template
// =============================================================================
#ifdef ONLINE_JUDGE
#define fastio            std::ios::sync_with_stdio(false)
#define dbg(X)
#define _                 _
#else
#include <unistd.h>
#define fastio
#define dbg(X)            cerr << ">>> (" << #X << ") = (" << X << ")\n"
#define _                 << " _ " <<
#endif
#define   ff                first
#define   ss                second
#define   pb                push_back
#define   eb                emplace_back
#define   em                emplace
#define   pq                priority_queue
#define   M                 ((L+R)>>1)
#define   pqmin(X)          priority_queue<X,vector<X>,greater<X>>
#define   all(X)            (X).begin(),(X).end()
#define   sci1(X)           scanf("%d",&(X))
#define   sci2(X,Y)         scanf("%d%d",&(X),&(Y))
#define   sci3(X,Y,Z)       scanf("%d%d%d",&(X),&(Y),&(Z))
#define   scl(X)            scanf("%lld",&(X))
#define   scs(X)            scanf("%s",X)
#define   flush             fflush(stdout)
#define   pc(X)             __builtin_popcountll(X)
#define   lg(X)             (63 - __builtin_clzll(X))
#define   LG(X)             (lg(X)+((1<<lg(X)) < (X)))
#define    rp(i,L,R)        for (ll i = L, __R = R; i <= __R; i++)
#define   rpd(i,R,L)        for (ll i = R, __L = L; __L <= i; i--)

// functions
void reopen(const string& name) {
#ifdef ONLINE_JUDGE
	char fn[256];
	sprintf(fn,"%s.in",name.c_str());
	freopen(fn,"r",stdin);
	sprintf(fn,"%s.out",name.c_str());
	freopen(fn,"w",stdout);
#endif
}

// dps
#define DP1(type,X)\
	static type dp[X];\
	static bool mark[X];\
	auto& ans = dp[i];\
	if (mark[i]) return ans;\
	mark[i] = true;
#define DP2(type,X,Y)\
	static type dp[X][Y];\
	static bool mark[X][Y];\
	auto& ans = dp[i][j];\
	if (mark[i][j]) return ans;\
	mark[i][j] = true;
#define DP3(type,X,Y,Z)\
	static type dp[X][Y][Z];\
	static bool mark[X][Y][Z];\
	auto& ans = dp[i][j][k];\
	if (mark[i][j][k]) return ans;\
	mark[i][j][k] = true;

// overloads
#define GET_SCI(_1,_2,_3,NAME,...) NAME
#define sci(...) GET_SCI(__VA_ARGS__,sci3,sci2,sci1)(__VA_ARGS__)
#define GET_DP(_1,_2,_3,_4,NAME,...) NAME
#define DP(...) GET_DP(__VA_ARGS__,DP3,DP2,DP1)(__VA_ARGS__)

// types
typedef   long long     ll;
typedef   pair<int,int> ii;
typedef   vector<int>   vi;
typedef   vector<bool>  vb;
typedef   set<int>      si;

// constants
const ll  oo =          0x3f3f3f3f3f3f3f3fll;
const int LGN =         25;
const int MOD =         1e9+7;
const int N =           2e5+5;
const int NLGN =        N*LGN;
// =============================================================================
// END template
// =============================================================================

vector<vi> adj;
vb blocked;

int sz[N];
void dfs_sz(int u, int p) {
	sz[u] = 1;
	for (int& v : adj[u]) if (v != p && !blocked[v]) {
		dfs_sz(v, u);
		sz[u] += sz[v];
		if (
			adj[u][0] == p ||
			blocked[adj[u][0]] ||
			sz[v] > sz[adj[u][0]]
		) swap(v, adj[u][0]);
	}
}

int solve_through_centroids(int root) {
	dfs_sz(root, root);
	int half = sz[root]/2;
	int cent = root;
	while (0 < half && half < sz[adj[cent][0]]) cent = adj[cent][0];
	blocked[cent] = true;

	printf("1 %d\n", cent);
	fflush(stdout);

	int y;
	sci(y);

	if (y == -1) return cent;
	if (blocked[y]) return -1;

	return solve_through_centroids(y);
}

int main() {
	fastio;

	int t;
	sci(t);

	rp(i,1,t) {
		int n;
		sci(n);

		vector<vi> tadj(n+1);
		vb tblocked(n+1,false);

		rp(i,2,n) {
			int u,v;
			sci(u,v);

			tadj[u].pb(v);
			tadj[v].pb(u);
		}
		swap(tadj, adj);
		swap(tblocked, blocked);

		printf("2 %d\n", solve_through_centroids(1));
		fflush(stdout);

		int s;
		sci(s);
	}

	return 0;
}