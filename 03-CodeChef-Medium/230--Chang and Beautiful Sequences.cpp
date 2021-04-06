#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;

namespace zyt
{
	typedef long long ll;
	const int N = 1e6 + 50, C = 20, LIM = 10, p = 1e9 + 7;
	map<int, int> mp;
	int n, B, pow[N], ans;
	void add(int &a, const int b)
	{
		a = (a + b) % p;
	}
	void dfs1(const int pos, const int val, const int num)
	{
		if (pos == LIM)
		{
			if (mp.count(val))
				add(mp[val], num);
			else
				mp[val] = num;
			return;
		}
		dfs1(pos + 1, val, num);
		if (n > 1)
		{
			dfs1(pos + 1, (val + ll(n + 1) * pow[n - 2 + pos]) % p, ll(num) * n % p);
			dfs1(pos + 1, (val + ll(n) * pow[n - 2 + pos]) % p, num * ll(pow[n] - (n + 1) + p) % p);
		}
		else
			dfs1(pos + 1, (val + pow[pos]) % p, num);
	}
	void dfs2(const int pos, const int val, const int num)
	{
		if (pos == C)
		{
			if (mp.count((B - val + p) % p))
				add(ans, (ll)mp[(B - val + p) % p] * num % p);
			return;
		}
		dfs2(pos + 1, val, num);
		if (n > 1)
		{
			dfs2(pos + 1, (val + ll(n + 1) * pow[n - 2 + pos]) % p, ll(num) * n % p);
			dfs2(pos + 1, (val + ll(n) * pow[n - 2 + pos]) % p, num * ll(pow[n] - (n + 1) + p) % p);
		}
		else
			dfs2(pos + 1, (val + pow[pos]) % p, num);
	}
	int work()
	{
		int T;
		scanf("%d", &T);
		pow[0] = 1;
		for (int i = 1; i < N; i++)
			pow[i] = (ll)pow[i - 1] * 2 % p;
		while (T--)
		{
			int c;
			ans = 0;
			mp.clear();
			scanf("%d%d%d", &n, &B, &c);
			dfs1(0, 0, 1);
			dfs2(LIM, 0, 1);
			printf("%d\n", ans);
		}
		return 0;
	}
}
int main()
{
#ifdef BlueSpirit
	freopen("CHNGSEQ.in", "r", stdin);
#endif
	return zyt::work();
}