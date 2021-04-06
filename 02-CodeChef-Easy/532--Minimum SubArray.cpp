#include <bits/stdc++.h>
using namespace std;
template <typename A, typename B>
string to_string(pair<A, B> p);
template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string &s) { return '"' + s + '"'; }
string to_string(const char *s) { return to_string((string)s); }

string to_string(bool b) { return (b ? "true" : "false"); }

string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template <size_t N>
string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
string to_string(A v) {

    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}
class xxx {
    public:
    xxx(int x) : i(x) {}
    int i;
    void operator()() const { cout << i << endl; }
};
template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " +
           to_string(get<3>(p)) + ")";
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);

    debug_out(T...);
}
#define LOCAL 1
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

#define rep(i, a, n) for (int i = a; i < n; i++)
#define per(i, a, n) for (int i = n - 1; i >= a; i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef vector<vector<int>> VII;
typedef long long ll;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;
typedef double db;
mt19937 mrand(random_device{}());
const ll mod = 1e9 + 7;
// int rnd(int x) { return mrand() % x; }
// ll powmod(ll a, ll b) {
//     ll res = 1;
//     a %= mod;
//     assert(b >= 0);
//     for (; b; b >>= 1) {
//         if (b & 1)
//             res = res * a % mod;
//         a = a * a % mod;
//     }
//     return res;
// }
// ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
// // head

// #define ls (v << 1)
// #define rs (ls | 1)
// #define tm ((tl + tr) >> 1)

// #define eps 1e-9

// #define cls(x) memset(x, 0, sizeof x)
// #define inf(x) memset(x, 0x3f, sizeof x)
// #define neg(x) memset(x, -1, sizeof x)
// #define ninf(x) memset(x, 0xc0, sizeof x)

// // #define INF 0x3f3f3f3f
// constexpr int maxn = 1;

// int dx[] = {-1, 0, 0, 0, 1};
// int dy[] = {0, 1, -1, 0, 0};
// const int N = 100 + 10;

// int tot;
// const int level = int(log2(maxn) + 1);
// int parent[level][maxn];
// vector<int> dp(maxn, 0);
// int gl[maxn];
// // map<pair<int, int>, int> dict;
// int fa[maxn], par[maxn];

// int find(int p) { return fa[p] == p ? p : fa[p] = find(fa[p]); }

// void unite(int p, int q) {
//     auto pp = find(p);
//     auto pq = find(q);

//     fa[pq] = pp;
// }
// struct edge {
//     int b, e, w;
// } e[maxn];

// map<int, ll> dic;
// ll dfs(string &v) {

//     int n = v.size();
//     ll res = 0;

//     ll c = 5;
//     for (int i = 1; i < n; ++i) {
//         res += c;
//         c *= 5;
//         // debug(c);
//     }
//     // debug(res);
//     int i = 0;
//     while (i < n) {
//         for (int j = 0; j < (v[i] - '0'); j++) {
//             if (i % 2 == 0 and j % 2 == 0)
//                 continue;
//             if (i % 2 and j % 2)
//                 continue;
//             res += pow(5, (n - i - 1));
//         }
//         if ((v[i] - '0') % 2 and (i % 2 == 0)) {
//             i++;

//         } else if ((v[i] - '0') % 2 == 0 and (i % 2)) {
//             i += 1;
//         } else
//             break;
//     }

