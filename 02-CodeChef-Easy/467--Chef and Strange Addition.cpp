#include "bits/stdc++.h"
using namespace std;

int32_t main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;
        bitset<32> a1(a);
        bitset<32> a2(b);
        bitset<32> c1(c);
        long long dp[32][32][32][2] = {0};
        for (int i = 0; i < 32; i++) {
            for (int x = 0; x < 32; x++) {
                for (int y = 0; y < 32; y++) {
                    if (i == 0) {
                        if (c1[i]) {
                            dp[i][1][0][0] = 1;
                            dp[i][0][1][0] = 1;
                        } else {
                            dp[i][1][1][1] = 1;
                            dp[i][0][0][0] = 1;
                        }
                    } else {
                        if (c1[i] == 1) {
                            if (x > 0) {
                                dp[i][x][y][0] += dp[i - 1][x - 1][y][0];
                            }
                            if (y > 0) {
                                dp[i][x][y][0] += dp[i - 1][x][y - 1][0];
                            }
                            if (x > 0 && y > 0) {
                                dp[i][x][y][1] += dp[i - 1][x - 1][y - 1][1];
                            }
                            dp[i][x][y][0] += dp[i - 1][x][y][1];
                        } else {
                            if (x > 0) {
                                dp[i][x][y][1] += dp[i - 1][x - 1][y][1];
                            }
                            if (y > 0) {
                                dp[i][x][y][1] += dp[i - 1][x][y - 1][1];
                            }
                            if (x > 0 && y > 0) {
                                dp[i][x][y][1] += dp[i - 1][x - 1][y - 1][0];
                            }
                            dp[i][x][y][0] += dp[i - 1][x][y][0];
                        }
                    }
                }
            }
        }
        cout << dp[31][(int)a1.count()][(int)a2.count()][0] << "\n";
    }
    return 0;
}