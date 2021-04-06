#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define DEBUG(...) 6
#endif

template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << s << " = " << x << "\n";}
template <typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++; else
if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << s.substr(0, i) << " = " << x << " | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}

struct BCC {
    int n, ti;
    vector<int> num, id, stk;
    vector<bool> art;
    vector<vector<int>> adj, tree, comp;

    BCC(int _n) : n(_n), ti(0), num(n), id(n), art(n), adj(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void init() {
        for (int u=0; u<n; u++)
            if (!num[u]) {
                dfs(u, -1);
                if (num[stk.back()] == ti)
                    art[stk.back()] = true;
                stk.pop_back();
            }
        tree.resize(comp.size());
        for (int u=0; u<n; u++)
            if (art[u]) {
                id[u] = (int) tree.size();
                tree.emplace_back();
            }
        for (int i=0; i<(int)comp.size(); i++)
            for (int u : comp[i]) {
                if (art[u]) {
                    tree[id[u]].push_back(i);
                    tree[i].push_back(id[u]);
                } else {
                    id[u] = i;
                }
            }
    }

    int dfs(int u, int p) {
        int low = num[u] = ++ti;
        stk.push_back(u);
        for (int v : adj[u])
            if (v != p) {
                if (!num[v]) {
                    int ret = dfs(v, u);
                    low = min(low, ret);
                    if (num[u] <= ret) {
                        art[u] = p != -1 || num[v] > num[u] + 1;
                        comp.push_back({u});
                        while (comp.back().back() != v) {
                            comp.back().push_back(stk.back());
                            stk.pop_back();
                        }
                    }
                } else {
                    low = min(low, num[v]);
                }
            }
        return low;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> g(n);
    for (int i=0; i<n; i++)
        cin >> g[i];
    BCC bcc(n);
    for (int i=0; i<m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        bcc.addEdge(a, b);
    }

    bcc.init();
    int o = (int) bcc.tree.size(), c = (int) bcc.comp.size();
    long long globalTot = 0, curTot = 0;
    vector<int> id(o), node(o);
    vector<long long> up(o), down(o), ret(n);
    vector<bool> vis(o);
    vector<map<int, int>> nodeMap(o);
    map<int, int> globalMap, curMap;
    iota(id.begin(), id.end(), 0);
    for (int u=0; u<n; u++) {
        node[bcc.id[u]] = u;
        nodeMap[bcc.id[u]][g[u]]++;
    }

    auto sq = [&] (long long x) -> long long {
        return x * (x - 1) / 2;
    };

    auto dfs1 = [&] (auto &self, int u) -> void {
        vis[u] = true;
        for (auto &pi : nodeMap[u]) {
            curTot += (long long) curMap[pi.first] * pi.second + sq(pi.second);
            curMap[pi.first] += pi.second;
        }
        for (int v : bcc.tree[u])
            if (!vis[v])
                self(self, v);
    };

    auto dfs2 = [&] (auto &self, int u, int p) -> void {
        up[u] = curTot;
        if (u < c) {
            for (int v : bcc.comp[u])
                if (!bcc.art[v])
                    ret[v] = curMap[g[v]] - 1;
        }
        for (auto &pi : nodeMap[u]) {
            down[u] += sq(pi.second);
            up[u] -= (long long) (curMap[pi.first] - pi.second) * pi.second + sq(pi.second);
        }
        for (int v : bcc.tree[u])
            if (v != p) {
                self(self, v, u);
                if (u >= c)
                    ret[node[u]] += down[id[v]];
                if (nodeMap[id[u]].size() < nodeMap[id[v]].size())
                    swap(id[u], id[v]);
                for (auto &pi : nodeMap[id[v]]) {
                    down[id[u]] += (long long) nodeMap[id[u]][pi.first] * pi.second + sq(pi.second);
                    nodeMap[id[u]][pi.first] += pi.second;
                    up[id[u]] -= (long long) (curMap[pi.first] - nodeMap[id[u]][pi.first]) * pi.second + sq(pi.second);
                }
            }
        if (u >= c)
            ret[node[u]] = curTot - ret[node[u]] - up[id[u]];
    };

    for (int u=0; u<o; u++)
        if (!vis[u]) {
            curTot = 0;
            curMap.clear();
            dfs1(dfs1, u);
            dfs2(dfs2, u, -1);
            for (auto &pi : curMap) {
                globalTot += (long long) globalMap[pi.first] * pi.second;
                globalMap[pi.first] += pi.second;
            }
        }

    for (int u=0; u<n; u++)
        cout << globalTot + ret[u] << "\n";

    return 0;
}
