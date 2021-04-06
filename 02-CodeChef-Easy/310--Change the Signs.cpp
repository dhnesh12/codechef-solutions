#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <iostream>
#include <tuple>
#include <iomanip>
#include <string>
#include <ctime>
#include <cassert>
#include <queue>

using namespace std;

using ll = long long;
using pli = pair<ll, int>;

const int MAX_N = int(1e5);
const ll MAX_A = ll(1e9);

void solve() {
  int N; assert(cin >> N); assert(2 <= N && N <= MAX_N);
  vector<ll> A(N, 1e10); 
  for(int i = 0; i < N; i++) {
    cin >> A[i];
    assert(1 <= A[i] && A[i] <= MAX_A);
  }

  vector<vector<ll>> tb(N, vector<ll>(3));

  tb[1][0b00] = A[0] + A[1];
  tb[1][0b01] = (A[0] - A[1] > 0) ? A[0] - A[1] : ll(1e18);
  tb[1][0b10] = (A[0] - A[1] < 0) ? A[1] - A[0] : ll(1e18);
  for(int i = 2; i < N; i++) {
    tb[i][0b00] = min(tb[i-1][0b00], tb[i-1][0b10]) + A[i];
    tb[i][0b01] = min((A[i-1] - A[i] > 0) ? tb[i-1][0b00] - A[i] : ll(1e18), 
                      (-A[i-2] + A[i-1] - A[i] > 0) ? tb[i-1][0b10] - A[i] : ll(1e18));
    tb[i][0b10] = (-A[i-1] + A[i] > 0) ? tb[i-1][0b01] + A[i] : ll(1e18);
  }
  
  vector<ll> B = A;
  for(int i = N-1, j = min_element(tb[N-1].begin(), tb[N-1].end()) - tb[N-1].begin(); i >= 1; i--) {
    if(j % 2 == 1) B[i] = -B[i];
    if(i == 1 && j / 2 == 1) B[0] = -B[0];
    if(j == 0 || j == 1) {
      j = (tb[i][j] == tb[i-1][0] + (j == 0 ? A[i] : -A[i])) ? 0b00 : 0b10; 
    }else {
      j = 1;
    }
  }

  for(int i = 0; i < N; i++) {
    cout << B[i] << (i == N-1 ? "\n" : " ");
  }
}

int main() {
#ifdef IN_MY_COMPUTER
  freopen("chsign.in", "r", stdin);
#else
  cin.tie(nullptr);
  ios_base::sync_with_stdio(false);
#endif

  int T; cin >> T;
  while(T--) {
    solve();
  }
  return 0;
}