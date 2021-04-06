#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 5;

int t, n;
int a[MAXN], v[MAXN];

vector <int> q;

int cmmdc(int x, int y)  {
	int r = x % y;
	while (r)  {
		x = y;
		y = r;
		r = x % y;
	}
	return y;
}

bool cmp(int x, int y)  {
	return x > y;
}

void solve(bool flag)  {
	sort (q.begin(), q.end(), cmp);
	for (int i = 1; i < n; ++i)  {
		int ans = 0;
		for (int j = 0; j < q.size() && q[j] >= i; ++j)  {
			if (flag)
				ans += (q[j] - 1) / i;
			else ans += q[j] / i;
			if (flag)
				++ans;
		}
		cout << ans << ' ';
	}
	cout << '\n';
}

int main() {
	ios_base::sync_with_stdio(0);
	cin >> t;
	while (t--)  {
		cin >> n;
		q.clear();
		for (int i = 1; i <= n; ++i)  {
			cin >> a[i];
			v[i] = 0;
		}
		int start = 0;
		for (int i = 1; i < n; ++i)  {
			if (cmmdc(a[i], a[i + 1]) != 1)
				v[i] = 1;
			else start = i;
		}
		if (cmmdc(a[1], a[n]) != 1)
			v[n] = 1;
		else start = n;
		if (start == 0)  {
			q.push_back(n);
			solve(true);
			continue;
		}
		int poz = start, nr = 0;
		for (int i = 1; i <= n; ++i)  {
			++poz;
			if (poz > n)
				poz -= n;
			if (v[poz] == 1)
				++nr;
			else if (nr != 0)  {
				q.push_back(nr);
				nr = 0;
			}
		}
		solve(false);
	}
	return 0;
}
