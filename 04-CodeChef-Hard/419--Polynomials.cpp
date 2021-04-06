#include <bits/stdc++.h>
using namespace std;

struct Poly
{
	long long a, b, c, d;
	Poly(long long _a = 0, long long _b = 0, long long _c = 0, long long _d = 1e18)
	{
		a = _a;
		b = _b;
		c = _c;
		d = _d;
	}
	long long Eval(long long x)
	{
		return a * x * x * x + b * x * x + c * x + d;
	}
};

const int sq = 350;

int t;
int n;
long long ans[355];

struct LiChaoTree
{
	vector <Poly> Tree;
	LiChaoTree(int n = 0)
	{
		Tree.resize(4 * n);
	}
	void Insert(int node, int l, int r, Poly P)
	{
		int mid = (l + r) >> 1;
		bool left = Tree[node].Eval(l) > P.Eval(l);
		bool midd = Tree[node].Eval(mid) > P.Eval(mid);
		if(midd)
		{
			swap(P, Tree[node]);
		}
		if(l == r)
		{
			return;
		}
		if(left == midd)
		{
			Insert(node << 1 | 1, mid + 1, r, P);
		}
		else
		{
			Insert(node << 1, l, mid, P);
		}
	}
	long long Get(int node, int l, int r, int val)
	{
		if(l == r)
		{
			return Tree[node].Eval(val);
		}
		else
		{
			int mid = (l + r) >> 1;
			if(mid >= val)
			{
				return min(Tree[node].Eval(val), Get(node << 1, l, mid, val));
			}
			else
			{
				return min(Tree[node].Eval(val), Get(node << 1 | 1, mid + 1, r, val));
			}
		}
	}
};

signed main()
{	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	// freopen("Input.txt", "r", stdin);
	// freopen("Output.txt", "w", stdout);
	cin >> t;
	while(t--)
	{
		LiChaoTree Thisisatree(100001);
		for(int i = 0; i <= sq; i++)
		{
			ans[i] = 1e18;
		}
		cin >> n;
		for(int i = 1; i <= n; i++)
		{
			Poly tmp;
			cin >> tmp.d >> tmp.c >> tmp.b >> tmp.a;
			for(int j = 0; j <= sq; j++)
			{
				ans[j] = min(ans[j], tmp.Eval(j));
			}
			Thisisatree.Insert(1, sq + 1, 100000, tmp);
		}
		int q;
		cin >> q;
		while(q--)
		{
			int tmp;
			cin >> tmp;
			if(tmp <= sq)
			{
				cout << ans[tmp] << '\n';
			}
			else
			{
				cout << Thisisatree.Get(1, sq + 1, 100000, tmp) << '\n';
			}
		}
	}
}
