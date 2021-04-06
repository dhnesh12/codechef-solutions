/*
 	C++ Template
	Pradeep George Mathias
 */

/* Solution in 3 parts:
 * Part 1: Finding Cycles
 * Part 2: Solving for "choose node" and "don't choose node" DPs for trees rooted on cycles
 * Part 3: Solving for cycles by "disconnecting cycle" and solving as if its a path
 */

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <cstdlib>
using namespace std;

#define s(T) scanf("%d", &T)
#define sl(T) scanf("%lld", &T)
#define fill(a, val) memset(a, val, sizeof(a))
#define mp make_pair
#define pb push_back
#define all(x) x.begin(), x.end()
#define DREP(x) sort(all(x)); x.erase(unique(all(x)), x.end())
#define INDEX(a, val) (lower_bound(all(a), val) - a.begin())

const int maxn = 100000;
const int MOD = 1000000007;

int totalCases, testNum;
int N;
int enemy[maxn+1];
vector <int> adjl[maxn+1];
vector <int> child[maxn+1];
vector <vector<int> > cycles;

long long CH[maxn+1];
long long nCH[maxn+1];
int visited[maxn+1];
bool incycle[maxn+1];

void preprocess()
{
	
}

void reinit()
{
	for(int i = 1; i <= N; i++)
		adjl[i].clear();
	for(int i = 1; i <= N; i++)
		child[i].clear();
	cycles.clear();
	fill(CH, -1);
	fill(nCH, -1);
	fill(visited, 0);
}

bool input()
{
	s(N);	assert(2 <= N && N <= maxn);
	for(int i = 1; i <= N; i++)
	{	
		s(enemy[i]);
		assert(i != enemy[i]);
		adjl[i].push_back(enemy[i]);
		adjl[enemy[i]].push_back(i);
	}
	return true;
}

int cycle_dfs(int u, vector <int> &C)
{
	/* visited[u] == 2 iff it has been popped from stack
	 * == 1 iff it is still on stack
	 * == 0 iff not yet visited, was never on stack
	 * Cycle finding involves finding a vertex thats still on dfs stack, then "unrolling" the stack
	 * returns the "head" of the cycle, which is used to break "unrolling" too much
	 * stores the vertices of the cycle in C
	 */
	
	if(visited[u] == 2)
		return -1;
	if(visited[u] == 1)
		return u;	// call this u the "head"
	
	assert(visited[u] == 0);
	visited[u]++;	// push on dfs stack
	int ret = cycle_dfs(enemy[u], C);
	if(ret != -1)
	{	
		incycle[u] = true;
		C.push_back(u);
	}
	else 
		incycle[u] = false;
	visited[u]++;	// pop from stack
	if(ret == u)
		return -1;	// break unrolling
	else 
		return ret;	// continue unrolling
}

void compute_dfs(int u, int p)
{
	CH[u] = nCH[u] = 1;
	for(int i = 0; i < adjl[u].size(); i++)
	{
		int v = adjl[u][i];
		if(incycle[v] || v == p)
			continue;
		compute_dfs(v, u);
		CH[u] = (CH[u] * nCH[v]) % MOD;			// choosing 'u' means I do NOT choose v
		nCH[u] = (nCH[u] * (CH[v] + nCH[v])) % MOD;	// not choosing 'u' means I MAY or MAY NOT choose v
	}
}

long long f(vector <int> cycle)				// Cut off cycle[0] from cycle[size()-1] and treat it like a path
{
	long long ch, nch;
	
	long long ans1;
	//choose cycle[0]
	ch = CH[cycle[0]];
	nch = 0;
	
	for(int i = 1; i < cycle.size(); i++)
	{
		long long nxtnch, nxtch;
		if(i == cycle.size() - 1)
		{
			nxtch = 0;					// when cycle[0] is chosen, I CAN'T choose cycle[size()-1]
			nxtnch = (nCH[cycle[i]] * (ch + nch)) % MOD;
		}
		else 
		{
			nxtch = (CH[cycle[i]] * nch) % MOD;
			nxtnch = (nCH[cycle[i]] * (ch + nch)) % MOD;
		}
		ch = nxtch;
		nch = nxtnch;
	}
	ans1 = (ch + nch) % MOD;
	
	long long ans2;
	//don't choose cycle[0]
	ch = 0;
	nch = nCH[cycle[0]];
	
	for(int i = 1; i < cycle.size(); i++)
	{
		long long nxtnch, nxtch;
		nxtch = (CH[cycle[i]] * nch) % MOD;
		nxtnch = (nCH[cycle[i]] * (ch + nch)) % MOD;
		
		ch = nxtch;
		nch = nxtnch;
	}
	ans2 = (ch + nch) % MOD;
	
	return (ans1 + ans2) % MOD;
}

void solve()
{
	//find cycles
	for(int i = 1; i <= N; i++)
	{	
		vector <int> tmp;
		cycle_dfs(i, tmp);
		if(tmp.size() > 0)
			cycles.push_back(tmp);
	}
	
	//build rooted trees / fill in CH/nCH values
	for(int i = 1; i <= N; i++)
		if(incycle[i])
			compute_dfs(i, i);
	
	//accumulate over disconnected components
	long long ans = 1;
	for(int i = 0; i < cycles.size(); i++)
		ans = (ans * f(cycles[i])) % MOD;
	printf("%lld\n", ans);
}

int main()
{
	preprocess();
	s(totalCases);
	for(testNum = 1; testNum <= totalCases; testNum++)
	{
		if( !input())
			break;
		solve();
		reinit();
	}
}
