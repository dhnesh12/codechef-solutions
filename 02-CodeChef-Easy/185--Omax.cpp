#include <stdio.h>
using namespace std;
#define max(a,b) ((a > b) ? a : b)
#define min(a,b) ((a < b) ? a : b)

int Min[80][80][80][80];
int sum[80][80];

int solve(int n, int m) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; j++) {
		  scanf("%d",&sum[i][j]);
			sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
		}
	}
	int Omax = -((1LL << 31) - 1);
	for (int k = 0; k < n - 2; ++k) {
		for (int l = 0; l < m - 2; ++l) {
			for (int i = 2; i+k < n; ++i) {
				for (int j = 2; j+l < m; ++j) {
					int cur = sum[i-1][j-1] + sum[i+k][j+l] - sum[i-1][j+l] - sum[i+k][j-1];
					if (k != 0) cur = min(cur, Min[i+1][j][i+k][j+l]);
					if (l != 0) cur = min(cur, Min[i][j+1][i+k][j+l]);
					if (k != 0) cur = min(cur, Min[i][j][i+k-1][j+l]);
					if (l != 0) cur = min(cur, Min[i][j][i+k][j+l-1]);
					Min[i][j][i+k][j+l] = cur;
					Omax = max (Omax,(sum[i-2][j-2] + sum[i+k+1][j+l+1] - sum[i-2][j+l+1] - sum[i+k+1][j-2] - cur));
			  }
			}
		}
	}
	printf("%d\n",Omax);
}

int main () {
	while (true) {
		int n, m;
		scanf("%d%d",&n,&m);
		if (n == 0) return 0;
		solve(n, m);
	}
	return 0;
}