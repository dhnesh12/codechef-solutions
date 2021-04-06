
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <utility>
 
 
typedef long long ll;
typedef std::pair<long, long> pll;
typedef std::pair<long, ll> plll;
typedef std::vector<long> vecl;
typedef std::vector<pll> vecpll;
typedef std::vector<plll> vecplll;
typedef std::vector<vecl> vecvecl;
typedef std::vector<vecpll> vecvecpll;
typedef std::vector<vecplll> vecvecplll;
 
struct node {
  long val;
  long l;
  long r;
};
 
std::ostream& operator<<(std::ostream& out, const node data) {
  out << "(" << data.val << ", " << data.l
      << ", " << data.r << ")";
  return out;
}
 
template <typename T, typename S>
std::ostream& operator<<(std::ostream& out, const std::pair<T, S>& data) {
  out << "(" << data.first << ", " << data.second << ")";
  return out;
}
 
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& data) {
  out << "[";
  for (long i = 0; i < long(data.size()); ++i) {
    out << data[i];
    if (i != long(data.size()-1))
      out << " ";
  }
  out << "]";
  return out;
}
 
class ImplicitSegmentTree {
  public:
    ImplicitSegmentTree(const long v0, const long v1)
    : ctr(1), ub(v1), lb(v0) {
      assert(lb < ub);
      data.push_back({0, -1, -1});
    }
    void update(const long key, const long val) {
      //std::cerr << key << " " << val << std::endl;
      assert(lb <= key && key < ub);
      long left = lb;
      long right = ub;
      long idx = 0;
      data[0].val += val;
      while (right-left > 1) {
        const long mid = (right+left) / 2;
        if (key < mid) {
          right = mid;
          long idx0 = data[idx].l;
          if (idx0 < 0) {
            idx0 = ctr++;
            data[idx].l = idx0;
            data.push_back({val, -1, -1});
          }
          else
            data[idx0].val += val;
          idx = idx0;
        }
        else {
          left = mid;
          long idx0 = data[idx].r;
          if (idx0 < 0) {
            idx0 = ctr++;
            data[idx].r = idx0;
            data.push_back({val, -1, -1});
          }
          else
            data[idx0].val += val;
          idx = idx0;
        }
      }
    }
    ll sumuntil(const long key) const {
      assert(lb <= key && key <= ub);
      ll ans = 0LL;
      long left = lb;
      long right = ub;
      long idx = 0;
      if (key <= lb)
        return 0L;
      if (key >= ub)
        return data[0].val;
      while (right-left > 1 && idx >= 0) {
        const long mid = (right+left) / 2;
        if (key < mid) {
          right = mid;
          idx = data[idx].l;
        }
        else {
          if (data[idx].l >= 0)
            ans += data[data[idx].l].val;
          left = mid;
          idx = data[idx].r;
        }
      }
      return ans;
    }
  public:
    long ctr;
    long ub;
    long lb;
    std::vector<node> data;
};
 
void precalc(const vecvecl& children, const vecl& color,
             vecvecpll& p, vecvecplll& sump, vecvecpll& sumc) {
  const long n = color.size();
  assert(long(children.size()) == n);
  p.resize(n);
  sump.resize(n);
  sumc.resize(n);
  long ctr = 0;
  std::vector<long> stack;
  std::vector<bool> visited(n, false);
  stack.push_back(0);
  while (!stack.empty()) {
    const long u = stack.back();
    const long cu = color[u];
    if (!visited[u]) {
      const bool first = (p[cu].size() > 0) ? false : true;
      const long prevp = (!first) ? p[cu].back().second : 0;
      p[cu].push_back({ctr, prevp+1});
      const ll prevsump = (!first) ? sump[cu].back().second : 0;
      sump[cu].push_back({ctr, prevsump+prevp});
      const long prevsumc = (!first) ? sumc[cu].back().second : 0;
      sumc[cu].push_back({ctr, prevsumc+1});
      ++ctr;
      for (long v : children[u])
        stack.push_back(v);
      visited[u] = true;
    }
    else {
      const long prevp = p[cu].back().second;
      p[cu].push_back({ctr, prevp-1});
      ++ctr;
      stack.pop_back();
    }
  }
}
 
long getanc(vecvecpll& p, long color, long dfsin) {
  auto it = std::lower_bound(p[color].begin(), p[color].end(), pll(dfsin, 0));
  return (it != p[color].begin()) ? (--it)->second : 0;
}
 
