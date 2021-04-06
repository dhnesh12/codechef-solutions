#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> fwdEdges, backEdges;
vector<int> rnk;

void dfs(int v) {
    if (rnk[v] > 0) return;
    int cnt = 0;
    rnk[v] = 1;
    for (int x : backEdges[v]) {
        dfs(x);
        if (rnk[x] + 1 > rnk[v]) {
            rnk[v] = rnk[x] + 1;
            cnt = 0;
        }
        if (rnk[x] + 1 == rnk[v]) cnt++;
    }
    // rnk[v] += (cnt - 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    fwdEdges.resize(n + 1);
    backEdges.resize(n + 1);
    rnk.resize(n + 1);
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        fwdEdges[a].push_back(b);
        backEdges[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) {
        if (rnk[i] == 0) dfs(i);
    }
    priority_queue<pair<int, int>> q;
    vector<int> deg(n + 1);
    vector<vector<int>> ans;
    for (int i = 1; i <= n; i++) {
        deg[i] = fwdEdges[i].size();
        if (deg[i] == 0) q.push({rnk[i], i});
    }
    while (!q.empty()) {
        ans.emplace_back();
        ans.back().push_back(q.top().second);
        q.pop();
        if (!q.empty()) {
            ans.back().push_back(q.top().second);
            q.pop();
        }
        for (int v : ans.back()) {
            for (int x : backEdges[v]) {
                deg[x]--;
                if (deg[x] == 0) q.push({rnk[x], x});
            }
        }
    }
    cout << ans.size() << "\n";
    for (const auto& a : ans) {
        cout << a.size();
        for (int x : a) cout << " " << x;
        cout << "\n";
    }
    return 0;
}