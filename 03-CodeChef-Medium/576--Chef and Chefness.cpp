/// wa 

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
//#pragma comment(linker, "/STACK:36777216")

#include<bits/stdc++.h>

#define x first
#define y second
#define pb push_back
#define sz(x) (int) x.size()
#define all(z) (z).begin(), (z).end()
 
using namespace std;

using ll = long long;
using pii = pair<int, int>;                                   

const int MOD = 1e9 + 7; 
const int INF = 0x3f3f3f3f;
  
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void fin() {
#ifdef AM
    freopen(".in", "r", stdin);
#endif        
}                   

const bool flag = 1;

const int N = 33;

inline void relax(int& x, int y) {
    x = min(x, y);
}

int dp[2][N][N][N][N+1];

void ma1n() {
    int n, k;
    cin >> n >> k;
    for (int c = 0; c < N; ++c) {
        for (int c2 = 0; c2 < N; ++c2) {
            for (int c3 = 0; c3 < N; ++c3) {
                for (int c4 = 0; c4 <= k; ++c4) {
                    dp[0][c][c2][c3][c4] = INF;
                }
            }
        }
    }
    dp[0][0][0][0][0] = 0;
    char s;  
    for (int i = 0; i < n; ++i) {
        bool j = i&1;
        for (int c = 0; c < N; ++c) {
            for (int c2 = 0; c2 < N; ++c2) {
                for (int c3 = 0; c3 < N; ++c3) {
                    for (int c4 = 0; c4 <= k; ++c4) {
                        dp[j^1][c][c2][c3][c4] = INF;
                    }
                }
            }
        }
        cin >> s;
        for (int c = 0; c < N; ++c) {
            for (int c2 = 0; c2 < N; ++c2) {
                for (int c3 = 0; c3 < N; ++c3) {
                    for (int c4 = 0; c4 <= k; ++c4) {
                        relax(dp[j^1][c][c2][c3][c4], dp[j][c][c2][c3][c4]+1);
                        if (s == 'c') {
                            relax(dp[j^1][min(N-1, c+1)][c2][c3][c4], dp[j][c][c2][c3][c4]);  
                        } else if (s == 'h') {
                            relax(dp[j^1][c][min(N-1, c2+c)][c3][c4], dp[j][c][c2][c3][c4]);
                        } else if (s == 'e') {
                            relax(dp[j^1][c][c2][min(N-1, c3+c2)][c4], dp[j][c][c2][c3][c4]);
                        } else if (s == 'f') {
                            relax(dp[j^1][c][c2][c3][min(k+1, c4+c3)], dp[j][c][c2][c3][c4]);
                        }
                    }                                      
                }
            }
        }
    }
    int ans = INF;
    for (int che = 0; che < N; ++che) {
        for (int ch = 0; ch < N; ++ch) {
            for (int c = 0; c < N; ++c) {
                relax(ans, dp[n&1][c][ch][che][k]);       
            }
        }
    }
    cout << (ans < INF ? ans : -1) << "\n";
} 

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr), fin();
    int ts = 1;
    if (flag) {
        cin >> ts;
    }
    while (ts--) {
        ma1n(); 
    }
    return 0;
}
