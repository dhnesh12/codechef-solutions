#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

const int MAXN = 35;
string s;
int t, x, cnt, dp1[MAXN], dp0[MAXN], ans;
void BF(int pos) {
	if (pos == (int) s.size() - 1) {
		dp0[pos] = dp0[pos - 1] + dp1[pos - 1];
		if (dp0[pos] == x)
			ans = min(ans, cnt);
		return;
	}
	if (dp0[pos - 1] > x || cnt >= ans)
		return;
	if (s[pos] == '1') {
		dp1[pos] = dp1[pos - 1] + dp0[pos - 1] + 1;
		dp0[pos] = dp0[pos - 1];
		BF(pos + 1);
		s[pos] = '0';
		cnt++;
	}
	else {
		dp1[pos] = dp1[pos - 1];
		dp0[pos] = dp0[pos - 1] + dp1[pos - 1];
		BF(pos + 1);
		s[pos] = '1';
		cnt++;
	}
	dp1[pos] = dp0[pos] = 0;
	if (s[pos] == '1') {
		dp1[pos] = dp1[pos - 1] + dp0[pos - 1] + 1;
		dp0[pos] = dp0[pos - 1];
		BF(pos + 1);
		s[pos] = '0';
		cnt--;
	}
	else {
		dp1[pos] = dp1[pos - 1];
		dp0[pos] = dp0[pos - 1] + dp1[pos - 1];
		BF(pos + 1);
		s[pos] = '1';
		cnt--;
	}
	dp1[pos] = dp0[pos] = 0;
}

void solve() {
	cin >> s >> x;
	ans = 1e9;
	dp1[0] = 1;
	BF(1);
	if (ans == 1e9)
		cout << "NO";
	else
		cout << "YES" << '\n' << ans;
	cout << '\n';
}

int main() {
	cin >> t;
	while (t--)
		solve();
}