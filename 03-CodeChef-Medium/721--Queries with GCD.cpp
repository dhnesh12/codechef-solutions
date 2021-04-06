#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10, mod = 998244353;
int n, q, arr[N], tree[N<<2], ans[(int)5e5 + 10];
bool composite[N];
vector<int> pr, d[N];
vector<pair<int, int>> fac;
unordered_map<int, int> pre;
struct Query {
    int l, r, idx;
    bool operator < (const Query &ob) {
        return r > ob.r;
    }
};
void factorize(int x) {
    fac.clear();
    for(int p : pr) {
        if(p * p > x) break;
        if(x % p == 0) fac.push_back({p, 0});
        while(x % p == 0) {
            x /= p;
            fac.back().second++;
        }
    }
    if(x > 1) fac.push_back({x, 1});
}
void gen_divisors(int idx, int i, int cur) {
    if(i == fac.size()) {
        d[idx].push_back(cur);
        return;
    }
    gen_divisors(idx, i + 1, cur);
    for(int j = 1; j <= fac[i].second; j++) {
        cur *= fac[i].first;
        gen_divisors(idx, i + 1, cur);
    }
}
void upd(int i, int va, int x = 1, int l = 1, int r = n) {
    if(l == r) {
        tree[x] = max(tree[x], va);
        return;
    }
    int mid = (l + r) >> 1;
    if(i <= mid) upd(i, va, x<<1, l, mid);
    else upd(i, va, x<<1|1, mid + 1, r);
    tree[x] = max(tree[x<<1], tree[x<<1|1]);
}
int query(int i, int j, int x = 1, int l = 1, int r = n) {
    if(l >= i && r <= j) return tree[x];
    if(l > j || i > r) return 0;
    int mid = (l + r) >> 1;
    return max(query(i, j, x<<1, l, mid), query(i, j, x<<1|1, mid + 1, r));
}
void add(int i) {
    for(int div : d[i]) {
        if(pre[div] > 0) upd(pre[div], div);
        pre[div] = i;
    }
}

int main(){
    //ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    for(int i = 2; i < N; i++) {
        if(composite[i]) continue;
        for(int j = i + i; j < N; j += i) composite[j] = 1;
        pr.push_back(i);
    }
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
        factorize(arr[i]);
        gen_divisors(i, 0, 1);
    }
    vector<Query> Q(q);
    for(int i = 0; i < q; i++) {
        scanf("%d%d", &Q[i].l, &Q[i].r);
        Q[i].idx = i;
    }
    sort(Q.begin(), Q.end());
    for(int i = 1; i <= n && Q.size(); i++) {
        add(i);
        while(Q.size() && Q.back().r == i) {
            ans[Q.back().idx] = max(query(Q.back().l, Q.back().r), 1);
            Q.pop_back();
        }
    }
    for(int i = 0; i < q; i++)
        printf("%d\n", ans[i]);
    return 0;
}