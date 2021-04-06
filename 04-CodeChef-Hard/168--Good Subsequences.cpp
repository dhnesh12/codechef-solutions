#include <bits/stdc++.h>
 
using namespace std;
 
#define MS(a, b) memset(a, b, sizeof(a))
#define REP(a, b, c) for (register int a = b, _n = c; a <= _n; ++a)
#define DREP(a, b, c) for (register int a = b, _n = c; a >= _n; --a)
#define FOR(a, b, c) for (register int a = b, _n = c; a < _n; ++a)
#define EREP(a, b) for (register int a = head[b]; a; a = edge[a].nxt)
 
inline int rd () {
    int x = 0; bool f = 0; char c = getchar();
    while (c < '0' && c != '-') c = getchar();
    if (c == '-') f = 1, c = getchar();
    while (c >= '0') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return f ? -x : x;
}

const int SIZE = 5005;
const int Mod = 998244353;

int n, X;
int a[SIZE];

int sum[SIZE], tmp[SIZE];

bool Check (int L, int R) {
    int mi = a[L], mx = a[L];
    REP (i, L, R) mi = min(mi, a[i]), mx = max(mx, a[i]);
    return mi == L && mx == R;
}

void _main () {
    n = rd(), X = rd();
    REP (i, 1, n) a[i] = rd();
    int ans = 0;
    REP (R, 1, n) {
        REP (i, 0, n) tmp[i] = 0;
        int Mi = a[R], Mx = a[R];
        DREP (L, R, 1) {
            Mi = min(Mi, a[L]), Mx = max(Mx, a[L]);
            if (Mx - Mi == R - L) {
                ans = (ans + sum[L]) % Mod;
                //y > L
                //R - y + 1 >= X;
                //L + 1 <= y <= R - X + 1;
                if (L + 1 <= R - X + 1) {
                    ++tmp[L + 1];
                    --tmp[R - X + 2];
                }
            }
        }
        REP (i, 1, n) {
            tmp[i] += tmp[i - 1];
            sum[i] = (sum[i] + tmp[i]) % Mod;
        }
    }
    printf ("%d\n", (ans * 2) % Mod);
}

int main () {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
#endif
    _main();
    return 0;
}
