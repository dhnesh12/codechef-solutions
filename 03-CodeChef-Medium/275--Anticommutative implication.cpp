#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

const int N = 1010;
int c[N], pre[N];
int ones[N];
int cnt[N];
int dp[N][N];

vector<int> v[N];

int find(int x) {
	if (pre[x] == -1) return x;
	int y = find(pre[x]);
	c[x] ^= c[pre[x]];
	return pre[x] = y;
}

bool unions(int x, int y) {
	int fx = find(x);
	int fy = find(y);
	if (fx == fy) {
		return c[x] != c[y];
	}

	c[fx] ^= (c[x] == c[y]);
	pre[fx] = fy;
	cnt[fy] += cnt[fx];
	return true;
}

void solve() {
	memset(c, 0, sizeof(c));
	memset(pre, -1, sizeof(pre));
    memset(ones, 0, sizeof(ones));
	fill(cnt + 1, cnt + N, 1);
	int n;
	scanf("%d", &n);
    bool flag = true;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			int x;
			scanf("%d", &x);
			if (!x) continue;
			flag &= unions(i, j);
		}

	if (!flag) {
		printf("-1\n");
		return;
	}

    for (int i = 1; i <= n; i++) {
		int x = find(i);
		ones[x] += c[i];
	}

	vector<int> roots;
	for (int i = 1; i <= n; i++)
		if (pre[i] == -1) roots.push_back(i);
    for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			dp[i][j] = -1;
	dp[0][0] = 0;
	for (int i = 0; i < roots.size(); i++) {
		int x = ones[roots[i]], y = cnt[roots[i]] - ones[roots[i]];
		for (int j = 0; j <= n; j++) {
			if (-1 != dp[i][j] && j + x <= n && dp[i + 1][j + x] == -1)
				dp[i + 1][j + x] = j;
			if (-1 != dp[i][j] && j + y <= n && dp[i + 1][j + y] == -1)
				dp[i + 1][j + y] = j;
		}
	}

	int pos = 0;
	for (int i = 0; i <= n; i++)
		if (dp[roots.size()][i] != -1 && i * (n - i) > pos * (n - pos))
			pos = i;

	for (int i = roots.size(); i >= 1; pos = dp[i][pos], i--) {
		if (pos - dp[i][pos] == cnt[roots[i - 1]] - ones[roots[i - 1]]) {
			c[roots[i - 1]] ^= 1;
		}
	}

	for (int i = 1; i <= n; i++) {
		find(i);
		printf("%d", c[i]);
		if (i == n) printf("\n");
		else printf(" ");
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) solve();
	return 0;
}
