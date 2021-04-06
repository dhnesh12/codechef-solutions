#pragma GCC optimize("O2")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,fma,abm,mmx,avx")

#include<bits/stdc++.h>
using namespace std;

const int MK = 70000;
const int MN = 505;
const int MD = 8;
#define rep1(i, a, b) for (int i = a; i <= b; i ++)
#define rep2(i, a, b) for (int i = a; i < b; i ++)
#define pb push_back
#define endl '\n'

char key[] = "ULRD";
int dd[] = {-502, -1, 1, 502};
int val1, val2;

inline void chkmax(int& a, int b) {
	if (a < b) a = b;
}

inline void chkmin(int& a, int b) {
	if (a > b) a = b;
}

struct Answer {
	int s, e, load[66], len;
	inline void in(int S, int E, int* LOAD, int LEN) {
		s = S, e = E;
		memcpy(load, LOAD, LEN * sizeof(int));
		len = LEN;
	}
};

vector<Answer> ans;

namespace TIME {
	inline unsigned long long rdtsc() {
	#ifdef __amd64
		unsigned long long a, d;
		__asm__ volatile ("rdtsc" : "=a" (a), "=d" (d));
		return (d << 32) | a;
	#else
		unsigned long long x;
		__asm__ volatile ("rdtsc" : "=A" (x));
		return x;
	#endif
	}
	inline double gettime(){return rdtsc() / 2993344000.0;}	
};

using namespace TIME;

double start_time = gettime();
double desired_time = start_time + 4.99;

inline double getnow() {
	return gettime() - start_time;
}

namespace FIO {
	inline char gc() {
		static char buf[100000], *p1 = buf, *p2 = buf;
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
	}
	template <class T> inline int read(T &x) {
		char c = gc(), b = 1;
		for (; !(c >= '0' && c <= '9' || c == EOF); c = gc()) if (c == '-') b = -b;
		if (c == EOF) return 0;
		for (x = 0; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = gc());
		x *= b;
		return 1;
	}
	template <typename Head, typename... Tail>
	inline int read(Head& H, Tail&... T) {
		int rlt = read(H);
		return rlt + read(T...);
	}
	inline void pc(char c) {
		static char buf[100000], *p1 = buf, *p2 = buf + 100000;
		if (!c) fwrite(buf, 1, p1 - buf, stdout), p1 = buf;
		else {
			*p1++ = c;
			p1 == p2&&(fwrite(buf, 1, 100000, stdout), p1 = buf);
		}
	}
	template <class T> inline void write(T x) {
		static char str[64];
		if (x == 0) pc('0');
		else {
			if (x < 0) pc('-'), x = -x;
			int sn = 0;
			while (x) str[sn++] = x % 10 + '0', x /= 10;
			for (int i = sn - 1; i >= 0; i --) pc(str[i]);
		}
	}
	inline void write(char c) {
		pc(c);
	}
	inline void write(const char *s) {
		for (int i = 0; s[i]; i ++) pc(s[i]);
	}
	template <typename Head, typename... Tail>
	inline void write(Head H, Tail... T) {
		write(H), write(T...);
	}
	inline void flush() {
		pc(0);
	}
}
using namespace FIO;

int N, K, E;
int X[MK], Y[MK], L[MK], R[MK];
vector<int> _con[MK], con[MK];
int chk[MN][MN], lim[MN][MN], _chk[MN * MN], _lim[MN * MN];
int dir[20][4], dmode;

