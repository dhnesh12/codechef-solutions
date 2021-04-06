#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e9;
const int N = 3e5 + 5;
int a[N], c[N][10];
int range[N][2], idx[N], tree[5 * N], lazy[5 * N];
void update(int node, int st, int en, int l, int r, int val) {
    if(st > en or l > en or r < st) return;
    if(lazy[node] != 0) {
        tree[node] += lazy[node];
        if(st != en) { // if not a leaf node
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        //Reset the lazy node
        lazy[node] = 0;
    }
    if(st >= l and en <= r) {
        tree[node] += val;
        if(st != en) { // if not a leaf node
            lazy[2 * node] += val; // Postpone update to child nodes
            lazy[2 * node + 1] += val;
        }
        return;
    }
    int mid = (st + en) / 2;
    update(2 * node, st, mid, l, r, val);
    update(2 * node + 1, mid + 1, en, l, r, val);
    tree[node] = min(tree[2 * node] + lazy[2 * node], tree[2 * node + 1] + lazy[2 * node + 1]);  
}
int32_t main() {
    ios_base:: sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        int n, m, k;
        cin >> n >> m >> k;
        for(int i = 1; i < 5 * n; i++)
            tree[i] = lazy[i] = 0;
        vector<int> dish[m];
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            dish[a[i]].push_back(i);
        } 
        for(int i = 0; i < n; i++) 
            for(int j = 0; j < k; j++) {
                cin >> c[i][j];
                c[i][j]--;
            }
        int cnt = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < dish[i].size(); j++) {
                idx[dish[i][j]] = cnt++;
            }
            range[i][0] = cnt - dish[i].size();
            range[i][1] = cnt - 1;
        }
        int ans = 0;
        int i = 0, j = 0, st = 0; // i -> right pointer, j -> left pointer
        while(i < n and tree[1] == 0) {
            for(int l = 0; l < k; l++) {
                if(idx[c[i][l]] < range[a[i]][0] or idx[c[i][l]] > range[a[i]][1]) { 
                    // Friend is outside the range of chefs cooking same dish
                    update(1, 0, n - 1, idx[c[i][l]], idx[c[i][l]], 1);                                               
                }
            }
            update(1, 0, n - 1, range[a[i]][0], range[a[i]][1], 1);
            update(1, 0, n - 1, idx[i], idx[i], -1);

            // Now shift the left pointer as much as we can such that we still get a  valid range
            while(j <= i and tree[1] > 0) {
                for(int l = 0; l < k; l++) {
                    if(idx[c[j][l]] < range[a[j]][0] or idx[c[j][l]] > range[a[j]][1]) { 
                        // Friend is outside the range of chefs cooking same dish
                        update(1, 0, n - 1, idx[c[j][l]], idx[c[j][l]], -1);                                               
                    }
                }
                update(1, 0, n - 1, range[a[j]][0], range[a[j]][1], -1);
                update(1, 0, n - 1, idx[j], idx[j], 1);
                j++;
            }
            if(j > st) {
                ans += (j - st) * 1ll * (n - i);
                st = j;
            }
            i++;
        }
        cout << ans << endl;
    }
}