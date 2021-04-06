#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define mkp make_pair
#define si set < int >
#define vi vector < int >
#define pii pair < int, int >
#define mii map < int, int >
#define p_q priority_queue
#define INF ((1 << 30) - 1)
#define FI(n) FastIO::read(n)
#define FO(n) FastIO::write(n)
#define ull unsigned long long
#define mst(a, b) memset(a,b,sizeof(a))
#define foR(i, k, j) for(int i = (k); i >= (j); i--)
#define For(i, k, j) for(int i = (k); i <= (j); i++)
#define Foe(i, u) for(int i = lst[u], v = e[i].v; i; i = e[i].nxt, v = e[i].v)
#define IOS ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define Fin(s) freopen(s, "r", stdin)
#define Fout(s) freopen(s, "w", stdout)
#define file(s) Fin(s".in"), Fout(s".out")
//#define int long long
const int P = 1e9 + 7; //
using namespace std;
template <typename T> inline void ckmax(T &a, T b) {(a < b) && (a = b);}
template <typename T> inline void ckmin(T &a, T b) {(a > b) && (a = b);}
inline int mul(int a, int b) {return 1ll * a * b % P;}
inline int add(int a, int b) {return a + b >= P ? a + b - P : a + b;}
inline int sub(int a, int b) {return a - b >= 0 ? a - b : a - b + P;}
inline void mulmod(int &a, int b) {a = mul(a, b);}
inline void addmod(int &a, int b) {((a += b) >= P) && (a -= P);}
inline void submod(int &a, int b) {((a -= b) < 0) && (a += P);}
inline int ksm(int a, int b) {int ans=1; for(;b;b>>=1) {if(b&1) ans=1ll*ans*a%P;a=1ll*a*a%P;}return ans;}
inline int inv(int a) {return ksm(a, P-2);}
namespace FastIO {
    const int SIZE=1<<16; char buf[SIZE], obuf[SIZE], str[64]; int bi=SIZE, bn=SIZE, opt;
    int read_str(char *s) {
        while (bn) {for (;bi<bn&&buf[bi]<=' ';bi++);if (bi<bn) break; bn=fread(buf,1,SIZE,stdin),bi=0;}
        int sn=0;while (bn) {for (;bi<bn&&buf[bi]>' ';bi++) s[sn++]=buf[bi];if (bi<bn) break; bn=fread(buf,1,SIZE,stdin),bi=0;}s[sn]=0;return sn;
    }
    template <typename T> bool read(T& x) {if(x)x=0;int bf=0,n=read_str(str); if(!n) return 0; int i=0; if (str[i]=='-') bf=1,i=1; for(x=0;i<n;i++) x=x*10+str[i]-'0'; if(bf) x=-x; return 1;}
    template <typename T> void write(T x) {
        if(!x) obuf[opt++] = '0'; else {if(x<0) obuf[opt++]='-',x=-x;int sn=0; while(x)str[sn++]=x%10+'0',x/=10;for (int i=sn-1;i>=0;i--) obuf[opt++]=str[i];}
        if (opt>=(SIZE>>1)){fwrite(obuf, 1, opt, stdout); opt=0;}
    }
    void write_char(char x) {obuf[opt++]=x;if (opt>=(SIZE>>1)){fwrite(obuf, 1, opt, stdout); opt=0;}}
    void Fflush() { if (opt) fwrite(obuf, 1, opt, stdout); opt=0;}
};
inline int read() {int x; FI(x); return x;}
const int MAXN = 3e5 + 5;
int n, c[MAXN];
vector < int > e[MAXN];
namespace BAS {
    int dep[MAXN], f[MAXN], top[MAXN], siz[MAXN];
    void dfs1(int u, int fa) {
        siz[u] = 1, dep[u] = dep[fa] + 1, f[u] = fa;
        for(auto v : e[u]) {
            if(v == fa) continue;
            dfs1(v, u); siz[u] += siz[v];
        }
    }
    void dfs2(int u, int fir) {
        top[u] = fir; int hson = 0;
        for(auto v : e[u]) if(v != f[u] && siz[hson] < siz[v]) hson = v; 
        if(!hson) return; dfs2(hson, fir);
        for(auto v : e[u]) if(v != f[u] && v != hson) dfs2(v, v);
    }
    inline int lca(int u, int v) {
        while(top[u] != top[v]) 
            dep[top[u]] > dep[top[v]] ? u = f[top[u]] : v = f[top[v]];
        return dep[u] < dep[v] ? u : v;
    }
    inline int dist(int u, int v) {return dep[u] + dep[v] - 2 * dep[lca(u, v)];}
    inline void init() {dfs1(1, 0); dfs2(1, 1);}
}

struct Trie {
	static const int K = 20, N = MAXN * K;
	int c[N][2], tot = 1, siz[N], cnt[K];
	void insert(int v) {
		int p = 1; siz[p]++;
		for(int i = 0; i <= 19; i++) {
			if(!c[p][v >> i & 1]) c[p][v >> i & 1] = ++tot;
			p = c[p][v >> i & 1], siz[p]++; if(v >> i & 1) cnt[i]++;
		}
	}
	
