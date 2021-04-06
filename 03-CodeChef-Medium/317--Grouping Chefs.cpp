#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <chrono>
#define fi first
#define se second

using namespace std;
const int maxN = 1e4 + 5;
typedef pair<int, int> ii;

vector<int> res, adj[maxN];
int n, m, k;

void prt(vector<int> cp){
    sort(cp.begin(), cp.end());
    for(int el: cp) cout << el << ' ';
    cout << '\n';
}

bool t(int a, int b){
    int key = int(lower_bound(adj[a].begin(), adj[a].end(), b) - adj[a].begin());
    if(key == adj[a].size()) return false;
    return adj[a][key] == b;
}

void solve(const vector<ii> &vc){
    if(vc.empty()) {
        prt(res), k--;
        return;
    }
    res.push_back(666);
    vector<ii> cr;
    for(int i = 0; i < vc.size() && k; i++){
        cr.clear();
        res.back() = vc[i].se;
        for(int j = i + 1; j < vc.size(); j++)
            if(t(vc[i].se, vc[j].se))
                cr.push_back(vc[j]);
        solve(cr);
    }
    res.pop_back();
    if(k) solve(vector<ii>());
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        cin >> n >> m >> k;
        vector<ii> vc;
        
        for(int i = 0, inp; i < n; i++) {
            cin >> inp;
            adj[i].clear();
            vc.push_back(ii(inp, i));
        }
        sort(vc.begin(), vc.end(), greater<ii>());
        
        for(int i = 0, u, v; i < m; i++){
            cin >> u >> v;
            adj[u].push_back(v), adj[v].push_back(u);
        }
        
        for(int i = 0; i < n; i++) sort(adj[i].begin(), adj[i].end());
        
        solve(vc);
        cout << '\n';
    }
}
