#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAX = 31;
int N, C, D;
int S[MAX];
bool G[MAX][MAX];
int child[MAX], sibling[MAX];
int dp[MAX][MAX][MAX];
int out;
void root(int node, int parent)
{
	for (int adj = 1; adj <= N; adj++) if (G[node][adj]) if (adj != parent)
 	{
		sibling[adj] = child[node];
 		child[node] = adj;
		root(adj, node);
	}
}
int DP(int node, int parent, int chef, int day)
{
	if (node == 0)
	{
		// Build restaurant
		if (day && chef)
			return max(0, S[parent]);
		return 0;
	}
	int& ref = dp[node][chef][day];
	if (ref == -1)
	{
		// Don't transfer to node's child
		ref = DP(sibling[node], parent, chef, day);
		// Transfer to node's child
		for (int c = 1; c <= chef; c++)
			for (int d = 0; d <= day-1; d++)
				ref = max(ref, DP(child[node], node, c, d) +
								   DP(sibling[node], parent, chef-c, day-1-d));
	}
	return ref;
} 
void trace(int node, int parent, int chef, int day)
{
	if (node == 0)
	{
 	// Build restaurant
		if (day && chef && S[parent] >= 0)
		{
			printf("build %d\n", parent);
			out++;
		}
	}
	else
	{
		int ref = DP(node, parent, chef, day);
		// Don't transfer to node's child
		if (ref == DP(sibling[node], parent, chef, day))
		{
			trace(sibling[node], parent, chef, day);
			return;
		}
 	// Transfer to node's child
		for (int c = 1; c <= chef; c++)
			for (int d = 0; d <= day-1; d++)
			{
				int cur = DP(child[node], node, c, d) +
							 DP(sibling[node], parent, chef-c, day-1-d);
				if (ref == cur)
				{
					printf("transfer %d %d %d\n", parent, node, c);
					out++;
					trace(child[node], node, c, d);
					trace(sibling[node], parent, chef-c, day-1-d);
					return;
				}
			}
	}
}
 
int main()
{
	scanf("%d%d%d", &N, &C, &D);
	for (int i = 1; i <= N; i++)
		scanf("%d", &S[i]);
	for (int i = 1, u, v; i <= N-1; i++)
	{
		scanf("%d%d", &u, &v);
		G[u][v] = G[v][u] = true;
	}
 
	root(1, 0);
	memset(dp, -1, sizeof dp);
 
	printf("%d\n", DP(child[1], 1, C,  D));
 
	out = 0;
 
	trace(child[1], 1, C, D);
 
	for (; out < D; out++)
 
		printf("nothing\n");
 
}
 
 