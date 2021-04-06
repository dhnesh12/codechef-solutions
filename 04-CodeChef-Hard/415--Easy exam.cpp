#include<bits/stdc++.h>
using namespace std;

#define FRE(i,a,b)  for(i = a; i <= b; i++)
#define FRL(i,a,b)  for(i = a; i < b; i++)
#define mem(t, v)   memset ((t) , v, sizeof(t))
#define sqr(x)      (x)*(x)
#define all(x)      x.begin(),x.end()
#define un(x)       x.erase(unique(all(x)), x.end())
#define sf(n)       scanf("%d", &n)
#define sff(a,b)    scanf("%d %d", &a, &b)
#define sfff(a,b,c) scanf("%d %d %d", &a, &b, &c)
#define D(x)        cout<<#x " = "<<(x)<<endl
#define pf          printf
#define VI          vector <int>
#define pii         pair <int, int>
#define pll         pair <LL, LL>
#define pb          push_back
#define mp          make_pair
#define pi          acos(-1.00)
#define DBG         pf("Hi\n")
#define sz          size()
#define ins         insert
#define fi          first
#define se          second
#define xx          first
#define yy          second
#define inf         (1<<29)
#define MOD         2003
#define eps         1e-9
#define MAX         2003

typedef long long int LL;
typedef double db;

/* Min Priority queue
   priority_queue<int, vector<int>, greater <int> > q;
*/

//int dx[] = {+0,+1,+0,-1};
//int dy[] = {+1,+0,-1,+0};
//int dx[] = {-1,-1,-1,+0,+0,+1,+1,+1};
//int dy[] = {-1,+0,+1,-1,+1,-1,+0,+1};
//bool check(int n, int pos) {return (bool) (n & (1<<pos));}
//int on(int n, int pos) {return n | (1<<pos); }
//int off(int n, int pos) {return n & ~(1<<pos); }
LL ipow(LL a, int b)
{
    if(a == 0 )
        return 0;
    if(a == 1 || b == 0)
        return 1;
    if(b & 1)
        return (a * ipow(a,b-1)) % MOD;
    LL ret = ipow(a,b/2);
    return (ret * ret) % MOD;
}
int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    //ios_base::sync_with_stdio(0); cin.tie(0);
    int i, j, k, cs, t, n,  l, f;
    sf(t);
    FRE(cs,1,t)
    {
        sfff(n,k,l);
        sf(f);
        LL up = 1, down = 1;
        down = ipow(k, l);
        if(down % MOD == 0)
        {
            printf("0\n");
            continue;
        }
        down = ipow(down, MOD-2);
        for(i = n; i> n-l; i--)
            up = (up * i) % MOD;
        printf("%lld\n",(up * down) % MOD);
    }
    return 0;
}
