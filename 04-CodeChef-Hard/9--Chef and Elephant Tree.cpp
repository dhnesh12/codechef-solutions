
/********fft***************
import numpy as np
from scipy import signal

p=[1,1]
f = signal.fftconvolve(p, p)
f = np.around(f).astype(int)

print(f)

/*********** trie *******************
typedef struct data
{
       data* bit[2];
       int cnt = 0;
}trie;

trie* head;

void insert(int x)
{
       trie* cur = head;
       for(int i=30;i>=0;i--)
       {
               int b = (x>>i) & 1;
               if(!cur->bit[b])
                       cur->bit[b] = new trie();
               cur = cur->bit[b];
               cur->cnt++;
       }
}

void remove(int x)
{
       trie* cur = head;
       for(int i=30;i>=0;i--)
       {
               int b = (x>>i) & 1;
               cur = cur->bit[b];
               cur->cnt--;
       }
}

int maxxor(int x)
{
       trie* cur = head;
       int ans = 0;
       for(int i=30;i>=0;i--)
       {
               int b = (x>>i)&1;
               if(cur->bit[!b] && cur->bit[!b]->cnt>0)
               {
                       ans += (1LL<<i);
                       cur = cur->bit[!b];
               }
               else
                       cur = cur->bit[b];
       }
       return ans;
}
/*********** extended euclid *******************
int xgcd(int a, int b, int &x, int &y) //Returns GCD of A, B
{
       if(a==0)
       {
               x=0;
               y=1;
               return b;
       }
       int x1, y1;
       int d = xgcd(b % a, a, x1, y1);
       x = y1 - (b/a)*x1;
       y = x1;
       return d;
}

int modular_inverse(int a, int m)
{
       int x, y;
       int g=xgcd(a, m, x, y);
       if(g!=1)
               return -1;
       else
       {
               x=(x%m + m)%m;
               return x;
       }
}

void shift_solution(int &x, int &y, int a, int b, int cnt)
{
       x+=cnt*b;
       y-=cnt*a;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0)
{
       int g=xgcd(abs(a), abs(b), x0, y0);
       if(c%g!=0)
               return false;
       x0 *= c/g;
       y0 *= c/g;
       if(a<0)
               x0*=-1;
       if(b<0)
               y0*=-1;
       return true;
}

int find_all_solutions(int a, int b, int c, int minx, int maxx, int miny, int
maxy) //Returns number of solutions with x∈[minx, maxx], y∈[miny, maxy]
{
       int x, y, g;
       if(!find_any_solution(a, b, c, x, y, g))
               return 0;
       a /= g;
       b /= g;

       int sign_a = a>0 ? +1 : -1;
       int sign_b = b>0 ? +1 : -1;

       shift_solution(x, y, a, b, (minx - x) / b);
       if (x < minx) shift_solution(x, y, a, b, sign_b);
       if (x > maxx) return 0;
       int lx1 = x;

       shift_solution(x, y, a, b, (maxx - x) / b);
       if (x > maxx) shift_solution(x, y, a, b, -sign_b);
       int rx1 = x;

       shift_solution(x, y, a, b, - (miny - y) / a);
       if (y < miny) shift_solution(x, y, a, b, -sign_a);
       if (y > maxy) return 0;
       int lx2 = x;

       shift_solution(x, y, a, b, - (maxy - y) / a);
       if (y > maxy) shift_solution(x, y, a, b, sign_a);
       int rx2 = x;

       if (lx2 > rx2)
               swap (lx2, rx2);
       int lx = max (lx1, lx2);
       int rx = min (rx1, rx2);

       return (rx - lx) / abs(b) + 1;
}
/*********** bridge in graph *******************
int tim=0;
int u[N], v[N], vis[N];
int tin[N], tout[N], isBridge[M], minAncestor[N];
vector<pair<int, int> > g[N]; //vertex, index of edge

void dfs(int k, int par)
{
       vis[k]=1;
       tin[k]=++tim;
       minAncestor[k]=tin[k];
       for(auto it:g[k])
       {
               if(it.first==par)
                       continue;
               if(vis[it.first])
               {
                       minAncestor[k]=min(minAncestor[k], tin[it.first]);
                       continue;
               }
               dfs(it.first, k);
               minAncestor[k]=min(minAncestor[k], minAncestor[it.first]);
               if(minAncestor[it.first]>tin[k])
                       isBridge[it.second]=1;
       }
       tout[k]=tim;
}

//Sample Problem 1: https://www.spoj.com/problems/EC_P/
//Sample Solution 1: http://p.ip.fi/shDA
/*********** bridge tree *******************
int tim=0, grp=1;
int u[N], v[N], comp[N];
bool vis[N], vis2[N], isBridge[M];
int tin[N], tout[N], minAncestor[N];
queue<int> Q[N];
vector<pair<int, int> > g[N];
vector<int> tree[N], vertices[N]; //Tree stores Bridge Tree, vertices stores the
nodes in each component

void dfs(int k, int par)
{
       vis[k]=1;
       tin[k]=++tim;
       minAncestor[k]=tin[k];
       for(auto it:g[k])
       {
               if(it.first==par)
                       continue;
               if(vis[it.first])
               {
                       minAncestor[k]=min(minAncestor[k], tin[it.first]);
                       continue;
               }
               dfs(it.first, k);
               minAncestor[k]=min(minAncestor[k], minAncestor[it.first]);
               if(minAncestor[it.first]>tin[k])
                       isBridge[it.second]=1;
       }
       tout[k]=tim;
}

void dfs2(int k)
{
       int comp=grp;
       Q[comp].push(k);
       vis2[k]=1;
       while(!Q[comp].empty())
       {
               int u=Q[comp].front();
               Q[comp].pop();
               vertices[comp].push_back(u);
               for(auto it:g[u])
               {
                       int v=it.first;
                       int edgeidx=it.second;
                       if(vis2[v])
                               continue;
                       if(isBridge[edgeidx])
                       {
                               grp++;
                               tree[comp].push_back(grp);
                               tree[grp].push_back(comp);
                               dfs2(v);
                       }
                       else
                       {
                               Q[comp].push(v);
                               vis2[v]=1;
                       }
               }
       }
}

//Problem 1: http://codeforces.com/contest/1000/problem/E
//Solution 1: http://codeforces.com/contest/1000/submission/40743431

//Problem 2: http://codeforces.com/contest/178/problem/B3
//Solution 2: http://codeforces.com/contest/178/submission/40744889
/*********** online bridge *******************
const int N=1e5+5;

int n, bridges, m;
int bcc[N], comp[N], link[N], sz[N], vis[N];
int current = 0;

void init()
{
       for(int i=0;i<=n;i++)
       {
               bcc[i] = comp[i] = i; //BCC and CC of a node
               link[i] = -1; //Link to parent in Connected Component
               sz[i] = 1; //Size of Connected Component
       }
       bridges = 0;
}

int getBCC(int u)
{
       if(u == -1)
               return -1;
       if(bcc[u] == u)
               return u;
       return bcc[u] = getBCC(bcc[u]);
}

int getComp(int u)
{
       if(comp[u] == u)
               return u;
       return comp[u] = getComp(comp[u]);
}

void mergePath(int u, int v)
{
       current++;
       vector<int> va, vb;
       int lca = -1;
       while(lca == -1)
       {
               if(u != -1)
               {
                       u = getBCC(u);
                       va.push_back(u);
                       if(vis[u] == current)
                               lca = u;
                       vis[u] = current;
                       u = link[u];
               }
               if(v != -1)
               {
                       vb.push_back(v);
                       v = getBCC(v);
                       if(vis[v] == current)
                               lca = v;
                       vis[v] = current;
                       v = link[v];
               }
       }
       for(auto &it:va)
       {
               bcc[it] = lca;
               if(it == lca)
                       break;
               bridges--;
       }
       for(auto &it:vb)
       {
               bcc[it] = lca;
               if(it == lca)
                       break;
               bridges--;
       }
}

void MakeRoot(int u)
{
       u = getBCC(u);
       int root = u, child = -1;
       while(u != -1)
       {
               int par = getBCC(link[u]);
               link[u] = child;
               comp[u] = root;
               child = u;
               u = par;
       }
       sz[root] = sz[child];
}

void addEdge(int u, int v)
{
       u = getBCC(u), v = getBCC(v);
       if(u == v)
               return;
       int compu = getComp(u), compv = getComp(v);
       if(compu != compv)
       {
               bridges++;
               if(sz[compu] > sz[compv])
               {
                       swap(u, v);
                       swap(compu, compv);
               }
               MakeRoot(u);
               link[u] = v;
               comp[u] = v;
               sz[compv] += sz[compu];
       }
       else
               mergePath(u, v);
}

//Problem 1: https://www.codechef.com/ENFE2019/problems/HTST9
//Solution 1: https://www.codechef.com/viewsolution/23221102
/*********** articulation *******************
const int N = 1e5 + 5;

int n;
int timer;
int tin[N], low[N];
bool vis[N], isArticulation[N];
vector<int> g[N];

void dfs(int u, int par)
{
       vis[u] = 1;
       tin[u] = low[u] = ++timer;
       int children = 0;
       for(auto &it:g[u])
       {
               if(it == par)
                       continue;
               if(vis[it])
                       low[u] = min(low[u], tin[it]);
               else
               {
                       dfs(it, u);
                       low[u] = min(low[u], low[it]);
                       if(low[it] >= tin[u] && par != -1)
                               isArticulation[u] = 1;
                       children++;
               }
       }
       if(par == -1 && children > 1)
               isArticulation[u] = 1;
}

void articulationPoints()
{
       timer = 0;
       memset(vis, 0, sizeof(vis));
       memset(isArticulation, 0, sizeof(isArticulation));
       memset(tin, -1, sizeof(tin));
       memset(low, -1, sizeof(low));
       for(int i = 1; i <= n; i++)
       {
               if(!vis[i])
                       dfs(i, -1);
       }
}

/**************parallel bs*************
for all logQ steps:
   clear range tree and linked list check
   for all member states i:
       if L[i] != R[i]:
           mid = (L[i] + R[i]) / 2
           insert i in check[mid]
   for all queries q:
       apply(q)
       for all member states m in check[q]:
           if m has requirements fulfilled:
               R[m] = q
           else:
               L[m] = q + 1
*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using namespace std;

static constexpr long long P = (119 << 23) + 1;

static long long pow(long long a, unsigned n) {
  if (n == 0)
    return 1;
  long long b = a;
  for (int s = 8 * sizeof(unsigned) - __builtin_clz(n) - 1; s-- > 0;) {
    b = b * b % P;
    if (n >> s & 1)
      b = a * b % P;
  }
  return b;
}

static long long inv(long long x) { return pow(x, P - 2); }

template <typename T> static void destroy(T &t) { t.~T(); }

struct Summary {
  long long root, leaf, self, count;
  bool leafy;

  static Summary child(const Summary &s, long long depth) {
    return {
        .root = s.root + (s.leafy ? depth : 0),
        .leaf = s.root + (s.leafy ? depth : 0),
        .self = s.self + (s.leafy ? s.leaf : 0),
        .count = s.count + (s.leafy ? 1 : 0),
        .leafy = false,
    };
  }
  static Summary chain(const Summary &so, long long deptho, const Summary &si,
                       long long depthi) {
    return {
        .root = so.root + (si.root + si.count * deptho),
        .leaf = (so.leaf + so.count * depthi) + si.leaf,
        .self = so.self + si.self + si.count * so.leaf + so.count * si.root,
        .count = so.count + si.count,
        .leafy = si.leafy,
    };
  }
};

static const Summary EDGE_SUMMARY = {
    .root = 0, .leaf = 0, .self = 0, .count = 0, .leafy = true};
static const Summary EMPTY_SUMMARY = {
    .root = 0, .leaf = 0, .self = 0, .count = 0, .leafy = false};

struct Bound {
  unsigned a, b, c, d;
};

struct Edge {
  unsigned i;
};

struct Forest {
  enum class Tag { EDGE, CHILD, CHAIN } tag;
  union {
    Edge edge;
    struct {
      unique_ptr<Forest> f;
    } child;
    struct {
      unique_ptr<Forest> fo, fi;
      Bound bound;
      long long depth;
      Summary summary, lsummary, rsummary;
    } chain;
  };

  struct MakeEdge {};
  Forest(MakeEdge, const Edge &edge) : tag{Tag::EDGE}, edge{edge} {}

  struct MakeChild {};
  Forest(MakeChild, unique_ptr<Forest> &&f) : tag{Tag::CHILD}, child{move(f)} {}

  struct MakeChain {};
  Forest(MakeChain, unique_ptr<Forest> &&fo_, unique_ptr<Forest> &&fi_)
      : tag{Tag::CHAIN}, chain{.fo = move(fo_),
                               .fi = move(fi_),
                               .bound = {},
                               .depth = chain.fo->depth() + chain.fi->depth()} {
    Bound bo = chain.fo->bound(), bi = chain.fi->bound();
    if (bo.b == bo.c) {
      if (bi.b == bi.c) {
        if (bo.d <= bi.a)
          chain.bound = {.a = bo.a, .b = bo.d, .c = bi.a, .d = bi.d}; // oo_ii
        else if (bi.d <= bo.a)
          chain.bound = {.a = bi.a, .b = bi.d, .c = bo.a, .d = bo.d}; // ii_oo
      } else if (bo.d == bi.a) {
        chain.bound = {.a = bo.a, .b = bi.b, .c = bi.c, .d = bi.d}; // ooi_i
      } else if (bi.d == bo.a) {
        chain.bound = {.a = bi.a, .b = bi.b, .c = bi.c, .d = bo.d}; // i_ioo
      }
    } else if (bo.b == bi.a) {
      if (bi.d == bo.c)
        chain.bound = {.a = bo.a, .b = bi.b, .c = bi.c, .d = bo.d}; // oi_io
      else if (bi.b == bi.c && bi.d <= bo.c)
        chain.bound = {.a = bo.a, .b = bi.d, .c = bo.c, .d = bo.d}; // oii_o
    } else if (bi.b == bi.c) {
      if (bo.b <= bi.a && bi.d == bo.c)
        chain.bound = {.a = bo.a, .b = bo.b, .c = bi.a, .d = bo.d}; // o_iio
      else if (bo.d == bi.a)
        chain.bound = {.a = bo.a, .b = bo.b, .c = bo.c, .d = bi.d}; // o_oii
      else if (bi.d == bo.a)
        chain.bound = {.a = bi.a, .b = bo.b, .c = bo.c, .d = bo.d}; // iio_o
    }
    assert(chain.bound.a != 0);
    long long deptho = chain.fo->depth(), depthi = chain.fi->depth();
    chain.summary =
        Summary::chain(chain.fo->query(chain.bound.a, chain.bound.d), deptho,
                       chain.fi->query(chain.bound.a, chain.bound.d), depthi);
    chain.lsummary =
        Summary::chain(chain.fo->query(chain.bound.a, chain.bound.b), deptho,
                       chain.fi->query(chain.bound.a, chain.bound.b), depthi);
    chain.rsummary =
        Summary::chain(chain.fo->query(chain.bound.c, chain.bound.d), deptho,
                       chain.fi->query(chain.bound.c, chain.bound.d), depthi);
  }

  Forest(Forest &&f) : tag{f.tag} {
    switch (tag) {
    case Tag::EDGE:
      edge = move(f.edge);
      break;
    case Tag::CHILD:
      child = move(f.child);
      break;
    case Tag::CHAIN:
      chain = move(f.chain);
      break;
    }
  }

  ~Forest() {
    switch (tag) {
    case Tag::EDGE:
      destroy(edge);
      break;
    case Tag::CHILD:
      destroy(child);
      break;
    case Tag::CHAIN:
      destroy(chain);
      break;
    }
  }

  Bound bound() const {
    switch (tag) {
    case Tag::EDGE:
      return Bound{.a = edge.i, .b = edge.i, .c = edge.i, .d = edge.i + 1};
    case Tag::CHILD:
      return child.f->bound();
    case Tag::CHAIN:
      return chain.bound;
    }
  }

  long long depth() const {
    switch (tag) {
    case Tag::EDGE:
      return 1;
    case Tag::CHILD:
      return 0;
    case Tag::CHAIN:
      return chain.depth;
    }
  }

  Summary query(unsigned a, unsigned b) const {
    switch (tag) {
    case Tag::EDGE:
      if (a <= edge.i && b >= edge.i + 1)
        return EDGE_SUMMARY;
      else
        return EMPTY_SUMMARY;
    case Tag::CHILD:
      return Summary::child(child.f->query(a, b), child.f->depth());
    case Tag::CHAIN:
      if (b <= chain.bound.a || (a >= chain.bound.b && b <= chain.bound.c) ||
          a >= chain.bound.d)
        return EMPTY_SUMMARY;
      else if (a <= chain.bound.a && b >= chain.bound.d)
        return chain.summary;
      else if (a <= chain.bound.a && b >= chain.bound.b && b <= chain.bound.c)
        return chain.lsummary;
      else if (a >= chain.bound.b && a <= chain.bound.c && b >= chain.bound.d)
        return chain.rsummary;
      return Summary::chain(chain.fo->query(a, b), chain.fo->depth(),
                            chain.fi->query(a, b), chain.fi->depth());
    }
  }
};

static unsigned n;
static vector<unsigned> fs;

struct Builder {
  vector<pair<unsigned, unique_ptr<Forest>>> fs;
  unsigned size = 0;

  void push(unsigned n, unique_ptr<Forest> f) {
    size += n;
    while (!fs.empty() && 2 * n > fs.back().first) {
      while (fs.size() >= 2 && n > fs[fs.size() - 2].first) {
        auto p1 = move(fs.back());
        fs.pop_back();
        auto p2 = move(fs.back());
        fs.back() =
            make_pair(p1.first + p2.first,
                      make_unique<Forest>(Forest::MakeChain{}, move(p1.second),
                                          move(p2.second)));
      }
      auto p1 = move(fs.back());
      fs.pop_back();
      n += p1.first;
      f = make_unique<Forest>(Forest::MakeChain{}, move(f), move(p1.second));
    }
    fs.emplace_back(n, move(f));
  }

  unique_ptr<Forest> chain() && {
    assert(!fs.empty());
    auto f = move(fs.back()).second;
    fs.pop_back();
    while (!fs.empty()) {
      auto f1 = move(fs.back()).second;
      fs.pop_back();
      f = make_unique<Forest>(Forest::MakeChain{}, move(f), move(f1));
    }
    return f;
  }
};

static pair<Builder, unsigned> build_forest(unsigned i) {
  if (i + 1 > n || fs[i + 1] != i)
    return make_pair(Builder{}, i + 1);
  auto p = build_forest(i + 1);
  p.first.push(1, make_unique<Forest>(Forest::MakeEdge{}, Edge{i + 1}));
  while (p.second <= n && fs[p.second] == i) {
    auto q = build_forest(p.second);
    q.first.push(1, make_unique<Forest>(Forest::MakeEdge{}, Edge{p.second}));
    if (q.first.size <= p.first.size) {
      p.first.push(q.first.size, make_unique<Forest>(Forest::MakeChild{},
                                                     move(q.first).chain()));
    } else {
      q.first.push(p.first.size, make_unique<Forest>(Forest::MakeChild{},
                                                     move(p.first).chain()));
      p.first = move(q.first);
    }
    p.second = q.second;
  }
  return p;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  unsigned q;
  cin >> n >> q;
  fs.resize(n + 1);
  for (unsigned i = 2; i <= n; i++)
    cin >> fs[i];
  auto p = build_forest(1);
  assert(p.second == n + 1);
  Builder &builder = p.first;
  builder.push(1, make_unique<Forest>(Forest::MakeEdge{}, Edge{1}));
  unique_ptr<Forest> f =
      make_unique<Forest>(Forest::MakeChild{}, move(builder).chain());

  long long ans = 0;
  while (q--) {
    long long x, y;
    cin >> x >> y;
    Summary s = f->query(x ^ ans, (y ^ ans) + 1);
    ans =
        s.count < 2 ? 0 : s.self % P * inv(s.count * (s.count - 1) / 2 % P) % P;
    cout << ans << '\n';
  }
  return 0;
}
