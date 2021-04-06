#include <bits/stdc++.h>
using namespace std;

int A[310][310];
int ct[11][310][310];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n, q, x1, y1, x2, y2, ans, final;
	cin >> n;

	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++) {
			cin >> A[i][j];
			ct[A[i][j]][i][j]=1;
		}
	}

	for (int k=1; k<11; k++) {
		for(int i=1; i<=300; i++) {
			for (int j=1; j<=300; j++) {
				ct[k][i][j] += ct[k][i-1][j] + ct[k][i][j-1] - ct[k][i-1][j-1];
			}
		}
	}

	cin >> q;
	for (int i=1; i<=q; i++) {
		final=0;
		cin >> x1 >> y1 >> x2 >> y2;
		for(int k=1; k<11; k++) {
			ans = ct[k][x2][y2]-ct[k][x1-1][y2]-ct[k][x2][y1-1]+ct[k][x1-1][y1-1];
			if (ans) {
				final++;
			}
		}
		cout << final << '\n';
	}
	return 0;
}