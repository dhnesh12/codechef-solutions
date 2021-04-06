#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
#include <random>
#include <cassert>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define MEM(a,b) memset((a),(b),sizeof(a))
const LL INF = 1e9 + 7;
const int N = 4e5 + 10;
int maxv = N;
vector<int> v[N];
struct Node
{
	int x, y, z;
	void init()
	{
		scanf("%d%d%d", &x, &y, &z);
	}
} qr[N];
class SegmentTree
{
public:
	struct InnerNode
	{
		int sum1;
		LL sum2;
		InnerNode operator +(const InnerNode& node) const
		{
			return InnerNode{ sum1 + node.sum1,sum2 + node.sum2 };
		}
	} sumv[N * 4];
	int ql, qr, qx, qy;
	void init()
	{
		MEM(sumv, 0);
	}
	void set(int l, int r, int x = 1, int y = 1)
	{
		ql = l, qr = r, qx = x, qy = y;
	}
	inline void maintain(int o)
	{
		sumv[o] = sumv[o << 1] + sumv[o << 1 | 1];
	}
	void add(int l, int r, int o = 1)
	{
		if (ql <= l && r <= qr)
		{
			sumv[o].sum1 += qy;
			sumv[o].sum2 += 1LL * qx * qy;
			return;
		}
		int mid = (l + r) / 2;
		if (ql <= mid) add(l, mid, o << 1);
		if (mid < qr) add(mid + 1, r, o << 1 | 1);
		maintain(o);
	}
	void refrain(int l, int r, int o = 1)
	{
		if (l == r)
		{
			sumv[o].sum1 = 0;
			sumv[o].sum2 = 0;
			return;
		}
		int mid = (l + r) / 2;
		if (ql <= mid) refrain(l, mid, o << 1);
		if (mid < qr) refrain(mid + 1, r, o << 1 | 1);
		maintain(o);
	}
	InnerNode queryr(int l, int r, int o = 1)
	{
		if (qx == 0) return InnerNode{ 0,0LL };
		if (ql <= l && r <= qr)
		{
			if (qx >= sumv[o].sum1)
			{
				qx -= sumv[o].sum1;
				return sumv[o];
			}
		}
		if (l == r)
		{
			int s = min(qx, sumv[o].sum1);
			qx = 0;
			return InnerNode{ s,sumv[o].sum2 / sumv[o].sum1 * s };
		}
		InnerNode ret;
		ret.sum1 = ret.sum2 = 0;
		int mid = (l + r) / 2;
		if (mid < qr) ret = ret + queryr(mid + 1, r, o << 1 | 1);
		if (ql <= mid) ret = ret + queryr(l, mid, o << 1);
		return ret;
	}
	InnerNode queryl(int l, int r, int o = 1)
	{
		if (qx == 0) return InnerNode{ 0,0LL };
		if (ql <= l && r <= qr)
		{
			if (qx >= sumv[o].sum1)
			{
				qx -= sumv[o].sum1;
				return sumv[o];
			}
		}
		if (l == r)
		{
			int s = min(qx, sumv[o].sum1);
			qx = 0;
			return InnerNode{ s,sumv[o].sum2 / sumv[o].sum1 * s };
		}
		InnerNode ret;
		ret.sum1 = ret.sum2 = 0;
		int mid = (l + r) / 2;
		if (ql <= mid) ret = ret + queryl(l, mid, o << 1);
		if (mid < qr) ret = ret + queryl(mid + 1, r, o << 1 | 1);
		return ret;
	}
	int query(int l, int r, int o = 1)
	{
		if (ql <= l && r <= qr)
		{
			return sumv[o].sum1;
		}
		int mid = (l + r) / 2;
		if (ql <= mid) return query(l, mid, o << 1);
		else return query(mid + 1, r, o << 1 | 1);
	}
} st;
int len[N];
LL ans[N];
int depth[N];
int sons[N];
int e;
inline LL getsum(int n)
{
	return 1LL * n * (n + 1) / 2;
}
void dfslen(int x, int fa = 0)
{
	depth[x] = depth[fa] + 1;
	sons[x] = 0;
	len[x] = -1;
	int key = 0;
	for (int i = 0; i < v[x].size(); i++)
	{
		int y = v[x][i];
		if (y == fa) continue;
		dfslen(y, x);
		if (len[v[x][i]] > len[v[x][0]]) swap(v[x][0], v[x][i]);
		key = max(key, len[y]);
		sons[x] += sons[y] + 1;
	}
	len[x] = key + 1;
	depth[x]--;
}
void dfs(int x, int s, int l, int r, int fa = 0)
{
	//cout << x << endl;
	for (int i = 0; i < v[x].size(); i++)
	{
		int y = v[x][i];
		if (y == fa) continue;
		if (i == 0) dfs(y, s, l + 1, r, x);
		else
		{
			int sn = r + 1, sl = sn, sr = len[y] + sn - 1;
			st.set(sl, sr);
			st.refrain(1, maxv);
			dfs(y, sn, sl, sr, x);
			int cur = l + 1 - s;
			int pos = l + 1;
			for (int j = sl; j <= sr; j++)
			{
				st.set(j, j);
				auto key = st.query(1, maxv);
				st.set(pos, pos, cur, key);
				st.add(1, maxv);
				pos++, cur++;
			}
		}
		st.set(l + 1, l + 1, l + 1 - s);
		st.add(1, maxv);
	}
	int X = qr[x].x, Y = qr[x].y, Z = qr[x].z;
	if (X > depth[x] || Y > sons[x] || depth[x] + sons[x] < e)
	{
		ans[x] = -1;
		return;
	}
	int lx = max(X, e - sons[x]), ly = max(Y, e - depth[x]);
	int rx = min(depth[x], e - Y), ry = min(sons[x], e - X);
	LL lsumx = getsum(lx);
	st.set(l, r, ly);
	LL lsumy = st.queryl(1, maxv).sum2 - 1LL * (l - s) * ly;
	//cout << x << ' ' << lx << ' ' << ly << ' ' << lsumx << ' ' << lsumy << endl;
	if (lsumx - lsumy + Z >= 0)
	{
		int L = lx, R = rx;
		st.set(l, r, e - lx);
		ans[x] = max(0LL, getsum(lx) - (st.queryr(1, maxv).sum2 - 1LL * (l - s) * (e - lx)) + Z);
	}
	else
	{
		LL L = lx, R = rx;
		st.set(l, r, e - rx);
		ans[x] = max(0LL, -(getsum(depth[x]) - getsum(depth[x] - rx) - (st.queryl(1, maxv).sum2 - 1LL * (l - s) * (e - rx)) + Z));
	}
}
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int ncase;
	scanf("%d", &ncase);
	while (ncase--)
	{
		int n;
		scanf("%d%d", &n, &e);
		//maxv = n * 2;
		maxv = 2e5;
		for (int i = 1; i <= n; i++)
		{
			v[i].clear();
		}
		st.init();
		for (int i = 1; i < n; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			v[x].push_back(y);
			v[y].push_back(x);
		}
		dfslen(1);
		for (int i = 1; i <= n; i++)
			qr[i].init();
		dfs(1, 1, 1, len[1]);
		for (int i = 1; i <= n; i++)
			printf("%lld%c", ans[i], " \n"[i == n]);
	}
	return 0;
}