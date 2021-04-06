#include <bits/stdc++.h>

constexpr int P = 1000000007;

std::pair<int64_t, int> f(int64_t n) {
    if ((n & (n - 1)) == 0) {
        return {n - 1, n % P * (n % P) % P};
    } else {
        int k = std::__lg(n);
        int64_t m = 1ll << k;
        return {2 * m - 1, m % P * ((n - m) % P) * 2 % P};
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    while (t--) {
        int64_t l, r;
        std::cin >> l >> r;
        
        if (l == r) {
            std::cout << 0 << " " << 1 << "\n";
            continue;
        }
        
        int k = std::__lg(l ^ r) + 1;
        int64_t L = l & ~((1ll << k) - 1), R = L + (1ll << k);
        
        std::pair<int64_t, int> ans;
        if (L == l || r == R - 1) {
            ans = f(r + 1 - l);
        } else {
            auto ans1 = f((L + R) / 2 - l);
            auto ans2 = f(r + 1 - (L + R) / 2);
            if (ans1.first > ans2.first) ans = ans1;
            else if (ans1.first < ans2.first) ans = ans2;
            else ans = {ans1.first, (ans1.second + ans2.second) % P};
        }
        
        std::cout << ans.first << " " << ans.second << "\n";
    }
    
    return 0;
}