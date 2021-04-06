#include<bits/stdc++.h>
using namespace std;
int get_point_mn(int x);
int get_last(int l, int r, int ll, int rr, int x, int y);
long long get_sum(int l, int r, int ll, int rr, int x, int y);

const int N = 250005;


struct NODE {
    int mn, cnt_mn;
    int qmn;
    long long sum, qsum;
    bool ob;
    NODE () {
        mn = cnt_mn = sum = qsum = 0;
        ob = false;
    }
    
} t[3 * N];

int ans_query7;
int n, m, sz, group, timer, sz_pred;
string bin_ed;
int vert_cnt[3 * N];
int max_tout[3 * N];
int qob[N];
int tin[N], tout[N], poc[N];
vector<pair<int, int> > v[N];
pair<int, int> ed[N];
int depth[N], first_pos[N], poc2[N + N], pred[19][N + N], max_step[N + N];
int pw[30];
bool comp[N];

void dfs(int x, int y) {
    tin[x] = ++timer;
    depth[x] = depth[y] + 1;
    poc[timer] = x;
    poc2[++sz_pred] = x;
    first_pos[x] = sz_pred;
    for (int i = 0; i < v[x].size(); ++i) {
        int to = v[x][i].first;
        if (to != y) {
            dfs(to, x);
            poc2[++sz_pred] = x;
        }
    }
    tout[x] = timer;
    return;
}

void build_sparse_table() {
    for (int i = 2; i <= sz_pred; ++i)
        max_step[i] = max_step[(i >> 1)] + 1;
    for (int i = 1; i <= sz_pred; ++i) {
        pred[0][i] = poc2[i];
    }
    for (int i = 0; i <= 25; ++i)
        pw[i] = (1 << i);
    for (int it = 1; it <= max_step[sz_pred]; ++it) {
        for (int j = 1; j <= sz_pred - pw[it] + 1; ++j) {
            pred[it][j] = pred[it - 1][j];
            if (depth[pred[it][j]] > depth[pred[it - 1][j + pw[it - 1]]]) pred[it][j] = pred[it - 1][j + pw[it - 1]];
        }
    }
    return;
}

int get_lca(int x, int y) {
    x = first_pos[x];
    y = first_pos[y];
    if (x > y) swap(x, y);
    int len = max_step[y - x + 1];
    int xx = pred[len][x];
    int yy = pred[len][y - pw[len] + 1];
    if (depth[xx] <= depth[yy]) return xx;
    return yy;
}

int get_number_of_edges(int x, int y, int xx, int yy) {
    int z = get_lca(x, y);
    if (tout[x] >= tout[y]) return yy - xx;
    return xx + yy - (get_point_mn(tin[z]) << 1);
}

///////////////////////                 Segment Tree for Components

void tree_update_vertex(int x, int y) {
    x += sz - 1;
    vert_cnt[x] = y;
    x >>= 1;
    while (x) {
        vert_cnt[x] = vert_cnt[x + x] + vert_cnt[x + x + 1];
        x >>= 1;
    }
    return;
}

int get_last_vertex(int l, int r, int ll, int rr, int x) {
    if (l > r || ll > r || l > rr || ll > rr || !vert_cnt[x]) return 0;
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int res = get_last_vertex(mid + 1, r, ll, rr, x + x + 1);
    if (res) return res;
    return get_last_vertex(l, mid, ll, rr, x + x);
}

int get_first_vertex(int l, int r, int ll, int rr, int x) {
    if (l > r || ll > r || l > rr || ll > rr || !vert_cnt[x]) return 0;
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int res = get_first_vertex(l, mid, ll, rr, x + x);
    if (res) return res;
    return get_first_vertex(mid + 1, r, ll, rr, x + x + 1);
}

int FIR = 1e9, SEC = -1e9;

