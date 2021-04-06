#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1e2 + 7;
struct edge {int t, w, n;} e[maxn * maxn];
int ecnt, h[maxn];
void addedge(int f, int t, int w){e[++ecnt] = (edge){t, w, h[f]};h[f] = ecnt;}
int a[maxn][maxn];
ll cnt[maxn];
int main(){int n, m; scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++ i){int u, v, w;scanf("%d%d%d", &u, &v, &w);addedge(u, v, w);addedge(v, u, w);}
    for (int i = 1; i <= n; ++i){for (int j = h[i]; j; j = e[j].n) {
            for (int k = h[e[j].t]; k; k = e[k].n){a[i][max(e[j].w, e[k].w)] ++;}}}
    for (int i = 1; i <= n; ++i){for (int j = 1; j <= 100; ++ j){
            for (int k = 1; k <= 100; ++ k){cnt[max(j, k)] += a[i][j] * a[i][k];}}}
    int q;scanf("%d", &q);while (q --){int x;scanf("%d", &x);printf("%lld\n", cnt[x]);}}