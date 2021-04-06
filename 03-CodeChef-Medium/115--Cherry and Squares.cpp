#include<vector>
#include<map>
#include<algorithm>
#include<set>
#include<iostream>
#include<string>
#include<set>
#include<queue>
#include<random>
#include<unordered_set>

using namespace std;

mt19937 rnd(51);

#pragma GCC optimize("Ofast")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,tune=native")

#define pb push_back
#define ld long double

const int N = 1e6 + 10, M = 600;
vector<int> lg(N);
int go[20][M][M];

void fill(){
    for (int i = 0; i < 20; i++){
        lg[(1 << i)] = i;
    }
    for (int i = 1; i < N; i++){
        lg[i] = max(lg[i], lg[i - 1]);
    }
}

int32_t main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif // LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    fill();
    int n, m;
    cin >> n >> m;
    vector<vector<char>> v(n, vector<char>(m));
    vector<vector<int>> dp(n, vector<int>(m, 1));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cin >> v[i][j];
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (i == 0 || j == 0){
                continue;
            }
            else{
                if (v[i][j] >= v[i - 1][j - 1] && v[i][j] >= v[i - 1][j] && v[i][j] >= v[i][j - 1]){
                    int ans = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
                    if (ans == 1){
                        if (v[i - 1][j] >= v[i - 1][j - 1] && v[i][j - 1] >= v[i - 1][j - 1]){
                            dp[i][j] = 2;
                        }
                    }
                    else{
                        dp[i][j] = ans + 1;
                    }
                }
            }
        }
    }
    for (int k = 0; k < 20; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j + (1 << k) - 1 < m; j++){
                if (k == 0){
                    go[k][i][j] = dp[i][j];
                }
                else{
                    go[k][i][j] = max(go[k - 1][i][j], go[k - 1][i][j + (1 << (k - 1))]);
                }
            }
        }
    }
    int q;
    cin >> q;
    while(q--){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--, y1--, x2--, y2--;
        int l = 1, r = min(x2 - x1, y2 - y1) + 2;
        while(r - l > 1){
            int mid = (r + l) / 2, j = y1 + mid - 1;
            int need = lg[y2 - j + 1];
            bool x = 0;
            for (int i = x1 + mid - 1; i <= x2; i++){
                if (max(go[need][i][j], go[need][i][y2 - (1 << need) + 1]) >= mid){
                    x = 1;
                    break;
                }
            }
            if (x) l = mid;
            else r = mid;
        }
        cout << l << "\n";
    }
    return 0;
}
