#include <bits/stdc++.h>
#include <tr1/unordered_set>
#define pb push_back
#define mp make_pair
#define pi acos(-1.0)
#define ff first
#define ss second
#define re return
#define QI queue<int>
#define SI stack<int>
#define SZ(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define sqr(x) ((x) * (x))
#define ms(a,b) memset((a),(b),sizeof(a))
#define G() getchar()
#define MAX3(a,b,c) max(a,max(b,c))
#define II ( { int a ; read(a) ; a; } )
#define LL ( { Long a ; read(a) ; a; } )
#define DD ({double a; scanf("%lf", &a); a;})
 
double const EPS=3e-8;
using namespace std;
 
#define FI freopen ("input.txt", "r", stdin)
#define FO freopen ("output.txt", "w", stdout)
 
typedef long long Long;
typedef long long int64;
typedef unsigned long long ull;
typedef vector<int> vi ;
typedef set<int> si;
typedef vector<Long>vl;
typedef pair<int,int>pii;
typedef pair<string,int>psi;
typedef pair<Long,Long>pll;
typedef pair<double,double>pdd;
typedef vector<pii> vpii;
 
// For loop
 
#define forab(i, a, b)	for (__typeof (b) i = (a) ; i <= b ; ++i)
#define rep(i, n)		forab (i, 0, (n) - 1)
#define For(i, n)		forab (i, 1, n)
#define rofba(i, a, b)	for (__typeof (b)i = (b) ; i >= a ; --i)
#define per(i, n)		rofba (i, 0, (n) - 1)
#define rof(i, n)		rofba (i, 1, n)
#define forstl(i, s)	for (__typeof ((s).end ()) i = (s).begin (); i != (s).end (); ++i)
 
template< class T > T gcd(T a, T b) { return (b != 0 ? gcd<T>(b, a%b) : a); }
template< class T > T lcm(T a, T b) { return (a / gcd<T>(a, b) * b); }
 
//Fast Reader
template<class T>inline bool read(T &x){int c=getchar();int sgn=1;while(~c&&c<'0'||c>'9'){if(c=='-')sgn=-1;c=getchar();}for(x=0;~c&&'0'<=c&&c<='9';c=getchar())x=x*10+c-'0'; x*=sgn; return ~c;}
 
//int dx[]={1,0,-1,0};int dy[]={0,1,0,-1}; //4 Direction
//int dx[]={1,1,0,-1,-1,-1,0,1};int dy[]={0,1,1,1,0,-1,-1,-1};//8 direction
//int dx[]={2,1,-1,-2,-2,-1,1,2};int dy[]={1,2,2,1,-1,-2,-2,-1};//Knight Direction
//int dx[]={2,1,-1,-2,-1,1};int dy[]={0,1,1,0,-1,-1}; //Hexagonal Direction
 
/* **************************************  My code start here ****************************************** */
 
const int MX = ( 1 << 16 ) + 10  ;
const int D = 500000 + 10 ;
char str[D][18] , inp[35] , xx[35] , w[20]  ;
int idx ;
int vis[MX] ,len[D] ,  marked[D] , n  , cs , m;
bool dp[MX] , v[D] ;
unordered_set<string> vv ;
bool DP(int mask)
{
   //  printf(" mask :: %d\n",mask);
    if( mask == ( 1 << m ) - 1 ) return 0 ;
    bool &ret = dp[mask];
    if( vis[mask] == cs ) return ret ;
    vis[mask] = cs ;
    ret = 0 ;
    int i ;
    for ( i = 0 ; i < idx ; i++ )
    {
 
        if( (mask & marked[i]) == 0 )
        {
            if( DP( mask | marked[i] ) == 0 ) return ret = 1 ;
        }
    }
    return ret  ;
 
}
int main()
{
   // I will always use scanf and printf
   // May be i won't be a good programmer but i will be a good human being
   while( scanf("%d",&n) == 1 ) {
    vv.clear();
   rep( i , n )
   {
       scanf("%s",str[i]);
       int sz = strlen( str[i] );
       sort( str[i]  , str[i] + sz ) ;
       vv.insert( str[i] );
 
 
   }
   ms( vis , -1 );
   // ms( v , 0 );
   int r = II , c = II ;
   m = r * c ;
   int lim = 1 << m ;
   int t = II ;
   for ( cs = 1 ; cs <= t ; cs++ )
   {
 
       int id = 0 ;
 
       rep( j , r )
       {
          scanf("%s",xx );
          rep ( k , c ) inp[id++] = xx[k];
 
       }
       idx = 0 ;
       int i , j , k;
       for ( i = 1 ; i <= lim ; i++ )
       {
           id = 0 ;
           rep ( j , m )
           {
               if( i & ( 1 << j ) ) w[id++] = inp[j];
           }
           w[id] = '\0';
           sort( w , w + id  );
           if( vv.find(w) != vv.end() )
           {
               marked[idx++] = i ;
           }
       }
 
       if( DP( 0 ) ) puts("Alice");
       else puts("Bob");
   }
 
}
 
 
    return 0;
}