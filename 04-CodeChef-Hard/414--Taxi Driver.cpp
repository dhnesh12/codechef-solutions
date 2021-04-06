#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() 
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int Test; cin >> Test;
  for (int T=1; T<=Test; ++T) {
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> x(n), y(n);
    for (int i=0; i<n; ++i)
      cin >> x[i] >> y[i], x[i] *= a, y[i] *= b;
    for (int i=0; i<n; ++i) {
      int _x=x[i], _y=y[i];
      x[i] = (_x + _y);
      y[i] = (_x - _y);
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    long long int pre=0, ans=0;
    for (int i=0; i<n; ++i) 
      ans += (x[i] * 1LL * i) - pre, pre += x[i];
    pre = 0;
    for (int i=0; i<n; ++i)
      ans += (y[i] * 1LL * i) - pre, pre += y[i];
    ans /= 2;
    cout << ans << '\n';
  }
  return 0;
}