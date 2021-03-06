#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
 
#include <cmath>
#include <cstdio>
#include <queue>
#include <list>
#include <stack>
#include <utility>
#include <numeric>
#include <map>
#include <cctype>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include <iomanip>
#include <set>
 
using namespace std;
 
#define F(a,b) for(int a=0;a<b;a++)
#define REP(a,b) for(int a=0;a<b;a++)
#define FOR(a,b,c) for(int a=b;a<c;a++)
#define FORD(a,b,c) for(int a=b;a>=c;a--)
 
#define S scanf
#define P printf
 
#define LEN(x) ((int)x.length())
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define MP(x,y) make_pair(x,y)
#define PB(x) push_back(x)
#define INF 1000000000
 
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<int, PII> PIII;
typedef vector<int> VI;
typedef vector<bool> VB;
typedef vector<string> VS;
 
//int d[][2]={{-1.0},{1,0},{0,-1},{0,1}};
 
int tourCity[4000001];
int tourCost[23100001];
int tourNextCost[4000001];
//priority_queue< pair<pair<int,int> ,int> , vector<pair<pair<int, int> ,int> >, greater<pair< pair<int,int> ,int> > > OutRoad[100005];
 
vector< pair<pair<int, int>, int> > OR[100005];
int pointer[100005];
 
 
int maxOut[100005];
int visCount[100005];
int visNCount[100005];
bool visEdge[200010];
 
char *ipos, InpFile[20000000];
inline int input() {
	 
	while(*ipos <= 32) ++ipos;
	int x=0, neg = 0;char c;
	while( true ) {
		c=*ipos++; if(c == '-') neg = 1;
		else {
			if (c<=32) return neg?-x:x;
			x=(x<<1)+(x<<3)+c-'0';
		}
	}
}
inline LL inputll() {
	 
	while(*ipos <= 32) ++ipos;
	LL x=0, neg = 0;char c;
	while( true ) {
		c=*ipos++; if(c == '-') neg = 1;
		else {
			if (c<=32) return neg?-x:x;
			x=(x<<1)+(x<<3)+c-'0';
		}
	}
}
 
int main()
{
	ipos = InpFile; 
	fread_unlocked(InpFile,20000000,1,stdin);
	int n,m;
	int a,b;
	int ca,cb;
	int pathCount=0;
	//S("%d%d",&n,&m);
 
	n= input();
	m = input();
	REP(i,n+1) pointer[i] = 0;
	REP(i,m)
	{
		//S("%d%d%d%d",&a, &b, &ca, &cb );
		a=input();
		b=input();
		ca=input();
		cb=input();
		//OutRoad[a-1].push( MP( MP( ca, b-1 ), 2*i) );
		OR[a-1].PB( MP( MP( ca, b-1), 2*i));
		maxOut[a-1] = max( maxOut[a-1], ca );
 
		//OutRoad[b-1].push( MP( MP( cb, a-1 ), 2*i+1) );
		OR[b-1].PB( MP( MP( cb, a-1), 2*i+1));
		maxOut[b-1] = max( maxOut[b-1], cb );
	}
	REP(i,n) sort(ALL(OR[i]));
 
	//int finalInd = OutRoad[0].top().second;
	int finalInd = OR[0][0].second;
	int ctr=0;
	int city = 0;
	int offset=0;
	bool flIn = false;
	while(1)
	{
		//if( pathCount >23000000 ) return 0;
		/*if(OutRoad[city].empty())
		{
			//assert(false);
			P("Fucked\n");
			P("%d\n",city);
			P("%d\n",ctr);
			exit(0);
		}*/
 
		//int ind = OutRoad[city].top().second;
		int ind = OR[city][pointer[city]].second;
		if(ctr>=2*m && finalInd == ind)
		{
			if( ! flIn )
			{
				offset = pathCount;
				flIn = true;
			}
			else break;
		}
		//int tmpCity = OutRoad[city].top().first.second;
		int tmpCity = OR[city][pointer[city]].first.second;
		if(flIn)
			//tourCity[pathCount-offset] = OutRoad[city].top().first.second;
			tourCity[pathCount-offset] = OR[city][pointer[city]].first.second;
		//tourCost[pathCount] = OutRoad[city].top().first.first;
		tourCost[pathCount] = OR[city][pointer[city]].first.first;
		visCount[city]++;
		if( flIn ) visNCount[city]++;
		//OutRoad[city].pop();
 
		OR[city][pointer[city]].first.first = visCount[city]+maxOut[city];
		pointer[city]++;
		if( pointer[city] >= SZ(OR[city]) ) pointer[city]-=SZ(OR[city]);
		//OR[city].erase( OR[city].begin() );
		if(flIn)
			tourNextCost[pathCount-offset] = maxOut[city] + visCount[city];
		//OutRoad[city].push( MP( MP( visCount[city]+maxOut[city] , tmpCity ), ind) );
		//OR[city].PB( MP( MP( visCount[city]+maxOut[city] , tmpCity ), ind) );
		if(!visEdge[ind])
		{
			ctr++;
			visEdge[ind]=true;
		}
 
		city = tmpCity;
		pathCount++;
	}
 
 
	//P("%d\n",pathCount);
 
	int query;
	LL k;
	//S("%d",&query );
	query = input();
	while(query--)
	{
		//S("%lld",&k);
		k=inputll();
		if( k <= pathCount )
		{
			P("%d\n", tourCost[k-1] );
		}
		else
		{
 
			int pathind = (k-1-offset)%(pathCount-offset);
			int times = (k-1-offset)/(pathCount-offset);
 
			//pathind+= offset;
 
			int pathPrev = pathind-1;
			if( pathPrev == -1 ) pathPrev = pathCount-1-offset;
			LL ans = tourNextCost[pathind];
			times--;
			ans += (LL)times*visNCount[tourCity[pathPrev]];
			//ans += (edgeGap[tourEdgeInd[pathind]]);
			P("%lld\n",ans);
 
		}
	}
	return 0;
}
