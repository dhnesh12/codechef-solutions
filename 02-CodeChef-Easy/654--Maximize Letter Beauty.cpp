//https://www.codechef.com/COOK116A/problems/MAXBTY
#include <iostream>
#include <cstring>
#include <limits.h>

#define int long long int

using namespace std;

const int INF = 1e17;
const int NINF = -INF;
const int maxN = 101000;
int arr[maxN];
int segment_tree[4 * maxN][3];

void build(int l, int r, int index)
{
  if (l > r)
    return;

  if (l == r)
  {
    segment_tree[index][0] = arr[l]; //sum
    segment_tree[index][1] = arr[l]; //prefix max
    segment_tree[index][2] = arr[l]; //suffix max
    return;
  }

  int mid = l + (r - l) / 2;
  build(l, mid, 2 * index + 1);
  build(mid + 1, r, 2 * index + 2);

  segment_tree[index][0] = segment_tree[2 * index + 1][0] + segment_tree[2 * index + 2][0];
  segment_tree[index][1] = max(segment_tree[2 * index + 1][1], segment_tree[2 * index + 1][0] + segment_tree[2 * index + 2][1]);
  segment_tree[index][2] = max(segment_tree[2 * index + 2][2], segment_tree[2 * index + 2][0] + segment_tree[2 * index + 1][2]);
}

int sum_query(int l, int r, int qs, int qe, int index)
{
  if (l > qe || r < qs)
    return 0;

  if (l >= qs && r <= qe)
  {
    return segment_tree[index][0];
  }

  int mid = l + (r - l) / 2;
  return sum_query(l, mid, qs, qe, 2 * index + 1) + sum_query(mid + 1, r, qs, qe, 2 * index + 2);
}

int prefix_max_query(int l, int r, int qs, int qe, int index)
{

  if (l > qe || r < qs)
    return 0;

  if (l >= qs && r <= qe)
  {
    return segment_tree[index][1];
  }

  int mid = l + (r - l) / 2;
  int p1 = prefix_max_query(l, mid, qs, qe, 2 * index + 1);
  int p2 = prefix_max_query(mid + 1, r, qs, qe, 2 * index + 2);
  int sum = sum_query(l, mid, qs, qe, 2 * index + 1);

  return max(p1, sum + p2);
}

int suffix_max_query(int l, int r, int qs, int qe, int index)
{
  if (l > qe || r < qs)
    return 0;

  if (l >= qs && r <= qe)
  {
    return segment_tree[index][2];
  }

  int mid = l + (r - l) / 2;
  int s1 = suffix_max_query(l, mid, qs, qe, 2 * index + 1);
  int s2 = suffix_max_query(mid + 1, r, qs, qe, 2 * index + 2);
  int sum = sum_query(mid + 1, r, qs, qe, 2 * index + 2);

  return max(s2, sum + s1);
}

void update(int l, int r, int pos, int val, int index)
{

  if (l > r)
    return;

  if (l == r)
  {
    segment_tree[index][0] = val;
    segment_tree[index][1] = val;
    segment_tree[index][2] = val;
    return;
  }

  int mid = l + (r - l) / 2;
  if (pos <= mid)
    update(l, mid, pos, val, 2 * index + 1);
  else
    update(mid + 1, r, pos, val, 2 * index + 2);

  segment_tree[index][0] = segment_tree[2 * index + 1][0] + segment_tree[2 * index + 2][0];
  segment_tree[index][1] = max(segment_tree[2 * index + 1][1], segment_tree[2 * index + 1][0] + segment_tree[2 * index + 2][1]);
  segment_tree[index][2] = max(segment_tree[2 * index + 2][2], segment_tree[2 * index + 2][0] + segment_tree[2 * index + 1][2]);
}

int32_t main()
{

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t, n, q;
  cin >> t;

  while (t--)
  {
    memset(segment_tree, 0, sizeof(segment_tree));
    cin >> n >> q;
    for (int i = 0; i < n; i++)
      cin >> arr[i];

    build(0, n - 1, 1);

    char type;
    int x, y;
    while (q--)
    {
      cin >> type >> x >> y;
      if (type == 'Q')
      {
        x--, y--;

        int ans = 0;
        ans += sum_query(0, n - 1, x, y, 1);
        ans += suffix_max_query(0, n - 1, 0, x - 1, 1);
        ans += prefix_max_query(0, n - 1, y + 1, n - 1, 1);
        cout << ans << "\n";
      }
      else
      {
        x--;
        update(0, n - 1, x, y, 1);
      }
    }
  }

  return 0;
}