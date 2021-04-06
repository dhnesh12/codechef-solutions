#include<iostream>
#include<cstring>
#include<cstdio>
#include<map>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn = 100000 + 10;
const int maxm = 2000000 + 10;
const int INF = 0x3f3f3f3f;

template<typename T> bool chkmin(T& a, const T& b) { return a > b ? a = b, 1 : 0; }
template<typename T> bool chkmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

#define debug(...) fprintf(stderr, __VA_ARGS__)
#define REP(i, a, b) for(int i = (a); i < (b); i++) 
#define DREP(i, a, b) for(int i = (a-1); i >= (b); i--)
#define EREP(i, a) for(int i = Begin[(a)]; i; i = Next[i])

int V, S, T;
int C[maxm], F[maxn];
int Begin[maxn], Next[maxm], To[maxm], E;

int read() {
	int n(0), f(1);
	char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >='0' && ch <='9') { n = n * 10 + ch - 48; ch = getchar(); }
	return n * f;
}

void Add(int u, int v, int c) {
	To[++E] = v; Next[E] = Begin[u]; C[E] = c; Begin[u] = E;
	To[++E] = u; Next[E] = Begin[v]; C[E] = 0; Begin[v] = E;
}

int cur[maxn], dis[maxn], pre[maxn], gap[maxn];

void pre_bfs() {
	static int q[maxn], head, tail;
	head = tail = 0;
	memset(dis, INF, sizeof dis);

	++ gap[dis[q[tail++] = T] = 0];
	while(head < tail) {
		int x = q[head++];
		EREP(i, x) if(C[i] == 0)
			if(dis[x] + 1 < dis[To[i]])
				++gap[dis[q[tail++] = To[i]] = dis[x] + 1];
	}
}

int ISAP() {
	pre_bfs();
	REP(i, 0, V) cur[i] = Begin[i];

	F[S] = INF;
	int u = S, v, flow = 0;
	while(dis[S] < V) {
		v = -1;
		for(int i = cur[u]; i; i = Next[i]) 
			if(C[i] && dis[To[i]] + 1 == dis[u])
				{ v = To[cur[u] = i]; break; }
		if(~v) {
			F[v] = min(F[u], C[pre[v] = cur[u]]);
			if((u = v) == T) {
				do {
					C[pre[u]] -= F[T];
					C[pre[u]^1] += F[T];
				}while((u = To[pre[u]^1]) ^ S); flow += F[T];
			}
		}else {
			if(--gap[dis[u]] == 0) break;
			dis[u] = V;
			for(int i = cur[u] = Begin[u]; i; i = Next[i]) 
				if(C[i] && dis[To[i]] + 1 < dis[u]) 
					dis[u] = dis[To[i]] + 1;
			++gap[dis[u]];
			if(u^S) u = To[pre[u]^1];
		}
	}
	return flow;
}


int a, sum;

int _;
int P, D, H, N, L, R;
int people(int k, int i, int j) {
	int K = P*(D+1) + k*D*2 + i*2 + j;
	if(K >= S) cerr << 'e' << endl;
	return K;
}
int day(int d, int h) {
	int K = (3*D+1)*P + d*H + h;
	if(K >= S) cerr << 'e' << endl;
	return K;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("data.txt", "r", stdin);
	freopen("ans.txt", "w", stdout);
#endif

	_ = read();
	while(_--) {
		P = read(), D = read(), H = read(), N = read();

		S = (3*D+1)*P + D*H, T = S + 1, V = T + 1, E = 1;

		sum = 0;
		memset(gap, 0, sizeof gap);
		memset(Begin, 0, sizeof Begin);

		REP(i, 0, P) Add(S, i, read());

		L = read(), R = read();

		REP(i, 0, D) REP(j, 0, H) sum += (a=read()), Add(day(i, j), T, a);
				
		int ok = true;
		REP(i, 0, P) {
			REP(j, 0, D) {
				int m[2] = {0, 0};
				REP(k, 0, H) {
					bool lunch = (L <= k+1 && k+1 <= R);
					m[lunch] += 1 - (a = read());
					if(a) 
						Add(people(i, j, lunch), day(j, k), 1);
				}
				if(m[0] + m[1] > N || m[1] + 1 > (R-L+1)) ok = false;
				Add(i, P + i*D + j, N - m[0] - m[1]);
				Add(P + i*D + j, people(i, j, 0), H - (R-L+1) - m[0]);
				Add(P + i*D + j, people(i, j, 1), (R-L+1) - m[1] - 1);
			}
		}
		if(!ok) { puts("No"); continue; }
		puts(sum == ISAP() ? "Yes" : "No");
	}

	return 0;
}