//bs:-program
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define all(x) begin(x), end(x)
typedef long double ld;
typedef long long ll;

const int MAX_MASK = 1 << 16, MOD = 1e9 + 7, AND_MASK = MAX_MASK - 1, C = 4;

ll masks[MAX_MASK];

vector<int> popcnt;

void addTo(int mask, ll add) {
    // cout << "add to " << bitset<16>(mask) << " " << add << endl;
    if (__builtin_popcount(mask) >= C) {
        int imask = (~mask) & AND_MASK;
        for (int i = imask; i; i = (i - 1) & imask)
            (masks[(~i) & AND_MASK] += add) %= MOD;
        (masks[AND_MASK] += add) %= MOD;
    } else {
        (masks[mask] += add) %= MOD;
    }
}

ll getSubmasks(int mask) {
    // cout << "get " << bitset<16>(mask) << endl;
    ll add = 0;
    if (__builtin_popcount(mask) >= C)
        add = masks[mask];
    for (int i : popcnt) {
        if ((i & mask) == i) {
            add += masks[i];
        }
    }
    // cout << add << endl;
    return add % MOD;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tests;
    cin >> tests;
    for (int u = 0; u < MAX_MASK; ++u)
        if (__builtin_popcount(u) < C)
            popcnt.push_back(u);
    while (tests--) {
        int n, m;
        cin >> n >> m;
        fill(masks, masks + MAX_MASK, 0);
        addTo(0, 1);
        for (int i = 0; i < n; ++i) {
            int x = 0;
            for (int j = 0; j < m; ++j) {
                char c;
                cin >> c;
                x = ((x << 1) + (c - '0'));
            }
            addTo(x, getSubmasks((~x) & AND_MASK));
        }
        cout << getSubmasks(AND_MASK) - 1 << "\n";
    }
    return 0;
}