long getdesc(vecvecpll& sumc, long color, long dfsin, long dfsout) {
  auto it0 = std::lower_bound(sumc[color].begin(), sumc[color].end(),
                              pll(dfsin+1, 0));
  const long before = (it0 != sumc[color].begin()) ? (--it0)->second : 0;
  auto it1 = std::lower_bound(sumc[color].begin(), sumc[color].end(),
                              pll(dfsout, 0));
  const long after = (it1 != sumc[color].begin()) ? (--it1)->second : 0;
  return after-before;
}
 
ll getdescsum(vecvecplll& sump, long color, long dfsin, long dfsout) {
  auto it0 = std::lower_bound(sump[color].begin(), sump[color].end(),
                              plll(dfsin+1, 0));
  const ll before = (it0 != sump[color].begin()) ? (--it0)->second : 0;
  auto it1 = std::lower_bound(sump[color].begin(), sump[color].end(),
                              plll(dfsout, 0));
  const ll after = (it1 != sump[color].begin()) ? (--it1)->second : 0;
  return after-before;
}
 
 
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
 
  long n, q;
  std::cin >> n >> q;
  std::vector<std::vector<long>> children(n);
  for (long i = 1; i < n; ++i) {
    long parent;
    std::cin >> parent;
    children[parent].push_back(i);
  }
  std::vector<long> color(n);
  for (long& c : color)
    std::cin >> c;
  std::vector<long> x(q);
  for (long& xx : x)
    std::cin >> xx;
  long ctr = 0;
  std::vector<long> dfsin(n);
  std::vector<long> dfsout(n);
  std::vector<bool> visited(n, false);
  std::vector<long> stack;
  stack.push_back(0);
  while (!stack.empty()) {
    const long u = stack.back();
    if (!visited[u]) {
      dfsin[u] = ctr++;
      for (long v : children[u])
        stack.push_back(v);
      visited[u] = true;
    }
    else {
      dfsout[u] = ctr++;
      stack.pop_back();
    }
  }
  //std::cerr << dfsin << std::endl;
  //std::cerr << dfsout << std::endl;
  ll ans = 0;
  long nblocks = (q+n-1) / n;
  for (long b = 0; b < nblocks; ++b) {
    std::vector<std::vector<std::pair<long, long>>> p;
    std::vector<std::vector<std::pair<long, ll>>> sump;
    std::vector<std::vector<std::pair<long, long>>> sumc;
    precalc(children, color, p, sump, sumc);
    if (b == 0) {
      for (long i = 0; i < n; ++i) {
        ans += ll(getanc(p, color[i], dfsin[i]))
            * getdesc(sumc, color[i], dfsin[i], dfsout[i]);
      }
      std::cout << ans << "\n";
    }
    //std::cerr << sump << std::endl;
    //std::cerr << dfsin << std::endl;
    //std::cerr << dfsout << std::endl;
    std::vector<ImplicitSegmentTree> st(n, ImplicitSegmentTree(0, 2*n));
    const long imax = std::min((b+1)*n, q);
    for (long i = b*n; i < imax; ++i) {
      const long idx = i % n;
      const long ini = dfsin[idx];
      const long outi = dfsout[idx];
      assert(idx < n && idx >= 0);
      assert(0 <= ini && ini < 2*n && 0 <= outi && outi < 2*n);
      const long ci = color[idx];
      const long cii = (x[i] + ans) % n;
      assert(0 <= ci && 0 <= cii && ci < n && cii < n);
      st[cii].update(ini, 1);
      st[cii].update(outi, -1);
      color[idx] = cii;
      const ll anci = getanc(p, ci, ini);
      const ll ancii = getanc(p, cii, ini);
      const ll desci = getdesc(sumc, ci, ini, outi);
      const ll descii = getdesc(sumc, cii, ini, outi);
      const ll descsumi = getdescsum(sump, ci, ini, outi);
      const ll descsumii = getdescsum(sump, cii, ini, outi);
      const ll curranci = st[ci].sumuntil(ini);
      const ll currancii = st[cii].sumuntil(ini);
      const ll corrii = (ci == cii) ? 1 : 0;
      ans -= curranci * desci + descsumi - desci * (anci+1)
           + curranci * (curranci - 1) / 2;
      ans += currancii * descii + descsumii - descii * (ancii+corrii)
           + currancii * (currancii - 1) / 2;
      std::cout << ans << "\n";
    }
  }
 
  return EXIT_SUCCESS;
}