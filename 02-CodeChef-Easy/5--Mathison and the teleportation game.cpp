#include <bits/stdc++.h>

#define index(i, n) for (long long i = 0; i < n; i++)
#define fast_io std::ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL)
#define print(x) cout << (x) << '\n'

using namespace std;

int t, n, m, k, sx, sy, r, ans, c;
vector<pair<int, int>> telpairs(9);
int pres[] = { 1, 1, -1, 1, 1, -1, -1, -1 };

int solve(int sx, int sy, int mask, vector<vector<vector<int>>> dp, vector<vector<int>> board)
{
        if (dp[sx][sy][mask] != -1)
                return dp[sx][sy][mask];

        int ans = 0;
        index(tp, n)
        {
                if ((mask & (1 << tp)) == 0) {
                        for (int pre = 0; pre < 8; pre += 2) {
                                int nx = sx + telpairs[tp].first * pres[pre];
                                int ny = sy + telpairs[tp].second * pres[pre + 1];
                                if (0 <= nx && nx < r && 0 <= ny && ny < c)
                                        ans = max(ans, solve(nx, ny, mask | (1 << tp), dp, board));
                        }
                }
        }
        dp[sx][sy][mask] = ans + board[sx][sy];
        return dp[sx][sy][mask];
}

int main()
{
        fast_io;
        cin >> t;
        while (t--) {
                cin >> r >> c >> n >> sx >> sy;
                vector<vector<int>> board(r, vector<int>(c));
                vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(1 << n, -1)));
                index(i, n) cin >> telpairs[i].first;
                index(i, n) cin >> telpairs[i].second;
                index(i, r) index(j, c) cin >> board[i][j];
                print(solve(sx, sy, 0, dp, board));
        }
        return 0;
}
