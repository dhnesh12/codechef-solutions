#include <bits/stdc++.h>

using namespace std;

long long t, n, a, mod, nrcif;


int logpow (int a, long long b) {
  int p = 1;
  while (b) {
    if (b & 1) {
      p = 1ll * p * a % mod;
    }
    a = 1ll * a * a % mod;
    (b >>= 1);
  }
  return p;
}

int calc (long long n) {
  if (n == 0)
    return 0;
  int nr = calc(n / 2);
  int p = nr;
  p = 1ll * p * logpow(10, nrcif * (n / 2)) % mod;
  p = (p + nr) % mod;
  if (n % 2 == 1)
    p = 1ll * p * logpow(10, nrcif) % mod + a;
  p %= mod;
  return p;
}


int main () 
{
  cin >> t;
  while (t--) {
    cin >> a >> n >> mod;
    nrcif = 0;
    long long ca = a;
    while (ca) {
      nrcif++;
      ca /= 10;
    }
    cout << calc(n)<< "\n";
  }
  return 0;
}