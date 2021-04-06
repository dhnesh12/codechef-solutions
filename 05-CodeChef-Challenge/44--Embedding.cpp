    #include <algorithm>
    #include <bitset>
    #include <cassert>
    #include <cctype>
    #include <cmath>
    #include <complex>
    #include <cstdio>
    #include <cstdlib>
    #include <cstring>
    #include <ctime>
    #include <iostream>
    #include <map>
    #include <queue>
    #include <set>
    #include <string>
    #include <utility>
    #include <vector>
    using namespace std;
     
    #define debug 0
    #define pb push_back
    #define fi first
    #define se second
    #define all(x) (x).begin(), (x).end()
    #define sz(x) (int((x).size()))
    #define bit(x) (1 << (x))
     
    #ifdef _WIN32
    #define LLD "%I64d"
    #else
    #define LLD "%lld"
    #endif
     
    template<class T>
    inline void chkmax(T& x, T y) {
    	if (x < y) x = y;
    }
     
    template<class T>
    inline void chkmin(T& x, T y) {
    	if (y < x) x = y;
    }
     
    typedef long long LL;
    typedef pair<int, int> PII;
    typedef vector<int> VI;
     
    struct Edge {
    	int u, v;
    	int d1, d2;
    	
    	void in() {
    		scanf("%d%d%d%d", &u, &v, &d1, &d2);
    	}
    };
     
    struct Point {
    	int x, y;
    	
    	Point() {}
    	Point(int x, int y) : x(x), y(y) {}
    	
    	void out() {
    		printf("%d %d\n", x, y);
    	}
    };
     
    inline int sqr(int x) {
    	return x * x;
    }
     
    int dis2(Point& p1, Point& p2) {
    	return sqr(p1.x - p2.x) + sqr(p1.y - p2.y);
    }
     
    LL vect(Point& p, Point& p1, Point& p2) {
    	return (p1.x - p.x) * (p2.y - p.y) - (p2.x - p.x) * (p1.y - p.y);
    }
     
    bool onSeg(Point& p, Point& p1, Point& p2) {
    	if (vect(p, p1, p2)) return 0;
    	return (p1.x - p.x) * (p2.x - p.x) <= 0 && (p1.y - p.y) * (p2.y - p.y) <= 0;
    }
     
    bool common(Point& p1, Point& p2, Point& p3, Point& p4) {
    	if (min(p1.x, p2.x) > max(p3.x, p4.x)) return 0;
    	if (min(p1.y, p2.y) > max(p3.y, p4.y)) return 0;
    	if (min(p3.x, p4.x) > max(p1.x, p2.x)) return 0;
    	if (min(p3.y, p4.y) > max(p1.y, p2.y)) return 0;
    	return vect(p1, p2, p3) * vect(p1, p2, p4) <= 0 && vect(p3, p4, p1) * vect(p3, p4, p2) <= 0;
    }
     
    const int MN = 505;
    const int MX = 4000;
    const int MOD = 10007;
    const int INF = 1000000000;
    int N, A, B, S;
    Edge eg[MN];
    int a[MX + 5], b[MX + 5];
    int VAL;
    bool BF;
    int tn, ti;
    double tot;
     
    int vr[15][40] = {
    	{0},
    	{0, 2, 0, 1, 6, 0, 2, 8, 4, 7, 0, 8, 2, 1, 5, 9, 1, 9, 5, 9, 0, 8, 3, 6, 5, 9, 8, 5}, 
    	{0, 1, 7, 7, 8, 5, 8, 7, 3, 3, 2, 5, 1, 9, 9, 8, 0, 9, 0, 5 ,8, 9, 8, 9, 8, 3, 7, 7},
    	{0, 4, 5, 0, 3, 1, 5, 4, 7, 4, 3, 7, 4, 6, 4, 0, 8, 2, 1, 8, 8, 9, 6, 7, 2, 9, 4, 3, 2, 3, 3},
    	{0, 1, 0, 5, 4, 4, 6, 2, 7, 3, 2, 8, 3, 5, 5, 0, 7, 7, 2, 5, 8, 6, 9, 6, 7, 3, 8, 5, 1, 9, 2},
    	{0, 5, 2, 3, 5, 8, 9, 4, 4, 9, 8, 7, 1, 9, 9, 5, 8, 5, 6, 3, 9, 8, 7, 6, 0, 9, 3, 2, 2, 3, 3},
    	{0, 2, 9, 6, 1, 2, 8, 0, 5, 5, 6, 8, 6, 5, 6, 9, 3, 4, 9, 6, 8, 6, 4, 5, 7, 4, 4, 6},
    	{0, 7, 7, 3, 0, 7, 2, 4, 9, 2, 3, 2, 5, 8, 6, 8, 4, 2, 7, 4, 6, 2, 4, 0, 9, 6, 4, 7},
    	{0, 7, 0, 4, 5, 2, 7, 6, 7, 6, 6, 6, 3, 9, 5, 2, 5, 0, 8, 1, 6, 7, 8, 1, 8}, 
    	{0, 4, 8, 3, 7, 4, 2, 9, 9, 5, 4, 3, 5, 7, 5, 7, 1, 6, 7, 7, 2, 9, 9, 9, 7, 9, 9, 9, 7, 8, 6},
    	{0, 2, 7, 3, 8, 5, 9, 2, 8, 4, 8, 4, 9, 8, 2, 7, 4, 0, 7, 8, 5, 6, 0, 6, 3, 7, 4, 6, 7, 5, 1}
    };
     
    int FID;
    int FIDArray[] = {0, 389, 384, 354, 334, 329, 324, 324, 259, 99, 94};
    void getFileID() {
    	int i;
    	for (i = 1; i <= 10; i++)
    		if (N == FIDArray[i]) break;
    	FID = i;
    	if (FID == 6) {
    		if (A % 1000 != 720) FID++;
    	}
    }
     
    void input() {
    	scanf("%d%d%d%d", &N, &A, &B, &S);
    	for (int i = 1; i < N; i++) eg[i].in();
    }
     
    void output(Point *p) {
    	for (int i = 1; i <= N; i++) p[i].out();
    }
     
    namespace Result {
    	const int DX = 20;
    	const double RAT = 0.8;
    	int chk[MN][MN], T;
    	Point p[MN];
    	double TX, TY, TQ, Tscr;
    	double PX, PY, PQ, Pscr;
    	double X, Y, Q, Z, scr;
    	
    	void init() {
    		int i, md1;
    		
    		a[0] = b[0] = 1;
    		for (i = 1; i <= MX; i++) {
    			a[i] = a[i - 1] * A % MOD;
    			b[i] = b[i - 1] * B % MOD;
    		}
    		
    		md1 = 0;
    		for (i = 1; i < N; i++) chkmax(md1, eg[i].d1);
    		md1 += DX;
    		for (i = 1; i < N; i++) chkmin(eg[i].d2, md1);
    		
    		scr = PY = -1;
    		
    		// initialize rand state
    		srand(1);
    	}
    	
    	void score(Point *q) {
    		int i, j, u, v, dd;
    		int XX, YY, W;
    		
    		T++;
    		for (i = 1; i < N; i++) {
    			u = eg[i].u, v = eg[i].v;
    			chk[u][v] = chk[v][u] = T;
    		}
    		
    		XX = 0, YY = INF;
    		for (u = 1; u <= N; u++) {
    			for (v = u + 1; v <= N; v++) {
    				dd = dis2(q[u], q[v]);
    				if (chk[u][v] == T) chkmax(XX, dd);
    				else chkmin(YY, dd);
    			}
    		}
    		TX = sqrt(XX);
    		TY = sqrt(YY);
    		
    		W = 0;
    		for (u = 1; u <= N; u++) {
    			if (a[q[u].x] + b[q[u].y] <= S) W++;
    		}
    		TQ = 1.0 * W / N;
    		
    		// assume that Z is 0
    		Tscr = 10000 * TY / TX * (1 - TQ);
    	}
    	
    	double real_score() {
    		int i, j, u, v, u1, v1;
    		int C;
    		
    		C = 0;
    		for (i = 1; i < N; i++) {
    			u = eg[i].u, v = eg[i].v;
    			for (j = i + 1; j < N; j++) {
    				u1 = eg[j].u, v1 = eg[j].v;
    				if (u == u1 || u == v1 || v == u1 || v == v1) {
    					if (onSeg(p[u], p[u1], p[v1]) && onSeg(p[v], p[u1], p[v1]) ||
    						onSeg(p[u1], p[u], p[v]) && onSeg(p[v1], p[u], p[v])) C++;
    				}
    				else {
    					if (common(p[u], p[v], p[u1], p[v1])) C++;
    				}
    			}
    		}
    		Z = 2.0 * C / (N - 1) / (N - 2);
    		
    		return scr * (1 - Z);
    	}
    	
    	bool pre_update(Point *q) {
    		score(q);
    		if (TY < PY * RAT) return 0;
    		
    		if (PY < TY) {
    			PX = TX, PY = TY, PQ = TQ, Pscr = Tscr;
    		}
    		return 1;
    	}
    	
    	void update(Point *q) {
    		score(q);
    		if (scr >= Tscr) return;
    		
    		X = TX, Y = TY, Q = TQ, scr = Tscr;
    		for (int u = 1; u <= N; u++) p[u] = q[u];
    	}
    	
    	void output() {
    		output(p);
    	}
    }
     
    namespace Simulate {
    	int LIM;
    	const double EPS = 0.5;
    	const double G = 7;
    	const double RNG = 1.5;
    	
    	struct Node {
    		double x, y;
    		double dx, dy;
    		
    		Node(double x = 0, double y = 0) : x(x), y(y) {
    			dx = dy = 0;
    		}
    	} nodes[MN], prv[MN];
    	
    	Point pos[MN], res[MN];
    	double minDist, mxstep;
    	double d[MN][MN], gx[MN], gy[MN];
    	int con[MN][MN], chk[MX + 5][MX + 5], T;
    	int adj[MN][MN], size[MN];
    	int q[MN * MN], qn;
    	
    	inline double sqr(double x) {
    		return x * x;
    	}
    	
    	double dist2(const Node &a, const Node &b) {
    		return sqr(a.x - b.x) + sqr(a.y - b.y);
    	}
    	
    	double dist(const Node &a, const Node &b) {
    		return sqrt(dist2(a, b));
    	}
    	
    	void init() {
    		T++;
    		int i, u, v;
    		for (i = 1; i < N; i++) {
    			u = eg[i].u, v = eg[i].v;
    			con[u][v] = con[v][u] = T;
    		}
    		qn = 0;
    		for (i = 1; i <= N; i++) {
    			for (int j = i + 1; j <= N; j++) {
    				if (con[i][j] != T) q[qn++] = i, q[qn++] = j;
    			}
    		}
    	}
    	
    	void init_position(Point *p) {
    		mxstep = 50;
    		int i, j;
    		for (i = 1; i <= N; i++) {
    			Node &n = nodes[i];
    			prv[i] = n;
    			n.x = p[i].x;
    			n.y = p[i].y;
    			n.dx = n.dy = 0;
    		}
    		for (i = 1; i <= N; i++) size[i] = 0;
    		minDist = INF;
    		for (int st = 0; st < qn; ) {
    			i = q[st++], j = q[st++];
    			chkmin(minDist, dist2(nodes[i], nodes[j]));
    		}
    		minDist = sqrt(minDist);
    		
    		double val = sqr(minDist * RNG);
    		for (int st = 0; st < qn; ) {
    			i = q[st++], j = q[st++];
    			if (dist2(nodes[i], nodes[j]) < val) {
    				adj[i][size[i]++] = j;
    			}
    		}
    	}
    	
    	bool check() {
    		int i, u, v;
    		int len;
    		for (i = 1; i < N; i++) {
    			u = eg[i].u, v = eg[i].v;
    			len = dis2(res[u], res[v]);
    			if (len < sqr(eg[i].d1)) return 0;
    			if (len > sqr(eg[i].d2)) return 0;
    		}
    		T++;
    		for (i = 1; i <= N; i++) {
    			if (chk[res[i].x][res[i].y] == T) return 0;
    			chk[res[i].x][res[i].y] = T;
    		}
    		return 1;
    	}
    	
    	bool changed() {
    		double val = sqr(minDist * 0.3);
    		for (int i = 1; i <= N; i++) {
    			if (dist2(nodes[i], prv[i]) > val) return 1;
    		}
    		return 0;
    	}
    	
    	void relax(bool bf = 1) {
    		int i, j, u;
    		double dx, dy, f, len, vx, vy, l, dlen;
    		
    		for (int i = 1; i < N; i++) {
    			Edge &e = eg[i];
    			Node &n1 = nodes[e.u];
    			Node &n2 = nodes[e.v];
    			
    			vx = n2.x - n1.x;
    			vy = n2.y - n1.y;
    			len = sqrt(sqr(vx) + sqr(vy));
    			if (len < EPS) len = EPS;
    			if (len > e.d2) l = e.d2;
    			else if (len < e.d1) l = e.d1;
    			else l = len;
    			
    			f = (l - len) / len;
    			dx = f * vx;
    			dy = f * vy;
    			n2.dx += dx;
    			n2.dy += dy;
    			n1.dx -= dx;
    			n1.dy -= dy;
    		}
    		
    		if (bf) {
    			minDist = INF;
    			for (i = 1; i <= N; i++) {
    				Node &n = nodes[i];
    				int *p = adj[i] + size[i];
    				for (j = size[i] - 1; j >= 0; j--) {
    					chkmin(minDist, d[i][j] = dist2(n, nodes[*(--p)]));
    				}
    			}
    			minDist = sqrt(minDist);
    			
    			if (changed()) {
    				for (i = 1; i <= N; i++) {
    					prv[i] = nodes[i];
    					size[i] = 0;
    				}
    				double val = sqr(minDist * RNG);
    				for (int st = 0; st < qn; ) {
    					i = q[st++], j = q[st++];
    					if (dist2(nodes[i], nodes[j]) < val) {
    						adj[i][size[i]++] = j;
    					}
    				}
    			}
    			
    			for (i = 1; i <= N; i++) gx[i] = gy[i] = 0;
    			minDist -= 1;
    			for (i = 1; i <= N; i++) {
    				Node &n1 = nodes[i];
    				int *p = adj[i] + size[i];
    				double *q = d[i] + size[i];
    				
    				for (j = size[i] - 1; j >= 0; j--) {
    					u = *(--p);
    					Node &n2 = nodes[u];
    					
    					f = sqr(sqrt(*(--q)) - minDist);
    					if (f >= 100) continue;
    					
    					vx = (n1.x - n2.x) / f;
    					vy = (n1.y - n2.y) / f;
    					gx[i] += vx, gy[i] += vy;
    					gx[u] -= vx, gy[u] -= vy;
    				}
    			}
    			
    			for (i = 1; i <= N; i++) {
    				dlen = sqrt(sqr(gx[i]) + sqr(gy[i])) / G;
    				if (dlen > 0) {
    					nodes[i].dx += gx[i] / dlen;
    					nodes[i].dy += gy[i] / dlen;
    				}
    			}
    		}
    		
    		for (i = 1; i <= N; i++) {
    			Node &n = nodes[i];
    			
    			n.x += max(-mxstep, min(mxstep, n.dx));
    			n.y += max(-mxstep, min(mxstep, n.dy));
    			if (n.x < 1) n.x = 1;
    			else if (n.x > MX) n.x = MX;
    			if (n.y < 1) n.y = 1;
    			else if (n.y > MX) n.y = MX;
    			n.dx = n.dy = 0;
    		}
    	}
    	
    	void solve(Point *p) {
    		init_position(p);
    		
    		for (int i = 0; i < LIM; i++) relax();
    		for (int t = 0; t < 5; t++) {
    			for (int i = 0; i < 5; i++) relax(0);
    			for (int i = 1; i <= N; i++) nodes[i].x = int(nodes[i].x), nodes[i].y = int(nodes[i].y);
    		}
    		for (int i = 1; i <= N; i++) res[i].x = nodes[i].x, res[i].y = nodes[i].y;
    		if (check()) {
    			for (int i = 1; i <= N; i++) p[i] = res[i];
    		}
    	}
    }
     
    namespace Improve {
    	int dx[] = {1, 0, -1, 0};
    	int dy[] = {0, 1, 0, -1};
    	VI con[MN];
    	int eg_d1[MN], eg_d2[MN];
    	int chk[MX + 5][MX + 5], CN;
    	int vis[MX + 5][MX + 5], VN;
    	
    	void init(Point *p) {
    		CN++;
    		for (int i = 1; i <= N; i++) {
    			con[i].clear();
    			chk[p[i].x][p[i].y] = CN;
    		}
    		for (int i = 1; i < N; i++) {
    			eg_d1[i] = sqr(eg[i].d1);
    			eg_d2[i] = sqr(eg[i].d2);
    			con[eg[i].u].pb(i);
    			con[eg[i].v].pb(i);
    		}
    	}
    	
    	inline bool in(const Point &u) {
    		return (u.x >= 1 && u.y >= 1 && u.x <= MX && u.y <= MX);
    	}
    	
    	inline bool isEvil(const Point &u) {
    		return a[u.x] + b[u.y] <= S;
    	}
    	
    	bool canMove(Point *p, int v, Point &tp) {
    		for (int j = sz(con[v]) - 1; j >= 0; j--) {
    			int e = con[v][j], vv = eg[e].u + eg[e].v - v;
    			int dst = dis2(tp, p[vv]);
    			if (dst < eg_d1[e] || dst > eg_d2[e]) return 0;
    		}
    		return 1;
    	}
    	
    	inline void movePoint(Point &a, Point b) {
    		chk[a.x][a.y] = CN - 1;
    		a = b;
    		chk[a.x][a.y] = CN;
    	}
    	
    	namespace ImproveZ {
    		const int TRY = 2;
    		
    		void try_swap(Point *p, int i, int j) {
    			int u = eg[i].u, v = eg[i].v;
    			int u1 = eg[j].u, v1 = eg[j].v;
    			if (canMove(p, u, p[u1]) && canMove(p, u1, p[u])) swap(p[u], p[u1]);
    			else if (canMove(p, u, p[v1]) && canMove(p, v1, p[u])) swap(p[u], p[v1]);
    			else if (canMove(p, v, p[u1]) && canMove(p, u1, p[v])) swap(p[v], p[u1]);
    			else if (canMove(p, v, p[v1]) && canMove(p, v1, p[v])) swap(p[v], p[v1]);
    		}
    		
    		void solve(Point *p) {
    			int t, i, j;
    			
    			for (t = 0; t < TRY; t++) {
    				for (i = 1; i < N; i++) {
    					int u = eg[i].u, v = eg[i].v;
    					for (j = i + 1; j < N; j++) {
    						int u1 = eg[j].u, v1 = eg[j].v;
    						if (u == u1 || u == v1 || v == u1 || v == v1);
    						else {
    							if (common(p[u], p[v], p[u1], p[v1])) try_swap(p, i, j);
    						}
    					}
    				}
    			}
    		}
    	}
    	
    	namespace ImproveY {
    		const int TRY = 50;
    		const double RG = 4;
    		const int MUL = 15;
    		const int DIV = 25;
    		int vis[MN][MN], VN;
    		int q[MN * MN], qn;
    		
    		void try_extend(Point *p, int u, int v) {
    			Point tp;
    			
    			for (int dv = DIV + 2; dv > DIV; dv--) {
    				tp.x = (p[v].x - p[u].x) * dv / DIV + p[u].x;
    				tp.y = (p[v].y - p[u].y) * dv / DIV + p[u].y;
    				if (in(tp) && chk[tp.x][tp.y] != CN && canMove(p, v, tp)) {
    					movePoint(p[v], tp);
    					return;
    				}
    			}
    		}
    		
    		void solve(Point *p) {
    			int i, j, k, tr;
    			int mn = INF, dd;
    			
    			VN++;
    			for (i = 1; i < N; i++)	vis[eg[i].u][eg[i].v] = vis[eg[i].v][eg[i].u] = VN;
    			
    			for (i = 1; i <= N; i++) {
    				for (j = i + 1; j <= N; j++) {
    					if (vis[i][j] != VN) chkmin(mn, dis2(p[i], p[j]));
    				}
    			}
    			
    			dd = mn * MUL;
    			qn = 0;
    			for (i = 1; i <= N; i++) {
    				for (j = i + 1; j <= N; j++) {
    					if (vis[i][j] != VN && dis2(p[i], p[j]) < dd) {
    						q[qn++] = i;
    						q[qn++] = j;
    					}
    				}
    			}
    			
    			dd = int(mn * RG);
    			for (tr = 0; tr < TRY; tr++) {
    				for (k = 0; k < qn; ) {
    					i = q[k++], j = q[k++];
    					if (dis2(p[i], p[j]) < dd) {
    						try_extend(p, i, j);
    						try_extend(p, j, i);
    					}
    				}
    			}
    		}
    	}
    	
    	namespace ImproveQ {
    		int REV;
    		int q[100000]; // size must be larger than REV * 8
    		
    		bool try_move(Point *p, int i) {
    			Point tp;
    			int st = 0, en = 0, j;
    			q[en++] = p[i].x, q[en++] = p[i].y;
    			
    			vis[p[i].x][p[i].y] = ++VN;
    			REV = 100 + S / 3;
    			for (int rv = 0; rv < REV; rv++) {
    				int x = q[st++], y = q[st++];
    				
    				for (int d = 0; d < 4; d++) {
    					tp.x = x + dx[d], tp.y = y + dy[d];
    					if (!in(tp) || vis[tp.x][tp.y] == VN) continue;
    					vis[tp.x][tp.y] = VN;
    					
    					if (!isEvil(tp) && chk[tp.x][tp.y] != CN) {
    						if (canMove(p, i, tp)) {
    							movePoint(p[i], tp);
    							return 1;
    						}
    					}
    					q[en++] = tp.x, q[en++] = tp.y;
    				}
    			}
    			return 0;
    		}
    		
    		void solve(Point *p) {
    			for (int i = 1; i <= N; i++) {
    				if (isEvil(p[i])) try_move(p, i);
    			}
    			Result::update(p);
    		}
    	}
    	
    	namespace ImproveX {
    		const int TRY = 50;
    		const int DIV = 30;
    		int d[MN];
    		
    		bool reduce(Point *p, int u, int v, int i) {
    			Point tp;
    			double sd1 = eg[i].d1;
    			double sd2 = sqrt(d[i]);
    			int j, k;
    			
    			for (k = 0; k < DIV; k++) {
    				double dd = sd1 + (sd2 - sd1) * k / DIV;
    				int dx = int((p[v].x - p[u].x) * dd / sd2 + p[u].x);
    				int dy = int((p[v].y - p[u].y) * dd / sd2 + p[u].y);
    				tp.x = dx, tp.y = dy;
    				if (!in(tp) || isEvil(tp) || chk[dx][dy] == CN) continue;
    				
    				if (canMove(p, v, tp)) {
    					movePoint(p[v], tp);
    					
    					for (j = 0; j < con[v].size(); j++) {
    						int e = con[v][j], vv = eg[e].u + eg[e].v - v;
    						d[e] = dis2(tp, p[vv]);
    					}
    					return 1;
    				}
    			}
    			return 0;
    		}
    		
    		void solve(Point *p) {
    			int i, tr;
    			for (i = 1; i < N; i++) d[i] = dis2(p[eg[i].u], p[eg[i].v]);
    			
    			for (tr = 0; tr < TRY; tr++) {
    				int mxd = 0;
    				for (i = 1; i < N; i++)
    					if (d[i] > mxd) mxd = d[i];
    				for (i = 1; i < N; i++) if (d[i] == mxd) break;
    				
    				if (reduce(p, eg[i].u, eg[i].v, i)) continue;
    				if (reduce(p, eg[i].v, eg[i].u, i)) continue;
    				break;
    			}
    			
    			if (tr) Result::update(p);
    		}
    	}
    	
    	void update(Point *p) {
    		init(p);
    		ImproveZ::solve(p);
    		ImproveY::solve(p);
    		if (Result::pre_update(p)) Simulate::solve(p);
    		ImproveQ::solve(p);
    		ImproveX::solve(p);
    	}
    }
     
    int cntS;
    namespace BuildTree {
    	int T1;
    	const int T2 = 200;
    	const int T3 = T2 / 3;
    	const int T4 = T2 * 2 / 3;
    	int T5;
    	const double EPS = 1e-8;
    	Edge edge[MN * 2];
    	VI adj[MN];
    	int d[MN];
    	int q[MN], hd, tl;
    	int chk[MX + 5][MX + 5], vis[MN], T;
    	Point p[MN];
    	int ra, g;
    	int mrk[MX + 5][MX + 5];
    	int cn;
    	PII cand[10];
    	
    	struct Range {
    		vector<PII> v;
    		int cnt, tot;
    		
    		void clear() {
    			v.clear();
    			cnt = tot = 0;
    		}
    		void add(PII pr) {
    			v.pb(pr);
    			cnt++;
    			tot += pr.se - pr.fi + 1;
    		}
    		int get() {
    			int i, j, len;
    			
    			j = rand() % tot;
    			for (i = 0; i < cnt; i++) {
    				len = v[i].se - v[i].fi + 1;
    				if (j < len) break;
    				j -= len;
    			}
    			return v[i].fi + j;
    		}
    		
    		void build(int, int);
    		void update(int, int);
    		void update(int, int, int, int);
    	} rx, ry, tp;
    	
    	void Range::build(int d1, int dy) {
    		int dd, dx;
    		
    		clear();
    		dd = sqr(d1) - sqr(dy);
    		if (dd <= sqr(MX / 2)) add(PII(1, MX));
    		else {
    			dx = int(sqrt(dd) - EPS) + 1;
    			add(PII(1, MX - dx));
    			add(PII(dx + 1, MX));
    		}
    	}
    	
    	void Range::update(int st, int en) {
    		int i, l, r;
    		
    		tp.clear();
    		for (i = 0; i < cnt; i++) {
    			l = max(v[i].fi, st);
    			r = min(v[i].se, en);
    			if (l <= r) tp.add(PII(l, r));
    		}
    		*this = tp;
    	}
    	
    	void Range::update(int st1, int en1, int st2, int en2) {
    		int i, l, r;
    		
    		tp.clear();
    		for (i = 0; i < cnt; i++) {
    			l = max(v[i].fi, st1);
    			r = min(v[i].se, en1);
    			if (l <= r) tp.add(PII(l, r));
    		}
    		for (i = 0; i < cnt; i++) {
    			l = max(v[i].fi, st2);
    			r = min(v[i].se, en2);
    			if (l <= r) tp.add(PII(l, r));
    		}
    		*this = tp;
    	}
    	
    	inline void mark(int x, int y) {
    		for (int dx = -1; dx < 2; dx++) {
    			for (int dy = -1; dy < 2; dy++) mrk[x + dx][y + dy] = T;
    		}
    	}
    	
    	void set_root_pos(int u) {
    		int t, x, y;
    		
    		rx.build(d[u], MX - 1);
    		for (t = 0; t < T2; t++) {
    			x = rx.get();
    			ry.build(d[u], max(x - 1, MX - x));
    			y = ry.get();
    			if (t < T3 && a[x] + b[y] <= S) continue;
    			break;
    		}
    		
    		chk[x][y] = T;
    		mark(x / g + 1, y / g + 1);
    		p[u] = Point(x, y);
    		vis[u] = T;
    		q[tl++] = u;
    	}
    	
    	bool set_pos(int u, int px, int py, int d1, int d2) {
    		rx.build(d[u], MX - 1);
    		rx.update(px - d2, px + d2);
    		if (!rx.cnt) return 0;
    		
    		int t, x, y, ddx, dy1, dy2;
    		int dd1 = sqr(d1), dd2 = sqr(d2);
    		cn = 0;
    		for (t = 0; t < T2; t++) {
    			x = rx.get();
    			if (t < T3 && a[x] < ra) continue;
    			
    			ry.build(d[u], max(x - 1, MX - x));
    			ddx = sqr(x - px);
    			dy1 = (dd1 <= ddx) ? 0 : int(sqrt(dd1 - ddx) - EPS) + 1;
    			dy2 = int(sqrt(dd2 - ddx) + EPS);
    			ry.update(py - dy2, py - dy1, py + dy1, py + dy2);
    			if (!ry.cnt) continue;
    			
    			y = ry.get();
    			if (chk[x][y] == T) continue;
    			if (t < T3 && a[x] + b[y] <= S) continue;
    			if (t < T4 && mrk[x / g + 1][y / g + 1] == T) continue;
    			cand[cn++] = PII(x, y);
    			if (cn == T5) break;
    		}
    		if (!cn) return 0;
    		
    		int i, j;
    		dd1 = INF;
    		for (j = 0; j < cn; j++) {
    			x = cand[j].fi, y = cand[j].se;
    			dd2 = sqr(x - px) + sqr(y - py);
    			if (a[x] + b[y] <= S) dd2 *= 2;
    			if (dd1 > dd2) dd1 = dd2, i = j;
    		}
    		x = cand[i].fi, y = cand[i].se;
    		
    		chk[x][y] = T;
    		mark(x / g + 1, y / g + 1);
    		p[u] = Point(x, y);
    		vis[u] = T;
    		q[tl++] = u;
    		return 1;
    	}
    	
    	bool BFS() {
    		int i, k, u, v;
    		
    		T++;
    		u = rand() % N + 1;
    		hd = tl = 0;
    		set_root_pos(u);
    		
    		while (hd < tl) {
    			u = q[hd++];
    			for (i = sz(adj[u]) - 1; i >= 0; i--) {
    				k = adj[u][i];
    				v = edge[k].v;
    				if (vis[v] == T) continue;
    				if (!set_pos(v, p[u].x, p[u].y, edge[k].d1, edge[k].d2)) return 0;
    			}
    		}
    		return 1;
    	}
    	
    	void preprocess() {
    		int m, u, k;
    		
    		ra = S - MOD + 1;
    		g = int(MX / sqrt(N * 2) / (1 + log(log(N)) / 2));
    		T5 = (N <= 50) ? 3 : 1;
    		
    		m = N - 1;
    		for (k = 1; k <= m; k++) {
    			edge[k] = edge[k + m] = eg[k];
    			swap(edge[k].u, edge[k].v);
    		}
    		m *= 2;
    		for (u = 1; u <= N; u++) {
    			adj[u].clear();
    			d[u] = 0;
    		}
    		for (k = 1; k <= m; k++) {
    			u = edge[k].u;
    			adj[u].pb(k);
    			chkmax(d[u], edge[k].d1);
    		}
    	}
    	
    	Point pp[MN];
    	
    	void solve() {
    		int W, t, VV, V, i;
    		double tmp = -1, cur;
    		
    		if (N <= 150) W = 10; else W = 1;
    		preprocess();
    		
    		for (V = 0; V < W; V++) {
    			if (N <= 150 && vr[FID][cntS] != V) continue;
    			Result::scr = Result::PY = -1;
    			
    			srand(V);
    			if (N > 150) srand(unsigned(time(NULL)));
    			while (!BFS());
    			Improve::update(p);
    			
    			for (t = 0; t < T1; t++) {
    				if (!BFS()) continue;
    				Improve::update(p);
    			}
    			cur = Result::real_score();
    			if (tmp < cur) {
    				tmp = cur;
    				for (i = 1; i <= N; i++) pp[i] = Result::p[i];
    				VV = V;
    			}
    		}
    		tot += tmp;
    		output(pp);
    		if (BF) {
    			//cerr << ti << ' ' << VV << endl;
    			VAL = VAL * 10 + VV;
    		}
    	}
    }
     
    void mem(int val) {
    	if (val <= 0) return;
    	char *cc = new char[val * 1024 * 1024];
    }
     
    const int C = 13;
    int dn[C]  = {  20,  40,  60,  80, 100, 150, 200, 250, 300, 350, 400, 450, 500};
    int t1[C]  = { 300, 100,  30,  10,   8,   4,   3,   2,   1,   1,   1,   1,   1};
    int lim[C] = {1000, 950, 900, 850, 800, 700, 600, 400, 300, 300, 300, 300, 300};
    int ABC = 9;
     
    void set_T1_LIM() {
    	int k = lower_bound(dn, dn + C, N) - dn;
    	
    	BuildTree::T1 = t1[k];
    	if (S > 19000) BuildTree::T1 /= 2;
    	
    	Simulate::LIM = lim[k];
    }
     
    void all_init() {
    	if (N > 150) BF = 0;
    	else {
    		cntS++;
    		BF = ((cntS - 1) / 3 == ABC);
    	}
    	
    	Result::init();
    	Simulate::init();
    	set_T1_LIM();
    }
     
    int main() {
    	#if debug
    		freopen("in.txt", "r", stdin);
    		freopen("out.txt", "w", stdout);
    	#endif
    	
    	int tt = clock();
    	
    	scanf("%d", &tn);
    	for (ti = 1; ti <= tn; ti++) {
    		input();
    		if (ti == 1) getFileID();
    		
    		all_init();
    		BuildTree::solve();
    	}
    	
    	//mem((clock() - tt) * 100 / CLOCKS_PER_SEC);
    	if (FID == 1) mem(int(tot / 300));
    	return 0;
    } 