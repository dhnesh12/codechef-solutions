#include "bits/stdc++.h"
using namespace std;
#define max(a, b) (a < b ? b : a)
#define min(a, b) ((a > b) ? b : a)
#define mod 1e9 + 7
#define FOR(a, c) for (int(a) = 0; (a) < (c); (a)++)
#define FORL(a, b, c) for (int(a) = (b); (a) <= (c); (a)++)
#define FORR(a, b, c) for (int(a) = (b); (a) >= (c); (a)--)
#define INF 1000000000000000003
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
#define F first
#define S second
#define PB push_back
#define POB pop_back
#define MP make_pair
#define int long long int

bool isValid(int i, int j, int size, int N) {
	return (i + size <= N) && (i - size >= 1) && (j + size <= N) && (j - size >= 1);
}
int32_t main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;

		vector<vector<int>>v(N + 2, vector<int>(N + 2, 0)), d1(N + 2, vector<int>(N + 2, 0)), d2(N + 2, vector<int>(N + 2, 0));

		for (int i = 1; i <= N ; i++) {
			for (int j = 1; j <= N; j++) {
				cin >> v[i][j];
			}
		}

		//bottom right diagonal prefix sum
		//fill first row and first column
		for (int i = 1; i <= N; i++) {
			d1[i][1] = v[i][1];
			d1[1][i] = v[1][i];
		}

		for (int i = 2; i <= N; i++) {
			for (int j = 2; j <= N; j++) {
				d1[i][j] = v[i][j] + d1[i - 1][j - 1];
			}
		}

		//bottom left diagonals prefix sum
		//fill first row and last column
		for (int i = 1; i <= N; i++) {
			d2[1][i] = v[1][i];
			d2[i][N] = v[i][N];
		}

		for (int i = 2; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				d2[i][j] = v[i][j] + d2[i - 1][j + 1];
			}
		}

		//print d1 and d2
		// for (int i = 1; i <= N; i++) {
		// 	for (int j = 1; j <= N; j++) {
		// 		cout << d1[i][j] << " ";
		// 	} cout << endl;
		// } cout << endl;

		// for (int i = 1; i <= N; i++) {
		// 	for (int j = 1; j <= N; j++) {
		// 		cout << d2[i][j] << " ";
		// 	} cout << endl;
		// } cout << endl;


		int ans = INT_MIN;
		int sum = 0;
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				sum = v[i][j];
				ans = max(ans, sum);
				int size = 1;

				while (isValid(i, j, size, N)) {
					sum += d1[i + size][j] + d1[i][j + size] - d1[i - 1][j - size - 1] - d1[i - size - 1][j - 1];

					if (size > 1) {
						// sum += d2[i - size + 1][j - size + 1] - d2[i - size][j] + d2[i + size - 1][j + size - 1] - d2[i][j + size];
						sum += d2[i - 1][j - size + 1] - d2[i - size][j] + d2[i + size - 1][j + 1] - d2[i][j + size];
					}
					ans = max(ans, sum);
					size++;
				}
			}
		}

		cout << ans << endl;
	}
	return 0;
}