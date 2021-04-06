#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX_N = 300;
const int LIM_T = 100;
const int MAXN = MAX_N * 2 * LIM_T ;
const int MAXE = MAXN * 5 ;
#define MEM(p, v) memset(p, v, sizeof(p))
#define SET(p) memset(p, -1, sizeof(p))

struct MCMF {
    int src, snk, nNode, nEdge;
    int fin[MAXN], pre[MAXN], dist[MAXN];
    int cap[MAXE], cost[MAXE], next[MAXE], to[MAXE], from[MAXE];

    MCMF(int _src, int _snk, int nodes) {
        SET(fin);
        nNode = nodes, nEdge = 0;
        src = _src, snk = _snk;
    }

    inline void addEdge(int u, int v, int _cap, int _cost) {
        from[nEdge] = u, to[nEdge] = v, cap[nEdge] = _cap, cost[nEdge] = _cost;
        next[nEdge] = fin[u], fin[u] = nEdge++;
        from[nEdge] = v, to[nEdge] = u, cap[nEdge] = 0, cost[nEdge] = -(_cost);
        next[nEdge] = fin[v], fin[v] = nEdge++;
    }

    bool bellman() {
        int iter, u, v, i;
        bool flag = true;
        MEM(dist, 0x7f);
        SET(pre);
        dist[src] = 0;
        for(iter = 1; iter < nNode && flag; iter++) {
            flag = false;
            for(u = 0; u < nNode; u++) {
                for(i = fin[u]; i >= 0; i = next[i]) {
                    v = to[i];
                    if(cap[i] && dist[v] > dist[u] + cost[i]) {
                        dist[v] = dist[u] + cost[i];
                        pre[v] = i;
                        flag = true;
                    }
                }
            }
        }
        return (dist[snk] < INF);
    }

    int mcmf(int &fcost) {
        int netflow, bot, u;
        netflow = fcost = 0;
        while(bellman()) {
            bot = INF;
            for(u = pre[snk]; u >= 0; u = pre[from[u]]) bot = min(bot, cap[u]);
            for(u = pre[snk]; u >= 0; u = pre[from[u]]) {
                cap[u] -= bot;
                cap[u^1] += bot;
                fcost += bot * cost[u];
            }
            netflow += bot;
        }
        return netflow;
    }
};

const int LIM_D = 4 ;
const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, 1, 0, -1};
const int LIM_N = 300;

int R, C, T, RCP ;
char mapa[LIM_N][LIM_N];
int maxCs[LIM_T][LIM_N][LIM_N] ;

inline bool isValid(const int r, const int c) {
    return 0 <= r && r < R && 0 <= c && c < C && mapa[r][c] != '#';
}

inline int toNum(const int r, const int c, const int t, const int s) {
    return ((RCP * t + r * C + c) << 1) + s ;
}

int main() {
    MCMF* fl;
    int ini, fin ;
    int Q ;

    scanf("%d%d%d%d", &R, &C, &Q, &T);
    RCP = R * C ;
    ini = RCP * (T + 1) * 2;
    fin = ini + 1 ;
    fl = new MCMF(ini, fin, fin+1);
    for(int i=0; i < R; i++)
        scanf("%s", mapa[i]);
    for(int i=0, x, y, p, q, h; i < Q; i++) {
        scanf("%d%d%d%d%d", &x, &y, &p, &q, &h);
        x--, y--;
        for(int j=p; j < q; j++) {
            maxCs[j][x][y] = max(maxCs[j][x][y], h);
        }
    }

    for(int i=0; i < R; i++) {
        for(int j=0; j < C; j++) {
            if(mapa[i][j] == '#') continue;
            if(mapa[i][j] == 'S')
                fl->addEdge(ini, toNum(i, j, 0, 0), 1, 0);
            fl->addEdge(toNum(i, j, T, 1), fin, 1, 0);
            fl->addEdge(toNum(i, j, T, 0), toNum(i, j, T, 1), 1, 0);
            for(int t=0; t < T; t++) {
                fl->addEdge(toNum(i, j, t, 0), toNum(i, j, t, 1), 1, 0);
                fl->addEdge(toNum(i, j, t, 1), toNum(i, j, t+1, 0), 1, -maxCs[t][i][j]);
            }
            for(int d=0, x, y; d < LIM_D; d++) {
                x = i + dr[d];
                y = j + dc[d];
                if(!isValid(x, y)) continue;
                for(int t=0; t < T; t++) {
                    fl->addEdge(toNum(i, j, t, 1), toNum(x, y, t+1, 0), 1, 0);
                }
            }
        }
    }



    // fl->setpi(ini);
    int cst ;
    fl->mcmf(cst);

    printf("%d\n", -cst);
}