void update_component(int x) {
    comp[x] ^= 1;
    tree_update_vertex(tin[x], comp[x]);
    int xx = get_last_vertex(1, sz, 1, tin[x] - 1, 1);
    int xx1, xx2, xx3;
    xx1 = xx2 = xx3 = -1;
    if (xx) {
        xx1 = get_point_mn(tin[poc[xx]]), xx3 = get_point_mn(tin[x]);
        if (comp[x]) ans_query7 += get_number_of_edges(poc[xx], x, xx1, xx3);
        else ans_query7 -= get_number_of_edges(poc[xx], x, xx1, xx3);
    }
    int yy = get_first_vertex(1, sz, tin[x] + 1, n, 1);
    if (yy) {
        xx2 = get_point_mn(tin[poc[yy]]);
        if (xx3 == -1) xx3 = get_point_mn(tin[x]);
        if (comp[x]) ans_query7 += get_number_of_edges(x, poc[yy], xx3, xx2);
        else ans_query7 -= get_number_of_edges(x, poc[yy], xx3, xx2);
    }
    if (comp[x] == 1) {
        if (tin[x] < FIR) FIR = tin[x];
        if (tin[x] > SEC) SEC = tin[x];
    } else {
        if (FIR == SEC) FIR = 1e9, SEC = -1e9;
        else if (FIR == tin[x]) FIR = yy;
        else if (SEC == tin[x]) SEC = xx;
    }
    if (xx && yy) {
        xx = poc[xx];
        yy = poc[yy];
        if (xx1 == -1) xx1 = get_point_mn(tin[xx]);
        if (xx2 == -1) xx2 = get_point_mn(tin[yy]);
        if (comp[x]) ans_query7 -= get_number_of_edges(xx, yy, xx1, xx2);
        else ans_query7 += get_number_of_edges(xx, yy, xx1, xx2);
    }
    return;
}

bool is_there_somebody(int x, bool y) {
    if (!y) {
        x = get_last(1, sz, 1, tin[x], 1, tout[x]);
        if (!x) x = 1;
        x = poc[x];
    }
    return (bool)(get_sum(1, sz, tin[x], tout[x], 1, get_point_mn(tin[x])) > 0);
}

///////////////////////                 Closest blocked edge

void update_edge(int x, int y) {
    x += sz - 1;
    max_tout[x] = y;
    x >>= 1;
    while (x) {
        max_tout[x] = max_tout[x + x];
        if (max_tout[x + x + 1] > max_tout[x]) max_tout[x] = max_tout[x + x + 1];
        x >>= 1;
    }
    return;
}

int get_last(int l, int r, int ll, int rr, int x, int y) {
    if (l > r || ll > r || l > rr || ll > rr || max_tout[x] < y) return 0;
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int res = get_last(mid + 1, r, ll, rr, x + x + 1, y);
    if (res) return res;
    return get_last(l, mid, ll, rr, x + x, y);
}

//////////////////////                  Segment Tree for Queries

//////////                  Update NODE

void push(int x) {
    int xx = t[x].mn;
    if (t[x].qmn) {
        int z = t[x].qmn;
        t[x].qmn = 0;
        t[x + x].mn += z;
        t[x + x + 1].mn += z;
        t[x + x].qmn += z;
        t[x + x + 1].qmn += z;
    }
    if (t[x].ob) {
        t[x].ob = false;
        if (t[x + x].mn == xx) {
            t[x + x].sum = t[x + x].qsum = 0;
            t[x + x].ob = true;
        }
        if (t[x + x + 1].mn == xx) {
            t[x + x + 1].sum = t[x + x + 1].qsum = 0;
            t[x + x + 1].ob = true;
        }
    }
    if (t[x].qsum) {
        long long z = t[x].qsum;
        t[x].qsum = 0;
        if (t[x + x].mn == xx) {
            t[x + x].sum += (t[x + x].cnt_mn * z);
            t[x + x].qsum += z;
        }
        if (t[x + x + 1].mn == xx) {
            t[x + x + 1].sum += (t[x + x + 1].cnt_mn * z);
            t[x + x + 1].qsum += z;
        }
    }
    return;
}

