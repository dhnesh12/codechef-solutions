#include<bits/stdc++.h>
using namespace std;

#define boost ios_base::sync_with_stdio(0);cin.tie(NULL);cout.tie(NULL);

#define li long long int
#define mod 1000000007

int main() {
	boost
	li t;
	cin >> t;
	while (t--) {
		li n, k;
		cin >> n >> k;

		li nn[n];

		for (li i = 1; i <= n - 1; ++i) {
			li a, b, c;
			cin >> a >> b >> c;
			c--;
			nn[min(a, b)] = c;

		}
		li pp;
		li xx;
		li cc[1 << k];
		for (li i = 1; i < n; ++i) {

			memset(cc, 0, sizeof(cc));

			xx = (1 << nn[i]);

			cc[xx] = 1;

			for (li j = 2; j <= n - i; ++j) {

				pp = j + i - 1;

				xx = (1 << nn[j - 1]) | (1 << nn[pp]);

				cc[xx] = 1;

			}

			xx = (1 << nn[n - i]);

			cc[xx] = 1;

			for (auto x : cc) {
				cout << x;

			}

			cout << "\n";

		}
		memset(cc, 0, sizeof(cc));
		cc[0] = 1;

		for (auto x : cc) {
			cout << x;

		}

		cout << "\n";

	}

	return 0;
}
