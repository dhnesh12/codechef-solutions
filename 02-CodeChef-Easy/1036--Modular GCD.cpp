#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <math.h>
#include <iomanip>
#include <deque>
#include <set>
#include <queue>
#include <stack>
#include <sstream>

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

#define MAX 100005
const int INF = 1e9;

long long mod = 1e9 + 7;
long long gcd(long long u, long long v) {
	return (u % v == 0) ? v : gcd(v, u % v);
}

long long exp(long long base, long long n, long long mod) {
	if (n == 0) return 1;
	if (n == 1) return base;
	if (n % 2 == 0) return exp(((base % mod) * (base % mod)) , n / 2, mod) % mod;
	if (n % 2 == 1) return ((base % mod)  * exp(((base % mod) * (base % mod)) , n / 2, mod)) % mod;
}

int main() {	
	int t;
	long long a, b, n;
	cin >> t;
	while (t > 0) {
		cin >> a >> b >> n;
		if (a == b) {
			cout << ((exp(a, n, mod) + exp(b, n, mod)) % mod) << endl;
		}
		else {
			long long range = abs(a - b), ans = 1;
			for (long long i = 1; i * i <= range; i++) {
				if (range % i == 0) {
					long long d1 = i, d2 = range / i, val;
					if ((exp(a, n, d1) + exp(b, n, d1)) % d1 == 0) {
						ans = max(ans, d1);
					}
					if ((exp(a, n, d2) + exp(b, n, d2)) % d2 == 0) {
						ans = max(ans, d2);
					}
				}
			}
			cout << ans << endl;
		}
		t--;
	}
}