#include <bits/stdc++.h>
#define ull unsigned long long

using namespace std;

const int MAXN = 100100;
char s[MAXN];
int n, k;

ull sum(ull a) {
	ull h = a/2 + a%2;
	return (a + a - (h - 1)*2) * h / 2;
}

int calc2(int l, int r) {
	int res = 0, diff = 0;
	while (l >= 0 && r < n) {
		diff += (s[l] != s[r]);
		if (diff > k) {
			return res;
		}
		res++;
		l--; r++;
	}
	return res;
}

int main() {
	int test;
	cin>>test;
	while (test--) {
		scanf("%d%d%s", &n, &k, s);
		long long ans = 0, c =0;
		for (int i = 0; i < n; i++) {
			c += (s[i] != 'a');
			int maxlen = calc2(i, i);
			ans += sum(2*maxlen - 1);

			if (i + 1 < n) {
				maxlen = calc2(i, i + 1);
				ans += sum(2*maxlen);
			}
		}
		cout << ans << endl;
	}
	return 0;
}