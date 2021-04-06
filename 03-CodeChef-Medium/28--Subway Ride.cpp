/**
 *    File Name:      my.cpp
 *    Author:         BlockChanZJ
 *    Created Time:   2019年12月05日 星期四 14时27分10秒
**/

#include<bits/stdc++.h>
using namespace std;

#undef _GLIBCXX_DEBUG

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
	return '"' + s + '"';
}

string to_string(const char* s) {
	return to_string((string) s);
}

string to_string(bool b) {
	return (b ? "true": "false");
}

string to_string(vector<bool> v) {
	bool first = true;
	string res = "{";
	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		if (!first) {
			res += ", ";
		}
		first = false;
		res += to_string(v[i]);
	}
	res += "}";
	return res;
}

template <size_t N>
string to_string(bitset<N> v) {
	string res = "";
	for (size_t i = 0; i < N; i++) {
		res += static_cast<char>('0' + v[i]);
	}
	return res;
}

template <typename A>
string to_string(A v) {
	bool first = true;
	string res = "{";
	for (const auto &x : v) {
		if (!first) {
			res += ", ";
		}
		first = false;
		res += to_string(x);
	}
	res += "}";
	return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
	return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
	return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
	return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() { cerr << "\033[33;0m" << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
	cerr << " " << to_string(H);
	debug_out(T...);
}

template <typename T>
void debug_out (T a[], int n) {
	cerr << "{" << to_string(a[0]);
	for (int i = 1; i < n; ++i) cerr << ", " << to_string(a[i]);
	cerr << "}";
	debug_out();
}

#define LOCAL

#ifdef LOCAL
#define dbg(...)  cerr << "\033[33;1m" << "[" << #__VA_ARGS__ << "] : ", debug_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

using LL = long long;
using PII = pair<int,int>;

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x.size()))
#define sqr(x) ((x)*(x))

LL powmod (LL a, LL b, LL MOD) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans % MOD;
}

const int N = 500005, MOD = 1e9+7, INF = 1e9;

// head

