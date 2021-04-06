#include<cmath>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <utility>
#include<iostream>
#include<map>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;
 
#define LET(x,a) 	__typeof(a) x(a)
#define IFOR(i,a,b) 	for(LET(i,a);i!=(b);++i)
#define EACH(it,v)  	IFOR(it,v.begin(),v.end())
#define FOR(i,a,b)  	for(int i=(int)(a) ; i < (int)(b);++i)
#define REP(i,n) 	FOR(i,0,n)
#define PB		push_back
#define MP 		make_pair
#define EPS		1e-9
#define INF 2000000000
 
typedef vector<int>	VI;
typedef long long	LL;
typedef pair<int,int>	PI;
 
int main() {
	int t,n,m;
	int edges[10000][2], dimension[1000][2];
	long double X[1000],Y[1000];
  	scanf( "%d", &t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=0;i<m;i++){
			scanf("%d%d",&edges[i][0],&edges[i][1]);
		}
		for(int i=0;i<n;i++){
			scanf("%d%d",&dimension[i][0],&dimension[i][1]);
		}
		long double prevx = 0;
		REP(i,n){
			long double newx = prevx + dimension[i][0]/2.0 + 1;
			if(i)newx+=(dimension[i-1][0]/2.0);
			printf("%.7Lf 0\n",newx);
			prevx = newx;
		}
	}
	return 0;
}