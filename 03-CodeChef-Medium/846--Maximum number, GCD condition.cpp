// Smit Vavliya

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = (1LL<<60) - 1;
const int mod = 998244353;

const int N = 1e5 + 5;
int arr[N];

vector<int> primes[N];
int mark[N];
void init() {
    for(int i = 2; i <= N; i++) {
        if(!mark[i]) {
            for(int j = i; j <= N; j += i) {
                primes[j].push_back(i);
                mark[j]++;
            }
        }
    }
}

vector<vector<int>> v(N);
vector<vector<pair<int, int>>> st(N);

pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
    if(a.first > b.first) 
        return a;
    if(a.first < b.first) 
        return b;
    return {a.first, a.second + b.second};
}

void build(int node, int start, int end, vector<pair<int, int>> &t, vector<int> &v) {
    if(start == end) {
        t[node] = {arr[v[start]], 1};
    } else {
        int mid = (start + end) / 2;
        build(node * 2, start, mid, t, v);
        build(node * 2 + 1, mid + 1, end, t, v);

        t[node] = combine(t[node * 2], t[node * 2 + 1]);
    }
}

pair<int, int> query(int node, int start, int end, int l, int r, vector<pair<int, int>> &t, vector<int> &v) {
    if(start > end || r < start || l > end) 
        return {-inf, 0};
    
    if(start >= l && end <= r) 
        return t[node];

    int mid = (start + end) / 2;
    auto left = query(node * 2, start, mid, l, r, t, v);
    auto right = query(node * 2 + 1, mid + 1, end, l, r, t, v);

    return combine(left, right);
}

void buildSegtree() {
    for(int i = 1; i <= N; i++) {
        if(v[i].size()) {
            st[i].resize(4 * v[i].size());
            build(1, 0, v[i].size() - 1, st[i], v[i]);
        }
    }   
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
        for(auto &x : primes[arr[i]]) {
            v[x].push_back(i);
        }
    }
    buildSegtree();
    while(q--) {
        int G, l, r;
        cin >> G >> l >> r;
        pair<int, int> ans(-1, -1);
        for(auto &x : primes[G]) {
            if(v[x].empty()) 
                continue;
            int left = lower_bound(v[x].begin(), v[x].end(), l) - v[x].begin(); 
            if(left == v[x].size()) continue;
            int right = upper_bound(v[x].begin(), v[x].end(), r) - v[x].begin();
            right--;
            auto res = query(1, 0, v[x].size() - 1, left, right, st[x], v[x]);
            if(res.first > ans.first) ans = res;
        }
        cout << ans.first << " " << ans.second << endl;
    }
}