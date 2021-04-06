#include <cstdio>
#include <cstring>

#ifdef _WIN32
#define LLFORMAT "I64"
#else
#define LLFORMAT "ll"
#endif

const int MAXN = 35;
const int MAXM = 35;
const int MAXS = 905;
const int MAXQ = 900005;
const int INF = 0x3f3f3f3f;
const int DR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct State {
    int n, m;
    const int (*aa)[2];
    int *ans;
    int snake[MAXS][2];
    int sqb, sqe;
    bool vis[MAXN][MAXM];
    int ansn;
    const int (*foodnow)[2];

    State() {}
    State(int n_, int m_, int x0, int y0, const int (*aa_)[2], int *ans_) : n(n_), m(m_), aa(aa_), ans(ans_)
    {
        sqb = 0;
        sqe = 1;
        snake[0][0] = x0;
        snake[0][1] = y0;
        memset(vis, 0, sizeof(vis));
        vis[x0][y0] = true;
        ansn = 0;
        foodnow = aa;
    }

    bool try_go(int dir);
    bool go_next();
    bool try_down();
    void solve();
};

inline bool State::try_go(int dir)
{
    int ex = (snake[(sqe + MAXS - 1) % MAXS][0] + DR[dir][0] + n) % n;
    int ey = (snake[(sqe + MAXS - 1) % MAXS][1] + DR[dir][1] + m) % m;
    int bx = snake[sqb][0];
    int by = snake[sqb][1];
    bool eatfood = (ex == (*foodnow)[0] && ey == (*foodnow)[1]);
    if (vis[ex][ey] && (ex != bx || ey != by || eatfood)) {
        return false;
    }
    ans[ansn++] = dir;
    if (!eatfood) {
        vis[bx][by] = false;
        sqb++;
        if (sqb == MAXS) sqb = 0;
    } else {
        foodnow++;
    }
    snake[sqe][0] = ex;
    snake[sqe][1] = ey;
    vis[ex][ey] = true;
    sqe++;
    if (sqe == MAXS) sqe = 0;
    return true;
}

inline bool State::go_next()
{
    int cx = snake[(sqe + MAXS - 1) % MAXS][0];
    int cy = snake[(sqe + MAXS - 1) % MAXS][1];
    int dy = (cx % 2 ? -1 : 1);
    int dir;
    if (cy + dy < 0 || cy + dy >= m) {
        dir = 1;
    } else if (dy == -1) {
        dir = 2;
    } else {
        dir = 3;
    }
    return try_go(dir);
}

bool State::try_down()
{
    int cy = snake[(sqe + MAXS - 1) % MAXS][1];
    int nx = (*foodnow)[0];
    int ny = (*foodnow)[1];
    if ((cy == ny ? 0 : (cy < ny ? 1 : -1)) * (nx % 2 ? -1 : 1) == -1) {
        return false;
    }
    State tmp = *this;
    while (tmp.snake[(tmp.sqe + MAXS - 1) % MAXS][0] != nx) {
        if (!tmp.try_go(1)) {
            return false;
        }
    }
    while (tmp.foodnow == foodnow) {
        if (!tmp.go_next()) {
            return false;
        }
    }
    State tmp2 = tmp;
    for (int i = tmp.sqb; i != tmp.sqe; i = (i + 1) % MAXS) {
        if (!tmp2.go_next()) {
            return false;
        }
        if (tmp2.foodnow == aa + n * m - 1) {
            break;
        }
    }
    *this = tmp;
    return true;
}

void State::solve()
{
    while (foodnow < aa + n * m - 1) {
        if (!try_down()) {
            go_next();
        }
    }
}

struct InState {
    int n, m;
    int a[MAXS][2];
};

struct OutState {
    int ansn;
    int ans[MAXQ];
};

InState in;
OutState out;

void input()
{
    scanf("%d%d", &in.n, &in.m);
    for (int i = 0; i < in.n * in.m - 1; i++) {
        scanf("%d%d", &in.a[i][0], &in.a[i][1]);
    }
}

void solve()
{
    int ansn = INF;
    static int ans[MAXQ];
    for (int toswap = 0; toswap <= 1; toswap++) {
        int nn = (toswap ? in.m : in.n);
        int mm = (toswap ? in.n : in.m);
        if (nn % 2 == 0) {
            for (int toflipx = 0; toflipx <= 1; toflipx++) {
                for (int toflipy = 0; toflipy <= 1; toflipy++) {
                    int x0 = (toflipx ? nn - 1 : 0);
                    int y0 = (toflipy ? mm - 1 : 0);
                    int aa[MAXS][2];
                    memcpy(aa, in.a, (nn * mm - 1) * sizeof(*aa));
                    for (int i = 0; i < nn * mm - 1; i++) {
                        if (toswap) {
                            int t = aa[i][0];
                            aa[i][0] = aa[i][1];
                            aa[i][1] = t;
                        }
                        if (toflipx) {
                            aa[i][0] = nn - aa[i][0] - 1;
                        }
                        if (toflipy) {
                            aa[i][1] = mm - aa[i][1] - 1;
                        }
                    }
                    static int anstmp[MAXQ];
                    State ss(nn, mm, x0, y0, aa, anstmp);
                    ss.solve();
                    if (ss.ansn < ansn) {
                        ansn = ss.ansn;
                        for (int i = 0; i < ansn; i++) {
                            int x = anstmp[i];
                            if (toflipx && x < 2) {
                                x ^= 1;
                            }
                            if (toflipy && x >= 2) {
                                x ^= 1;
                            }
                            if (toswap) {
                                x ^= 2;
                            }
                            ans[i] = x;
                        }
                    }
                }
            }
        }
    }
    out.ansn = ansn;
    memcpy(out.ans, ans, ansn * sizeof(*ans));
}

void output()
{
    printf("%d\n", out.ansn);
    for (int i = 0; i < out.ansn; i++) {
        printf("%d\n", out.ans[i]);
    }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("SEASNAKE.in", "r", stdin);
    freopen("SEASNAKE.out", "w", stdout);
#endif

    input();
    solve();
    output();

#ifndef ONLINE_JUDGE
    fclose(stdin); fclose(stdout);
#endif
    return 0;
}
