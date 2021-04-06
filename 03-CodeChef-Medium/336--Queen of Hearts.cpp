
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define repr(i,a,b) for (int i = a; i > b; --i)
#define mm(lamb, tttt) memset(lamb, tttt, sizeof lamb)

#define null NULL
#define eps 0.000000001
#define mod 1000000007
#define PI 3.14159265358979323846
#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define ALL(V) V.begin(), V.end()
#define sz(V) (int)V.size()
#define _ <<" "<<

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <iterator>
#include <bitset>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <limits.h>
#include <iomanip>
#include <cctype>
#include <numeric>
#include <complex>

using namespace std;

typedef long long ll;
typedef vector <int> vi;
typedef pair <int, int> ii;
typedef pair<int, pair<int,int> > iii;
typedef vector<ii> vii;

#define N 100100

int n,q;
int best[N];
vi ranges[N];
vi cycleranges[N];
vi vis;
vi cycle;

int mini = 10000000, maxi = -1;

void dfsCycle(int u)
{
	cycle[u] = 1;
	mini = min(mini, u), maxi = max(maxi , u);
	int v = best[u];
	if (cycle[v] == -1)
	{
		dfsCycle(v);
	}
	return;
}

void dfs(int u)
{
	vis[u] = 0;
	int v = best[u];
	if (vis[v] == 0)
	{
		mini = 10000000, maxi = -1;
		dfsCycle(v);
		cycleranges[mini].pb(maxi);
	}
	else if (vis[v] == -1)
	{
		dfs(v);
	}
	vis[u] = 1;
	return;
}

vi segtree[4*N];
vi tree[4*N];

void build(int ind, int start, int end)
{
	if (end < start)
		return;
	else if (start == end)
	{
		sort(ranges[start].begin(), ranges[start].end());
		sort(cycleranges[start].begin(), cycleranges[start].end());
		segtree[ind] = ranges[start];
		tree[ind] = cycleranges[start];
		return;
	}
	int mid  = (start + end)>>1;
	build(2*ind, start, mid);
	build(2*ind + 1, mid+1, end);
	int l = 0, r = 0;
	vi &curr = segtree[ind];
	vi &left = segtree[2*ind], &right = segtree[2*ind + 1];
	while (l < sz(left) || r < sz(right))
	{
		if (l == sz(left))
		{
			curr.pb(right[r++]);
		}
		else if (r == sz(right))
		{
			curr.pb(left[l++]);
		}
		else if (left[l] <= right[r])
		{
			curr.pb(left[l++]);
		}
		else curr.pb(right[r++]);
	}
	l = r= 0;
	vi &curry = tree[ind];
	vi &lefty = tree[2*ind], &righty = tree[2*ind + 1];
	while (l < sz(lefty) || r < sz(righty))
	{
		if (l == sz(lefty))
		{
			curry.pb(righty[r++]);
		}
		else if (r == sz(righty))
		{
			curry.pb(lefty[l++]);
		}
		else if (lefty[l] <= righty[r])
		{
			curry.pb(lefty[l++]);
		}
		else curry.pb(righty[r++]);
	}

	return;
}
	
int query(int ind, int start, int end, int lo, int hi)
{
	if (start > end || lo > end || hi < start)
		return 0;
	if (lo <= start && hi >= end)
	{
		int p1 =  upper_bound(segtree[ind].begin(), segtree[ind].end(), hi) - lower_bound(segtree[ind].begin(), segtree[ind].end(), lo);
		int p2=  upper_bound(tree[ind].begin(), tree[ind].end(), hi) - lower_bound(tree[ind].begin(), tree[ind].end(), lo);
		return p1 - p2;
	}
	int mid = (start + end)>>1;
	return query(2*ind, start, mid, lo, hi) + query(2*ind + 1, mid+1, end, lo, hi);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin>>n>>q;
	rep(i, 0, n) 
	{
		cin>>best[i];
		best[i]--;
		ranges[i].pb(best[i]);
	}
	vis.resize(n, -1);
	cycle.resize(n, -1);
	rep(i, 0, n)
	{
		if (vis[i] == -1)
			dfs(i);
	}
	build(1, 0, n-1);
	rep(i, 0, q)
	{
		int l,r;
		cin>>l>>r;
		l--,r--;
		cout<<r - l + 1 - query(1, 0, n-1, l, r)<<"\n";
	}
	return 0;
}