void update_NODE(int x) {
    t[x].mn = t[x + x].mn;
    t[x].cnt_mn = t[x + x].cnt_mn;
    t[x].sum = t[x + x].sum;
    if (t[x + x + 1].mn < t[x].mn) {
        t[x].mn = t[x + x + 1].mn;
        t[x].cnt_mn = t[x + x + 1].cnt_mn;
        t[x].sum = t[x + x + 1].sum;
    } else if (t[x + x + 1].mn == t[x].mn) {
        t[x].cnt_mn += t[x + x + 1].cnt_mn;
        t[x].sum += t[x + x + 1].sum;
    }
    return;
}

/////////////////////

void update_cnt(int l, int r, int ll, int rr, int x, int y) {
    if (l > r || ll > r || l > rr || ll > rr) return;
    if (l >= ll && r <= rr) {
        t[x].mn += y;
        t[x].qmn += y;
        return;
    }
    int mid = (l + r) >> 1;
    push(x);
    update_cnt(l, mid, ll, rr, x + x, y);
    update_cnt(mid + 1, r, ll, rr, x + x + 1, y);
    update_NODE(x);
    return;
}

int global_pos1;

void update_sum_point(int l, int r, int ll, int x, long long y) {
    if (l == r) {
        global_pos1 = t[x].mn;
        t[x].sum += y;
        return;
    }
    int mid = (l + r) >> 1;
    push(x);
    if (ll <= mid) update_sum_point(l, mid, ll, x + x, y);
    else update_sum_point(mid + 1, r, ll, x + x + 1, y);
    if (t[x].mn == global_pos1) t[x].sum += y;
    return;
}

void update_sum(int l, int r, int ll, int rr, int x, int y, int z) {
    if (l > r || ll > r || l > rr || ll > rr || t[x].mn > z) return;
    if (l >= ll && r <= rr) {
        if (t[x].mn != z) return;
        t[x].sum += (t[x].cnt_mn * 1ll * y);
        t[x].qsum += y;
        return;
    }
    int mid = (l + r) >> 1;
    push(x);
    update_sum(l, mid, ll, rr, x + x, y, z);
    update_sum(mid + 1, r, ll, rr, x + x + 1, y, z);
    update_NODE(x);
    return;
}

void clr_node(int l, int r, int ll, int rr, int x, int y) {
    if (l > r || ll > r || l > rr || ll > rr || t[x].mn > y) return;
    if (l >= ll && r <= rr) {
        if (t[x].mn != y) return;
        t[x].ob = true;
        t[x].sum = t[x].qsum = 0;
        return;
    }
    int mid = (l + r) >> 1;
    push(x);
    clr_node(l, mid, ll, rr, x + x, y);
    clr_node(mid + 1, r, ll, rr, x + x + 1, y);
    update_NODE(x);
    return;
}

/////////////////////////////                   Answer Queries

long long get_point(int l, int r, int ll, int x) {
    int mid;
    while (l != r) {
        mid = (l + r) >> 1;
        push(x);
        if (ll <= mid) x <<= 1, r = mid;
        else x = x + x + 1, l = mid + 1;
    }
    return t[x].sum;
}

int get_point_mn(int x) {
    x += sz - 1;
    int res = t[x].mn;
    x >>= 1;
    while (x) {
        res += t[x].qmn;
        x >>= 1;
    }
    return res;
}


long long get_sum(int l, int r, int ll, int rr, int x, int y) {
    if (l > r || ll > r || l > rr || ll > rr || t[x].mn > y) return 0;
    if (l >= ll && r <= rr) {
        if (t[x].mn != y) return 0;
        return t[x].sum;
    }
    int mid = (l + r) >> 1;
    push(x);
    return get_sum(l, mid, ll, rr, x + x, y) + get_sum(mid + 1, r, ll, rr, x + x + 1, y);
}

long long query_4(int x) {
    return get_point(1, sz, tin[x], 1);
}

