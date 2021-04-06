
	#include <bits/stdc++.h>

constexpr int P = 998244353;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> a(n);
    
    int maxA = 0;
    
    for (int i = 0; i < n; ++i) {
        int m;
        std::cin >> m;
        a[i].resize(m);
        for (int j = 0; j < m; ++j) {
            std::cin >> a[i][j];
            maxA = std::max(maxA, a[i][j]);
            a[i][j]--;
        }
        std::sort(a[i].begin(), a[i].end());
    }
    
    int ans = 0;
    if (n >= 400) {
        
        int k = 0;
        for (int i = 0; i < n; ++i)
            if (a[i].size() < a[k].size()) k = i;
        
        std::rotate(a.begin(), a.begin() + k, a.end());
        
        std::vector<int> dp, g;
        for (int i = 0; i < int(a[0].size()); ++i) {
            dp.assign(maxA, 0);
            g.assign(maxA, 0);
            dp[a[0][i]] = 1;
            int sum = 1;
            for (int j = 1; j < n; ++j) {
                int nSum = 0;
                for (auto x : a[j]) {
                    dp[x] = (sum - (g[x] == j - 1 ? dp[x] : 0) + P) % P;
                    nSum = (nSum + dp[x]) % P;
                    g[x] = j;
                }
                sum = nSum;
            }
            ans = (ans + sum - (g[a[0][i]] == n - 1 ? dp[a[0][i]] : 0)) % P;
        }
        ans = (ans + P) % P;
        
    } else {
        
        auto solve = [&](auto self, auto &a) {
            if (a.size() == 1) return 0;
            
            int n = a.size();
            
            std::vector<int> dp(maxA), g(maxA);
            int sum = 1;
            for (int j = 0; j < n; ++j) {
                int nSum = 0;
                for (auto x : a[j]) {
                    dp[x] = (sum - (g[x] == j - 1 ? dp[x] : 0) + P) % P;
                    nSum = (nSum + dp[x]) % P;
                    g[x] = j;
                }
                sum = nSum;
            }
            int ans = sum;
            
            std::vector<int> inter(a[0].size());
            inter.erase(std::set_intersection(a[0].begin(), a[0].end(), a[n - 1].begin(), a[n - 1].end(), inter.begin()), inter.end());
            a.pop_back();
            a[0] = std::move(inter);
            
            ans = (ans - self(self, a) + P) % P;
            return ans;
        };
        
        ans = solve(solve, a);
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
	
