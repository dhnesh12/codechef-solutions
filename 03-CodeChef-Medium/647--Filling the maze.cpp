#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
#define sz(v) (int)v.size() 
#define all(v) v.begin(), v.end()
void dbg_out() { cerr << "\b\b]\n"; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T){ cerr << H << ", "; dbg_out(T...);}
#define watch(...) cerr << "[" << #__VA_ARGS__ << "]: [", dbg_out(__VA_ARGS__)

void solve() {
    int n, m; cin >> n >> m;
    vector <string> A(n);
    for (auto &i: A) cin >> i;
    vector <vector <bool>> used(n, vector <bool> (m, false));
    int cmp = 0;
    function <void(int, int)> dfs = [&](int r, int c) {
        used[r][c] = true;
        cmp++;
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        for (int i = 0; i < 4; ++i) {
            int x = r + dx[i], y = c + dy[i];
            if (x < 0 or y < 0 or x >= n or y >= m or used[x][y] or A[x][y] == '#') continue;
            dfs(x, y);
        }
    };
    vector <int> c_size;
    int c0 = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!used[i][j] and A[i][j] != '#') {
                cmp = 0;
                dfs(i, j);
                if (used[n-1][m-1] and c0 == -1) c0 = cmp;
                else c_size.push_back(cmp);
            }
        }
    }

    long double ans = 1;
    for (int i: c_size) {
        ans += 1.0 * i / (i + c0);
    }
    cout << fixed << setprecision(10) << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();


    return 0;
}


/*
 * Break down the grid into components.
 * We use here linearity of expectation.
 * Y = X_1 + X_2 .. X_n
 * X_i = { 1, if ith component is clicked before X_0 component
           0, otherwise
        }
    X_0 component is that component which contains the exit point (n-1, m-1).
 * Y = number of components clicked before X_0 component
 * So, as you can see the above equation is correct, i.e., if some component is clicked then it will become '1' else 0. And
   all these 1's and 0's constitute a sequence of selected components.
   Ex: Y = 1 + 0 + 1 + 0 + 0 => 2
     : then that means 2 components selected, or we can say 2 times clicked before X_0 component.

 * We have to calculate E(Y), 
   E(Y) = E(X_1) + E(X_2) + E(X_3)... E(X_n)
   Now, main goal is to calculate the E(X_i)
   Since, X_i => indicator random variable such that ith component is active or not.
   E(X_i) = probability(i == true)
   P(i) = ?? (how to find)
   To calculate it, just focus on ith component, other components gets selected or not but our main goal is for ith component, We dont' 
   care about other components, we just focus on this component.
   E(X_i) = P(i) = size(i) / (size(i) + size(0))

   Now, just calculate for each of them then add them.

   This is how you can use Linearity of expectation, find think in terms of random variables: main goal (Y) and break it down into other
   indicator variables. Then use linearity of expectation and calculate for each and individual indicator varaiable.

*/