//     return res + (i == n);
// }
inline ll gcd(ll a, ll b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
class RMQ {
    public:
    std::vector<ll> v;
    vector<vector<ll>> f;
    RMQ(vector<ll> &t) {
        v = t;
        build();
    }

    void build() {
        int n = v.size();
        int level = log(n) / log(2) + 1;
        f = vector<vector<ll>>(n, vector<ll>(level, 0));
        for (int i = 0; i < n; ++i)
            f[i][0] = v[i];

        for (int i = 1; i < level; ++i) {
            for (int j = 0; j <= n - (1 << i); ++j) {
                f[j][i] = gcd(f[j][i - 1], f[j + (1 << i - 1)][i - 1]);
            }
        }
    }

    ll query(int l, int r) {
        int k = log(r - l + 1) / log(2);
        // debug(l, k, f[l][k], f[r - (1 << k)][k]);
        return gcd(f[l][k], f[r - (1 << k) + 1][k]);
    }
};
const ll INF = LLONG_MAX;

// vector<vector<int>> d;
// vector<vector<int>> g;

// void dijkstra(int s, vector<int> &d) {
//     d = vector<int>(n, INF);
//     d[s] = 0;
//     set<pair<int, int>> st;
//     st.insert({d[s], s});
//     while (!st.empty()) {
//         int v = st.begin()->second;
//         st.erase(st.begin());
//         for (auto to : g[v]) {
//             if (d[to] > d[v] + 1) {
//                 auto it = st.find({d[to], to});
//                 if (it != st.end())
//                     st.erase(it);
//                 d[to] = d[v] + 1;
//                 st.insert({d[to], to});
//             }
//         }
//     }
// }

int take(VI &a, VI &b, int &i, int &j) {
    if (i < a.size() and j < b.size()) {
        if (a[i] > b[j]) {

            return a[i++];
        } else {
            j++;
            return 0;
        }
    } else if (i < a.size()) {

        return a[i++];
    } else {
        j++;
        return 0;
    }
}
#define ls now << 1
#define rs now << 1 | 1
#define mid (l + r) / 2
typedef long long ll;
const int maxn = 2e5 + 5;
ll n, m;
vector<ll> a;
ll b[maxn];
// struct node {
//     ll sum, lazy; // sum为区间和，lazy为懒标记
// } t[maxn << 2];

// void pushup(int now) { t[now].sum = t[ls].sum + t[rs].sum; }

// void build(int now, int l, int r) {
//     if (l == r) {
//         // cin >> t[now].sum;
//         // a[index++] = t[now].sum;
//         return;
//     }
//     build(ls, l, mid);
//     build(rs, mid + 1, r);
//     pushup(now);
// }

// void pushdown(int now, int tot) {
//     t[ls].lazy += t[now].lazy;                  //懒标记给左孩子
//     t[rs].lazy += t[now].lazy;                  //懒标记给右孩子
//     t[ls].sum += (tot - tot / 2) * t[now].lazy; //区间和加上懒标记的影响，注意范围
//     t[rs].sum += (tot / 2) * t[now].lazy;
//     t[now].lazy = 0; //记得懒标记下传后清0
// }

// void update(int now, int l, int r, int x, int y, int value) {
//     if (x <= l && r <= y) {
//         t[now].lazy += value;
//         t[now].sum += (r - l + 1) * value;
//         return;
//     }
//     if (t[now].lazy)
//         pushdown(now, r - l + 1); //懒标记下传，与本次修改的信息无关，只是清算之前修改积压的懒标记
//     if (mid >= x)
//         update(ls, l, mid, x, y, value);
//     if (mid < y)
//         update(rs, mid + 1, r, x, y, value);
//     pushup(now);
// }

// ll query(int now, int l, int r, int x, int y) {
//     if (x <= l && r <= y)
//         return t[now].sum;
//     if (t[now].lazy)
//         pushdown(now, r - l + 1);
//     ll ans = 0;
//     if (mid >= x)
//         ans += query(ls, l, mid, x, y);
//     if (mid < y)
//         ans += query(rs, mid + 1, r, x, y);
//     return ans;
// }
int nxt[1000010];
int k;

// void calc_next(string a) {
//     nxt[1] = 0;
//     for (int i = 2, j = 0; i <= n; i++) {

//         while (j > 0 && a[i - 1] != a[j + 1 - 1])
//             j = nxt[j];
//         if (a[i - 1] == a[j + 1 - 1])
//             j++;
//         nxt[i] = j;

//         // cout << i << " " << nxt[i] << endl;
//     }
// }
const string str[] = {"1110111", "0010010", "1011101", "1011011", "0111010",
                      "1101011", "1101111", "1010010", "1111111", "1111011"};
int cost[2010][12];
void calc(string x, int pos) {

    for (int i = 0; i <= 9; ++i) {
        bool flag = false;
        int cnt = 0;
        for (int j = 0; j < 7; ++j) {
            if (str[i][j] != x[j]) {
                if (x[j] == '1') {
                    flag = true;
                    break;
                } else
                    cnt++;
            }
        }
        if (flag)
            cost[pos][i] = -1;
        else
            cost[pos][i] = cnt;
    }
}
vector<int> factor[500010];

bool is_prime(long long x) {
    if (x < 2)
        return false;
    for (ll i = 2; i <= sqrt(x); ++i) {
        if (x % i == 0)
            return false;
    }
    return true;
}
int get_first_prime(ll n) {
    ll i, j;
    ll res;
    ll order = 0;               //计算找到质数时需要次数
    for (i = n; i < 2 * n; i++) //我们寻找的是第一个质数，所以要小于2n
    {

        if (is_prime(i))
            return i;
    }
    return 0;
}
ll sums = 0;
ll prefix[maxn];
void read1() {
    a.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i], sums += a[i];
}