namespace INIT {
	void Input() {
		memset(chk, 0, sizeof(chk));
		read(N); read(K);
		E = 0;
		rep1(i, 1, K) {
			read(X[i], Y[i], L[i], R[i]);
			chk[X[i]][Y[i]] = i;
			chkmax(E, R[i]);
		}
		if (E == 8) val1 = 6500, val2 = 8;
		if (E == 16) val1 = 5000, val2 = 28;
		if (E == 32) val1 = 2000, val2 = 93;
		if (E == 64) val1 = 4000, val2 = 112;
	}
	
	
	void Connect() {
		int x, y, xx, yy, u, NL, NR, Ndist, D, DD;
		rep1(i, 1, K) {
			x = X[i], y = Y[i];
			D = R[i] - 1;
			rep1(j, -D, D) {
				xx = x + j;
				if (xx < 1 || xx > N) continue;
				DD = D - abs(j);
				rep1(k, -DD, DD) {
					yy = y + k;
					if (yy < 1 || yy > N) continue;
					if (!chk[xx][yy]) continue;
					u = chk[xx][yy];
					if (i == u) continue;
					NL = max(L[u], L[i]), NR = min(R[u], R[i]);	
					if (NR < NL) continue;
					Ndist = abs(j) + abs(k) + 1;
					if (Ndist > NR) continue;
					if (NR == NL && (NL - Ndist) & 1) continue;
					con[i].pb(u);
				}
			}
		}
		queue<int> q;
		rep1(i, 1, K) {
//			_con[i] = con[i];
			if (con[i].size() == 1) q.push(i);
		}
		while (!q.empty()) {
			int u = q.front(); q.pop();
			int v = con[u][0];
			for (int x : con[v]) {
				if (x == u) continue;
				rep2(i, 0, con[x].size()) {
					if (con[x][i] != v) continue;
					con[x][i] = con[x].back();
					con[x].pop_back();
				}
				if (con[x].size() == 1) q.push(x);
			}
			con[v] = {u};
		}
		rep1(i, 1, K) {
			int l = INT_MAX, r = 0;
			for (int x : con[i]) {
				chkmin(l, L[x]);
				chkmax(r, R[x]);
			}
			chkmax(L[i], l);
			chkmin(R[i], r);
		}
		rep1(i, 1, K) {
			sort(con[i].begin(), con[i].end());
		}
	}
	
	void Init() {
		int x, y, D, DD, xx, yy;
		memset(lim, -1, sizeof(lim));
		rep1(i, 1, K) {
			x = X[i], y = Y[i];
			D = R[i] - 1;
			rep1(j, -D, D) {
				xx = x + j;
				if (xx < 1 || xx > N) continue;
				DD = D - abs(j);
				rep1(k, -DD, DD) {
					yy = y + k;
					if (yy < 1 || yy > N) continue;
					chkmax(lim[xx][yy], R[i] - abs(j) - abs(k));
				}
			}
		}
		int b[4], tp_sz = 0;
		iota(b, b + 4, 0);
		do {
			if ((b[0] ^ b[3]) == 3) {
				memcpy(dir[tp_sz], b, sizeof b);
				tp_sz ++;
			}
		}while(next_permutation(b, b + 4));
	}
	void solve() {
		Input();
		Connect();
		Init();
	}
};

bool vis[MN * MN];
int use[MN * MN], *direct;
int id[MN][MN], pnt[MK], deg[MK];
int sl, sr, cnt, en, dirs[66], d, Rd, Rdirs[66], T, COUNT;
int r[MN * MN], c[MN * MN];

inline void update(int s, int e, int* A, int& An, bool mode = true) {
	int from = pnt[s], to = pnt[e], len = An;
//	if (mode) {
//		int rec = An - max(L[s], L[e]), i;
//		if (rec > 1) {
//			i = len = 1;
//			while (i < An) {
//				if (len > 2 && ((A[len - 2] ^ A[i]) == 3) && rec > 1) {
//					A[len - 2] = A[len - 1];
//					len --; rec -= 2;
//				}
//				else A[len ++] = A[i];
//				i ++;
//			}
//		}
//	}
	
	for (int i = 1; i < len; i ++) {
		vis[from] = mode;
		from += dd[A[i]];
	}
	An = len;
	vis[from] = mode;
}

void dfs1(int u) {
	int v = _chk[u];
	if (v && d > 1) {
		if (d >= sl && d >= L[v] && d <= R[v]) {
			memcpy(Rdirs, dirs, d* sizeof (int));
			en = v;
			Rd = d;
			cnt ++;
		}
		return;
	}
	if (d >= sr || d > _lim[u]) return;
	vis[u] = true;
	rep2(i, 0, 4) {
		int j = direct[i];
		int uu = u + dd[j];
		if (vis[uu]) continue;
		dirs[d ++] = j;
		dfs1(uu);
		d --;
		if (cnt > 1) break;
	}
	vis[u] = false;
}

int _L, _R, _en, _enx, _eny;