// dp[i][j][a][b] i ~ fa[i][j]路径上 
struct edge {
	int v, next;
} e[N<<1];
map <PII, int> ma;
vector <int> color[N];
int n, m, cnt, tot, Q;
int head[N];
PII ask[N];
const int DEG = 20;
int fa[N][DEG], dep[N], pw[DEG];
int dp[N][DEG][2][2], son[N], w[N][DEG][2], sz[N][DEG];
void add (int u, int v) {
	e[tot].v = v, e[tot].next = head[u], head[u] = tot++;
}
void BFS (int root) {
	queue <int> q;
	dep[root] = 0;
	fa[root][0] = root;
	q.push(root);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = 1; i < DEG; ++i) {
			fa[u][i] = fa[fa[u][i-1]][i-1];
			sz[u][i] = sz[fa[u][i-1]][i-1];
			w[u][i][0] = w[fa[u][i-1]][i-1][0];
			w[u][i][1] = w[fa[u][i-1]][i-1][1];
		}
		for (int i = head[u]; ~i; i = e[i].next) {
			int v = e[i].v;
			if (v == fa[u][0]) continue;
			dep[v] = dep[u] + 1;
			int pos = ma[mp(u,v)];
			sz[v][0] = color[pos].size();
			if (sz[v][0] > 3) sz[v][0] = 3;
			for (int i = 0; i < min (2, sz[v][0]); ++i) w[v][0][i] = color[pos][i];
			fa[v][0] = u;
			q.push(v);
		}
	}
}
void upd (int &x, int y) {
	if (y > x) x = y;
}
void getDP (int u, int father) {
	//dbg (u, father);
	for (int i = 1; i < DEG; ++i) {
		if (dep[u]-pw[i] < 0) break;
		for (int a = 0; a < min (2, sz[u][0]); ++a) {
			for (int b = 0; b < min (2, sz[son[fa[u][i]]][0]); ++b) {
				int szC = sz[son[fa[u][i-1]]][0], szD = sz[fa[u][i-1]][0];
				if (szC == 3 || szD == 3) {
					for (int c = 0; c < min (2, szC); ++c) {
						for (int d = 0; d < min(2, szD); ++d) {
							if (i == 1 && (a != c || b != d)) continue;
							upd (dp[u][i][a][b], dp[u][i-1][a][c] + dp[fa[u][i-1]][i-1][d][b] + 1);
						}
					}
				} else {
					for (int c = 0; c < szC; ++c) {
						for (int d = 0; d < szD; ++d) {
							if (i == 1 && (a != c || b != d)) continue;
							if (w[son[fa[u][i-1]]][0][c] != w[fa[u][i-1]][0][d]) upd (dp[u][i][a][b], dp[u][i-1][a][c]+dp[fa[u][i-1]][i-1][d][b]+1);
							else upd (dp[u][i][a][b], dp[u][i-1][a][c]+dp[fa[u][i-1]][i-1][d][b]);
						}
					}
				}
			}
		}
	}
	for (int i = head[u]; ~i; i = e[i].next) {
		int v = e[i].v;
		if (v == father) continue;
		son[u] = v;
		getDP (v, u);
	}
}
int LCA (int u, int v) {
	if (dep[u] > dep[v]) swap (u, v);
	int hu = dep[u], hv = dep[v];
	int tu = u, tv = v;
	// 同一高度
	for (int det = hv-hu, i = 0; det; det >>= 1, ++i) 
		if (det & 1) tv = fa[tv][i];
	if (tu == tv) return tu;
	// 一起向上爬
	for (int i = DEG-1; i >= 0; --i) {
		if (fa[tu][i] == fa[tv][i]) continue;
		tu = fa[tu][i];
		tv = fa[tv][i];
	}
	return fa[tu][0];
}
struct Ds {
	int pST, pED, colST, colED, val, sizeST, sizeED;
	void show () {
		printf ("pST = %d, pED = %d, colST = %d, colED = %d, val = %d, sizeST = %d, sizeED = %d\n",pST,pED,colST,colED,val,sizeST,sizeED);
	}
};
// 2^4改成3^4 可以 省掉这个log
int getSon (int u, int v) {
	// v在含u子树上的孩子
	int len;
	for (len = 0; len < DEG; ++len) {
		if (dep[u] - pw[len+1] <= dep[v]) break;
	}
	if (dep[u] - pw[len] > dep[v]) u = fa[u][len];
	for (; len >= 0; --len) {
		if (dep[u] - pw[len] <= dep[v]) continue;
		u = fa[u][len];
	}
	return u;
}
int Merge (const Ds &x, const Ds &y) {
	if (x.sizeED == 3 || y.sizeST == 3) return x.val + y.val + 1;
	if (x.colED >= x.sizeED || y.colST >= y.sizeST || x.colST >= x.sizeST || y.colED >= y.sizeED) return 0;
	int ans = x.val + y.val;
	if (w[getSon(x.pST,x.pED)][0][x.colED] != w[getSon(y.pST,y.pED)][0][y.colST]) ++ans;
	return ans;
}
int Query (int u, int v) {
	if (u == v || fa[u][0] == v || fa[v][0] == u) return 0;
	int lca = LCA (u, v);
	if (dep[u] < dep[v]) swap (u, v);
	bool flag = (v == lca);
	vector <Ds> v1, v2;
//	dbg (u, v, lca, getSon(u,1), getSon(v,1));
	if (u != lca) {
		// u 向上爬
		int len;
		for (len = 0; len < DEG; ++len) {
			if (dep[u]-pw[len+1] < dep[lca]) {
				for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) 
					v1.push_back ({u, fa[u][len], i, j, dp[u][len][i][j], sz[u][0], sz[getSon(u,fa[u][len])][0]}); 
				u = fa[u][len];
				break;
			}
		}
		for (; len >= 0; --len) {
			if (u == lca) break;
			if (dep[u] - pw[len] < dep[lca]) continue;
			vector <Ds> tmp;
			int tmpDP[2][2] = {0};
			for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) 
				tmp.push_back ({u, fa[u][len], i, j, dp[u][len][i][j], sz[u][0], sz[getSon(u,fa[u][len])][0]});
			for (auto &x : v1) for (auto &y : tmp) upd (tmpDP[x.colST][y.colED], Merge (x, y));
			int st = v1[0].pST, ed = tmp[0].pED, sizeED = tmp[0].sizeED, sizeST = v1[0].sizeST;
			v1.clear();
			for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) v1.push_back ({st, ed, i, j, tmpDP[i][j], sizeST, sizeED});
			u = fa[u][len];
		}
	}
	if (v != lca) {
		// v 向上爬
		int len;
		for (len = 0; len < DEG; ++len) {
			if (dep[v]-pw[len+1] < dep[lca]) {
				for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) 
					v2.push_back ({v, fa[v][len], i, j, dp[v][len][i][j], sz[v][0], sz[getSon(v,fa[v][len])][0]});
				v = fa[v][len];
				break;
			}
		}
		for (; len >= 0; --len) {
			if (v == lca) break;
			if (dep[v] - pw[len] < dep[lca]) continue;
			int tmpDP[2][2] = {0};
			vector <Ds> tmp;
			for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) 
				tmp.push_back ({v, fa[v][len], i, j, dp[v][len][i][j], sz[v][0], sz[getSon(v,fa[v][len])][0]});
			for (auto &x : v2) for (auto &y : tmp) upd (tmpDP[x.colST][y.colED], Merge (x, y));
			int st = v2[0].pST, ed = tmp[0].pED, sizeED = tmp[0].sizeED, sizeST = v2[0].sizeST;
			v2.clear();
			for (int i = 0; i < 2; ++i) for (int j = 0; j < 2; ++j) v2.push_back ({st, ed, i, j, tmpDP[i][j], sizeST, sizeED});
			v = fa[v][len];
		}
	}
	if (flag) {
		int ans = 0;
		for (auto &x : v1) ans = max(ans, x.val);
		return ans;
	} else {
		/*
		for (auto &x : v1) x.show();
		for (auto &x : v2) x.show();
		*/
		int ans = 0;
		for (auto &x : v1) for (auto &y : v2) upd (ans, Merge (x, y));
		return ans;
	}
}
set <pair<PII,int> > S;
void init () {
	tot = 0; memset (head, -1, sizeof(head));
	scanf ("%d%d",&n,&m);
	for (int i = 0; i < m; ++i) {
		int u, v, w; scanf ("%d%d%d",&u,&v,&w);
		if (S.count(mp(mp(u,v),w))) continue;
		S.insert (mp(mp(u,v),w));
		if (ma.count(mp(u,v))) color[ma[mp(u,v)]].push_back (w);
		else ma[mp(u,v)] = ++cnt, ma[mp(v,u)] = cnt, color[cnt].push_back (w), add (u, v), add (v, u);
	}
	scanf ("%d",&Q);
	for (int i = 0; i < Q; ++i) scanf("%d%d",&ask[i].fi,&ask[i].se);
}
void work () {
	pw[0] = 1;
	for (int i = 1; i < DEG; ++i) pw[i] = pw[i-1]<<1; 
	BFS (1);
	getDP (1, -1);
//	dbg ("fa's val : \n");	for (int i = 1; i <= n; ++i) for (int j = 0; j <= 2; ++j) printf ("fa[%d][%d] = %d\n",i,j,fa[i][j]);
//	dbg ("dp's val : \n"); for (int i = 1; i <= n; ++i) for (int j = 0; j <= 2; ++j) for (int a = 0; a < 2; ++a) for (int c = 0; c < 2; ++c) printf ("dp[%d][%d][%d][%d] = %d\n",i,j,a,c,dp[i][j][a][c]);
//	dbg ("sz's val : \n"); for (int i = 1; i <= n; ++i) for (int j = 0; j < 2; ++j) printf ("sz[%d][%d] = %d\n",i,j,sz[i][j]);
	//dbg ("w's val : \n"); for (int i = 1; i <= n; ++i) for (int j = 0; j <= 2; ++j) for (int k = 0; k < 2; ++k) printf ("w[%d][%d][%d] = %d\n",i,j,k,w[i][j][k]);
	for (int i = 0; i < Q; ++i) {
		printf ("%d\n", Query (ask[i].fi,ask[i].se));
	}
}

int main () {
        time_t tic = clock();
        int T = 1;
        //scanf ("%d",&T);
        while (T--) {
                init (); 
                work (); 
        }
        time_t toc = clock();
        cerr << "execute time = " << (toc-tic) / CLOCKS_PER_SEC << "ms\n"; 
        return 0;
}