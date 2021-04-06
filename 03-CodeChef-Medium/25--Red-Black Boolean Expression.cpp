#include <bits/stdc++.h>

using namespace std;

const int MaxV = 300;
const int MaxE = 90000;
const int inf = 1e9;

struct Goldberg_Tarjan {
	int head[MaxV];
	int cap[MaxE], to[MaxE], next[MaxE];
	int ecnt;
	int maxFlow;
	int height[MaxV], C[MaxV];
	int S, T, V;
	void init() {
		memset(head, -1, sizeof(head));
		memset(height, 0, sizeof(height));
		memset(C, 0, sizeof(C));
		ecnt=0;
	}
	
	void add(int s, int e, int c) {
		cap[ecnt]=c, to[ecnt]=e, next[ecnt]=head[s], head[s]=ecnt++;
		cap[ecnt]=0, to[ecnt]=s, next[ecnt]=head[e], head[e]=ecnt++;
	}
	
	int ISAP(int x, int y) {
		int mn=V-1, F=0, R=y, t;
		if (x==T) return y;
		for (int i=head[x]; i!=-1; i=next[i]) {
			if (cap[i]>0) {
				if (height[x]==height[to[i]]+1) {
					t=ISAP(to[i], min(cap[i], R));
					cap[i]-=t;
					cap[i^1]+=t;
					R-=t;
					F+=t;
					if (height[S]>=V) return F;
					if (!R) break;
				}
				mn=min(mn, height[to[i]]);
			}
		}
		if (!F) {
			C[height[x]]--;
			if (!C[height[x]]) height[S]=V;
			height[x]=mn+1;
			C[height[x]]++;
		}
		return F;
	}
	
	int GT(int src, int dst, int cnt) {
		S=src, T=dst, V=cnt;
		C[0]=V;
		maxFlow=0;
		while (height[S]<V) maxFlow+=ISAP(S, inf);
		return maxFlow;
	}
} G;

#define NX 600

int T;
int n, m, c[NX], val[NX];
char s[NX];
vector <int> adj[NX], adj_[NX];
int vis[NX], cn, q[NX], qn;


int get (int u) {
	if (u > 0) return u - 1;
	return n + abs(u) - 1;
}

#define pb(x) push_back(x)
#define NOT(x) (x + n) % (2 * n)
#define OR(x, y) adj[NOT(x)].pb(y), adj[NOT(y)].pb(x)
#define diff(x, y) OR(x, y), OR(NOT(x), NOT(y))

void DFS (int u) {
	vis[u] = 1;
	for (auto v : adj[u]) if(!vis[v]) DFS(v);
	q[qn ++] = u;
}

void DFS_ (int u) {
	vis[u] = cn;
	for (auto v : adj_[u]) if(!vis[v]) DFS_(v);
}

void SCC () {
	fill_n(vis, 2 * n, 0);
	cn = qn = 0;
	for (int i = 0; i < 2 * n; i ++) if(!vis[i]) DFS(i);
	fill_n(vis, 2 * n, 0);
	for (int i = 0; i < 2 * n; i ++)
		for (auto v : adj[i]) adj_[v].push_back(i);
	for (int i = qn - 1; i >= 0; i --) {
		int u = q[i];
		if(!vis[u]) cn ++, DFS_(u);
	}
} 

bool TSAT() {
	SCC();
	for (int i = 0; i < n; i ++) {
		if(vis[i] == vis[i + n]) return 0;
		val[i] = vis[i] > vis[i + n];
		val[i + n] = !val[i];
	}
	return 1;
}

int u[NX * NX], v[NX * NX];

int vis_[NX];
vector <int> P;

void PRO() {
	fill_n(vis_, 2 * n, 0);
	G.init();
	int S = n, T = n + 1;
	int cn = 0;
	for (int i = 0; i < 2 * n; i ++) if(val[i]) {
		int c1, c2;
		if(i < n) {
			if(s[i] == '1') c1 = 0, c2 = c[i];
			else c1 = c[i], c2 = 0;
		}
		else {
			if(s[i - n] == '1') c1 = c[i - n], c2 = 0;
			else c1 = 0, c2 = c[i - n];
		}
		G.add(S, cn, c2);
		G.add(cn, T, c1);
		vis_[i] = cn ++;
	}
	for (int i = 0; i < m; i ++) {
		if(val[get(u[i])]) G.add(vis_[NOT(get(v[i]))], vis_[get(u[i])], inf);
		else G.add(vis_[NOT(get(u[i]))], vis_[get(v[i])], inf);
	}
	printf("%d\n", G.GT(S, T, T + 1));
}

int main () {
//#ifndef ONLINE_GUDGE
//	freopen ("in_rb2cnf.txt", "r", stdin);
//	freopen ("out.txt", "w", stdout);
//#endif
	int cs, i;
	scanf("%d", &cs);
	for (T = 1; T <= cs; T ++) {
		scanf ("%d %d", &n, &m);
		scanf ("%s", s);
		for (int i = 0; i < 2 * n; i ++) adj[i].clear(), adj_[i].clear();
		for (int i = 0; i < n; i ++) scanf ("%d", c + i);
		for (int i = 0; i < m; i ++) scanf ("%d %d", u + i, v + i), diff(get(u[i]), get(v[i]));
		if(!TSAT()) assert(0);
		else PRO();
	}
}