bool dfs2(int u) {
	int v = _chk[u];
	if (v && d > 1) {
		if (v != _en || d < _L) return false;
		return true;
	}
	if (abs(_enx - r[u]) + abs(_eny - c[u]) + d > _R) return false;
	vis[u] = 1;
	rep2(i, 0, 4) {
		int j = direct[i];
		int uu = u + dd[j];
		if (vis[uu]) continue;
		dirs[d ++] = j;
		if (dfs2(uu)) {
			vis[u] = 0;
			return true;
		}
		d --;
	}
	vis[u] = 0;
	return false;
}

bool dfs3(int u) {
	int v = _chk[u];
	if (v && d > 1) {
		if (d >= sl && d >= L[v] && d <= R[v]) {
			en = v;
			return true;
		}
		return false;
	}
	if (E > 8) {
		if (use[u] == T) return false;
		use[u] = T;
	}
	if (d >= sr || d > _lim[u]) return false;
	vis[u] = true;
	rep2(i, 0, 4) {
		int uu = u + dd[direct[i]];
		if (vis[uu]) continue;
		dirs[d ++] = direct[i];
		if (dfs3(uu)) {
			vis[u] = false;
			return true;
		}
		d --;
	}
	vis[u] = false;
	return false;
}

int ids[MK];

void find1() {
	rep1(i, 1, K) {
		int u = ids[i];
		if (E != 8 && con[u].size() > 2) continue;
		if (vis[pnt[u]]) continue;
		sl = L[u], sr = R[u];
		if (sr > 20) continue;
		d = 1, cnt = 0;
		dfs1(pnt[u]);
		if (cnt == 1) {
			Answer tp;
			tp.in(u, en, Rdirs, Rd);
			update(u, en, tp.load, tp.len);
			ans.pb(tp);
		}
	}
	if (E <= 8) {
		rep1(i, 1, K) {
			int u = ids[i];
			if (vis[pnt[u]]) continue;
			sl = L[u], sr = R[u];
			d = 1, cnt = 0;
			dfs1(pnt[u]);
			if (cnt == 1) {
				Answer tp;
				tp.in(u, en, Rdirs, Rd);
				update(u, en, tp.load, tp.len);
				ans.pb(tp);
			}
		}
	}
}

void find2() {
	rep1(i, 1, K) {
		int u = ids[i];
		if (vis[pnt[u]]) continue;
		if (con[u].size() > 1) break;
		int v = con[u][0];
		en = pnt[v];
		if (vis[en]) continue;
		_en = v;
		_enx = r[en], _eny = c[en];
		d = 1, cnt = 0;
		_L = max(L[u], L[v]), _R = min(R[u], R[v]);
		if (dfs2(pnt[u])) {
			Answer tp;
			tp.in(u, v, dirs, d);
			update(u, v, tp.load, tp.len);
			ans.pb(tp);
		}
	}
	if (E > 8) return;
	rep1(i, 1, K) {
		int u = ids[i];
		if (vis[pnt[u]]) continue;
		if (con[u].size() > 2) break;
		for (int v : con[u]) {
			en = pnt[v];
			if (vis[en]) continue;
			_en = v;
			_enx = r[en], _eny = c[en];
			d = 1, cnt = 0;
			_L = max(L[u], L[v]), _R = min(R[u], R[v]);
			if (dfs2(pnt[u])) {
				Answer tp;
				tp.in(u, v, dirs, d);
				update(u, v, tp.load, tp.len);
				ans.pb(tp);
				break;
			}
		}
	}
}

void find3() {
	rep1(i, 1, K) {
		int u = ids[i];
		if (vis[pnt[u]]) continue;
		sl = L[u], sr = R[u];
		d = 1;
		T ++;
		if (dfs3(pnt[u])) {
			Answer tp;
			tp.in(u, en, dirs, d);
			update(u, en, tp.load, tp.len);
			ans.pb(tp);
		}
	}
}

inline void del(int u) {
	for (int x : con[u]) {
		deg[x] --;
	}
}

inline void add(int u) {
	for (int x : con[u]) {
		deg[x] ++;
	}
}

vector<int> Uvis;
bool can[MK];

