#include <bits/stdc++.h>
using namespace std;

#define ll long long

inline void setmin(int &x, int y) { if (y < x) x = y; }
inline void setmax(int &x, int y) { if (y > x) x = y; }

const int N = 100000;
const int inf = (int)1e9 + 1;

int a[N];
int min_pref[N * 3];
bool dp[N];
int gp[N];
int res[N];

void solve(int n, int W) {
  // sort the power of dragons in decreasing order.
  sort(a, a + n, [](int x, int y) { return x > y; });
  if (a[0] >= W) {
    // If the first dragon has power greater than that of prince, then he will
    // always be defeated.
    for (int i = 0; i < n; i++) {
      res[i] = n;
    }
    return;
  }
  // We will first find the minimum size of partition for which the sum of
  // elements in both partition is greater than or equal to W.
  // Since the most powerful dragon is counted in both sets, we remove its
  // contribution.
  W -= a[0];
  // min_pref[x] = lower_bound(x)
  // It means to find minimum number of dragons required to obtain a sum of
  // powers greater than or equal to "x".
  for (int i = 0; i < N * 3; i++) {
    min_pref[i] = 0;
  }
  // As explained in editorial, we only consider sums till W * 3. The author
  // has used a safety value of N * 3, where N = max(W) for any test case.
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += (i > 0 ? a[i] : 0);
    if (sum + 1 >= N * 3) {
      break;
    }
    min_pref[sum + 1] = i + 1;
  }
  // In the previous loop, the asnwer would be set for some value of "x" which
  // can be exactly obtained. Since, the initial answer is set to 0, we do a
  // max operation to get the answer for greater than or equal to "x".
  for (int i = 1; i < N * 3; i++) {
    min_pref[i] = max(min_pref[i - 1], min_pref[i]);
  }
  // min prefix that can be split into two parts with sum >= W
  int ans = n;
  // dp[i] = 1 deontes that there exists a partition of dragons (not necessarily
  // consecutive) such that the sum of powers of dragons is exactly "i". For
  // other cases it is set to 0.
  for (int i = 0; i < W; i++) {
    dp[i] = false;
  }
  // There always exists a null set meaning that sum of powers of selecting no
  // dragon is 0.
  dp[0] = true;
  // As p[0] is already acccounted, we start seeing dragons from index 1.
  int p = 1;
  while (p < n) {
    // If we already found a partiton of dragons into 2 parts such that sum of
    // both is greater than (W - a[0]), then we can safely break as the number
    // of dragons we will consider will only increase.
    if (p >= ans) {
      break;
    }
    // Find the list of dragons which have the same power. Similar to 2-pointer
    // trick.
    int p1 = p + 1;
    while (p1 < n && a[p1] == a[p]) {
      p1++;
    }
    // Let the 2 partitions have sums A and B. We consider A = j + a[p] * k,
    // for valid j and k. We need A >= W, meaning for particular "j",
    // k = ceil((W-j)/a[p]). We find shortest prefix with sum >= A + W. Based
    // on these values, we update the answer.
    for (int j = max(0LL, W - (ll)a[p] * (p1 - p)); j < W; j++) {
      if (!dp[j]) {
        // There is no partition such that sum of power of dragons is exactly "j".
        continue;
      }
      // Extend the partiton for "j" with dragons having power a[p].
      int cnt = (W - j + (a[p] - 1)) / a[p];
      if (cnt > (p1 - p)) {
        // We don't have enough number of a[p].
        continue;
      }
      int need_sum = (j + a[p] * cnt) + W;
      int pos = min_pref[need_sum];
      // We need to consider disjoint partions. The number of dragons we take
      // currenltly is (p + cnt). So if min_pref gave answer (i.e. pos) as a
      // lesser value, we must increase it to consider disjoint partiton
      // correctly as we know the partitions for our case.
      pos = max(pos, p + cnt);
      setmin(ans, pos);
    }
    // Update the values of "j" such that dp[j] is achievable. For this, we
    // maintain another dynamic programming, gp[v] = minimal number of a[p]
    // required to obtain a value of "v".
    for (int j = 0; j < W; j++) {
      if (dp[j]) {
        // dp[j] was already obtainable without any usage of a[p]
        gp[j] = 0;
      }
      else {
        // gp[j] = (gp[j - a[p]] + 1) i.e. minimum number to obtain "j-a[p]" and
        // append a[p] to it.
        gp[j] = inf;
        if (j >= a[p]) {
          setmin(gp[j], gp[j - a[p]] + 1);
        }
      }
      if (!dp[j]) {
        // dp[j] can be obtained if we have sufficient number of a[p].
        // This is because :
        // 1. gp[j] = inf, then we don't have sufficient number of a[p].
        // 2. "j < a[p]", then gp[j] = inf.
        // 3. "j = a[p]", then yes as (p1 - p) >= 1
        // 4. "j > a[p]", As dp[j] was earlier not obtainable, we tried to see
        // if it can be obtained using some number of a[p]. The logic used in
        // gp[j] calculation ensured that dp[j - a[p]*gp[j]] was obtainable
        // as each operation successively appended a[p] to a valid sequence as
        // gp[x] was not inf.
        dp[j] = (gp[j] <= (p1 - p));
        if (j < a[p]) {
          assert(gp[j] == inf);
        }
        else if (j > a[p]) {
          if (j > ((long long)a[p] * gp[j])) {
            if (gp[j] <= (p1 - p)) {
              assert(dp[j - a[p] * gp[j]]);
            }
          }
        }
      }
    }
    p = p1;
  }
  // Minimum number of dragons required on one side such that sum of power of
  // dragons is greater than or equal to W.
  int pos = min_pref[W];
  for (int i = 0; i < n; i++) {
    // In first case, 2 is subtracted as in both directions, the prince would be
    // killed as we calculated the length for sum of powers >= W. But it was
    // mentioned prince dies if sum of powers == W. Similarly for other case,
    // since only one side is considered, we subtracted 1.
    res[i] = max((ans < n ? (n - 1) - (ans - 2) : 0), max(i, n - i - 1) - (pos - 1));
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.precision(20);
  cout << fixed;
  int T;
  cin >> T;
  while (T--) {
    int n, W;
    // Input.
    cin >> n >> W;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    solve(n, W);
    // Output.
    for (int i = 0; i < n; i++) {
      cout << res[i] << (i < n - 1 ? " " : "\n");
    }
  }
  return 0;
}