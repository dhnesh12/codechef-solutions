#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include<bits/stdc++.h>
 
using namespace std;
 
#define LL long long int
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
const int oo = 1e9 + 5;
const LL ooll = (LL)1e18 + 5;
const int MOD = 1e9 + 7;
// const int MOD = 998244353;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<int>(l, r)(rng)

clock_t start = clock();

const int N = (int)1e4 + 5;
const int M = (int)1e5 + 5;

set<array<int,2>> g[N];
int c[N], color[N];
array<int, 2> Edge[M];
map<array<int,2>, int> mp;
int n, m, k;

const int K = 256;

vector<int> getPath(int v) {
    vector<int> go(1, v);
    int i;
    for (i=1;i<K;++i) {
        int nxt = -1;
        for (auto it : g[v]) {
            int cand = Edge[it[1]][0] ^ v;
            if (i > 1 && go[i-2] == cand) continue;
            nxt = cand;
            break;
        }
        if (nxt == -1) break;
        bool ok = true;
        for (int j=0;j<i-1;++j) {
            int x = nxt, y = go[j];
            if (x > y) swap(x, y);
            if (mp.find({x, y}) != mp.end()) {
                ok = false;
                break;
            }
        }
        if (!ok) break;
        go.push_back(nxt);
        v = nxt;
    }
    return go;
}

void Hit(int v) {
    vector<int> remove_path = getPath(v);
    int sz = remove_path.size();
    for (int i=0;i<sz-1;++i) {
        int vertex = remove_path[i];
        int e = (*g[vertex].begin())[1];
        g[vertex].erase(g[vertex].begin());
        int u = vertex;
        vertex = Edge[e][0] ^ vertex;
        g[vertex].erase(g[vertex].find({Edge[e][1], e}));
        if (u > vertex) swap(u, vertex);
        mp.erase(mp.find({u, vertex}));
    }
}
void HitPath(vector<int> remove_path) {
    int sz = remove_path.size();
    for (int i=0;i<sz-1;++i) {
        int vertex = remove_path[i];
        int e = (*g[vertex].begin())[1];
        g[vertex].erase(g[vertex].begin());
        int u = vertex;
        vertex = Edge[e][0] ^ vertex;
        g[vertex].erase(g[vertex].find({Edge[e][1], e}));
        if (u > vertex) swap(u, vertex);
        mp.erase(mp.find({u, vertex}));
    }
}

void solve1() {
    int re = m, tot_cost = 0;

    set<array<int,2>> alive;
    for (int i=1;i<=n;++i) alive.insert({c[i], i});

    vector<int> ops;
    while (!alive.empty()) {
        auto it = alive.begin();
        if ((int)g[(*it)[1]].size() == 0) {
            alive.erase(it);
            continue;
        }
        int tried = 0, choice = (*it)[1], opt_wt = 0;
        auto path = getPath(choice);
        for (auto it : path) opt_wt += (int)g[it].size() > k ? c[it] : 0;
        
        for (it++;;it++) {
            if (it == alive.end()) break;
            ++tried;
            int hitme = (*it)[1], wt = 0;
            auto cur_path = getPath(hitme);
            for (auto it : cur_path) wt += (int)g[it].size() > k ? c[it] : 0;
            if (wt * 1LL * c[choice] > opt_wt * 1LL * c[hitme]) {
                choice = hitme;
                opt_wt = wt;
                path.swap(cur_path);
            }
            if (tried > (n == 10000 ? 70 : 200)) break;

            if ((clock() - start) / (long double)(CLOCKS_PER_SEC) > 6.50) {
                if (tried > 10) break;
            }
        }

        HitPath(path);
        ops.push_back(choice);
        tot_cost += c[choice];
        re -= (int)path.size() - 1;
    }
    cout << ops.size() << '\n';
    for (auto it : ops) cout << it << " ";
    cout << '\n';
    for (int i=1;i<=n;++i) cout << "1 ";
    cout << '\n';

    cerr << tot_cost << " total cost\n";
}

