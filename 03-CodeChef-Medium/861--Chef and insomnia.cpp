#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 1e5 + 10, inf = 1e9 + 10;
int n, k, mn[N], ans, c[N], a[N], f[N], s = 1;
vector<int> v[N];

bool cmp(int a, int b) {
	return mn[a] < mn[b];
}

int32_t main () {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> k;
	for (int i = k + 1; i < N; i++)
		for (int j = 0; j < N; j += i)
			v[j].push_back(i);
	
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		c[i] = i;
		//f[i] = inf;
	}
	memset(f, 69, sizeof f);
	for (int i = n; 0 < i; i--) {
		mn[i] = n + 1;
		int tmp = abs(k - a[i]);
		for (int j: v[tmp])
			mn[i] = min(mn[i], f[j]);
		f[a[i]] = i;
	}
	sort(c + 1, c + n + 1, cmp);
	/*for (int i = 1; i <= n; i++)
		cout << c[i] << ' ' << mn[c[i]] << '\n';*/
	for (int i = 1; i <= n; i++) {
		while (c[s] < i)
			s++;
		ans += mn[c[s]] - i;
	}
	cout << ans;
}
