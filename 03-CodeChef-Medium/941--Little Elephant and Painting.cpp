#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>

const int maxT = 10;
const int maxk = 50;
const int maxn = 50;
const int maxc = 100;

int n, k, c;
double f[maxk + 1][maxn][maxc];

int main()
{
	int T;
	for (assert(scanf("%d", &T) == 1 && 1 <= T <= maxT); T --;) {
		assert(scanf("%d%d%d", &n, &c, &k) == 3);
		assert(1 <= n && n <= maxn);
		assert(1 <= k && k <= maxk);
		assert(2 <= c && c <= maxc);
		
		memset(f, 0, sizeof(f));
		for (int i = 0; i < n; ++ i) {
			f[0][i][1] = 1;
		}
		for (int i = 0; i < k; ++ i) {
			int l, r;
			assert(scanf("%d%d", &l, &r) == 2);
			assert(1 <= l && l <= r && r <= n);
			-- l; -- r;
			for (int j = 0; j < n; ++ j) {
				for (int x = 0; x < c; ++ x) {
					if (f[i][j][x] < 1e-12) {
						continue;
					}
//fprintf(stderr, "%d %d %d: %.10f\n", i, j, x, f[i][j][x]);
					if (l <= j && j <= r) {
						double ratio = 1.0 / c / 2;
						for (int y = 0, yu = 0; y < c; ++ y) {
							yu += x;
							if (yu >= c) {
								yu -= c;
							}
							f[i + 1][j][yu] += f[i][j][x] * ratio; 
						}
						f[i + 1][j][x] += f[i][j][x] * 0.5;
					} else {
						f[i + 1][j][x] += f[i][j][x];
					}
				}
			}
		}
		
		double answer = 0;
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < c; ++ j) {
				answer += f[k][i][j] * j;
			}
		}
		
		printf("%.10f\n", answer);
	}
	return 0;
}