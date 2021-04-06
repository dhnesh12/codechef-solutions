#include <bits/stdc++.h>

const int N = 500010;
const int BIT = 20;
const int moder = 998244353;

struct Value{
    // 1 ... pi
    int y, pi;

    Value():y(0), pi(0){}
    Value(int y, int pi):y(y), pi(pi){}
};

void add(int &u, int v){u += v; u -= u >= moder ? moder : 0;}
void add(Value &u, Value v){add(u.y, v.y), add(u.pi, v.pi);}

int seg_cnt;
Value seg[N * 100];
int ch[N * 100][2];
char s[N];
int w[N];
int pre[N];
int n;

int new_seg(){
    ++ seg_cnt;
    assert(seg_cnt < N * 100);
    seg[seg_cnt] = {0, 0};
    ch[seg_cnt][0] = ch[seg_cnt][1] = 0;
    return seg_cnt;
}

void add(int root, int sit, Value value){
    for (int i = BIT - 1; i >= 0; -- i){
        add(seg[root], value);
        int pos = sit >> i & 1;
        if (!ch[root][pos]){
            ch[root][pos] = new_seg();
        }
        root = ch[root][pos];
    }
    add(seg[root], value);
}

Value query(int root, int l, int r, int ql, int qr){
    if (!root || qr < l || ql > r){
        return {0, 0};
    }
    if (ql <= l && qr >= r){
        return seg[root];
    }
    int mid = (l + r) / 2;
    Value ret = query(ch[root][0], l, mid, ql, qr);
    add(ret, query(ch[root][1], mid + 1, r, ql, qr));
    return ret;
}

Value query(int root, int ql, int qr){
    if (ql > qr) return {0, 0};
    return query(root, 0, (1 << BIT) - 1, ql, qr);
}

struct SAM{
    const static int N = 1000010;
    const static int MAXNODE = N << 1;
    const static int DICTSIZE = 26;

    int go[MAXNODE][DICTSIZE], link[MAXNODE], len[MAXNODE];
    int last, sz, root;
    std::vector<int> e[MAXNODE]; // parent tree
    int sz1[MAXNODE], son[MAXNODE], rt[MAXNODE];
    int end[MAXNODE];

    int newnode(){
        ++ sz;
        memset(go[sz], 0, sizeof(go[sz]));
        end[sz] = 0;
        return sz;
    }

    void init(){
        sz = 0;
        root = last = newnode();
        len[root] = link[root] = 0;
    }

    int split(int p, int q, int ch){
        int clone = newnode();
        memcpy(go[clone], go[q], sizeof(go[q]));
        link[clone] = link[q];
        link[q] = clone;
        len[clone] = len[p] + 1;
        for (int i = p; i && go[i][ch] == q; i = link[i]){
            go[i][ch] = clone;
        }
        return clone;
    }

    void insert(int ch){
        int cur = newnode();
        len[cur] = len[last] + 1;
        int p = last;
        for ( ; p && !go[p][ch]; p = link[p]){
            go[p][ch] = cur;
        }
        if (!p){
            link[cur] = root;
        }
        else{
            int q = go[p][ch];
            link[cur] = len[p] + 1 == len[q] ? q : split(p, q, ch);
        }
        last = cur;
    }

    void build(char *s){ // must init() first
        for (char *p = s; *p != '\0'; ++ p){
            insert(*p - 'a');
            end[last] = int(p - s) + 1;
        }
        last = root;
    }

    void build_parent_tree(){
        for (int i = root; i <= sz; ++ i){
            e[i].clear();
            sz1[i] = rt[i] = son[i] = 0;
            b[i] = sum[i] = sum1[i] = 0;
        }
        for (int i = root; i <= sz; ++ i){
            e[link[i]].emplace_back(i);
        }
    }

    void dfs(int u){
        sz1[u] = 1;
        for (auto v : e[u]){
            dfs(v);
            if (sz1[v] > sz1[son[u]]){
                son[u] = v;
            }
            sz1[u] += sz1[v];
        }
    }

    int ans;
    int b[MAXNODE], sum[MAXNODE], sum1[MAXNODE];

