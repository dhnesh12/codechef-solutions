#include <vector>
#include <list>
#include <cassert>
#include <sstream>
#include <map>
#include <set>
#include <climits>
#include <deque>
#include <fstream>
#include <stack>
#include <bitset>
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstring>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
template<class A, class B> A cvt(B x)
{
    stringstream s;
    s<<x;
    A r;
    s>>r;
    return r;
}
#define FOR(i,a,b) for(int i= (int )a ; i < (int )b ; ++i) 
#define REV(i,a,b) for(int i= (int )a ; i >= (int)b ; --i)
#define REP(i,n) FOR(i,0,n)
#define DEP(i,n) REV(i,n,0)
#define PB push_back
#define PP pop()
#define EM empty()
#define INF 1000000000
#define PF push_front
#define ALL(x) x.begin(),x.end()
#define SORT(x) sort(ALL(x))
#define V(x) vector< x >
#define Debug false
#define PRINT(x)        cout << #x << " " << x << endl
#define LET(x,a) 	    __typeof(a) x(a)
#define IFOR(i,a,b) 	for(LET(i,a);i!=(b);++i)
#define EACH(it,v)  	IFOR(it,v.begin(),v.end())
#define PRESENT(c,x) 	((c).find(x) != (c).end())
#define SZ(x) 		x.size()
#define CPRESENT(c,x) 	(find(c.begin(),c.end(),x) != (c).end())
#define D(N) 		int N
#define S(N)		scanf("%d",&N)
#define FASTIO          1
typedef pair<int,int>   PI;
typedef pair<int,PI>    TRI;
typedef V( int )        VI;
typedef V( PI  )        VII;
typedef V( string )     VS;
typedef long long       LL;
typedef long double     LD;
#ifndef FASTIO
char *ipos, *opos, InpFile[20000000], OutFile[20000000], DIP[20];
inline int input(int flag=0)
{
    while(*ipos <= 32)
    ++ipos;
	if(flag)
	return (*ipos++ - '0');
	int x=0, neg = 0;char c;
	while( true )
	{
		c=*ipos++;
		if(c == '-')
		neg = 1;
		else
		{
			if (c<=32)
			return neg?-x:x;
			x=(x<<1)+(x<<3)+c-'0';
		}
	}
}
inline void output(int x,int flag)
{
	int y,dig=0;
	while (x||!dig)
	{
	    y=x/10;
	    DIP[dig++]=x-((y << 3) + (y << 1))+'0';
	    x=y;
	}
	while (dig--)
	*opos++=DIP[dig];
	*opos++= flag ? '\n' : ' ';
}
inline void InitFASTIO()
{
	ipos = InpFile; opos = OutFile;
	fread_unlocked(InpFile,20000000,1,stdin);
}
inline void FlushFASTIO()
{
	fwrite_unlocked(OutFile,opos-OutFile,1,stdout);	
}
#endif
#define Max 5010
int r, c, sr, sc, er, ec, bad;
int badones[Max][2];
int dist[310][310];
int d[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
int mark1[310][310], mark2[310][310];
queue<TRI> Q1, Q2;
bool check(int x,int y)
{
   return x >= 0 && x < r && y >= 0 && y < c;
}
void pre()
{
   REP(i,r) REP(j,c) if(!mark2[i][j]) Q2.push(TRI(0,PI(i,j)));
   while(!Q2.empty())
   {
       TRI top = Q2.front(); Q2.pop();
       int dist = top.first, x = top.second.first, y = top.second.second;
       REP(k,4)
       {
           int x1 = x + d[k][0];
           int y1 = y + d[k][1];
           if(check(x1,y1) && mark2[x1][y1] == -1)
           {
               mark2[x1][y1] = dist + 1;
               Q2.push(TRI(dist+1,PI(x1,y1)));
           }
       }
   }
}
bool simulate(int d1)
{
    memset(mark1,-1,sizeof mark1);
    mark1[sr][sc] = 0;
    queue<PI> Q; Q.push(PI(sr,sc));
    while(!Q.empty())
    {
      PI top = Q.front();
      Q.pop();
      int x = top.first, y = top.second;
      if(x == er && y == ec && mark1[x][y] <= mark2[x][y]*d1)
      {
          return true;
      }
      else if(!d1)
      return false;
      if(mark1[x][y] >= mark2[x][y]*d1)
      continue;
      REP(k,4)
      {
          int x1 = x + d[k][0];
          int y1 = y + d[k][1];
          if(check(x1,y1) && mark1[x1][y1] == -1)
          {
              mark1[x1][y1] = mark1[x][y] + 1;
              Q.push(PI(x1,y1));
          }
      }
   }
   return false;
}
int main()
{
    int kases, x, y; scanf("%d",&kases);
    while(kases--)
    {
      scanf("%d%d%d%d%d%d%d",&r,&c,&sr,&sc,&er,&ec,&bad);
      memset(mark1,-1,sizeof mark1);
      memset(mark2,-1,sizeof mark2);
      REP(i,bad)
      {
          scanf("%d%d",&badones[i][0], &badones[i][1]);
          mark2[badones[i][0]][badones[i][1]] = 0;
      }
      pre();
      int low = 0, high = r + c + 1, mid, solved = 0;
      REP(i,9)
      {
          mid = (low + high)/2;
          if(simulate(mid))
          {
              solved = 1;
              high = mid;
          }
          else low = mid + 1;
      }
      if(!solved)
      puts("Impossible!");
      else
      printf("%d\n",high);
   }
   return 0;
}