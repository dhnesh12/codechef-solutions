#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 5;
bitset<N> mask, pos;
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, X;
		scanf("%d%d", &n, &X);
		vector<int> a(n);
		vector<bool> has(N);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			has[a[i]] = true;
		}
		pos.reset();
		int mn = *min_element(a.begin(), a.end());
		mask.set();
		for (int x = N - 1; x >= 0; --x) {
			mask.reset(x);
			if (!has[x]) continue;
			pos[X % x] = 1;
			auto b = pos;
			for (int i = 0; (1 << i) * x < N; ++i)
				b = b | (b >> (1 << i) * x);
			pos |= b & mask;
		}
		int ans = 0;
		for (int i = 0; i < mn; ++i)
			if (pos[i] == 1) ++ans;
		printf("%d\n", ans);
	}
}