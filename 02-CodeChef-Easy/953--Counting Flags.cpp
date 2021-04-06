#include <bits/stdc++.h>
using namespace std;
#define ll long long int
bool cmp(vector<ll> a, vector<ll> b)
{
  return a[0] > b[0];
}

bool sortfirst(pair<ll, char> a, pair<ll, char> b)
{
  return a.first > b.first;
}
ll gcd(ll a, ll b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
  return (a / gcd(a, b)) * b;
}
bool isPowerOfTwo(int n)
{
  if (n == 0)
    return false;

  return (ceil(log2(n)) == floor(log2(n)));
}
//int a[100010];
double sumOfGP(double a, double r, int n)
{
  double sum = 0;
  for (int i = 0; i < n; i++)
  {
    sum = sum + a;
    a = a * r;
  }
  return sum;
}
void solve()
{
  ll t;
  cin >> t;
  while (t--)
  {
    ll n;
    cin >> n;
    ll s = 2 * (n * (n - 1)) + 3 * n * (n - 1) * (n - 2);
    s += 2 * (n * (n - 1) * (n - 2) + n * (n - 1) * (n - 2) * (n - 3));
    cout << s << '\n';
  }
}
int main()
{
  solve();
  return 0;
}