    void update(int u, int point, int &bb){
        Value p = query(rt[u], 1, point - 1);
        bb = (bb + 1ll * pre[point] * p.y - p.pi) % moder;
        p.y = (sum[u] - p.y) % moder;
        p.pi = (sum1[u] - p.pi) % moder;
        bb = (bb - 1ll * pre[point] * p.y + p.pi) % moder;
        bb += bb < 0 ? moder : 0;
    }

    void update1(int u, int point){
        Value to_add(1, pre[point]);
        add(rt[u], point, to_add);
        add(sum[u], 1);
        add(sum1[u], pre[point]);
    }

    std::vector<int> solve1(int u){
        std::vector<int> vector;
        if (son[u]){
            vector = std::move(solve1(son[u]));
            rt[u] = rt[son[u]];
            add(b[u], b[son[u]]);
            add(sum[u], sum[son[u]]);
            add(sum1[u], sum1[son[u]]);
        }
        else{
            rt[u] = new_seg();
        }
        if (end[u]){
            vector.emplace_back(end[u]);
            update(u, end[u], b[u]);
            update1(u, end[u]);
        }
        for (auto v : e[u]){
            if (v == son[u]){
                continue;
            }
            std::vector<int> vec = solve1(v);
            for (auto w : vec){
                vector.emplace_back(w);
                update(u, w, b[u]);
            }
            for (auto w : vec){
                update1(u, w);
            }
            add(b[u], b[v]);
        }
        int left = len[link[u]] + 1, right = len[u];
        ans = (ans + 1ll * (right - left + 1) * b[u]) % moder;
        return vector;
    }

    int solve(){
        seg_cnt = 0;
        ans = 0;
        dfs(root);
        solve1(root);
        return ans;
    }
};

SAM sam;

int powermod(int a, int exp){
    int ret = 1;
    for ( ; exp > 0; exp >>= 1){
        if (exp & 1){
            ret = 1ll * ret * a % moder;
        }
        a = 1ll * a * a % moder;
    }
    return ret;
}

int bf(std::string s){
    int n = s.size();
    long long ans = 0;
    for (int i = 0; i < n; ++ i){
        for (int j = i; j < n; ++ j){
            for (int k = i + 1; k < n; ++ k){
                int v = k + j - i;
                if (v >= n){
                    break;
                }
                if (s.substr(i, j - i + 1) == s.substr(k, j - i + 1)){
                    ans = (ans + pre[v + 1] - pre[j + 1]) % moder;
                }
            }
        }
    }
    ans += ans < 0 ? moder : 0;
    return ans;
}

void solve(){
    auto seed = std::chrono::steady_clock().now().time_since_epoch().count();
    std::mt19937 rnd(seed);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    /*n = 500000;
    for (int i = 1; i <= n; ++ i){
        s[i] = 'a' + rnd() % 3;
    }*/
    for (int i = 0; i < 26; ++ i){
        scanf("%d", &w[i]);
        // w[i] = rnd() % 1'000'000'001;
    }
    for (int i = 1; i <= n; ++ i){
        pre[i] = (pre[i - 1] + w[s[i] - 'a']) % moder;
    }
    sam.init();
    sam.build(s + 1);
    sam.build_parent_tree();
    int ans = sam.solve();
    /*printf("%d\n", ans);
    int standard = bf(s + 1);
    printf("%d\n", standard);
    if (ans != standard){
        puts("------------ WA ------------");
        puts(s + 1);
        for (int i = 0; i < 26; ++ i){
            printf("%d%c", w[i], " \n"[i == 25]);
        }
        exit(0);
    }*/
    for (int i = 1; i <= n; ++ i){
        ans = (ans + 1ll * (i - (n - i)) * pre[i]) % moder;
    }
    ans += ans < 0 ? moder : 0;
    ans = 1ll * ans * powermod(1ll * n * (n + 1) / 2 % moder, moder - 2) % moder;
    printf("%d\n", ans);
}

int main(){
    int test;
    scanf("%d", &test);
    while (test --){
        solve();
    }
    return 0;
}

/*
1
abacaba
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1
aabaa
1 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

1
bbb
119658703 251658004 925394407 93728415 731765764 766049469 229980129 845996936 51157907 133843269 692736635 890429553 662020628 606644080 721783522 447799784 799102421 157920370 71958332 817093364 834613372 713405025 641073839 908732729 222476399 280544492
 */