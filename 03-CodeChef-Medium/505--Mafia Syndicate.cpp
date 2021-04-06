#include<bits/stdc++.h>

typedef long long ll;
typedef long double lld;
using namespace std;

#define endl "\n"
#define fi first
#define se second
#define MEMS(a,b) memset(a,b,sizeof(a))
#define _ ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define __ freopen("input.txt","r",stdin);freopen("output.txt","w",stdout);
#define all(c) c.begin(),c.end()
#define pii pair<int, int>

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r)
{
	uniform_int_distribution<int> uid(l, r);
	return uid(rng);
}

#define tr(...) cout<<__FUNCTION__<<' '<<__LINE__<<" = ";trace(#__VA_ARGS__, __VA_ARGS__)
template<typename S, typename T>
ostream& operator<<(ostream& out,pair<S,T> const& p){out<<'('<<p.fi<<", "<<p.se<<')';return out;}

template<typename T>
ostream& operator<<(ostream& out,vector<T> const& v){
ll l=v.size();for(ll i=0;i<l-1;i++)out<<v[i]<<' ';if(l>0)out<<v[l-1];return out;}

template <typename T>
ostream &operator<<(ostream &out, set<T> const &v) {
    for (auto i = v.begin(); i != v.end(); i++)
        out << (*i) << ' ';
    return out;
}
template <typename T>
ostream &operator<<(ostream &out, multiset<T> const &v) {
    for (auto i = v.begin(); i != v.end(); i++)
        out << (*i) << ' ';
    return out;
}
template <typename T, typename V>
ostream &operator<<(ostream &out, map<T, V> const &v) {
    for (auto i = v.begin(); i != v.end(); i++)
        out << "\n" << (i->first) <<  ":"  << (i->second);
    return out;
}

template<typename T>
void trace(const char* name, T&& arg1){cout<<name<<" : "<<arg1<<endl;}

template<typename T, typename... Args>
void trace(const char* names, T&& arg1, Args&&... args){
const char* comma = strchr(names + 1, ',');cout.write(names, comma-names)<<" : "<<arg1<<" | ";trace(comma+1,args...);}

#define int ll

const int N = 1e5 + 10;

int sz[N];
bool big[N];
int have[N], cap[N];
int n;
int dpt[N];

vector<vector<int>> g(N);

int t[4*N];
int off[N];

int get(int v, int tl, int tr, int val) {
    if (t[v] <= val) return 0;
    if (tl == tr) {
        // tr(t[v], tl, val);
        return tl;
    }
    int tm = (tl + tr) / 2;
    if (t[2 * v] > val) {
        return get(2 * v, tl, tm, val);
    } else if (t[2 * v + 1] > val) {
        return get(2 * v + 1, tm + 1, tr, val);
    }
    return 0;
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] += new_val;
        // tr(tl, t[v], pos);
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}

void dfs0(int v, int p, int d = 1) {
    sz[v] = 1;
    dpt[v] = d;
    for (auto u : g[v]) {
        if (u == p) continue;
        dfs0(u, v, d + 1);
        sz[v] += sz[u];
    }    
}

vector<vector<int>> present(N);

void add(int v, int p, int x){
    // tr(v, dpt[v], have[v]);
    update(1, 1, n, dpt[v], have[v]);
    present[dpt[v]].push_back(v);
    for(auto u: g[v])
        if(u != p && !big[u] && (off[u] == 0))
            add(u, v, x);
}


void dfs(int v, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(auto u : g[v])
       if(u != p && sz[u] > mx)
          mx = sz[u], bigChild = u;
    for(auto u : g[v])
        if(u != p && u != bigChild)
            dfs(u, v, 0);  // run a dfs on small childs and clear them from cnt
    if(bigChild != -1)
        dfs(bigChild, v, 1), big[bigChild] = 1;  // bigChild marked as big and not cleared from cnt
    add(v, p, 1);
    int x = get(1, 1, n, cap[v]);
    // tr(v, x, cap[v]);
    if (x != 0 && v != 1) {
        for (int i = x; i <= n; i++) {
            if (present[i].empty()) break;
            for (auto j : present[i]) {
                // tr(j);
                update(1, 1, n, i, -have[j]);
                off[j] = 1;
            }
            present[i].clear();
        }
    }
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    if(bigChild != -1)
        big[bigChild] = 0;
    if(keep == 0) {
        for (int i = dpt[v]; i <= n; i++) {
            if (present[i].empty()) break;
            for (auto j : present[i]) {
                update(1, 1, n, i, -have[j]);
            }
            present[i].clear();
        }
    }
}

int solve() {
    cin >> n;
    for (int i = 2; i <= n; i++) {
        cin >> have[i] >> cap[i];
    }

    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
    }
    dfs0(1, 0);
    dfs(1, 0, 1);

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (auto j : present[i]) {
            ans += have[j];
        }
    }
    cout << ans << endl;
    return 0;
}

int32_t main(){ _
    int t;
    // cin >> t;
    t = 1;
    while (t--) solve();
    return EXIT_SUCCESS;	
}