long long query_5(int x) {
    x = get_last(1, sz, 1, tin[x], 1, tout[x]);
    if (!x) x = 1;
    x = poc[x];
    int y = get_point_mn(tin[x]);
    return get_sum(1, sz, tin[x], tout[x], 1, y);
}

int query_7() {
    int x, y;
    x = FIR;
    if (x != 1e9) {
        y = SEC;
        x = poc[x];
        y = poc[y];
        return ((ans_query7 + get_number_of_edges(x, y, get_point_mn(tin[x]), get_point_mn(tin[y]))) >> 1);
    }
    return 0;
}

/////////////////////////////////                   Modify  Queries


void query_1(int r) {
    int x = ed[r].second;
    int xx = ed[r].first;
    xx = get_last(1, sz, 1, tin[xx], 1, tout[xx]);
    if (!xx) xx = 1;
    xx = poc[xx];
    
    if (get_first_vertex(1, sz, tin[x], tout[x], 1)) {
        if (FIR < tin[x]) {
            if (bin_ed[r] == '0') ++ans_query7;
            else --ans_query7;
        }
        if (SEC > tout[x]) {
            if (bin_ed[r] == '0') ++ans_query7;
            else --ans_query7;
        }
    }
    
    if (bin_ed[r] == '1') {
        update_edge(tin[x], 0);
        update_cnt(1, sz, tin[x], tout[x], 1, -1);
        bin_ed[r] = '0';
    } else {
        update_edge(tin[x], tout[x]);
        update_cnt(1, sz, tin[x], tout[x], 1, 1);
        bin_ed[r] = '1';
    }
    
    if (bin_ed[r] == '0') {
        if (comp[x]) {
            update_component(x);
            if (!comp[xx]) update_component(xx);
        }
    } else if (comp[xx]) {
        if (is_there_somebody(x, 1)) {
            update_component(x);
            if (!is_there_somebody(xx, 1)) update_component(xx);
        }
    }
    return;
}

void query_2(int x, int z) {
    x = get_last(1, sz, 1, tin[x], 1, tout[x]);
    if (!x) x = 1;
    x = poc[x];
    if (!comp[x]) update_component(x);
    int y = get_point_mn(tin[x]);
    update_sum(1, sz, tin[x], tout[x], 1, z, y);
    return;
}

void query_6(int x) {
    x = get_last(1, sz, 1, tin[x], 1, tout[x]);
    if (!x) x = 1;
    x = poc[x];
    if (comp[x]) update_component(x);
    int y = get_point_mn(tin[x]);
    clr_node(1, sz, tin[x], tout[x], 1, y);
    return;
}

void query_3(int x) {
    int y = x;
    x = get_last(1, sz, 1, tin[x], 1, tout[x]);
    if (!x) x = 1;
    x = poc[x];
    long long xx = query_5(x);
    clr_node(1, sz, tin[x], tout[x], 1, get_point_mn(tin[x]));
    update_sum_point(1, sz, tin[y], 1, xx);
    return;
}

///////////                             INIT Queries O(n)

bool dfs_init(int x, int y, bool edge) {
    bool is_there = false;
    if (t[sz + tin[x] - 1].sum) is_there = true;
    for (int i = 0; i < v[x].size(); ++i) {
        int to = v[x][i].first;
        if (to == y) continue;
        if (bin_ed[v[x][i].second] == '1') {
            dfs_init(to, x, 1);
        } else {
            if (dfs_init(to, x, 0)) is_there = true;
        }
    }
    if (edge && is_there) {
        comp[x] = 1;
        vert_cnt[sz + tin[x] - 1] = 1;
    }
    return is_there;
}

bool dfs_init2(int x, int y) {
    bool is_there = false;
    if (t[sz + tin[x] - 1].sum) is_there = true;
    for (int i = 0; i < v[x].size(); ++i) {
        int to = v[x][i].first;
        if (to == y) continue;
        if (bin_ed[v[x][i].second] == '1') {
            if (dfs_init2(to, x)) {
                is_there = true;
                ++ans_query7;
            }
        } else if (dfs_init2(to, x)) is_there = true;
    }
    return is_there;
}

