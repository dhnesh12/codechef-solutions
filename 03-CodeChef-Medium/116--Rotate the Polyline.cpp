#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//point struct and basic operations
struct point
{
	ll x, y;
	point() {x = 0; y = 0;}
	point(ll x, ll y): x(x), y(y) {}
	int quarter()const
	{
		if (x >= 0 && y >= 0)
			return 0;
		if (x <= 0 && y >= 0)
			return 1;
		if (x <= 0 && y <= 0)
			return 2;
		if (x >= 0 && y <= 0)
			return 3;
		assert(false);
		return -1;
	}
};
point operator-(const point &a, const point &b)
{
	return point(a.x - b.x, a.y - b.y);
}
point operator+(const point &a, const point &b)
{
	return point(a.x + b.x, a.y + b.y);
}
ll cross(const point &a, const point &b)
{
	return a.x * b.y - a.y * b.x;
}
ll dot(const point &a, const point &b)
{
	return a.x * b.x + a.y * b.y;
}
//comparator for sorting A and X
bool operator<(pair<point, int> c, pair<point, int> d) {
	if (c.first.quarter() != d.first.quarter())
		return c.first.quarter() < d.first.quarter();
	ll cr = cross(c.first, d.first);
	if (cr != 0)
		return cr > 0;
	else
		return c.second < d.second;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int t;
	cin >> t;
	assert(1 <= t && t <= 5);
	while (t--)
	{
		int n;
		cin >> n;
		assert(n >= 3 && n <= 100000);
		vector<point>P(n + 1);
		for (int i = 0; i < n; i++)
		{
			cin >> P[i].x >> P[i].y;
			assert(abs(P[i].x) <= 500000000);
			assert(abs(P[i].y) <= 500000000);
		}
		P[n] = P[0];
 
		//storing all points in a sorted vector
		vector<pair<point, int>>A;
		for (int i = 0; i < n; i++)
		{
			A.push_back({P[i] - P[i + 1], i});
// 			A.push_back({P[i + 1] - P[i], -1});
		}
		//adding some more vectors so A[i]+A[i+1] would work properly
		for (int x = -1; x <= 1; x++)
		{
			for (int y = -1; y <= 1; y++)
			{
				if (x != 0 || y != 0)
					A.push_back({point(x, y), -1});
			}
		}
		sort(A.begin(), A.end());
		//X[side][quarter]
		//Y[side]
		set<pair<point, int>>X[3][4];
		set<int>Y[3];
		for (auto i : A)
		{
			if (i.second != -1)
			{
				X[0][i.first.quarter()].insert(i);
				Y[0].insert(i.second);
			}
		}
		A.push_back(A[0]);
		for (int i = 0; i + 1 < (int)A.size(); i++)
		{
			point v = A[i].first + A[i + 1].first;
			//0 ->  >0
			//1 ->  <0
			//2 ->  =0
			auto s = [&](pair<point, int>a)
			{
				ll val = cross(v, a.first);
				if (val > 0)
					return 0;
				if (val < 0)
					return 1;
				return 2;
			};
			for (int c = 0; c < 3; c++)
			{
				for (int k = 0; k < 4; k++)
				{
					while (!X[c][k].empty())
					{
						auto it = X[c][k].begin();
						if (s(*it) != c)
						{
							Y[s(*it)].insert(it->second);
							Y[c].erase(it->second);
							X[s(*it)][k].insert(*it);
							X[c][k].erase(it);
							continue;
						}
						it = --X[c][k].end();
						if (s(*it) != c)
						{
							Y[s(*it)].insert(it->second);
							Y[c].erase(it->second);
							X[s(*it)][k].insert(*it);
							X[c][k].erase(it);
							continue;
						}
						break;
					}
				}
			}
			bool ok = false;
			if (Y[2].empty())
			{
				for (int t : {0, 1})
				{
					assert(!Y[t].empty());
					int sz = Y[t].size();
					int diff = (*(--Y[t].end())) - (*Y[t].begin()) + 1;
					if (diff == sz)
					{
						cout << v.y << " " << -v.x << "\n";
						goto GG;
					}
				}
			}
		}
		cout << "0 0\n";
GG:;
	}
} 