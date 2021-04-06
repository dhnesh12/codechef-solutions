# include <bits/stdc++.h>
using namespace std;
# define FOR(i, a, b) for (int i = a; i <= b; ++i)
# define FDR(i, a, b) for (int i = a; i >= b; --i)
# define mp make_pair
# define pb push_back
# define lch p<<1, l, mid
# define rch p<<1|1, mid + 1, r
# define mem(a, b) memset(a, b, sizeof(a))
# define fi first
# define se second
# define MOD 163577857
# define INF 1000000000
typedef long long i64;
typedef vector<int> VI;
typedef pair<int, int> PII;
const int N = 25;
 
int G[N][N], per[N*N], vis[N][N], f[N][N];
queue<PII > que;
int n, m;
int ps[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
string res, tmp;
 
void Init_G() {
    int pos = 0;
    FDR(i, n, 2) FDR(j, m, 1){
        res += "P";
        FOR(k, 3, i) res += "S";
        FOR(k, 2, j) res += "E";
        res += "US";
        FOR(k, 2, j) res += "W";
        FOR(k, 3, i) res += "N";
        G[i][j] = per[++pos];
    }
    FDR(j, m, 2) {
        res += "P";
        FOR(k, 3, j) res += "E";
        res += "UE";
        FOR(k, 3, j) res += "W";
        G[1][j] = per[++pos];
    }
}
int check(int x, int y, int i) {
    FOR(j, 0, 3) {
        int dx = x + ps[j][0], dy = y + ps[j][1];
        if (dx < 1 || dy < 1 || dx > n || dy > m || G[dx][dy] != i) continue;
        return j;
    }
}
void debug() {
    FOR(i, 1, n) {
        FOR(j, 1, m) printf("%d ", G[i][j]);
        puts("");
    }
    cout << res.size() << endl;
    cout <<  res << endl;
}
void BFS(int x, int y) {
    memset(vis, -1, sizeof(vis)); memset(f, -1, sizeof(f));
    que.push(mp(x, y)); vis[x][y] = 0;
    PII temp;
    while (!que.empty()) {
        temp = que.front(); que.pop();
        FOR(i, 0, 3) {
            int dx = temp.fi + ps[i][0], dy = temp.se + ps[i][1];
            if (dx < 1 || dy < 1 || dx > n || dy > m || G[dx][dy] || vis[dx][dy] != -1) continue;
            vis[dx][dy] = vis[temp.fi][temp.se] + 1; que.push(mp(dx, dy)); f[dx][dy] = i;
        }
    }
}
int main ()
{
    int t, sum;
    scanf("%d", &t);
    while (t--) {
        res.clear();
        scanf("%d %d", &n, &m); sum = m * n - 1;
        FOR(i, 1, sum) scanf("%d", per + i);
        Init_G();
        FOR(i, 1, sum) {
            tmp.clear();
            int px, py;
            FOR(j, 1, n) FOR(k, 1, m) if (G[j][k] == i) {px = j; py = k; break;}
            FOR(j, 2, px) {
                if (G[j][1]) res += "LSSUN";
                else res += "S";
                swap(G[j - 1][1], G[j][1]);
            }
            FOR(j, 2, py) {
                if (G[px][j]) res += "LEEUW";
                else res += "E";
                swap(G[px][j - 1], G[px][j]);
            }
            res.pop_back(); res.pop_back();
            BFS(px, py);
            FOR(j, 1, n) FOR(k, 1, m) if (G[j][k] == i) {G[j][k] = 0; break;}
            int mx = px, my = py, ma = px + py;
            FOR(j, 1, n) FOR(k, 1, m) {
                if (vis[j][k] == -1 || j + k > ma) continue;
                if (k + j < ma) ma = k + j, mx = j, my = k;
                else if (vis[mx][my] > vis[j][k]) mx = j, my = k;
            }
            int nowx = mx, nowy = my;
            while (nowx != px || nowy != py) {
                if (f[nowx][nowy] == 0) {
                    --nowy;
                    tmp += "E";
                }
                else if (f[nowx][nowy] == 1) {
                    ++nowy;
                    tmp += "W";
                }
                else if (f[nowx][nowy] == 2) {
                    --nowx;
                    tmp += "S";
                }
                else {
                    ++nowx;
                    tmp += "N";
                }
            }
            reverse(tmp.begin(), tmp.end());
            res += tmp;
            if (mx == 1 && my == 1) {
                res += "D";
                continue;
            }
            FOR(j, 0, 3) {
                int dx = mx + ps[j][0], dy = my + ps[j][1];
                if (dx >= 1 && dx <= n && dy >= 1 && dy <= m && G[dx][dy] == 0) {
                    if (j == 0) res += "UE";
                    else if (j == 1) res += "UW";
                    else if (j == 2) res += "US";
                    else res += "UN";
                    G[dx][dy] = i;
                    break;
                }
            }
            nowx = mx, nowy = my;
            while (1) {
                int tmp = check(nowx, nowy, i);
                if (nowx + ps[tmp][0] == 1 && nowy + ps[tmp][1] == 1) {
                    if (tmp == 0) res += "LEE";
                    else if (tmp == 1) res += "LWW";
                    else if (tmp == 2) res += "LSS";
                    else res += "LNN";
                    res += "D";
                    G[1][1] = 0;
                    break;
                }
                if (tmp == 0) {
                    if (nowx != 1) {
                        if (G[nowx - 1][nowy]) res += "LNNUS";
                        else res += "N";
                        swap(G[nowx - 1][nowy], G[nowx][nowy]);
                        if (G[nowx - 1][nowy + 1]) res += "LEEUW";
                        else res += "E";
                        swap(G[nowx - 1][nowy + 1], G[nowx - 1][nowy]);
                        res += "LSSUN";
                        swap(G[nowx - 1][nowy + 1], G[nowx][nowy + 1]);
                    }
                    else {
                        if (G[nowx + 1][nowy]) res += "LSSUN";
                        else res += "S";
                        swap(G[nowx + 1][nowy], G[nowx][nowy]);
                        if (G[nowx + 1][nowy + 1]) res += "LEEUW";
                        else res += "E";
                        swap(G[nowx + 1][nowy + 1], G[nowx + 1][nowy]);
                        res += "LNNUS";
                        swap(G[nowx + 1][nowy + 1], G[nowx][nowy + 1]);
                    }
                }
                else if (tmp == 1){
                    if (nowx != 1) {
                        if (G[nowx - 1][nowy]) res += "LNNUS";
                        else res += "N";
                        swap(G[nowx - 1][nowy], G[nowx][nowy]);
                        if (G[nowx - 1][nowy - 1]) res += "LWWUE";
                        else res += "W";
                        swap(G[nowx - 1][nowy - 1], G[nowx - 1][nowy]);
                        res += "LSSUN";
                        swap(G[nowx - 1][nowy - 1], G[nowx][nowy - 1]);
                    }
                    else {
                        if (G[nowx + 1][nowy]) res += "LSSUN";
                        else res += "S";
                        swap(G[nowx + 1][nowy], G[nowx][nowy]);
                        if (G[nowx + 1][nowy - 1]) res += "LWWUE";
                        else res += "W";
                        swap(G[nowx + 1][nowy - 1], G[nowx + 1][nowy]);
                        res += "LNNUS";
                        swap(G[nowx + 1][nowy - 1], G[nowx][nowy - 1]);
                    }
                }
                else if (tmp == 2) {
                    if (nowy != 1) {
                        if (G[nowx][nowy - 1]) res += "LWWUE";
                        else res += "W";
                        swap(G[nowx][nowy - 1], G[nowx][nowy]);
                        if (G[nowx + 1][nowy - 1]) res += "LSSUN";
                        else res += "S";
                        swap(G[nowx + 1][nowy - 1], G[nowx][nowy - 1]);
                        res += "LEEUW";
                        swap(G[nowx + 1][nowy], G[nowx + 1][nowy - 1]);
                    }
                    else {
                        if (G[nowx][nowy + 1]) res += "LEEUW";
                        else res += "E";
                        swap(G[nowx][nowy + 1], G[nowx][nowy]);
                        if (G[nowx + 1][nowy + 1]) res += "LSSUN";
                        else res += "S";
                        swap(G[nowx + 1][nowy + 1], G[nowx][nowy + 1]);
                        res += "LWWUE";
                        swap(G[nowx + 1][nowy], G[nowx + 1][nowy + 1]);
                    }
                }
                else {
                    if (nowy != 1) {
                        if (G[nowx][nowy - 1]) res += "LWWUE";
                        else res += "W";
                        swap(G[nowx][nowy - 1], G[nowx][nowy]);
                        if (G[nowx - 1][nowy - 1]) res += "LNNUS";
                        else res += "N";
                        swap(G[nowx - 1][nowy - 1], G[nowx][nowy - 1]);
                        res += "LEEUW";
                        swap(G[nowx - 1][nowy], G[nowx - 1][nowy - 1]);
                    }
                    else {
                        if (G[nowx][nowy + 1]) res += "LEEUW";
                        else res += "E";
                        swap(G[nowx][nowy + 1], G[nowx][nowy]);
                        if (G[nowx - 1][nowy + 1]) res += "LNNUS";
                        else res += "N";
                        swap(G[nowx - 1][nowy + 1], G[nowx][nowy + 1]);
                        res += "LWWUE";
                        swap(G[nowx - 1][nowy], G[nowx - 1][nowy + 1]);
                    }
                }
                nowx += ps[tmp][0]; nowy += ps[tmp][1];
            }
        }
        cout << res<< endl;
    }
    return 0;
} 