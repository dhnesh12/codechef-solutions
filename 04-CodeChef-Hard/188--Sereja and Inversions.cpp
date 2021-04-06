// Why am I so dumb? :c
// chrono::system_clock::now().time_since_epoch().count()
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

#define pb push_back
#define mp make_pair

#define all(x) (x).begin(), (x).end()

#define fi first
#define se second

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<int, int> pii; 
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int MAXN = (int)1e5 + 5;
const int MOD = (int)1e9 + 7;
const int INF = (int)1e9;      

struct node {
    int sum, c1, c2;

    node() {
        sum = c1 = c2 = 0;
    }    
};

vector<node> pers;

int fact[MAXN];

int root[MAXN];

int rev[MAXN];

int arr[MAXN];

int n, q;

int addMod(int a, int b, int m = MOD) {
    a += b;

    if (m <= a) {
        a -= m;
    }

    return a;
}

int mulMod(int a, int b, int m = MOD) {
    return a * 1ll * b % m;
}

int binPow(int a, int b) {
    int ret = 1;

    while (b > 0) {
        if (b & 1) {
            ret = mulMod(ret, a);
        }

        a = mulMod(a, a);
        b >>= 1;
    }

    return ret;
}

void pre() {
    fact[0] = 1;
    rev[0] = 1;

    for (int i = 1; i < MAXN; ++i) {
        fact[i] = mulMod(fact[i - 1], i);
    } 

    for (int i = 1; i < MAXN; ++i) {
        rev[i] = binPow(fact[i], MOD - 2);
    }
}

int newleaf() {
    node it;
    it.sum = 1;
    pers.pb(it);
    return (int)pers.size() - 1;
}

int newpar(int a, int b) {
    node it;
    it.sum = pers[a].sum + pers[b].sum;
    it.c1 = a;
    it.c2 = b;
    pers.pb(it);
    return (int)pers.size() - 1;
}

int updVal(int v, int tl, int tr, int pos) {
    if (tl == tr) {
        return newleaf();
    }

    int mid = (tl + tr) >> 1;
    
    if (pos <= mid) {
        return newpar(updVal(pers[v].c1, tl, mid, pos), pers[v].c2);
    }
    else {
        return newpar(pers[v].c1, updVal(pers[v].c2, mid + 1, tr, pos));
    }
}

int kthQuery(int v0, int v1, int tl, int tr, int k) {
    if (tl == tr) {
        return tl;
    }

    int mid = (tl + tr) >> 1;
    int cur = pers[pers[v1].c1].sum - pers[pers[v0].c1].sum;

    if (cur >= k) {
        return kthQuery(pers[v0].c1, pers[v1].c1, tl, mid, k);
    }
    else {
        return kthQuery(pers[v0].c2, pers[v1].c2, mid + 1, tr, k - cur);
    }
}

int lowerBound(int v0, int v1, int tl, int tr, int x) {
    if (tl == tr) {
        return 1;
    }

    int mid = (tl + tr) >> 1;
    int cur = pers[pers[v1].c1].sum - pers[pers[v0].c1].sum;

    if (x > mid) {
        return cur + lowerBound(pers[v0].c2, pers[v1].c2, mid + 1, tr, x);
    }
    else {
        return lowerBound(pers[v0].c1, pers[v1].c1, tl, mid, x);
    }    
}

int query(int l1, int r1, int l2, int r2) {
    int ret = 1, ptr = 1;                           
    int len = r1 - l1 + 1;

    while (ptr <= len) {
        int B_ptr = kthQuery(root[l2 - 1], root[r2], 1, n, ptr); 
        int pos = lowerBound(root[l1 - 1], root[r1], 1, n, B_ptr);
        int nxt;

        if (pos > len) {
            nxt = len + 1;                        
        }
        else {
            int A_pos = kthQuery(root[l1 - 1], root[r1], 1, n, pos);
            nxt = lowerBound(root[l2 - 1], root[r2], 1, n, A_pos);
        }

        ret = mulMod(ret, mulMod(fact[pos - ptr], rev[pos - nxt]));
        ptr = nxt;        
    }        
    
    return ret;
}

void solve() {
    scanf("%d %d", &n, &q);
    pers.clear();
    pers.pb(node());
    root[0] = 0;

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &arr[i]);
        root[i] = updVal(root[i - 1], 1, n, arr[i]);
    }    

    for (int i = 1; i <= q; ++i) {
        int l1, r1, l2, r2;
        scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
        printf("%d\n", query(l1, r1, l2, r2));
    }    
}

int main() {
    int tt;
    scanf("%d", &tt);

    pre();

    while (tt--) {
        solve();
    }

    return 0;
}