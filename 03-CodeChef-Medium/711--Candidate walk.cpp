#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <string.h>
#include <set>
#include <map>
#include <stdlib.h>
#include <iomanip>
#include <bitset>
#include <cmath>

using namespace std;

long long dp[(1<<16)];
int n, d;
const long long inf = 1E18;

int get(const vector<int>&x)
{
	int res = 0;
	for (int i=0; i<x.size(); i++) res = res*d + x[i];
	return res;
}
long long penalty(const vector<int>&x)
{
	int a = 0, b = 0;
	for (int i=0; i<x.size(); i++)
		a ^= x[i], b += x[i];
	long long A = a, B = b;
	return A*B;
}
long long rec(vector<int>&pos)
{
	int id = get(pos);
	if ( dp[id] != -1 ) return dp[id];
	if ( id == 0 )
	{
		dp[id] = 0;
		return 0;
	}
	dp[id] = inf;
	vector<int>go = pos;
	long long cost = penalty(pos), mint = inf;
	for (int i=0; i<n; i++)
	{
		if ( pos[i] > 0 )
		{
			go[i]--;
			mint = min( mint, rec(go) );
			go[i]++;
		}
	}
	dp[id] = mint + cost;
	return dp[id];
}
void solve()
{
	cin>>n>>d;
	memset(dp, -1, sizeof(dp));
	vector<int>start;
	for (int i=1; i<=n; i++) start.push_back(d-1);
	cout<<rec(start)<<"\n";
}
int main()
{
	int test;
	cin>>test;
	while ( test-- ) solve();
	return 0;
}