/*
 * DATE : 2017-09-09
 * Algo :
*/
#include<bits/stdc++.h>
using namespace std;
/*------- Constants---- */

#define LL                      long long
#define Ulong                   unsigned long long
#define FOR(I,A,B)              for(long long i=0; i < n ; i++ )
#define REP(i,n)                for(long long i=0; i < n ; i++ )
#define mp                      make_pair
#define pb                      push_back
#define all(x)                  (x).begin(),(x).end()
#define PI                      acos(-1.0)
#define EPS                     1e-14
#define F                       first
#define S                       second
#define di(x)                   int x; input(x)
#define in(x)                   input(x)
#define in2(x,y)                in(x),in(y)
#define in3(x,y,z)              in(x),in2(y,z)
#define lc                      ((n)<<1)
#define rc                      ((n)<<1|1)
#define db(x)                   cout << #x << " -> " << x << endl
#define nl                      cout<<endl
#define ms(ara_name,value)      memset(ara_name,value,sizeof(ara_name))
#define IO                      ios_base::sync_with_stdio(0);cin.tie(0)
#define READ                    freopen("in.txt","r",stdin)
#define WRITE                   freopen("out.txt","w",stdout)
template<class T> inline void input(T &x) {
    register char c = getchar();x = 0;
    int neg = 0;
    for(; ((c<48 || c>57) && c != '-'); c = getchar());
    if(c=='-'){neg = 1;c = getchar();}
    for(; c>47 && c<58 ; c = getchar()){x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x = -x;
}
inline long long bigmod(long long p,long long e,long long M){
    long long ret = 1;
    for(; e > 0; e >>= 1){
        if(e & 1) ret = (ret * p) % M;
        p = (p * p) % M;
    } return ret;
}
template <class T> inline T gcd(T a,T b){if(b==0)return a;return gcd(b,a%b);}
template <class T> inline T modinverse(T a,T M){return bigmod(a,M-2,M);}

/***************************** END OF TEMPLATE *******************************/

const int N = 806;
int n,m;
LL x;
int D;
LL C[12];
const int MOD = 1e9+7;
LL MEM[N];
LL dp[N][N];

LL Func(LL x)
{
      LL ret = 0;
      LL PW = 1;
      for(int i=0;i<=D;i++) {
            ret += C[i]*PW;
            PW = (PW * x) % MOD;
            if(ret >=MOD) ret %= MOD;
      }
      return ret;
}

void add(LL &a,LL b) {
      a += b;
      if(a>=MOD) a-=MOD;
}
int main()
{
      //READ;
      int t;
      in(t);
      while(t--) {
            in3(m,n,x);
            in(D);
            for(int i=0;i<=D;i++) in(C[i]);
            for(int i=0;i<=n;i++) MEM[i] = Func((i*x)%MOD);
            for(int i=0;i<=n;i++) dp[1][i] = MEM[i];

            for(int i=2;i<=m;i++){
                  for(int j=0;j<=n;j++){
                        LL sum = 0;
                        for(int k=0;k<=j;k++) add(sum , (dp[i-1][j-k] * MEM[k]) %MOD );
                        dp[i][j]= sum;
                  }
            }
            printf("%lld\n",dp[m][n]);
      }
      return 0;
}