	int calc() {
		int res = 0;
		For(i, 0, 19) res += (cnt[i] & 1) << i;
		return res;
	}
	void doit() {
		int p = 1;
		For(i, 0, 19) {
			cnt[i] -= siz[c[p][1]] + siz[c[p][0]]; swap(c[p][0], c[p][1]); 
			p = c[p][0];
		}
	}
	void clear() {
		For(i, 1, tot) c[i][0] = c[i][1] = siz[i] = 0; mst(cnt, 0);	tot = 1;
	}
}tr;
#define dist(u, v) BAS::dist(u, v)

int f[MAXN], siz[MAXN], rt, vrt, vis[MAXN], allrt; vector < int > g[MAXN];

void getroot(int u, int fa, int allsiz) {
	siz[u] = 1; int mxval = 0;
	for(auto v : e[u]) {
		if(vis[v] || v == fa) continue;	
		getroot(v, u, allsiz); siz[u] += siz[v]; 
		ckmax(mxval, siz[v]);
	}
	ckmax(mxval, allsiz - siz[u]);
	if(vrt > mxval) rt = u, vrt = mxval;
}

void dfs(int u, int fa, int allsiz) {
	vis[u] = 1;
	for(auto v : e[u]) {
		if(vis[v] || v == fa) continue;
		int tsiz = siz[v] < siz[u] ? siz[v] : allsiz - siz[u]; vrt = INF, rt = 0;
		getroot(v, u, tsiz); f[rt] = u, g[u].pb(rt);
//		cerr << u << ' ' << rt << endl; 
		dfs(rt, u, tsiz);
	}
}
vector < int > tag[MAXN], tagf[MAXN];
void update(int u) {
//	cerr << u << endl;
	int s = u, lst = -1, tlst = -1;
	while(u) {
		int t = dist(u, s);
//		cerr << s << ' ' << u << ' ' << t << endl;
//		cerr << t << endl;
		tag[u].pb(t); if(lst != -1) tagf[lst].pb(t);
		lst = u, u = f[u];
	}
}
int ans[MAXN], mxdep, dep[MAXN], used[MAXN]; vector < int > d[MAXN], rem;
void getinfo(int u, int fa, int op) {
	ckmax(mxdep, dep[u] = dep[fa] + 1); if(op || used[u]) d[dep[u]].pb(u); if(op) used[u] = 1, rem.pb(u);
	for(auto v : e[u]) {
		if(v == fa || vis[v]) continue;
		getinfo(v, u, op); 
	}
}
void solve(int x) {
//	fprintf(stderr, "Solve on %d\n", x); 
	mxdep = 0;
	for(auto it : tag[x]) tr.insert(it); rem.clear();
	dep[0] = -1; getinfo(x, 0, 1);
	For(i, 0, mxdep) { int val = tr.calc();
		for(auto it : d[i]) ans[it] ^= val;
		tr.doit();
	}
	tr.clear(); For(i, 0, mxdep) d[i].clear(); mxdep = 0;
//	For(i, 1, n) cerr << used[i] << ' '; cerr << endl;
	if(tagf[x].size()) {
		dep[0] = -1; getinfo(f[x], 0, 0);
//		cerr << "?" << mxdep << endl;
		for(auto it : tagf[x]) tr.insert(it);
		For(i, 0, mxdep) { int val = tr.calc();
//			cerr << "! " << i << ' ' << val << endl;
			for(auto it : d[i]) ans[it] ^= val;
//			cerr << val << ' ' << i << ' ' << it << endl;
			tr.doit();
		}
		tr.clear(); For(i, 0, mxdep) d[i].clear(); 
	}
	for(auto it : rem) used[it] = 0; rem.clear();
}

void getans(int u, int fa) {
	solve(u); vis[u] = 1; 
	for(auto v : g[u]) {
		if(v == fa || vis[v]) continue;	
		getans(v, u);
	}
}	

signed main()
{
    #ifndef ONLINE_JUDGE
        file("pro");
    #endif
	int T = read();
	For(td, 1, T) {
//		fprintf(stderr, "Running on testdata %d\n", td);
		n = read(); For(i, 1, n) e[i].clear(), g[i].clear(), siz[i] = vis[i] = ans[i] = f[i] = 0, tag[i].clear(), tagf[i].clear();
		For(i, 1, n - 1) {
			int u = read(), v = read();
			e[u].pb(v), e[v].pb(u);
		}
		For(i, 1, n) c[i] = read() & 1;
		BAS::init(); vrt = INF; getroot(1, 0, n); allrt = rt; dfs(rt, 0, n);
		For(i, 1, n) if(c[i]) update(i); For(i, 1, n) vis[i] = 0; 
//		For(i, 1, n) {
//			fprintf(stderr, "tag[%d] : ", i);
//			for(auto it : tag[i]) cerr << it << ' '; cerr << endl;
//		}
//		For(i, 1, n) {
//			fprintf(stderr, "tagf[%d] : ", i);
//			for(auto it : tagf[i]) cerr << it << ' '; cerr << endl;
//		}
		getans(allrt, 0);
		int fans = 0, pw = 2;
		For(i, 1, n) {if(!ans[i]) addmod(fans, pw); pw = (pw << 1) % P;};
//		For(i, 1, n) cerr << ans[i] << ' '; cerr << endl;
		printf("%d\n", fans);
	}
    return FastIO::Fflush(), 0;
}
/*

*/

