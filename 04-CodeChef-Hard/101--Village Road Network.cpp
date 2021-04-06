#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    auto go = [&](int64_t x, int64_t y) {
        vector<pair<int64_t, int64_t>> ans;
        while (x != 1 || y != 1 ) {
            if (ans.size() >= 300000) break;
            ans.emplace_back(x, y);
            if (x > 0) {
                if (x > y) x -= 2 * y;
                else y -= 2 * x;
            } else {
                if (-x > y) x += 2 * y;
                else y += 2 * x;
            }
            if (y < 0) x = -x, y = -y;
        }
        ans.emplace_back(x, y);
        return ans;
    };
    int T; cin >> T;
    while (T--) {
        int64_t x0, y0, x1, y1; cin >> x0 >> y0 >> x1 >> y1;
        auto g0 = go(x0, y0);
        auto g1 = go(x1, y1);
        map<pair<int64_t, int64_t>, int> mp;
        for (int i = 0; i < g1.size(); ++i) {
            mp[g1[i]] = i;
        }
        for (int i = 0; i < g0.size(); ++i) {
            if (mp.count(g0[i])) {
                cout << i + mp[g0[i]] << '\n';
                break;
            }
        }
    }
}
