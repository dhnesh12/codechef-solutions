#include<bits/stdc++.h>

using namespace std;

#define For(i, a, b) for(int i = a; i <= b; ++ i)
#define pb push_back
#define ii pair<int, int>
#define fi first
#define se second

const int N = 3e5 + 5, INF = 1e9 + 1;
int n, q, cnt, sz, used;
int child[N], head[N], pos[N], p[N], ind[N], root[N], val[N], lazy[N];
vector <ii> adj[N], cycle;

struct data{
    int sum, ans_max, lef_max, rig_max, ans_min, lef_min, rig_min;
}node[4*N];

stack<ii> s;

void solve(int u, int w, int pa){
    if(used) return; s.push(ii(u, w)); p[u] = pa;
    for(ii v : adj[u]){
        if(v.fi == pa || used) continue;
        if(p[v.fi]){
            while(s.size() > 0){
                cycle.pb(s.top());
                if(s.top().fi == v.fi) break;
                s.pop();
            }
            reverse(cycle.begin(), cycle.end());
            cycle[0].se = v.se; used = true;
        }
        solve(v.fi, v.se, u);
    }
    if(s.size() > 0) s.pop(); p[u] = 0;
}

void dfs(int u){
    child[u] = 1;
    for(ii v: adj[u]){
        if(v.fi == p[u] || pos[v.fi]) continue;
        if(u != n) root[v.fi] = root[u];
        p[v.fi] = u; dfs(v.fi);
        child[u] += child[v.fi];
    }
}

void hld(int u, int w){
    if(!head[cnt]) head[cnt] = u;
    ind[u] = cnt; pos[u] = ++sz; val[sz] = w;
    ii Max = ii(0, 0);
    for(ii v: adj[u]) if(v.fi != p[u] && !pos[v.fi] && child[v.fi] > child[Max.fi]) Max = v;
    if(Max.fi) hld(Max.fi, Max.se);
    for(ii v: adj[u]) if(v.fi != p[u] && !pos[v.fi] && v != Max) cnt++, hld(v.fi, v.se);
}

void prepare(){
    solve(1, 0, 1); n++;
    for(ii u : cycle) pos[u.fi] = ++sz, val[sz] = u.se;
    for(ii u : cycle) for(ii v: adj[u.fi])
    if(!pos[v.fi]) root[v.fi] = u.fi, adj[n].pb(v);
    dfs(n);  hld(n, 0);
}

data cal(data res1, data res2){
    data res;
    res.sum = res1.sum + res2.sum;
    res.lef_min = min(res1.lef_min, res1.sum + res2.lef_min);
    res.rig_min = min(res2.rig_min, res1.rig_min + res2.sum);
    res.ans_min = min(min(res1.ans_min, res2.ans_min), res1.rig_min + res2.lef_min);
    res.lef_max = max(res1.lef_max, res1.sum + res2.lef_max);
    res.rig_max = max(res2.rig_max, res1.rig_max + res2.sum);
    res.ans_max = max(max(res1.ans_max, res2.ans_max), res1.rig_max + res2.lef_max);
    return res;
}

void build_tree(int i, int l, int r){
    if(l > r) return;
    if(l == r){
        int x = val[l];
        node[i] = data{x, x, x, x, x, x, x};
        return;
    }
    int mid = l + r >> 1;
    build_tree(i << 1, l, mid);
    build_tree(i << 1 | 1, mid + 1, r);
    node[i] = cal(node[i << 1], node[i << 1 | 1]);
}

void true_val(int i, int l, int r){
    if(l > r || lazy[i] % 2 == 0) return;
    swap(node[i].ans_max, node[i].ans_min);
    node[i].ans_min *= -1; node[i].ans_max *= -1;
    swap(node[i].lef_max, node[i].lef_min);
    node[i].lef_min *= -1; node[i].lef_max *= -1;
    swap(node[i].rig_max, node[i].rig_min);
    node[i].rig_min *= -1; node[i].rig_max *= -1;
    node[i].sum *= -1;
    if(l != r){
        lazy[i << 1] += lazy[i];
        lazy[i << 1 | 1] += lazy[i];
    }
    lazy[i] = 0;
}

