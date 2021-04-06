#include <bits/stdc++.h>
#define PB push_back
using namespace std;
const int N = 2010;
const int md = 998244353;
vector<int> g[N];
int n, f[N][N][3], mem[3], ans, siz[N];

void SUM(int &x, int y){
    x += y;
    if (x >= md)
        x -= md;
}

int sum(int x, int y){
    x += y;
    if (x >= md)
        x -= md;
    return x;
}

int mult(int x, int y) { return (1ll * x * y) % md; }

int binpow(int x, int po){
    int res = 1;

    while (po > 0){
        if (po & 1)
            res = mult(res, x);
        x = mult(x, x);
        po >>= 1;
    }
    return res;
}

void dfs(int v, int p){
    f[v][0][0] = 1;
    f[v][0][1] = 1;
    f[v][1][2] = 1;

    siz[v] = 1;

    for (int u : g[v]){
        if (u == p) continue;

        dfs(u, v);

        for (int old = siz[v]; old >= 0; old--)
        for (int nw = siz[u]; nw >= 0; nw--){
            mem[0] = f[v][old][0];
            mem[1] = f[v][old][1];
            mem[2] = f[v][old][2];

            if (nw > 0) {
                SUM(f[v][old + nw][0], mult(mem[0], f[u][nw][0]));
                SUM(f[v][old + nw][0], mult(mem[0], f[u][nw][2]));

                SUM(f[v][old + nw][1], mult(mem[1], f[u][nw][0]));
                SUM(f[v][old + nw][1], mult(mem[1], f[u][nw][2]));

                SUM(f[v][old + nw][2], mult(mem[2], f[u][nw][0]));
                SUM(f[v][old + nw][2], mult(mem[2], f[u][nw][2]));
            }


            SUM(f[v][old + nw][1], mult(mem[0], f[u][nw][1]));
            SUM(f[v][old + nw + 1][2], mult(mem[1], f[u][nw][1]));
        }

        siz[v] += siz[u];
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

#ifdef _LOCAL
    freopen("in.txt","r",stdin);
#endif // _LOCAL

    cin >> n;

    for (int i = 1; i < n; i++){
        int x, y; cin >> x >> y;
        x--; y--;

        g[x].PB(y);
        g[y].PB(x);
    }

    dfs(0, -1);

    int fact = 1, cnst = (n * (n + 1)) / 2;

    for (int k = 1; k <= n; k++){
        fact = mult(fact, k);

        int cur = mult(fact, sum(f[0][k][0], f[0][k][2]));

        cur = mult(cur, binpow(binpow(cnst, md - 2), k));

        SUM(ans, cur);
    }

    cout << ans;

    return 0;
}