void read2() {
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < m; ++i)
        cin >> b[i], sums += b[i];
}
// void solve() {
//     vector<vector<int>> grid = {{1, 2, 3, 4, 17}};
//     int m = grid.size();
//     int n = grid[0].size();

//     // 1 2 3 4 17
//     // 5 6 7 8 18
//     // 9 10 11 12 19
//     // 13 14 15 16 20
//     int vis[m][n];
//     memset(vis, 0, sizeof(vis));

//     int i = 0, j = 0;

//     vector<pair<int, int>> dirs;
//     dirs.push_back({0, 1});
//     dirs.push_back({1, 0});
//     dirs.push_back({0, -1});
//     dirs.push_back({-1, 0});

//     int st = 0;
//     vector<int> res;
//     int nx = i;
//     int ny = j;
//     int minx = 0, miny = 0, maxx = m, maxy = n;
//     while (nx >= minx and ny >= miny and nx < maxx and ny < maxy) {

//         while (nx >= minx and ny >= miny and nx < maxx and ny < maxy) {

//             res.push_back(grid[nx][ny]);
//             nx += dirs[st].fi;
//             ny += dirs[st].se;
//         }
//         if (st == 0) // left
//             minx++;
//         else if (st == 1) //
//             maxy--;
//         else if (st == 2)
//             maxx--;
//         else if (st == 3)
//             miny++;

//         nx -= dirs[st].fi;
//         ny -= dirs[st].se;

//         st = (st + 1) % 4;

//         nx += dirs[st].fi;
//         ny += dirs[st].se;
//     }

//     debug(res);
// }
void solve() {

    cin >> n;
    int d;
    cin >> d;
    read1();

    ll delta = 0;
    deque<pair<int, ll>> q;
    int res = INT_MAX;
    for (int i = 0; i < n; ++i) {
        delta += a[i];
        while (!q.empty() and q.back().second + delta < a[i])
            q.pop_back();

        q.push_back({i, a[i] - delta});

        while (!q.empty() and q.front().second + delta >= d) {

            res = min(res, i - q.front().first + 1);
            q.pop_front();
        }
    }
    if (res == INT_MAX)
        cout << -1 << endl;
    else
        cout << res << endl;
}
int main() {

    // freopen("in.txt", "r", stdin);
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int tests;

    cin >> tests;

    for (int tc = 1; tc <= tests; tc++) {
        solve();

        cout << flush;
    }

    // aligned_free(alignmalloc(5, 4));

    return 0;
}

// void solve(int test_case) {

//     int N, Q;
//     cin >> N >> Q;
//     vector<int> masks(N, 0);
//     vector<vector<int>> dist(26, std::vector<int>(26, 1e9));
//     for (int i = 0; i < N; ++i) {
//         string str;
//         cin >> str;

