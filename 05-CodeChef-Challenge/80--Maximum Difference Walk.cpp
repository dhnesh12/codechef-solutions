#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <vector>
#include <cassert>
#include <complex>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 55;
int n, a[N][N];

void pr(int u, int v, bool my = true)
{
	a[u][v] = 0;
	if (my) printf("%d %d\n", u + 1, v + 1);
	fflush(stdout);
}

double out[N], deg[N];

int playavg(int u)
{
	int ret;
	double ans = -124123;
	for (int v = 0; v < n; v++)
	{
		if (a[u][v] == 0) continue;
		double sc = a[u][v];
		int st1 = a[u][v];
		out[u] -= a[u][v], deg[u]--, a[u][v] = 0;

		double avg = 0, ct = 0;
		for (int w = 0; w < n; w++)
		{
			if (a[v][w] == 0) continue;
			ct += 1;
			avg -= a[v][w];
			int st2 = a[v][w];
			out[v] -= a[v][w], deg[v]--, a[v][w] = 0;

			double supa = -12312312;
			for (int x = 0; x < n; x++)
			{
				if (a[w][x] == 0) continue;
				double cur = a[w][x];
				int st3 = a[w][x];
				out[w] -= a[w][x], deg[w]--, a[w][x] = 0;

				if (deg[x] > 0) cur -= out[x] / deg[x];
				if (cur > supa) supa = cur;
				if (deg[x] > 0) cur += out[x] / deg[x];

				a[w][x] = st3, out[w] += a[w][x], deg[w]++;
			}
			if(supa > -10000) avg += supa;

			a[v][w] = st2, out[v] += a[v][w], deg[v]++;
		}
		if (ct > 0) sc += avg / ct;
		if (sc > ans) ret = v, ans = sc;

		a[u][v] = st1, out[u] += a[u][v], deg[u]++;
	}
	return ret;
}

struct cmp
{
	bool operator() (const vector <int>& fst, const vector <int>& snd) const
	{
		int ret1 = 0;
		{
			int prev = -1, sgn = -1;
			for (int x : fst)
			{
				if (prev >= 0) ret1 += a[prev][x] * sgn;
				prev = x;
				sgn = -sgn;
			}
		}
		int ret2 = 0;
		{
			int prev = -1, sgn = -1;
			for (int x : snd)
			{
				if (prev >= 0) ret2 += a[prev][x] * sgn;
				prev = x;
				sgn = -sgn;
			}
		}
		if (ret1 == ret2) return fst.size() < snd.size();
		return ret1 > ret2;
	}
};

int go(int u, vector <int> seen = {})
{
	set <int> forbidden;
	int sz = seen.size();
	for (int i = 0; i < sz - 1; i++)
		if (seen[i] == u)
			forbidden.insert(seen[i + 1]);
	int ret = -1;
	for (int v = 0; v < n; v++)
		if (a[u][v] > 0 and (ret < 0 or a[u][v] > a[u][ret]))
			if (!forbidden.count(v))
				ret = v;
	return ret;
}

int playmax(int ver)
{
	set < vector <int>, cmp > s;
	for (int i = 0; i < n; i++)
	{
		if (a[ver][i] == 0) continue;
		vector <int> nn = {ver, i};
		int j = go(i, nn);
		if (j >= 0) nn.push_back(j);
		s.insert(nn);
	}

	while (!s.empty())
	{
		vector <int> cur = *s.begin();
		s.erase(s.begin());

		int u = cur.back();
		if ((int)cur.size() >= 9 or go(u, cur) < 0)
			return cur[1];

		set <int> forbidden;
		int sz = cur.size();
		for (int i = 0; i < sz - 1; i++)
			if (cur[i] == u)
				forbidden.insert(cur[i + 1]);

		for (int v = 0; v < n; v++)
		{
			if (a[u][v] == 0) continue;
			if (forbidden.count(v)) continue;
			vector <int> nn = cur;
			nn.push_back(v);
			int w = go(v, nn);
			if (w >= 0) nn.push_back(w);
			s.insert(nn);
		}
	}
	assert(0);
	return -1;
}

int main()
{
	scanf("%d", &n);
	int fst = 0, snd = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &a[i][j]);
			if (a[i][j] > 0)
				out[i] += a[i][j], deg[i]++;
			if (a[i][j] > a[fst][snd])
				fst = i, snd = j;
		}
	pr(fst, snd);

	int lst = snd, moves = 0, mx = 0;
	while (true)
	{
		if (go(lst) < 0) break;

		int u, v;
		scanf("%d%d", &u, &v);
		u--, v--, moves++;
		if (go(u) == v) mx++;
		pr(u, v, false);

		if (go(v) < 0) break;
		if (moves == mx) pr(v, lst = playmax(v));
		else pr(v, lst = playavg(v));
	}
	return 0;
}