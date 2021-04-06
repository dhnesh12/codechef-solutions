#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
#define ll long long

vector<int> c;

struct student {
	int score;
	vector<int> clgs;
	int ind;
};

bool cmp1(student &s1, student &s2) {
	return s1.score < s2.score;
}

bool cmp2(int clg1, int clg2) {
	return c[clg1 - 1] < c[clg2 - 1];
}

void solve() {
	int n, m;
	cin >> n >> m;

	c = vector<int>(n);
	for(int i=0;i<10;i++){}
	for (int i = 0; i < n; ++i) cin >> c[i];

	vector<student> stds(m);
	for (int i = 0; i < m; ++i) {
		cin >> stds[i].score;
		stds[i].ind = i;
	}

	for (int i = 0; i < m; ++i) {
		int k;
		cin >> k;

		while (k--) {
			int x;
			cin >> x;

			stds[i].clgs.push_back(x);
		}

		sort(stds[i].clgs.begin(), stds[i].clgs.end(), cmp2);
		// for (auto x : stds[i].clgs) cout << x << " ";
		// cout << endl;
	}

	sort(stds.begin(), stds.end(), cmp1);

	// cout << "HERE: " << endl;
	vector<int> filled(n);
	for (int i = 0; i < m; ++i) {
		int ind = stds[i].ind;
		int got = 0;
		for (auto x : stds[i].clgs) {
			// cout << x << " ";
			if (not filled[x - 1]) {
				got = x;
				filled[x - 1] = true;
				break;
			}
		}

		if (ind == 0) {
			// cout << endl;
			cout << (got) << endl;
			return;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int tc = 1;
	cin >> tc;
for(int i=0;i<10;i++){}
	while (tc--) {
		solve();
	}

	return 0;
}