void update(int i, int l, int r, int a, int b){
    true_val(i, l, r);
    if(l > r || r < a || b < l) return;
    if(a <= l && r <= b){
        lazy[i] ++; true_val(i, l, r);
        return;
    }
    int mid = l + r >> 1;
    update(i << 1, l, mid, a, b);
    update(i << 1 | 1, mid + 1, r, a, b);
    node[i] = cal(node[i << 1], node[i << 1 | 1]);
}

data get(int i, int l, int r, int a, int b){
    true_val(i, l, r);
    if(l > r || r < a || b < l) return {0, -INF, -INF, -INF, INF, INF, INF};
    if(a <= l && r <= b) return node[i];
    int mid = l + r >> 1;
    data res1 = get(i << 1, l, mid, a, b);
    data res2 = get(i << 1 | 1, mid + 1, r, a, b);
    return cal(res1, res2);
}

// return (u: lef --> v: rig)
data change_cycle(int u, int v, int kt){
    bool check = false;
    if(pos[u] > pos[v]) swap(u, v), check = true;
    // pos[u] < pos[v]
    if((pos[v] - pos[u])* 2 < cycle.size()){
        // go u to v
        if(kt){
            data res = get(1, 1, n, pos[u] + 1, pos[v]);
            if(check) swap(res.lef_max, res.rig_max);
            return res;
        }
        else update(1, 1, n, pos[u] + 1, pos[v]);
    }
    else{
        // go v to u
        if(kt){
            data res = cal(get(1, 1, n, pos[v] + 1, cycle.size()), get(1, 1, n, 1, pos[u]));
            if(!check) swap(res.lef_max, res.rig_max);
            return res;
        }
        else{
            update(1, 1, n, 1, pos[u]);
            update(1, 1, n, pos[v] + 1, cycle.size());
        }
    }
}

data change_hld(int u, int v, int kt){
    data res_u = {0, -INF, -INF, -INF, INF, INF, INF}, res_v = res_u;
    while(ind[u] != ind[v]){
            if(ind[u] > ind[v]){
                int x = head[ind[u]];
                if(kt) res_u = cal(get(1, 1, n, pos[x], pos[u]), res_u);
                else update(1, 1, n, pos[x], pos[u]);
                u = p[x];
            }
            else{
                int x = head[ind[v]];
                if(kt) res_v = cal(get(1, 1, n, pos[x], pos[v]), res_v);
                else update(1, 1, n, pos[x], pos[v]);
                v = p[x];
            }
    }
    if(pos[u] < pos[v]){
        if(kt) res_v = cal(get(1, 1, n, pos[u] + 1, pos[v]), res_v);
        else update(1, 1, n, pos[u] + 1, pos[v]);
    }
    else{
        if(kt) res_u = cal(get(1, 1, n, pos[v] + 1, pos[u]), res_u);
        else update(1, 1, n, pos[v] + 1, pos[u]);
    }
    swap(res_v.lef_max, res_v.rig_max);
    return cal(res_v, res_u);
}

int change(int u, int v, int kt){
    data res;
    if(pos[u] <= cycle.size() && pos[v] <= cycle.size()){
        res = change_cycle(u, v, kt);
        return res.ans_max;
    }
    if(pos[u] > cycle.size() && pos[v] > cycle.size()){
        if(root[u] == root[v]) return change_hld(u, v, kt).ans_max;
        else{
            res = cal(change_cycle(root[v], root[u], kt), change_hld(u, n, kt));
            swap(res.lef_max, res.rig_max);
            res = cal(res, change_hld(v, n, kt));
            return res.ans_max;
        }
    }
    if(pos[u] > cycle.size()) swap(u, v);
    res = cal(change_cycle(u, root[v], kt), change_hld(v, n, kt));
    return res.ans_max;
}

signed main(){
    cin >> n;
    For(i, 1, n){
        int u, v, w; cin >> u >> v >> w;
        adj[u].pb(ii(v, w));
        adj[v].pb(ii(u, w));
    }
    prepare();
    build_tree(1, 1, n);
    cin >> q;
    while(q--){
        char c; int u, v;
        cin >> c >> u >> v;
        if(c == 'f') change(u, v, 0);
        else cout << max(0, change(u, v, 1)) << endl;
    }
}
