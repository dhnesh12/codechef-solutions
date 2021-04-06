#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__);
#else
#define DEBUG(...) 6;
#endif

template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << s << " = " << x << "\n";}
template<typename T, typename... Args> void debug(string s, T x, Args... args) {cerr << s.substr(0, s.find(',')) << " = " << x << " | "; debug(s.substr(s.find(',') + 2), args...);}

#define MAXN 100005
#define LOG 17

const int MOD = 1e9 + 7;

struct Node {
    int ans, mx, lazy, l, r;

    void leaf(int val) {
        ans = val;
        mx = lazy = 0;
    }

    void Merge(Node &a, Node &b) {
        ans = 1;
        mx = max(a.mx, b.mx);
        if (mx == a.mx)
            ans = (long long) ans * a.ans % MOD;
        if (mx == b.mx)
            ans = (long long) ans * b.ans % MOD;
    }

    void push(int val) {
        lazy += val;
    }

    void apply() {
        mx += lazy;
        lazy = 0;
    }
};

struct SegmentTree {
    int n;
    vector<int> a;
    vector<Node> st;

    SegmentTree(const vector<int> &_a) : n(_a.size()), a(_a), st(4*n) {
        build(1, 0, n-1);
    }

    void build(int p, int l, int r) {
        st[p].l = l;
        st[p].r = r;
        if (l == r) {
            st[p].leaf(a[l]);
            return;
        }

        int m = (l + r) / 2;
        build(2*p, l, m);
        build(2*p+1, m+1, r);
        st[p].Merge(st[2*p], st[2*p+1]);
    }

    void push(int p) {
        if (st[p].lazy) {
            if (st[p].l != st[p].r) {
                st[2*p].push(st[p].lazy);
                st[2*p+1].push(st[p].lazy);
            }
            st[p].apply();
        }
    }

    void update(int p, int i, int j, int val) {
        if (st[p].l == i && st[p].r == j) {
            st[p].push(val);
            push(p);
            return;
        }

        push(p);

        int m = (st[p].l + st[p].r) / 2;
        if (j <= m) {
            update(2*p, i, j, val);
            push(2*p+1);
        } else if (i > m) {
            push(2*p);
            update(2*p+1, i, j, val);
        } else {
            update(2*p, i, m, val);
            update(2*p+1, m+1, j, val);
        }
        st[p].Merge(st[2*p], st[2*p+1]);
    }

    void update(int i, int j, int val) {
        update(1, i, j, val);
    }
};

int ti = 0, in[MAXN], out[MAXN], dp[MAXN][LOG];
vector<int> preorder, adj[MAXN];

bool anc(int u, int v) {
    return in[u] <= in[v] && out[v] <= out[u];
}

void dfs(int u) {
    in[u] = ti++;
    preorder.push_back(u + 1);
    for (int v : adj[u])
        if (v != dp[u][0]) {
            dp[v][0] = u;
            for (int j=1; j<LOG; j++)
                if (dp[v][j-1] != -1)
                    dp[v][j] = dp[dp[v][j-1]][j-1];
            dfs(v);
        }
    out[u] = ti++;
    preorder.push_back(1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    for (int i=0; i<n-1; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    memset(dp, -1, sizeof(dp));
    dfs(0);
    SegmentTree st(preorder);

    int numPaths = 0;
    for (int i=0; i<m; i++) {
        char c;
        int x, y;
        cin >> c >> x >> y;
        x--, y--;
        int val = (c == '+' ? 1 : -1);
        numPaths += val;

        if (anc(y, x))
            swap(x, y);
        if (anc(x, y)) {
            int u = y;
            for (int j=LOG-1; j>=0; j--)
                if (dp[u][j] != -1 && !anc(dp[u][j], x))
                    u = dp[u][j];
            if (in[u] > 0)
                st.update(0, in[u]-1, val);
            if (out[u] < 2 * n - 1)
                st.update(out[u]+1, 2*n-1, val);
        } else
            st.update(in[x], out[x], val);
        st.update(in[y], out[y], val);

        cout << (st.st[1].mx == numPaths ? st.st[1].ans : -1) << "\n";
    }

    return 0;
}
