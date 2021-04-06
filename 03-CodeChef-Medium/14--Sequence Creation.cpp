#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define sz(x) ((int)x.size())
#define i2 array<int,2>
#define i3 array<int,3>
#define PB push_back
using namespace std;
typedef long long ll;
const int N = 200100;
const int md = int(1e9) + 7;
vector<i3> rollbacks;
vector<int> vc;
int a[N], b[N], ans[N], pre[N], siz[N], edg[N], n, cans[N];
int res = 1, inv[N];

int mult(int x, int y) { return (1ll * x * y) % md; }

int sum(int x, int y){
    x += y;
    if (x >= md)
        x -= md;
    return x;
}

int binpow(int x, int po){
    int res = 1;

    while (po > 0){
        if (po & 1)
            res = mult(res, x);

        x = mult(x, x);
        po >>= 1;
    }

    return res;
}

int get(int x) { return (x == pre[x] ? x : get(pre[x])); }

void rollback(int id){
    while (sz(rollbacks) > id){
        int cx = rollbacks.back()[0];
        int cy = rollbacks.back()[1];

        if (cy > 0){
            pre[cy] = cy;
            siz[cx] -= siz[cy];
            edg[cx] -= edg[cy] + 1;

            res = mult(res, inv[cans[cx]]);

            cans[cx] = rollbacks.back()[2];

            res = mult(res, cans[cx]);
            res = mult(res, cans[cy]);
        } else {
            res = mult(res, inv[cans[cx]]);

            edg[cx]--;
            cans[cx] = siz[cx];

            res = mult(res, cans[cx]);
        }

        rollbacks.pop_back();
    }
}

bool link(int j){
    int x = a[j], y = b[j];
    int cx = get(x), cy = get(y);

    if (cx != cy){
        if (edg[cx] + edg[cy] + 1 > siz[cx] + siz[cy])
            return 0;

        res = mult(res, inv[cans[cx]]);
        res = mult(res, inv[cans[cy]]);

        if (siz[cx] < siz[cy]) swap(cx, cy);

        rollbacks.PB({cx, cy, cans[cx]});

        bool van = bool(edg[cx] == siz[cx]);

        pre[cy] = cx;
        siz[cx] += siz[cy];
        edg[cx] += edg[cy] + 1;

        if (edg[cx] == siz[cx]) {
            if (van)
                cans[cx] = cans[cx];
            else cans[cx] = cans[cy];
        } else cans[cx] = siz[cx];

        res = mult(res, cans[cx]);
    } else {
        if (edg[cx] == siz[cx])
            return 0;
        else {
            res = mult(res, inv[cans[cx]]);

            rollbacks.PB({cx, -1, -1});

            edg[cx]++;

            cans[cx] = (x == y ? 1 : 2);

            res = mult(res, cans[cx]);
        }
    }

    return 1;
}

void calc(int l, int r, int opt_l, int opt_r){
    int mem_ed = sz(rollbacks);

    int opt = -1;

    int md = (l + r) >> 1;

    assert(md <= opt_r);

    for (int j = md; j < min(r + 1, opt_l); j++)
        assert(link(j));

    for (int j = max(md, opt_l); j <= opt_r; j++) {
        if (link(j))
            opt = j;
        else break;
    }

    assert(opt >= md);

    ans[md] = res;

    rollback(mem_ed);

    if (l < md){
        for (int j = md; j < min(opt_l, r + 1); j++)
            assert(link(j));

        calc(l, md - 1, opt_l, opt);

        rollback(mem_ed);
    }

    if (md < r){
        for (int j = max(r + 1, opt_l); j < opt; j++)
            assert(link(j));

        calc(md + 1, r, opt, opt_r);

        rollback(mem_ed);
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

#ifdef _LOCAL
    freopen("in.txt","r",stdin);
#endif // _LOCAL

    inv[1] = 1;

    for (int i = 2; i < N; i++)
        inv[i] = binpow(i, md - 2);

    int qq; cin >> qq;

    for (; qq; qq--){
        cin >> n;

        vc.clear();

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            vc.PB(a[i]);
        }

        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            vc.PB(b[i]);
        }

        sort(all(vc));
        vc.resize(unique(all(vc)) - vc.begin());

        for (int i = 1; i <= n; i++){
            a[i] = lower_bound(all(vc), a[i]) - vc.begin();
            a[i]++;
        }

        for (int i = 1; i <= n; i++){
            b[i] = lower_bound(all(vc), b[i]) - vc.begin();
            b[i]++;
        }

        for (int i = 1; i <= sz(vc); i++){
            pre[i] = i;
            siz[i] = 1;
            edg[i] = 0;
            cans[i] = 1;
        }

        calc(1, n, 1, n);

        for (int i = 1; i <= n; i++)
            cout << ans[i] << " ";
        cout << '\n';
    }

    return 0;
}