void solve2() {
    int tot_cost = 0, check_color = 0;
    set<array<int,2>> alive;
    for (int i=1;i<=n;++i) alive.insert({c[i], i});
    vector<int> ops;
    while (!alive.empty()) {
        auto it = alive.begin();
        int v = (*it)[1];
        if ((int)g[v].size() < k) {
            alive.erase(alive.begin());
        } else {
            ++check_color;

            int tried = 0, choice = v, opt_wt = 0;
            auto path = getPath(v);
            for (auto it : path) opt_wt += (int)g[it].size() > k ? c[it] : 0;

            for (it++;;it++) {
                if ((clock() - start) / (long double)(CLOCKS_PER_SEC) > 6.50) {
                     break;
                }
                if (it == alive.end()) break;
                int v = (*it)[1], wt = 0;
                auto cur_path = getPath(v);
                for (auto it : cur_path) wt += (int)g[it].size() > k ? c[it] : 0;
                if ((wt * 1LL * c[choice] > opt_wt * 1LL * c[v])) {
                    opt_wt = wt;
                    choice = v;
                    path.swap(cur_path);
                }
                ++tried;
                if (tried > (n == 1000 ? 150 : 70)) break;
            }

            ops.push_back(choice);
            HitPath(path);
            tot_cost += c[choice];
        }
        if (check_color > (n == 1000 ? (k == 2 ? 10 : 50) : (k == 2 ? 50 : 100)) || alive.empty()) {
            check_color = 0;
            int TRY = (k == 2 ? 1 : (k == 3 ? 5 : 7));

            if ((clock() - start) / (long double)(CLOCKS_PER_SEC) > 6.50) TRY = 1; 

            bool found = false;
            while (TRY--) {
                set<array<int,2>> color_me;
                vector<vector<int>> avail(n+1, vector<int>(k, 1));
                vector<int> avail_cnt(n+1, k);
                for (int i=1;i<=n;++i) {
                    color[i] = 0;
                    color_me.insert({k, i});
                }
                while (!color_me.empty()) {
                    int u = (*color_me.begin())[1];
                    int cnt = 0;
                    for (int j=0;j<k;++j) if (avail[u][j]) {
                        if (rand(0, cnt) == 0) color[u] = j + 1;
                        ++cnt;
                    }
                    if (color[u] == 0) break;
                    color_me.erase(color_me.begin());
                    for (auto it : g[u]) {
                        int e = it[1], v = Edge[e][0] ^ u;
                        if (color[v] > 0) continue;
                        if (avail[v][color[u]-1]) {
                            avail[v][color[u]-1] = 0;
                            color_me.erase(color_me.find({avail_cnt[v], v}));
                            avail_cnt[v]--;
                            color_me.insert({avail_cnt[v], v});
                        }
                    }
                }
                if (color_me.empty()) {
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
    }
    cout << ops.size() << '\n';
    for (auto it : ops) cout << it << " ";
    cout << '\n';
    for (int i=1;i<=n;++i) cout << color[i] << " ";
    cout << '\n';

    cerr << tot_cost << " total cost\n";
}


void solve() {
    cin >> n >> m >> k;
    mp.clear();
    for (int i=1;i<=n;++i) {
        cin >> c[i];
        color[i] = 0;
        g[i].clear();
    }
    for (int i=0;i<m;++i) {
        int u, v, s;
        cin >> u >> v >> s;
        g[u].insert({s, i});
        g[v].insert({s, i});
        Edge[i] = {u^v, s};
        if (u > v) swap(u, v);
        mp[{u, v}] = i;
    }
    if (k == 1) {
        solve1();
        return;
    }
    solve2();
} 

int main() {
    FASTIO;
    cerr << fixed << setprecision(10);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
        cerr << "Time taken : ";
        cerr << (clock() - start) / (long double)(CLOCKS_PER_SEC) << '\n';
        start = clock();
    }
    return 0;
}