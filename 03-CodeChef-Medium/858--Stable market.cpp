#include <bits/stdc++.h>
using namespace std;

#define N 400020
#define M 200020

#define inf 0x3f3f3f3f
#define ls (i << 1)
#define rs (ls | 1)
#define md ((ll + rr) >> 1)
#define lson ll, md, ls
#define rson md + 1, rr, rs
#define LL long long

int a[N];
int n;
int L[N], R[N];

int q;
int ql[N], qr[N], qk[N];
struct node
{
  int type;
  int l, r, k, id;
  node(int type, int l, int r, int k, int id) : type(type), l(l), r(r), k(k), id(id)
  {
  }
  bool operator<(const node &rhs) const
  {
    return k > rhs.k;
  }
};
int tree[N], ans[N];

void add(int x, int v)
{
  while (x <= n)
  {
    tree[x] += v;
    x += x & -x;
  }
}
int query(int x)
{
  int ret = 0;
  while (x)
  {
    ret += tree[x];
    x -= x & -x;
  }
  return ret;
}
int main()
{
  int cas;
  cin>>cas;
  while (cas--)
  {
    cin>>n>>q;
    for (int i = 1; i <= n; ++i)
    {
      cin>>a[i];
    }
    for (int i = 1; i <= q; ++i)
    {
      cin>>ql[i]>>qr[i]>>qk[i];
    }
    for (int i = 1; i <= n; ++i)
    {
      if (i == 1 || a[i] != a[i - 1])
        L[i] = i;
      else
        L[i] = L[i - 1];
    }
    for (int i = n; i >= 1; --i)
    {
      if (i == n || a[i] != a[i + 1])
        R[i] = i;
      else
        R[i] = R[i + 1];
    }
    std::vector<node> vec;
    for (int i = 1; i <= n; i = R[i] + 1)
    {
      vec.push_back(node(0, L[i], R[i], R[i] - L[i] + 1, -1));
    }
    for (int i = 1; i <= q; ++i)
    {
      vec.push_back(node(1, ql[i], qr[i], qk[i], i));
    }
    std::sort(vec.begin(), vec.end());
    memset(ans, 0, sizeof ans);
    memset(tree, 0, sizeof tree);
    for (int i = 0, j = 0; i < vec.size(); i = j)
    {
      while (j < vec.size() && vec[j].k == vec[i].k)
        ++j;
      for (int k = i; k < j; ++k)
      {
        if (vec[k].type == 0)
        {
          add(vec[k].l, 1);
        }
      }
      for (int k = i; k < j; ++k)
      {
        if (vec[k].type == 1)
        {
          int id = vec[k].id;
          int l = vec[k].l;
          int r = vec[k].r;
          l = R[l] + 1;
          r = L[r] - 1;
          if (l <= r)
          {
            ans[id] += query(r) - query(l - 1);
          }
        }
      }
    }
    for (int i = 1; i <= q; ++i)
    {
      int l = ql[i], r = qr[i], k = qk[i];
      if (R[l] >= r)
      {
        if (r - l + 1 >= k)
          ans[i]++;
      }
      else
      {
        if (R[l] - l + 1 >= k)
          ans[i]++;
        if (r - L[r] + 1 >= k)
          ans[i]++;
      }
    }
    for (int i = 1; i <= q; ++i)
      cout<<ans[i]<<endl;
  }
  return 0;
}
