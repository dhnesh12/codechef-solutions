
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<map>
#include<vector>
#include<list>
#include<set>
#include<queue>
#include<cassert>
#include<sstream>
#include<string>
#include<cmath>
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define REP(i,n) FOR(i,0,n)
#define myabs(x) (x>=0?x:-x)
#define min(a,b) (a<b?a:b)
using namespace std;
#define BUFSIZE (10000)
char inputbuffer[BUFSIZE];
char *ioptr=inputbuffer+BUFSIZE,*ioend=inputbuffer+BUFSIZE;
int input_eof=0;
#define getchar() ({if (ioptr >= ioend) init_input(); *ioptr++;})
#define eof() (ioptr>=ioend && input_eof)
#define eoln() ({if(ioptr >= ioend) init_input(); *ioptr == '\n';})
void init_input()
{
  if (input_eof)
  return;
  int existing = BUFSIZE - (ioend - inputbuffer);
  memcpy(inputbuffer, ioend, existing);
  int wanted = ioend - inputbuffer;
  int count=fread(inputbuffer + existing, 1, wanted, stdin);
  if (count < wanted)
  input_eof = 1;
  ioend = inputbuffer + BUFSIZE - (wanted - count);
  while (*--ioend > ' ');
  ioend++;
  ioptr=inputbuffer;
}
inline void non_whitespace()
{
  for(;;)
  {
    if(ioptr>=ioend)
    init_input();
    if(*ioptr>' ')
    return;
    ioptr++;
  }
}
inline int getint()
{
  non_whitespace();
  int neg=0;
  if(*ioptr=='-')
  {
    ioptr++;
    neg=1;
  }
  int n=0;
  while(*ioptr>' ')
  n=(n<<3)+(n<<1)+*ioptr++-'0';
  ioptr++;
  if(neg)
  n=-n;
  return n;
}
vector<int> adj[200002];
set<int> compG[200002];
int id[200002];
int low[200002];
int S[200002];
int SCC[200002];
int scc[200002];
int vis[200002];
bool label[200002];
int Stack[200002], head;
int C, T;
int n,m;
void tarjan(int u, int c)
{
	id[u] = C;
	low[u] = C;
	C++;
	S[u] = c;
	Stack[head++] = u;
	REP(i, adj[u].size())
	{
		int v = adj[u][i];
		if (id[v] == -1)
		{
			tarjan(v, c);
			low[u] = min(low[u], low[v]);
		} 
		else if (S[v] == c) 
		low[u] = min(low[u], id[v]);
	}
	if (low[u] == id[u])
	{
		int x;
		do
		{
			x = Stack[--head];
			S[x] = -1;
			SCC[x] = T;
		}
		while (x != u);
		T++;
	}
}
void Tarjans()
{
	C=0;
	T=0;
	head = 0;
	REP(i, 2*n+1)
	{
		id[i] = -1;
		S[i] = -1;
	}
	id[n] = -2;
	int c = 0;
	REP(i, 2*n+1) 
	if (id[i] == -1)
	{
		tarjan(i, c);
		c++;
	}
}
bool dfs(int s, int t, int v)
{
	if (s == t)
	return true;
	if (vis[s] == v)
	return false;
	vis[s] = v;
	for(set<int>::iterator it = compG[s].begin(); it != compG[s].end(); ++it)
	if (dfs(*it, t, v))
	return true;
	return false;
}
void dfs1(int x, set<int>& G)
{
	label[x] = 1;
	label[T-1-x] = 1;
	for(set<int>::iterator it = G.begin(); it != G.end(); ++it)
	if (!label[*it])
	dfs1(*it, compG[*it]);
}
int main()
{
	int T1 = getint();
	while (T1--)
	{
		n = getint();
		m = getint();
		REP(i, 2*n+1)
		{
			adj[i].clear();
			compG[i].clear();
			vis[i] = 0;
			label[i] = 0;
			scc[i] = -1;
		}
		REP(i, m)
		{
			int u = getint();
			int v = getint();
			if (u == -v)
			continue;
			adj[n-u].push_back(n+v);
			if(u!=v)
			adj[n-v].push_back(n+u);
		}
		Tarjans();
		bool conflict = false, unique = true;
		FOR(i,1,n+1)
		if (SCC[n+i] == SCC[n-i])
		{
			conflict = true;
			break;
		}
		if (!conflict)
		{
			int k = 0;
			FOR(i,1,n+1)
			{
				int u = SCC[n-i];
				if (scc[u] != -1)
				continue;
				int v = SCC[n+i];
				scc[u] = k;
				scc[v] = T-1-k;
				++k;
			}
			REP(i,2*n+1) if (i!=n)
			{
				int u = scc[SCC[i]];
				REP(j, adj[i].size())
				{
					int v = scc[SCC[adj[i][j]]];
					if (u!=v)
					compG[u].insert(v);
				}
			}
			REP(i,T) if (!label[i] && compG[i].find(T-1-i)!=compG[i].end())
			{
				dfs1(T-1-i, compG[T-1-i]);
			}
			REP(i,T) if (!label[i])
			{
			    unique = false;
			    break;
			}
		}
		printf("%s\n", conflict ? "CONFLICT" : (unique ? "UNIQUE" : "MULTIPLE"));
	}
	return 0;
}