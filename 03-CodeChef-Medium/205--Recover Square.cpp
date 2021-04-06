#include <bits/stdc++.h>
using namespace std;
#ifndef _LOCAL
//#pragma GCC optimize("O3,Ofast")
#else
#pragma GCC optimize("O0")
#endif
//template<typename t> inline void umin(t &a, const t b) {a = min(a, b);}
//template<typename t> inline void umax(t &a, const t b) {a = max(a, b);}
typedef pair<int, int> pii;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vv;
#define ft first
#define sd second
#define PB push_back
#define sz(x) x.size()
#define all(f) (f).begin(), (f).end()
#define i2 array<int,2>
const int md = int(1e9) + 7;
const int N = 210;
const int NN = N * N;
const int M = 1000100;
const int oo = 2e9;
vector<int> g[NN], gr[NN], inds;
vector<i2> vc[N + N];
int n, m, nn, a[N][N], tt = 0, mrk[NN], deg[NN];
i2 loc[NN];
int per[NN];
bool bad;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#ifndef _LOCAL
//    freopen("fcolor.in", "r", stdin);
//    freopen("fcolor.out", "w", stdout);
#else
    freopen("in.txt","r",stdin);
#endif

    int qq; cin >> qq;

    for (; qq--; ){
        cin >> n >> m;

        nn = n * n;

        for (int i = 0; i < n + n + 1; i++)
            vc[i].clear();

        for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            a[i][j] = -1;
            vc[i + j].PB({i, j});
        }

        for (int i = 0; i < nn; i++) {
            g[i].clear();
            gr[i].clear();
            loc[i] = {-1, -1};
        }

        for (int i = 0; i < m; i++){
            int x, y; cin >> x >> y; x--; y--;

            g[x].PB(y);
            g[y].PB(x);

            gr[x].PB(y);
            gr[y].PB(x);
        }

        bad = 0;

        if (n == 1){
            cout << "1\n";
            continue;
        }

        if (n == 2){
            if (m == 6){
                cout << "1 2\n3 4\n";
            } else cout << "-1\n";
            continue;
        }

        bool was = 0;

        for (int i = 0; i < nn; i++){
            if (sz(g[i]) < 5 || sz(g[i]) > 12){
                bad = 1;
                break;
            }

        }

        for (int i = 0; i < nn; i++){
            if (sz(g[i]) > 5) continue;

            tt++;

            mrk[i] = tt;
            deg[i] = 0;

            for (int u : g[i]) {
                mrk[u] = tt;
                deg[u] = 0;
            }

            for (int u : g[i]){
                for (int oth : g[u])
                    if (mrk[oth] == tt)
                        deg[u]++;
            }

            int c5 = 0, c4 = 0, c3 = 0, bdsm = 0;

            for (int u : g[i]){
                if (deg[u] == 5) c5++; else
                if (deg[u] == 4) c4++; else
                if (deg[u] == 3) c3++; else bdsm++;
            }

            if (bdsm > 0 || c5 != 1 || c4 != 2 || c3 != 2)
                continue;

            int n1 = -1, n2 = -1;

            for (int u : g[i]) {
                if (deg[u] == 5) {
                    a[1][1] = u;
                    loc[u] = {1, 1};
                } else if (deg[u] == 4){
                    if (a[1][0] < 0) {
                        a[1][0] = u;
                        loc[u] = {1, 0};
                    } else {
                        a[0][1] = u;
                        loc[u] = {0, 1};
                    }
                } else {
                    if (n1 < 0)
                        n1 = u;
                    else n2 = u;
                }
            }

            a[0][0] = i;
            loc[i] = {0, 0};

            int id = -1;

            for (int u : g[n1])
                if (mrk[u] == tt && deg[u] == 4){
                    i2 now = {1, 0};

                    id = u;

                    if (loc[u] == now){
                        a[2][0] = n1;
                        loc[n1] = {2, 0};

                        a[0][2] = n2;
                        loc[n2] = {0, 2};
                    } else {
                        a[2][0] = n2;
                        loc[n2] = {2, 0};

                        a[0][2] = n1;
                        loc[n1] = {0, 2};
                    }

                    break;
                }

            if (id < 0){
                bad = 1;
                break;
            }

            was = 1;

            break;
        }

        if (bad || !was){
            cout << "-1\n";
            continue;
        }

        int digs = n + n + 1;

        for (int id = 1; id < digs && !bad; id++)
        for (i2 nm : vc[id]) {
            int i = nm[0], j = nm[1], vl = a[i][j];

            if (i + 2 >= n || j + 2 >= n) continue;

            //cerr << i << " " << j << " " << sz(g[vl]) << '\n';

            for (int it = 0; it < sz(g[vl]); it++){
                int u = g[vl][it];

                //cerr << u << '\n';

                if (loc[u][0] >= 0 && (loc[u][0] < i || loc[u][1] < j)){
                    swap(g[vl].back(), g[vl][it]);
                    g[vl].pop_back();
                    it--;
                    continue;
                }
            }

            if (sz(g[vl]) != 5){
                bad = 1;
                break;
            }

            tt++;

            mrk[vl] = tt;
            deg[vl] = 0;

            for (int u : g[vl]) {
                mrk[u] = tt;
                deg[u] = 0;
            }

            for (int u : g[vl]){
                //cerr << u << " " << deg[u] << '\n';
                for (int oth : g[u])
                    if (mrk[oth] == tt)
                        deg[u]++;

                //cerr << u << " " << deg[u] << '\n';
            }
            //cerr << '\n';

            int c5 = 0, c4 = 0, c3 = 0, bdsm = 0;

            for (int u : g[vl]){
                //cerr << u << '\n';
                if (deg[u] == 5) c5++; else
                if (deg[u] == 4) c4++; else
                if (deg[u] == 3) c3++; else bdsm++;
            }

            if (bdsm > 0 || c5 != 1 || c4 != 2 || c3 != 2){
                bad = 1;
                break;
            }

            int n1 = -1, n2 = -1;

            for (int u : g[vl]) {
                if (deg[u] == 5) {
                    if (a[i + 1][j + 1] >= 0 && a[i + 1][j + 1] != u){
                        bad = 1;
                        break;
                    }

                    a[i + 1][j + 1] = u;
                    loc[u] = {i + 1, j + 1};
                } else if (deg[u] == 4){
                    if (a[i + 1][j] != u && a[i][j + 1] != u){
                        bad = 1;
                        break;
                    }
                } else if (deg[u] == 3) {
                    if (n1 < 0)
                        n1 = u;
                    else n2 = u;
                }
            }

            int id = -1;

            for (int u : g[n1])
                if (mrk[u] == tt && deg[u] == 4){
                    i2 now = {i + 1, j + 0};

                    id = u;

                    if (loc[u] == now){
                        a[i + 2][j + 0] = n1;
                        loc[n1] = {i + 2, j + 0};

                        a[i + 0][j + 2] = n2;
                        loc[n2] = {i + 0, j + 2};
                    } else {
                        a[i + 2][j + 0] = n2;
                        loc[n2] = {i + 2, j + 0};

                        a[i + 0][j + 2] = n1;
                        loc[n1] = {i + 0, j + 2};
                    }

                    break;
                }

            if (id < 0){
                bad = 1;
                break;
            }
        }

        if (bad){
            cout << "-1\n";
            continue;
        }

        int ptr = 0;

        for (int i = 0; i < nn; i++) {
            sort(all(gr[i]));

//            //cerr << i << " " << loc[i][0] << " " << loc[i][1] << '\n';

            if (loc[i][0] < 0){
                per[ptr++] = i;
            }
        }

        assert(ptr == 3);

        sort(per, per + 3);

        was = 0;

        do {
            a[n - 1][n - 1] = per[0];
            a[n - 2][n - 1] = per[1];
            a[n - 1][n - 2] = per[2];

            bool ok = 1;

            for (int i = 0; i < n && ok; i++)
            for (int j = 0; j < n && ok; j++){
                inds.clear();

                for (int x = -2; x <= 2; x++)
                for (int y = -2; y <= 2; y++)
                    if (abs(x) + abs(y) <= 2){
                        int cx = i + x, cy = j + y;

                        if (cx == i && cy == j)
                            continue;

                        if (cx < 0 || cx >= n || cy < 0 || cy >= n)
                            continue;

                        inds.PB(a[cx][cy]);
                    }

                sort(all(inds));

//                //cerr << sz(inds) << '\n';

                int vl = a[i][j];

                if (sz(inds) != sz(gr[vl])){
                    ok = 0;
                    break;
                }

                for (int it = 0; it < sz(inds); it++)
                    if (gr[vl][it] != inds[it]){
                        ok = 0;
                        break;
                    }
            }

            if (ok) {
                for (int i = 0; i < n; i++){
                    for (int j = 0; j < n; j++)
                        cout << a[i][j] + 1 << " ";
                    cout << '\n';
                }

                was = 1;

                break;
            }

        } while (next_permutation(per, per + 3));

        if (!was){
            cout << "-1\n";
        }

        // insert all bad cases
        // chech that in resulting graph all edges the same
    }

    return 0;
}
