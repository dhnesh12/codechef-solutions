/* AUTHOR : Jagreet 'v01d' Das Gupta */

// --------------------<OPTIMIZ>--------------------
#pragma GCC optimize("O3")
//(UNCOMMENT WHEN HAVING LOTS OF RECURSIONS)\
#pragma comment(linker, "/stack:200000000")
//(UNCOMMENT WHEN TRYING TO BRUTEFORCE WITH A LOT OF LOOPS)\
#pragma GCC optimize("unroll-loops")
// -------------------</OPTIMIZ>--------------------

//--------------<MACROS-DEF>------------------
//Includes and Namespaces
#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <ratio>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
//TypeDefs
#define int long
#define i64 int64_t
#define ld long double
//Functs
#define pb push_back
#define mp make_pair
#define rmin(self,foreign) self = min(self,foreign)
#define rmax(self,foreign) self = max(self,foreign)
#define runtime() ((double)clock() / CLOCKS_PER_SEC)
#define sqr(x) ((x)*(x))
//Loops
#define REP(i,n) for (int i = 0; i < n; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FOR(i,a,b) for (int i = a; i <b; i++)
#define FORD(i,a,b) for (int i = b-1; i >=a; i--)
#define WL(t) while(t --)
#define all(v) v.begin(),v.end()
//DS
#define pii pair<int,int>
#define F first
#define S second
#define mii map<int,int>
#define vi vector<int>
#define vvi vector<vi>
#define pq(type) priority_queue<type>
#define pqd(type) priority_queue< type,vector<type>,greater<type> >
#define itr :: iterator it
//Printing
#define out_flush fflush(stdout)
#define precise(x) cout << fixed << setprecision(x); 
#define endl "\n"
#define print(x) cout << x << "\n";
#define printn(x) printf("%d\n",x);;
#define debug(x) cout << x << "\n";
#define debug2(x,y) cout << x << " " << y << "\n";
#define debug3(x,y,z) cout << x << " " << y << " " << z << "\n";
#define debug4(x,y,z,zz) cout << x << " " << y << " " << z <<" "<<zz << "\n";
#define debug5(x,y,z,zz,yy) cout << x << " " << y << " " << z <<" "<<zz << " "<< yy << "\n";
//--------------</MACROS-DEF>-----------------

//--------------<BOOST>------------------
//(UNCOMMENT WHEN USING BOOST LIBRARIES)
/*#include <boost/multiprecision/cpp_int.hpp> 
#include <boost/multiprecision/cpp_dec_float.hpp> 
using namespace boost::multiprecision;
using boost::multiprecision::cpp_dec_float_50; 
using boost::multiprecision::cpp_dec_float_100;
#define f50 cpp_dec_float_50
#define f100 cpp_dec_float_100
#define i128 int128_t
#define big_int cpp_int*/
//--------------</BOOST>-----------------

//--------------<CONST>------------------
const int INF  = (int)(1e14);
const int MOD  = 1000000007;
const int PI   = (int)(atan(1))*4;
const int LIM = (int)(2e5+10);
const int FMOD = 998244353;
const double EPS = 1e-9;
const int SQRTN = 1003;
const int LOGN = 22;
//--------------</CONST>-----------------

//---------------------<MOD_ARITH>------------------------
template<typename T> T gcd(T a, T b){return(b?__gcd(a,b):a);}
template<typename T> T lcm(T a, T b){return(a*(b/gcd(a,b)));}
int add(int a, int b, int c){int res=a+b;return(res>=c?res-c:res);}
int mod_neg(int a, int b, int c){int res;if(abs(a-b)<c)res=a-b;else res=(a-b)%c;return(res<0?res+c:res);}
int mul(int a, int b, int c){int res=(int)a*b;return(res>=c?res%c:res);}
int mulmod(int a,int b, int m){int q = (int)(((ld)a*(ld)b)/(ld)m);int r=a*b-q*m;if(r>m)r%=m;if(r<0)r+=m;return r;}
template<typename T>T expo(T e, T n){T x=1,p=e;while(n){if(n&1)x=x*p;p=p*p;n>>=1;}return x;}
template<typename T>T power(T e, T n, T m){T x=1,p=e;while(n){if(n&1)x=mul(x,p,m);p=mul(p,p,m);n>>=1;}return x;}
template<typename T>T extended_euclid(T a, T b, T &x, T &y){T xx=0,yy=1;y=0;x=1;while(b){T q=a/b,t=b;b=a%b;a=t;\
t=xx;xx=x-q*xx;x=t;t=yy;yy=y-q*yy;y=t;}return a;}
template<typename T>T mod_inverse(T a, T n){T x,y,z=0;T d=extended_euclid(a,n,x,y);return(d>1?-1:mod_neg(x,z,n));}
//--------------------</MOD_ARITH>------------------------

// -------------------------<RNG>-------------------------
mt19937 RNG(chrono::steady_clock::now().time_since_epoch().count()); 
#define SHUF(v) shuffle(all(v), RNG);
// Use mt19937_64 for 64 bit random numbers.
// ------------------------</RNG>-------------------------

//------------------------<EXT_DEBUG>---------------------
#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
	cerr << name << " : " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
	const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif
//-----------------------</EXT_DEBUG>---------------------


void solve();
signed main()
{
	#ifndef ONLINE_JUDGE
	freopen("../input.txt","r",stdin);
	freopen("../output.txt","w",stdout);
	#else
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	#endif
	int t = 1;
	//cin >> t;
	WL(t) solve();
}

int n;
int ar[LIM];
int color[LIM];
int c;

void dfs(int node,int col)
{
	if(color[node]!=-1) return;
	color[node] = col;
	REP(i,n)
	{
		if(i==node) continue;
		if(color[i]==-1&&gcd(ar[node],ar[i])==1)
		{
			dfs(i,col);
		}
	}
}

void solve()
{
	cin >> n;
	REP(i,n) cin >> ar[i];
	memset(color,-1,sizeof(int)*n);
	c=0;
	REP(i,n)
	{
		if(color[i]==-1) dfs(i,++c);
	}
	/*REP(i,n)
	{
		trace(i,color[i]);
	}*/
	print(c);
}