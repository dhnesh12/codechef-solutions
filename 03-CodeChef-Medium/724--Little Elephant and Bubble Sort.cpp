#include <bits/stdc++.h>

#define endl "\n"
#define FIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
const int N = 1e5 + 50;
typedef long long ll;
typedef long double ld;
map<int, int> comp;
int bit[N];

void update(int idx, int val) {
    if (idx == 0) assert(0);
    while (idx < N) {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

int get(int idx) {
    int ret = 0;
    while (idx > 0) {
        ret += bit[idx];
        idx -= (idx & -idx);
    }
    return ret;
}

int main() {
    FIO
    int t;
    cin >> t;
    while (t--) {
        comp.clear();
        memset(bit, 0, sizeof(bit));
        int n, d;
        cin >> n >> d;
        vector<int> v(n), p(n);
        priority_queue<int> q;
        for (auto &it:v) {
            cin >> it;
            q.push(it);
            q.push(it + d);
        }
        for (auto &it:p)
            cin >> it;
        while (q.size()) {
            if (comp[q.top()] == 0)
                comp[q.top()] = comp.size();
            q.pop();
        }
        ll res = 0;

        for (int i = 0; i < n; i++) {
            res += get(comp[v[i]] - 1) * (100 - p[i]);
            res += get(comp[v[i] + d] - 1) * (p[i]);
            update(comp[v[i]], 100 - p[i]);
            update(comp[v[i] + d], p[i]);
        }
        cout <<fixed<<setprecision(4)<< (ld) res / 10000.0 << endl;


    }
    return 0;
}