void _find3() {
	for (int u : Uvis) if (can[u]) {
		can[u] = 0;
		if (vis[pnt[u]]) continue;
		sl = L[u], sr = R[u];
		d = 1;
		T ++;
		if (dfs3(pnt[u])) {
			Answer tp;
			tp.in(u, en, dirs, d);
			update(u, en, tp.load, tp.len);
			ans.pb(tp);
			del(en);
			del(u);
		}
	}
	int x = 0;
	for (int u : Uvis) if (!vis[pnt[u]]) {
		can[u] = 1;
		Uvis[x ++] = u;
	}
	Uvis.resize(x);
}

void split(Answer& edge) {
	int s = edge.s, e = edge.e;
	bool rd = rand() & 1;
	if (rd) {
		swap(s, e);
	}
	int pts = pnt[s], pte = pnt[e];
	if (E == 8) {
		if (!deg[s] && !deg[e] && (rand() & 255) >= val2) return;
	}
	else if (!deg[e] && (rand()&255) >= val2) return;
	if (rd) swap(s, e);
	update(s, e, edge.load, edge.len, false);
	if (rd) swap(s, e);
	dmode = rand() & 7;
	direct = dir[dmode];
	bool flag = false;
	if (deg[s]) {
		vis[pte] = 1, sl = L[s], sr = R[s], d = 1, T ++;
		if (dfs3(pts)) {
			edge.in(s, en, dirs, d);
			update(s, en, edge.load, edge.len);
			del(en);
			flag = true;
		}
	}
//	if (deg[e]) {
		vis[pte] = 0, sl = L[e], sr = R[e], d = 1, T ++;
		if (dfs3(pte)) {
			if (flag) {
				Answer tp;
				tp.in(e, en, dirs, d);
				update(e, en, tp.load, tp.len);
				ans.pb(tp);
				del(en);
			}
			else {
				edge.in(e, en, dirs, d);
				update(e, en, edge.load, edge.len);
				if (en != s) {
					del(en);
					add(s);
				}
				flag = true;
			}
		}
		else {
			if (flag) add(e);
		}
//	}
//	else if (flag) deg[e] ++;
	if (!flag) {
		if (rd) swap(s, e);
		update(s, e, edge.load, edge.len);
	}
	else {
		if (!vis[pts] && !can[s]) Uvis.pb(s), can[s] = 1;
		if (!vis[pte] && !can[e]) Uvis.pb(e), can[e] = 1;
	}
	return;
}

void find4() {
	int k = COUNT - 1, kk = 0, sz = 0, TC = 0;
	rep1(i, 1, K) if (!vis[pnt[i]]) Uvis.pb(i);
	double start, tot = 0;
	while (1) {
		sz ++;
		if (!(sz & 8191)) {
			if (gettime() > desired_time) break;
		}
		kk ++;
		if (kk == val1) {
			kk = 0;
			_find3();
			TC ++;
		}
		k ++;
		if (k == ans.size()) k = COUNT;
		split(ans[k]);
	}
}

void step1() {
	memset(use, 0, sizeof(use));
	memset(_chk, 0, sizeof(_chk));
	direct = dir[0];
	
	int tp = 1;
	rep1(i, 0, N + 1) rep1(j, 0, N + 1) {
		if (i == 0 || i == N + 1 || j == 0 || j == N + 1) vis[tp] = 1;
		_lim[tp] = lim[i][j];
		r[tp] = i, c[tp] = j;
		id[i][j] = tp ++;
	}
	rep1(i, 1, K) {
		pnt[i] = id[X[i]][Y[i]];
		_chk[pnt[i]] = i;
		ids[i] = i;
		deg[i] = con[i].size();
	}
	sort(ids + 1, ids + K + 1, [](int a, int b) {
		if (con[a].size() != con[b].size()) return con[a].size() < con[b].size();
		return pnt[a] < pnt[b];
	});
	if (E == 32) COUNT = 0;
	else {
		if (E == 8) for (int i = 0; i < 1; i ++) find1();
		find1();
		COUNT = ans.size();
		find2();
	}
	sort(ids + 1, ids + K + 1, [](int a, int b) {
		return pnt[a] < pnt[b];
	});
	find3();
	rep2(i, 1, K) if (vis[pnt[i]]) del(i);
	find4();
}

int main() {
	INIT::solve();
	step1();
	cout << ans.size() << endl;
	for (auto x : ans) {
		cout << x.s << ' ' << x.e << ' ';
		for (int i = 1; i < x.len; i ++) {
			cout << key[x.load[i]];
		}
		cout << endl;
	}
}
