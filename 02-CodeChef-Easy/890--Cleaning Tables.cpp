#include <algorithm>
#include <iostream>
#include <vector>

#include <cstdio>

using namespace std;

const int MAX_CUSTOMER_ID = 1600;
const int M = 1600;

int main()
{
    ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("2.in", "r", stdin);
    freopen("2.dbg", "w", stdout);
#endif
    int t;
    cin >> t;

    vector<bool> present(MAX_CUSTOMER_ID +1);
    vector<int> last_use(MAX_CUSTOMER_ID +1);
    vector<int> seen_before(MAX_CUSTOMER_ID +1);
    vector<int> customer(M);

    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            cin >> customer[i];
            last_use[customer[i]] = i;
        }
        fill(present.begin(), present.end(), false);
        fill(seen_before.begin(), seen_before.end(), 0);
        int ans = 0;
        int order_no = 0;

        while (order_no < m && (ans < n || present[customer[order_no]])) {
            if (!present[customer[order_no]]) {
                present[customer[order_no]] = true;
                ans++;
            }
            order_no++;
        }

        while (order_no < m) {
            if (!present[customer[order_no]]) {
                //try to pick victim as customer who doesn't orders again
                int victim = -1;
                for (int i = order_no-1; i >= 0; i--) {
                    if (present[customer[i]] && last_use[customer[i]] == i){
                        victim = customer[i];
                        break;
                    }
                }
                //if all customer will order again, find the one who will order next the last
                if (victim == -1) {
                    for (int i = order_no+1; i < m; i++) {
                        if (present[customer[i]] && seen_before[customer[i]] != order_no) {
                            victim = customer[i];
                            seen_before[customer[i]] = order_no;
                        }
                    }
                }
                present[victim] = false;
                //cerr << victim << " ";
                present[customer[order_no]] = true;
                ans++;
            }
            order_no++;
        }
        //cerr << endl;
        cout << ans << endl;
    }
}