//         for (auto &c : str)
//             masks[i] |= 1 << (c - 'A');

//         for (int x = 0; x < 26; ++x)
//             if (masks[i] >> x & 1)
//                 for (int y = 0; y < 26; ++y)
//                     if (masks[i] >> y & 1)
//                         dist[x][y] = 1;
//     }
//     for (int x = 0; x < 26; ++x)
//         dist[x][x] = 0;

//     for (int k = 0; k < 26; ++k)
//         for (int i = 0; i < 26; ++i)
//             for (int j = 0; j < 26; ++j)
//                 dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

//     cout << "Case #" << test_case << ": ";

//     for (int q = 0; q < Q; ++q) {
//         int best = 1e9;
//         int x, y;
//         cin >> x >> y;
//         x--, y--;
//         for (int a = 0; a < 26; ++a)
//             if (masks[x] >> a & 1)
//                 for (int b = 0; b < 26; ++b)
//                     if (masks[y] >> b & 1)
//                         best = min(best, dist[a][b] + 2);

//         if (best == 1e9)
//             cout << ' ' << -1;
//         else
//             cout << ' ' << best;
//     }

//     cout << '\n';
// }

// void solve() {
//     ll n;
//     scanf("%lld", &n);
//     vector<PLL> arr(n);
//     vector<ll> tx(n);
//     for (int i = 0; i < n; ++i) {
//         scanf("%lld%lld", &arr[i].first, &arr[i].second);
//         tx[i] = arr[i].first;
//     }

//     auto ty = arr;
//     sort(tx.begin(), tx.end());
//     sort(ty.begin(), ty.end(), [](PLL x, PLL y) { return x.second < y.second; });

//     int mid = n / 2;
//     ll res = 0;

//     for (int i = 0; i < n; ++i) {
//         res += abs(arr[i].second - ty[mid].second);
//     }

//     unordered_map<ll, ll> mp1, mp2, mp3;
//     auto ttx = tx;
//     ttx.erase(unique(ttx.begin(), ttx.end()), ttx.end());
//     for (auto x : tx) {
//         mp1[lower_bound(ttx.begin(), ttx.end(), x) - ttx.begin()] = x;
//         mp2[x] = lower_bound(ttx.begin(), ttx.end(), x) - ttx.begin();
//         mp3[lower_bound(ttx.begin(), ttx.end(), x) - ttx.begin()]++;
//     }

//     queue<int> q;
//     q.push(mp2[tx[mid]]);
//     unordered_set<ll> vis;
//     ll move = 0;
//     int cnt = 0;
//     while (!q.empty()) {
//         int sz = q.size();

//         while (sz--) {
//             auto t = q.front();
//             q.pop();

//             vis.insert(t);
//             move -= 1;
//             cnt++;
//             if (mp3.count(t)) {
//                 move += (mp3[t]);
//             }
//             if (!vis.count(t - 1))
//                 q.push(t - 1);
//             if (!vis.count(t + 1)) {
//                 q.push(t + 1);
//             }
//             debug(move, t);
//         }

//         if (cnt >= n) {
//             break;
//         }
//         res += move;
//     }

//     res += (1 + move) * move / 2;

//     printf("%lld\n", res);
// }
int _, __;

// void *alignmalloc(int size, int alingment) {

//     void *p1;

//     int offset = alingment - 1 + sizeof(void *);
//     p1 = malloc(size + offset);
//     if (p1 == nullptr) {
//         return nullptr;
//     }
//     void **p2;
//     p2 = (void **)(((size_t)(p1) + offset) & ~(alingment - 1));
//     p2[-1] = p1;
//     cout << p2 << " " << p1 << endl;
//     return p2;
// }

// void aligned_free(void *p2) {
//     void *p1 = ((void **)p2)[-1];
//     cout << p1 << endl;
//     free(p1);
// }