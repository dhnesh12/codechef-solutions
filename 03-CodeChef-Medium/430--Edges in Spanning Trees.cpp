#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;

using pii = pair<int, int>;

const int MAX_N = 200000;

vector<int> gph1[MAX_N + 5];
vector<int> edgeNum1[MAX_N + 5];
int N;

int TIME1;
int in1[MAX_N + 5];
int out1[MAX_N + 5];
int par1[MAX_N + 5];
int ed1[MAX_N + 5];
void dfs1(int u, int p = -1) {
  in1[u] = ++TIME1;
  par1[u] = p;
  for(unsigned e = 0; e < gph1[u].size(); e++) {
    int v = gph1[u][e];
    if(v != p) {
      ed1[v] = edgeNum1[u][e];
      dfs1(v, u);
    }
  }
  out1[u] = TIME1;
}

vector<int> gph2[MAX_N + 5];

int TIME2;
int in2[MAX_N + 5];
int sz2[MAX_N + 5];
int heavy2[MAX_N + 5];
int par2[MAX_N + 5];
int head2[MAX_N + 5];
int level2[MAX_N + 5];
int chain2[MAX_N + 5];
int pos2[MAX_N + 5];
void dfs2(int u, int p = -1) {
  in2[u]= ++TIME2;
  sz2[u] = 1;
  for(int v : gph2[u]) if(v != p) {
    level2[v] = level2[u] + 1;
    dfs2(v, u);
    par2[v] = u;
    sz2[u] += sz2[v];
    if(heavy2[u] == 0 || sz2[v] > sz2[heavy2[u]]) {
      heavy2[u] = v;
    }
  }
}

typedef tree<
  pair<int, int>,
  null_type,
  less< pair<int, int> >,
  rb_tree_tag,
  tree_order_statistics_node_update> myset;

myset *intervals[MAX_N + 5];

myset *merge (myset *set1, myset *set2) {
  if(set1->size() < set2->size()) swap(set1, set2);

  for(auto interval : *set2) {
    {
      auto it1 = set1->upper_bound(interval);
      if(it1 != set1->end() && it1->first == interval.second + 1) {
        // merge
        interval.second = it1->second;
        set1->erase(it1);
      }
    }
    {
      auto it1 = set1->lower_bound(interval);
      if(it1 != set1->begin()) {
        it1--;
        if(it1->second + 1 == interval.first) {
          interval.first = it1->first;
          set1->erase(it1);
        }
      }
    }
    
    set1->insert(interval);
  }

  set2->clear();
  delete set2;
  return set1;
}

int ans[MAX_N + 5];

void go(int u) {
  intervals[u] = new myset;
  intervals[u]->insert(make_pair(pos2[u], pos2[u]));

  for(int v : gph1[u]) if(par1[v] == u) {
    go(v);
    intervals[u] = merge(intervals[u], intervals[v]);
  }

  auto *s = intervals[u];

  auto calc = [s](int u2, int v2) {
    if(s->empty()) return 0;

    int l = pos2[u2], r = pos2[v2]; if(l > r) swap(l, r);
    if(l == r) return 0;

    // l <= r

    auto ity = --s->upper_bound(make_pair(r, int(1e9)));
    if(ity->first <= l && r <= ity->second) {
      return 0;
    }

    auto itx = --s->upper_bound(make_pair(l, int(1e9)));

    if(itx == s->end() && ity == s->end()) {
      return 0;
    }

    if(itx == s->end() || itx->second < l) itx++;

    if(itx == s->end()) {
      return 0;
    }
    
    int ret = (l < itx->first ? 1 : 0) + (ity->second < r ? 1 : 0);
    if(itx != ity) {
      ret += (s->order_of_key(*ity) - s->order_of_key(*itx)) * 2;
    }
    return ret;
  };

  auto inside = [&](int v) {
    return in1[u] <= in1[v] && in1[v] <= out1[u];
  };

  if(par1[u] > 0) {
    int ret = 0;
    int a = u, b = par1[u];
    while(chain2[a] != chain2[b]) {
      int *t = (level2[head2[a]] > level2[head2[b]]) ? &a : &b;
      ret += calc(*t, head2[*t]);
      if(inside(head2[*t]) ^ inside(par2[head2[*t]])) ret += 1;
      *t = par2[head2[*t]];
    }
    ret += calc(a, b);
    ans[ed1[u]] = ret;
  }
}

void solve() {
  cin >> N;
  assert(2 <= N && N <= MAX_N);

  for(int _ = 1; _ <= N-1; _++) {
    int u, v; cin >> u >> v; 
    assert(1 <= u && u <= N);
    assert(1 <= v && v <= N);
    assert(u != v);
    gph1[u].emplace_back(v);
    gph1[v].emplace_back(u);
    edgeNum1[u].emplace_back(_);
    edgeNum1[v].emplace_back(_);
  }

  for(int _ = 1; _ <= N-1; _++) {
    int u, v; cin >> u >> v;
    assert(1 <= u && u <= N);
    assert(1 <= v && v <= N);
    assert(u != v);
    gph2[u].push_back(v);
    gph2[v].push_back(u);
  }

  dfs1(1);

  dfs2(1);
  for(int i = 1, x = 0, c = 0; i <= N; i++) {
    if(par2[i] == 0 || heavy2[par2[i]] != i) {
      c += 1;
      for(int u = i; u > 0; u = heavy2[u]) {
        pos2[u] = ++x;
        chain2[u] = c;
        head2[u] = i;
      }
    }
  }

  go(1);

  for(int i = 1; i <= N-1; i++) {
    cout << ans[i] << (i < N-1 ? ' ': '\n');
  }

  // initialization
  for(int i = 1; i <= N; i++) {
    gph1[i].clear();
    edgeNum1[i].clear();
    gph2[i].clear();
    in1[i] = 0;
    out1[i] = 0;
    par1[i] = 0;
    ed1[i] = 0;

    in2[i] = 0;
    sz2[i] = 0;
    pos2[i] = 0;
    head2[i] = 0;
    heavy2[i] = 0;
    level2[i] = 0;
    chain2[i] = 0;

    ans[i] = 0;
  }
  TIME1 = 0;
  TIME2 = 0;
  N = 0;
}

int main() {
#ifdef IN_MY_COMPUTER
  assert(freopen("edgest.in", "r", stdin) != NULL);
#else
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
#endif

  int T; assert(cin >> T);
  assert(1 <= T && T <= 10);
  while(T--) {
    solve();
  }
  return 0;
}