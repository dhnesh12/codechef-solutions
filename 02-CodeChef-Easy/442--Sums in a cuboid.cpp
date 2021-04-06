                                                                     
                                                                     
                                                                     
                                             

/* Author :: Yash */
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

template<class A, class B> A cvt(B x) {stringstream s;s<<x;A r;s>>r;return r;}

#define FOR(i,a,b) for(int i= (int )a ; i < (int )b ; ++i) 
#define REP(i,n) FOR(i,0,n)
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
#define SZ(x) 		x.size();
#define CPRESENT(c,x) 	(find(c.begin(),c.end(),x) != (c).end())
#define D(N) 		int N
#define S(N)		scanf("%d",&N)
#define B(i,j,k)      ((i>=0 && j>=0 && k>=0)?B[i][j][k]:0)

typedef pair<int,int>  PI;
typedef pair<int,PI>   TRI;
typedef V( int )       VI;
typedef V( PI  )       VII;
typedef V( string )    VS;
typedef long long      LL;

#define B(i,j,k)      ((i>=0 && j>=0 && k>=0)?B[i][j][k]:0)

typedef pair<int,int>  PI;
typedef pair<int,PI>   TRI;
typedef V( int )       VI;
typedef V( PI  )       VII;
typedef V( string )    VS;
typedef long long      LL;


char outfile[10000000] , infile[20000000],D[20],*opos,*ipos;
int input()
{
	while(*ipos <= 32) ++ipos;
	int x=0,neg=0;
	char c;
	for(;;)
	{
		c=*ipos++;
		if (c<=32)
			return neg?-x:x;
		if (c=='-')
			neg=1;
		else
			x=(x<<1)+(x<<3)+c-'0';
	}
	return x;
}
void output(int x,int flag)
{
	int y,dig=0;
	if (x<0)
	{
		*opos++='-';
		x=-x;
	}
	while (x||!dig)
	{
		y=x/10;
		D[dig++]=x-(10*y)+'0';
		x=y;
	}
	while (dig--)
		*opos++=D[dig];

	*opos++= flag ? '\n' : ' ';
}




int B[100][100][100] , A[100][100][100];
int main() {

	opos = outfile;
	ipos = infile;
	fread_unlocked(infile,20000000,1,stdin);



	int kases; kases = input();
	while ( kases-- ) {
	
		int  X , Y , Z;
		X = input();Y = input(); Z = input();
		//scanf("%d%d%d",&X,&Y,&Z);
		REP ( i, X ) REP ( j ,Y ) REP ( k ,Z ) /*scanf("%lld",&B[i][j][k]);*/B[i][j][k] = input();
		REP ( i ,X ) REP ( j , Y ) REP ( k , Z ) {
			A[i][j][k] = B[i][j][k];
			A[i][j][k] -= (B(i,j,k-1) + B(i-1,j,k) + B(i,j-1,k)) - B(i-1,j-1,k) - B(i,j-1,k-1) - B(i-1,j,k-1) +
				        B(i-1,j-1,k-1);	
		}
		REP ( i , X  ) REP ( j , Y ) REP ( k , Z ) {
			output(A[i][j][k],k == Z - 1);
		}
	}
	fwrite_unlocked(outfile,opos-outfile,1,stdout); 
	return 0;
}


