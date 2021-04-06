/*
    Author: Zhouxing Shi
    Created on Oct28, 2015
*/
#include <cstdio>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <cassert>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define drep(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a, b) for (int i = (a); i < (b); ++i)
#define pb(x) push_back(x)
#define mp(x, y) (make_pair(x, y))
#define clr(x) memset(x, 0, sizeof(x))
#define xx first
#define yy second

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const ll inf = 10000000000000000ll;
const ll INF = ~0ULL >> 1;
template <class T> inline void read(T &n)
{
    char c; int flag = 1;
    for (c = getchar(); !(c >= '0' && c <= '9' || c == '-'); c = getchar()); if (c == '-') flag = -1, n = 0; else n = c - '0';
    for (c = getchar(); c >= '0' && c <= '9'; c = getchar()) n = n * 10 + c - '0'; n *= flag;
}
//***************************

const int maxn = 110;
typedef pair<ll, ll> pll;

int N, M;
pll slack[maxn], G[maxn][maxn], U[maxn], V[maxn];
ll g[maxn][maxn], h[maxn][maxn];
int Match[maxn], Link[maxn], S[maxn], T[maxn], active[maxn][maxn];

struct edge
{
	int x, y;
	ll a, b;
	edge(){}
	edge(int _x, int _y, ll _a, ll _b) : x(_x), y(_y), a(_a), b(_b) {}
} E[maxn * maxn];

inline pll operator+(const pll &A, const pll &B) { return mp(A.xx + B.xx, A.yy + B.yy); }
inline pll operator-(const pll &A, const pll &B) { return mp(A.xx - B.xx, A.yy - B.yy); }

int dfs(int u)
{
	S[u] = 1;
	rep(i, 1, N)
		if (!T[i])
		{
			pll t = U[u] + V[i] - G[u][i];
			if (!t.xx && !t.yy)
			{
				T[i] = 1;
				if (!Link[i] || dfs(Link[i]))
				{
					Link[i] = u; Match[u] = i;
					return 1;
				}
			}
			else slack[i] = min(slack[i], t);
		}
	return 0;
}
	
bool cmp(const edge &A, const edge &B)
{
	return B.a > A.a || B.a == A.a && B.b < A.b;
}

void Go(int x)
{
	U[x] = mp(-INF, -INF);
	rep(j, 1, N) 
		U[x] = max(U[x], G[x][j] - V[j]);
	rep(j, 1, N) slack[j] = mp(INF, INF);
	Link[Match[x]] = 0;
	Match[x] = 0;
	while (1)
	{
		memset(S, 0, sizeof(S));
		memset(T, 0, sizeof(T));
		if (dfs(x)) break;
		pll delta = mp(INF, INF);
		rep(j, 1, N) if (!T[j]) delta = min(delta, slack[j]);
		rep(j, 1, N)
		{
			if (S[j]) U[j] = U[j] - delta;
			if (T[j]) V[j] = V[j] + delta;
		}
	}		

}
	
int main()
{
	#ifdef DEBUG
		freopen("in", "r", stdin);
	#endif
	
	scanf("%d", &N);
	rep(i, 1, N) rep(j, 1, N) 
	{
		scanf("%lld:%lld", &h[i][j], &g[i][j]);
		E[++M] = edge(i, j, h[i][j] - g[i][j], g[i][j]);
		G[i][j] = mp(-inf, -inf);
	}
	sort(E + 1, E + M + 1, cmp);
		
	int cnt = 0;
	ll best_H = -inf, best_G = inf;
	rep(i, 1, M) 
	{
		int x = E[i].x, y = E[i].y;
		active[x][y] = true;
		G[x][y] = mp(inf, inf);
		ll s = 0;
		rep(j, 1, N) s += U[j].xx + V[j].xx;
		s -= U[x].xx;
		ll t = -INF;
		rep(j, 1, N) t = max(t, G[x][j].xx - V[j].xx);
		s += t;
		if (s - (h[x][y] - g[x][y]) >= best_H)
		{
			Go(x);
			ll th = 0, tg = 0;
			int valid = true;
			rep(j, 1, N) if (!active[Link[j]][j]) valid = false;
			if (valid)
			{
				rep(j, 1, N) th += h[Link[j]][j], tg += g[Link[j]][j];
				if (E[i].a > 0) th -= h[x][y], tg -= g[x][y];
				if (th - tg > best_H - best_G || th - tg == best_H - best_G && th > best_H) best_H = th, best_G = tg;
			}
		}
		
		G[x][y] = mp(h[x][y] - g[x][y], h[x][y]);
		Go(x);				
	}
	printf("%lld %lld\n", best_H, best_G);
	return 0;
}
