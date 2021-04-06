#include <bits/stdc++.h>
using namespace std;
const int N = 500005;
#define X first 
#define Y second
typedef long long LL;
typedef pair<LL, int> pli;
int T, a[N], p[N], c[N];
LL ans, b[N], r[N], sum[N];
pli num[N];
void add(int x, int n) {
	for(;x <= n; x += x & -x)	++c[x];
}
int get(int x) {
	int t = 0;
	for (;x;x -= x & -x)	t += c[x];
	return t;
}
int gao(int n) {
	int t = 0;
	for (int i = 0; i < n; ++i)	num[i].X = b[i], num[i].Y = i + 1;
	sort(num, num + n);
	for (int i = 0; i < n; ++i)	p[num[i].Y] = i + 1;
	for (int i = 1; i <= n; ++i) {
		add(p[i], n);
		t += i - get(p[i]);
	}
	sort(b, b + n);
	return t;
}
int main() {
	int n, mini = 0;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &a[i]);
			b[i] = (i ? b[i - 1] : 0) + a[i];
			c[i + 1] = 0;
			if (b[i] < b[mini])	mini = i;
		}
		LL s = b[n - 1];
		b[0] = 0;
		for (int i = 1; i < n; ++i)	b[i] = b[i - 1] + a[(mini + i) % n];
		ans = gao(n);
		for (int i = 0; i < n; ++i) r[i] = b[i] % s ? s - b[i] % s : 0;
		for (int i = 0; i < n; ++i)	num[i].X = r[i], num[i].Y = i + 1;	
		sort(num, num + n);
		for (int i = 0; i < n; ++i)	p[num[i].Y] = i + 1;
		sum[0] = 0;
		for (int i = 1; i <= n; ++i)	c[i] = 0;
		for (int i = 0, j = 0; i < n; ++i) {
			LL cel = (b[i] + s - 1) / s;
			if (i < n - 1)	sum[i + 1] = sum[i] + cel;
			for (; j < n && b[j] + s < b[i]; ++j) {
				add(p[j + 1], n);
			}
			ans += j * cel - sum[j] - get(p[i + 1]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