void dfs_init3(int x, int y, int _d, int l) {
    if (x == l) ans_query7 -= _d;
    for (int i = 0; i < v[x].size(); ++i) {
        int to = v[x][i].first;
        if (to != y) dfs_init3(to, x, _d + (bin_ed[v[x][i].second] - '0'), l);
    }
    return;
}

///////////////////////////////                 INIT



void init(int N, vector<int> v, vector<int> u, vector<int> b, vector<int> a, int GROUP) {
    n = N;
    int x, y;
    for (int i = 1; i < n; ++i) {
        x = v[i - 1];
        y = u[i - 1];
        ed[i] = {x, y};
        ::v[x].push_back({y, i});
        ::v[y].push_back({x, i});
    }
    bin_ed = "#";
    for (int i = 0; i < b.size(); ++i)
        bin_ed += char(b[i] + '0');
    dfs(1, 0);
    build_sparse_table();
    for (int i = 1; i < n; ++i) {
        x = ed[i].first;
        y = ed[i].second;
        if (tin[y] < tin[x]) swap(ed[i].first, ed[i].second);
    }
    sz = 1;
    while (sz < n) sz += sz;
    for (int i = 1; i <= n; ++i)
        t[sz + i - 1].cnt_mn = 1;
    for (int i = sz - 1; i > 0; --i)
        t[i].cnt_mn = t[i + i].cnt_mn + t[i + i + 1].cnt_mn;
    
    int rr;
    for (int i = 1; i < n; ++i)
        if (bin_ed[i] == '1') {
            rr = ed[i].second;
            max_tout[tin[rr] + sz - 1] = tout[rr];
            qob[tin[rr]]++;
            qob[tout[rr] + 1]--;
        }
    for (int i = 1; i <= n; ++i) {
        qob[i] += qob[i - 1];
        t[sz + tin[i] - 1].sum += a[i - 1];
        t[sz + i - 1].mn = qob[i];
    }
    for (int i = sz - 1; i > 0; --i) {
        max_tout[i] = max_tout[i + i];
        if (max_tout[i + i + 1] > max_tout[i]) max_tout[i] = max_tout[i + i + 1];
        update_NODE(i);
    }
    
    dfs_init(1, 0, true);
    for (int i = sz - 1; i > 0; --i)
        vert_cnt[i] = vert_cnt[i + i] + vert_cnt[i + i + 1];
    
    int pos = 0;
    for (int i = 1; i <= n; ++i)
        if (comp[i]) {
            pos = i;
            break;
        }
    if (pos) {
        dfs_init2(pos, 0);
        ans_query7 *= 2;
        int fir = -1;
        int last = -1;
        for (int i = 1; i <= n; ++i)
            if (comp[poc[i]]) {
                if (fir == -1) fir = i;
                last = i;
            }
        FIR = fir;
        SEC = last;
        fir = poc[fir];
        last = poc[last];
        dfs_init3(fir, 0, 0, last);
    }
    return;
}
int main() {
	cin.tie(0)->sync_with_stdio(false);
	int n, m, g;
	vector<int> u, v;
	cin >> g;
	cin >> n >> m;
	u.resize(n-1);
	v.resize(n-1);
	for(int i = 0; i < n-1; i++) cin >> u[i] >> v[i];
	vector<int> a(n), b(n);
	char ch;
	for(int i = 0; i < n-1; i++) cin >> ch, b[i] = ch-'0';
	for(auto &i : a) cin >> i;
	int t, e, x, y;
	init(n, v, u, b, a, g);
	while(m--) {
		cin >> t;
		if(t == 1) cin >> e, query_1(e);
		if(t == 2) cin >> x >> y, query_2(x, y);
		if(t == 3) cin >> e, query_3(e);
		if(t == 4) cin >> e, cout << query_4(e) << endl;
		if(t == 5) cin >> e, cout << query_5(e) << endl;
		if(t == 6) cin >> e, query_6(e);
		if(t == 7) cout << query_7() << endl;
	}
}
