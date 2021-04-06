#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <climits>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <deque>
#include <climits>
#include <algorithm>
#include <utility>
#include <bitset>
#include <iterator>
#include <iomanip>
#include <cmath>

#define ll long long int

const int MAX = (int)1e5 + 1;

using namespace std;

class Solution {
    void update(vector<int> & bit, int index, int val) {
        for (int i = index + 1; i < bit.size(); i += (i & -i)) {
            bit[i] += val;
        }
    }
    int query(vector<int> & bit, int index) {
        int ans = 0;
        for (int i = index + 1; i >= 1; i -= (i & -i)) {
            ans += bit[i];
        }
        return ans;
    }
 public:
    void solve() {
        int n; cin >> n;
        int ar[n];
        for (int i = 0; i < n; ++i) {
            cin >> ar[i];
        }
        int m; cin >> m;
        vector<int> bit2(MAX, 0);
        vector<int> bit3(MAX, 0);
        vector<int> bit5(MAX, 0);
        for (int i = 0; i < m; ++i) {
            int ty; cin >> ty;
            if (ty == 1) {
                int l, r, p;
                cin >> l >> r >> p;
                l--;r--;
                if (p == 2) {
                    update(bit2, l, 1);
                    update(bit2, r + 1, -1);
                }
                else if (p == 3) {
                    update(bit3, l, 1);
                    update(bit3, r + 1, -1);
                }
                else {
                    update(bit5, l, 1);
                    update(bit5, r + 1, -1);
                }
            }
            else {
                int l, d;
                cin >> l; cin >> d; l--;
                ar[l] = d;
                int q2 = query(bit2, l);
                int q3 = query(bit3, l);
                int q5 = query(bit5, l);
                update(bit2, l, -q2);
                update(bit3, l, -q3);
                update(bit5, l, -q5);
                update(bit2, l + 1, q2);
                update(bit3, l + 1, q3);
                update(bit5, l + 1, q5);
            }
        }
        for (int i = 0; i < n; ++i) {
            int q2 = query(bit2, i);
            int q3 = query(bit3, i);
            int q5 = query(bit5, i);
            while(q2 > 0 && (ar[i] % 2 == 0)) {
                q2--;
                ar[i] /= 2;
            }
            while(q3 > 0 && (ar[i] % 3 == 0)) {
                q3--;
                ar[i] /= 3;
            }
            while(q5 > 0 && (ar[i] % 5 == 0)) {
                q5--;
                ar[i] /= 5;
            }
        }
        for (int i = 0; i < n; ++i) {
            cout << ar[i] << " ";
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    auto solution = new Solution();
    solution->solve();
    return 0;
}
