#include <cstdio>
using namespace std;
const int MAXN = 501005;
char s[MAXN];
int last, sz;
int son[26][MAXN], endpos[MAXN], len[MAXN], link[MAXN];
int tong[MAXN];
long long ans;
int to[MAXN], nxt[MAXN];
int head[MAXN], tot;
int log[MAXN];
template<typename T> inline T max(T a, T b) {
	return a > b ? a : b;
}
template<typename T> inline int strlen(T* s) {
	for (int i = 0; ; i++) {
		if (s[i] == 0) return i;
	}
}
inline void add(int u, int v) {
	to[++tot] = v;
	nxt[tot] = head[u];
	head[u] = tot;
}
inline char gc() {
	static char buf[1 << 16], *S, *T;
	if (T == S) {
		T = (S = buf) + fread(buf, 1, 1 << 16, stdin);
		if (T == S)
			return EOF;
	}
	return *S++;
}
#define getchar gc
inline int read() {
	char c;
	int w = 1;
	while ((c = getchar()) < '0' || c > '9')
		if (c == '-')
			w = -1;
	int res = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
		res = res * 10 + c - '0';
	return res * w;
}
inline void insert(int c, int id) {
	int p = last;
	while (s[id - len[p] - 1] != s[id]) p = link[p];
	if (!son[c][p]) {
		++sz;
		for (int i = 0; i < 26; i++) son[i][sz] = 0;
		int k = link[p];
		len[sz] = len[p] + 2;
		while (s[id - len[k] - 1] != s[id]) k = link[k];
		link[sz] = son[c][k], son[c][p] = sz;
	}
	last = son[c][p];
	endpos[son[c][p]]++;
}
void dfs(int u) {
//	printf("%d\n", u);
	if (u != 0) {
		tong[len[u]] = tong[len[u] / 2] + 1;
		// printf("%d %d %d\n", u, tong[len[u]], endpos[u]);
		ans += (long long)endpos[u] * tong[len[u]];
	}
	for (int i = head[u]; i; i = nxt[i]) {
		dfs(to[i]);
	}
	if (u != 0) tong[len[u]] = 0;
}
int main() {
	// freopen("C:\\Users\\Administrator\\Desktop\\FreadIn.txt", "r", stdin);
	log[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		log[i] = log[i >> 1] + 1;
	}
	int t = read();
	while (t--) {
		char ch;
		int n = 0;
		while ((ch = gc()) < 'a') {
			if (ch == -1) return 0;
		} s[++n] = ch;
		while ((ch = gc()) >= 'a') s[++n] = ch;
		sz = 1;
		last = 0;
		len[1] = -1;
		len[0] = 0;
		link[0] = 1;
		link[1] = -1;
		for (int i = 0; i < 26; i++) {
			son[i][0] = son[i][1] = 0;
		}
		for (int i = 1; i <= n; i++) {
			insert(s[i] - 'a', i);
		}
		// for (int i = 0; i <= sz; i++) {
		// 	for (int j = 0; j < 26; j++) {
		// 		if (son[j][i]) {
		// 			printf("%d %d %c\n", i, son[j][i], j + 'a');
		// 		}
		// 	}
		// 	if (i != 1) printf("%d %d _\n", link[i], i);
		// }
		for (int i = sz; i > 1; i--) {
			endpos[link[i]] += endpos[i];
			add(link[i], i);
		}
		dfs(0);
		printf("%lld\n", ans);
		ans = 0;
		for (int i = 0; i <= sz; i++) {
			head[i] = 0;
			endpos[i] = 0;
		}
		tot = 0;
	}
	return 0;
}