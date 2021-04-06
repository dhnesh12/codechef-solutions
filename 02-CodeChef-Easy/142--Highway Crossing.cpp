#include<bits/stdc++.h>
using namespace std;

typedef long long int LL;
typedef unsigned long long int ULL;

#define FORb(i, start, n) for(int i=start;i<n;i++)
#define FORe(i, end, n) for(int i=end;i>=n;i--)
#define PRINTARR(arr, n) for(int i=0; i<n; ++i)cout<<arr[i]<<" "
#define INTPAIR pair<int, int>
#define LSOne(S) (S & (-S))

#ifdef _WIN32
#define gx getchar
#define px putchar
#define ps putchar(' ')
#define pn putchar('\n')
#else
#define gx getchar_unlocked
#define px putchar_unlocked
#define ps putchar_unlocked(' ')
#define pn putchar_unlocked('\n')
#endif

#define MOD1 1000000007LL
#define MOD2 1000000009LL
#define BIG 10000000
//Fast Input
//Scan normal integer
void integer_scan( int &n )
{
int sign = 1; n = 0; char c = gx();
while( c < '0' || c > '9' )
{
if( c == '-' ) sign = -1;
c = gx();
}
while( c >= '0' && c <= '9' ) n = (n<<3) + (n<<1) + c - '0', c = gx();
n = n * sign;
}
//Scan a long long int
void long_integer_scan( LL &n )
{
int sign = 1; n = 0; char c = gx();
while( c < '0' || c > '9' )
{
if( c == '-' ) sign = -1; c = gx();
}
while( c >= '0' && c <= '9' ) n = (n<<3) + (n<<1) + c - '0', c = gx();
n = n * (LL)(sign);
}
//Scan a string
int string_scan( char a[] )
{
char c = gx();
while(c==' ' || c=='\n') c=gx();
int i=0;
while(c!='\n')a[i++] = c,c=gx();
a[i]=0;
return i;
}
//Scan a complete word
int word_scan( char a[] )
{
char c = gx();
while(c==' ' || c=='\n') c=gx();
int i=0;
while(c!='\n' && c!=' ')a[i++] = c,c=gx();
a[i]=0;
return i;
}
//Fast output
//Print a normal integer
void integer_print( int n )
{
if(n<0)
{
n=-n; px('-');
}
int i=10; char o[10];
do
{
o[--i] = (n%10) + '0';
n/=10;
}while(n);
do
{
px(o[i]);
}while(++i<10);
}
//Print a long long integer
void long_integer_print( LL n )
{
if(n<0LL)
{
n=-n; px('-');
}
int i=21; char o[21];
do
{
o[--i] = (n%10LL) + '0';
n/=10LL;
}while(n);
do
{
px(o[i]);
}while(++i<21);
}
//Print a string
void string_print( const char a[] )
{
const char *p=a;
while(*p)px(*p++);
}

const int len = 100004;

double v[len], p[len], c[len], s, y, safe_dist = 0.00001;
int n, d[len];

void solve()
{
	double ttime=0, ctime=y/s, wtime, dist_moved, ftime, btime;
	double fpos, bpos;
	
	FORb(i, 0, n)
	{
		//val1- Calculate the position of the car at ttime
		dist_moved = ttime*v[i];
		if(d[i] == 1)
		{
			fpos = p[i] + dist_moved;
			bpos = fpos - c[i];
		}
		else
		{
			fpos = p[i] - dist_moved;
			bpos = fpos + c[i];
		}
		
//		cout<<"After "<<ttime<<"s, position of car"<<i+1<<" is ["<<fpos<<" to "<<bpos<<"]"<<endl;
		
		//If val1 has already passed the chef, then check if the back part 
		// of the car has passed. If yes, cross immediately. Else, wait for some more time
		//cross now
		if(d[i] == 1 && bpos>=0)
		{
			ttime += ctime;
//			cout<<"Chef can cross- already passed"<<endl;
		}
		
		//cross now
		else if(d[i] == 0 && bpos<=0)
		{
			ttime += ctime;
//			cout<<"Chef can cross- already passed"<<endl;
		}
		
		//wait till it passes and then cross
		else
		{
			//val2- Calculate the time at which it will cross the chef
			//Calculate the time at which the front part reaches 0
			if(d[i] == 1)ftime = -fpos/v[i];
			else ftime = fpos/v[i];
			
			//If the chef can cross by then, do it
			if(ttime+ctime<ttime+ftime)
			{
				ttime += ctime;
//				cout<<"Chef can cross immediately"<<endl;
			}
			
			//Else, check at what time the back part crosses the 
			else
			{
				//Calculate the wtime = time for the bpos to cross 0 and go safe_dist ahead
				if(d[i] == 1)btime = -bpos/v[i];
				else btime = bpos/v[i];
				
				//Else, compute the waiting time for the back of the car to cross the chef
				// then make the chef cross and add that wtime and ctime to time
				
				wtime = btime + safe_dist/v[i];
				ttime += ctime + wtime;
				
//				cout<<"Chef has to wait for "<<wtime<<"s"<<endl;
			}
		}
	}
	
	printf("%0.8f\n", ttime);
//	cout<<ttime<<endl;
}

int main()
{
	int t, x;
	
	integer_scan(t);
	
	while(t--)
	{
		integer_scan(n);
		
		integer_scan(x);
		s = x;
		
		integer_scan(x);
		y = x;
		
		FORb(i, 0, n)
		{
			integer_scan(x);
			v[i] = x;	
		}
		
		FORb(i, 0, n)
		{
			integer_scan(d[i]);
		}
		
		FORb(i, 0, n)
		{
			integer_scan(x);
			p[i] = x;	
		}
		
		FORb(i, 0, n)
		{
			integer_scan(x);
			c[i] = x;	
		}
		
		solve();
	}	
	return 0;
}