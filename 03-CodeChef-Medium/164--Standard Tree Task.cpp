#include <bits/stdc++.h>
#define sz(x) ((int)x.size())
#define PB push_back
using namespace std;
const int PW = (1 << 11);
const int N = 75;
const int K = 11;
const int md = int(1e9) + 7;
vector<int> g[N];
bool mrk[N];
int n, res, primes[11] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
int ans[N][N][PW], siz[N], fact[N], f[N][N][PW];
bool ok[N][PW];

int sum(int x, int y){
    x += y;
    if (x >= md)
        x -= md;
    return x;
}

void SUM(int &x, int y){
    x += y;
    if (x >= md)
        x -= md;
}

int mult(int x, int y) { return (1ll * x * y) % md; }

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

#ifdef _LOCAL
    freopen("in.txt","r",stdin);
#endif // _LOCAL

    cin >> n;

    for (int i = 1; i < n; i++){
        int p; cin >> p;
        p--;

        g[p].PB(i);
    }

    for (int i = 2; i <= n; i++)
    for (int j = 0; j < K; j++)
        if (i % primes[j] == 0)
            fact[i] |= (1 << j);

    for (int i = 0; i <= n; i++)
    for (int msk = 0; msk < PW; msk++)
        if ((fact[i] & msk) == 0)
            ok[i][msk] = 1;

    for (int v = n - 1; v >= 0; v--){
        f[v][0][0] = 1;
        f[v][1][0] = 1;

        siz[v] = 1;

        for (int u : g[v]){
            for (int old = siz[v]; old >= 0; old--)
            for (int omk = 0; omk < PW; omk++){
                if (f[v][old][omk] == 0) continue;

                int base = ((PW - 1) ^ omk);

                for (int nw = 1; nw <= siz[u]; nw++) {
                    if (!ok[nw][omk]) continue;

                    for (int mk = base; ; (mk = (mk - 1) & base)){
                        if (ans[u][nw][mk] == 0) {
                            if (mk == 0) break;
                            continue;
                        }

                        SUM(f[v][old + nw][omk | mk], mult(f[v][old][omk], ans[u][nw][mk]));

                        if (mk == 0) break;
                    }
                }
            }

            siz[v] += siz[u];
        }

        for (int cnt = 0; cnt <= siz[v]; cnt++)
        for (int msk = 0; msk < PW; msk++)
            SUM(ans[v][cnt][msk | fact[cnt]], f[v][cnt][msk]);
    }

    for (int cnt = 0; cnt <= n; cnt++)
    for (int msk = 0; msk < PW; msk++)
        res = sum(res, ans[0][cnt][msk]);

    cout << res;

    return 0;
}
