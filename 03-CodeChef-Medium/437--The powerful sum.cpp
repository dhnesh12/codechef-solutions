#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>

typedef long long ll;

using namespace std;

int S(int, int, int);
int E(int, int, int);
int O(int, int, int);

int MP[105];
int choose[105][105];
int memo[105][33];
map<int,int> highb;

int highBit(int n)
{
	if (n==0)
		return 0;
	int &ret = highb[n];
	if (!ret)
		ret = 1+highBit(n>>1);
	return ret;
}

int modPow(int a, int b, int m)
{
	if (b==0) return 1;
	if (b%2==0) return modPow(((ll)a*a)%m,b/2,m);
	return ((ll)a*modPow(a,b-1,m))%m;
}

int S(int n, int k, int m) {
	if (n == 0)
		return 0;

	int &ret = memo[k][highBit(n)];
	if (ret<0)
	{
		if (n&1)
		{
			ret = ((ll)E(n / 2, k, m) + O(n / 2, k, m)) % m;
		}
		else
		{
			ret = (E(n / 2, k, m) + O(n / 2, k, m)) % m;
			ret = (ret - modPow(n+1,k,m))%m;
			ret = (ret+m)%m;
		}
	}
	return ret;
}

int E(int n, int k, int m) {
	if (n == 0)
		return k == 0;
	return ((ll)MP[k] * S(n, k, m)) % m;
}

int O(int n, int k, int m) {
	if (n == 0)
		return 1;
	int res = 0;
	for (int r = 0; r <= k; r++) {
		int tmp = MP[r];
		tmp = ((ll)tmp * choose[k][r]) % m;
		tmp = ((ll)tmp * S(n, r, m)) % m;
		res = (res + tmp) % m;
	}
	return res;
}

int main() {

	clock_t start = clock();
	int tc, N, k, m;

	scanf("%d", &tc);
	while (tc-- > 0) {
		scanf("%d %d %d", &N, &k, &m);

		for (int n = 0; n <= k; n++) {
			choose[n][0] = choose[n][n] = 1;
			for (int r = 1; r <= n-1; r++)
				choose[n][r] = (choose[n - 1][r - 1] + choose[n - 1][r]) % m;
		}

		for (int i = 0; i <= k; i++)
			for (int j=0; j<33; j++)
				memo[i][j] = -1;

		MP[0] = 1;
		for (int i = 1; i <= k; i++)
			MP[i] = (2 * MP [i - 1]) % m;

		printf("%d\n", S(N, k, m));
	}
	clock_t end = clock();
	fprintf(stderr, "Time = %lf(ms)", 1000.0 * (end - start) / CLOCKS_PER_SEC);
	return 0;
}
