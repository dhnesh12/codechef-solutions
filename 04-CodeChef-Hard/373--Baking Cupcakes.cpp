/**
 * @author Macesuted
 * @date 2021-04-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <bits/stdc++.h>
using namespace std;

namespace io {

#define SIZE (1 << 20)

char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55];
int f, qr;

inline void flush(void) {
    fwrite(obuf, 1, oS - obuf, stdout);
    oS = obuf;
    return;
}

inline char getch(void) { return (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++); }
inline void putch(char x) {
    *oS++ = x;
    if (oS == oT) flush();
    return;
}

void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (register int i = begin; i < end; i++) putch(str[i]);
    return;
}

template <typename T>
inline T read() {
    register T x = 0;
    for (f = 1, c = getch(); c < '0' || c > '9'; c = getch())
        if (c == '-') f = -1;
    for (x = 0; c <= '9' && c >= '0'; c = getch()) x = x * 10 + (c & 15);
    x *= f;
    return x;
}
template <typename T>
inline void write(const T &t) {
    register T x = t;
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    while (x) qu[++qr] = x % 10 + '0', x /= 10;
    while (qr) putch(qu[qr--]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace io
using io::getch;
using io::putch;
using io::putstr;
using io::read;
using io::write;

#define maxn 20005

typedef pair<int, int> pii;

pii graph[maxn];
int n, m, g;
bool vis[maxn];

bool dfs(int cnt, int tot) {
    if (tot < g) return false;
    if (cnt == m + 1) return tot >= g;
    if (vis[graph[cnt].first] || vis[graph[cnt].second]) return dfs(cnt + 1, tot);
    vis[graph[cnt].first] = true;
    if (dfs(cnt + 1, tot - 1)) return true;
    vis[graph[cnt].first] = false;
    vis[graph[cnt].second] = true;
    if (dfs(cnt + 1, tot - 1)) return true;
    vis[graph[cnt].second] = false;
    return false;
}

int main() {
    int T = read<int>();
    while (T--) {
        n = read<int>(), m = read<int>(), g = read<int>();
        for (register int i = 1; i <= m; i++) graph[i].first = read<int>(), graph[i].second = read<int>();
        memset(vis, 0, sizeof(vis));
        putstr(dfs(1, n) ? "Possible" : "Impossible"), putch('\n');
    }
    return 0;
}