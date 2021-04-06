#ifndef BZ
#pragma GCC optimize "-O3"
#endif
#include <bits/stdc++.h>

#define FASTIO
#define ALL(v) (v).begin(), (v).end()
#define rep(i, l, r) for (int i = (l); i < (r); ++i)

#ifdef FASTIO
#define scanf abacaba
#define printf abacaba
#endif

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

using namespace std;


/*
ll pw(ll a, ll b) {
	ll ans = 1; while (b) {
		while (!(b & 1)) b >>= 1, a = (a * a) % MOD;
		ans = (ans * a) % MOD, --b;
	} return ans;
}
*/

string s[100];

int n, m;

using bs = bitset<1030>;

int usr[1200];
int usc[1200];
int cc[1200];
bs bb[40];
const int INF = 1e9;

int gfl = 0;
int pr[1030];

void clear() {
	gfl = 0;
	for (int i = 0; i < m; ++i)
		pr[i] = -1;
}

void add(const bs &a) {
	int lst = -1;
	for (int i = 0; i < m; ++i) {
		if (a[i]) {
			if (lst != -1) {
				if (lst == i - 1)
					gfl = 1;
				else
					pr[i - 1] = max(pr[i - 1], lst + 1);
			}
			lst = i;
		}
	}
}

int get() {
	if (gfl)
		return INF;
	for (int i = m - 1; i > 0; --i) {
		if (usc[i])
			pr[i - 1] = max(pr[i - 1], pr[i]);
	}
	if (pr[0] > -1 && usc[0])
		return INF;
	for (int i = 0; i < m; ++i)
		if (pr[i] > i)
			return INF;
	int lst = -1;
	int ans = 0;
	for (int i = 0; i < m; ++i) {
		if (pr[i] <= lst || usc[i])
			continue;
		ans += 1;
		lst = i;
	}
	return ans;
}

void solve() {
	cin >> n >> m;
	int fl = 0;
	if (n > m) {
		fl = 1;
		for (int i = 0; i < m; ++i)
			s[i] = string(n, '.');
	}
	else {
		for (int i = 0; i < n; ++i)
			s[i] = string(m, '.');
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			char c;
			cin >> c;
			if (!fl)
				s[i][j] = c;
			else
				s[j][i] = c;
		}
	if (fl)
		swap(n, m);
	fill(usr, usr + n, 0);
	fill(usc, usc + m, 0);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			if (s[i][j] == 'K')
				usr[i] = 1, usc[j] = 1;
		}
	int fll = 0;
	for (int i = 0; i < n; ++i)
		fll += usr[i];
	if (fll == 0) {
		cout << 0 << "\n";
		return;
	}
	if (fll == n) {
		cout << -1 << "\n";
		return;
	}
	fll = 0;
	for (int i = 0; i < m; ++i)
		fll += usc[i];
	if (fll == m) {
		cout << -1 << "\n";
		return;
	}
	vector<int> vv;
	for (int i = 0; i < n; ++i) {
		if (usr[i])
			vv.push_back(i);
		else if (i != 0 && usr[i - 1])
			vv.push_back(i);
	}
	if (!usr[vv.back()])
		vv.pop_back();
	int cur = 0;
	fill(cc, cc + m, 0);
	for (int i = 0; i < vv.size(); ++i) {
		if (usr[vv[i]]) {
			for (int j = 0; j < m; ++j)
				if (s[vv[i]][j] == 'K')
					++cc[j];
		}
		if (!usr[vv[i]] || i + 1 == vv.size()) {
			for (int j = 0; j < m; ++j) {
				if (cc[j] >= 2) {
					cout << -1 << "\n";
					return;
				}
			}
			bb[cur].reset();
			for (int j = 0; j < m; ++j) {
				if (cc[j])
					bb[cur][j] = 1;
			}
			++cur;
			fill(cc, cc + m, 0);
		}
	}
	int msk = 0;
	for (int i = 0; i + 1 < cur; ++i) {
		if ((bb[i] & bb[i + 1]).any())
			msk |= (1 << i);
	}
	--cur;
	int ans = INF;
	for (int i = 0; i < (1 << cur); ++i) {
		if ((i & msk) != msk)
			continue;
		clear();
		bs now = bb[0];
		add(now);
		for (int j = 0; j < cur; ++j) {
			if ((i >> j) & 1)
				now.reset();
			now |= bb[j + 1];
			add(now);
		}
		int x = get();
		ans = min(ans, max(__builtin_popcount(i), x));
	}
	if (ans == INF)
		cout << -1 << "\n";
	else
		cout << ans << "\n";
}

int main() {
#ifdef FASTIO
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#endif
	int tt;
	cin >> tt;
	for (int i = 0; i < tt; ++i)
		solve();
	return 0;
}
