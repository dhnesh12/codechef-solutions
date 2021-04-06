#include <bits/stdc++.h>
using namespace std;

namespace TYC
{
	const int N = 45, INF = 0x3f3f3f3f;

	int T, n, m, Dis[N][N], F[1 << 18 | 5];

	void floyd()
	{
		int tot = n << 1;
		for (int k = 0; k < tot; k++)
			for (int i = 0; i < tot; i++)
				for (int j = 0; j < tot; j++)
					Dis[i][j] = min(Dis[i][j], Dis[i][k] + Dis[k][j]);
	}

	inline void upd(int &a, const int b) { a = a < b ? a : b; }

	inline int f(const int s, const int k)
	{
		if (!s)
			return 0;
		if (~F[s])
			return F[s];
		int p, &ans = F[s] = INF;
		for (p = 0; p < n; p++)
			if (s & (1 << p))
				break;
		for (int i = 0; i < n; i++)
			if (s & (1 << i))
				ans = min(ans, f(s ^ (1 << p) ^ (1 << i), k) + Dis[p << 1 | k][i << 1 | k]);
		return ans;
	}

	void work()
	{
		scanf("%d", &T);
		while (T--)
		{
			scanf("%d%d", &n, &m);
			memset(Dis, 0x3f, sizeof(Dis));
			for (int i = 1, u, v, w; i <= m; i++)
			{
				scanf("%d%d%d", &u, &v, &w);
				Dis[u][v] = Dis[v][u] = w;
			}
			floyd();
			memset(F, -1, sizeof(int[1 << n]));
			int ans = f((1 << n) - 1, 0);
			memset(F, -1, sizeof(int[1 << n]));
			ans = min(ans, f((1 << n) - 1, 1));
			printf("%d\n", ans);
		}
	}
}

int main()
{
	TYC::work();
	return 0;
}