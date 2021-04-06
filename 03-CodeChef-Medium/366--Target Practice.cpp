#include<bits/stdc++.h>

using namespace std;

#define fRead(x)        freopen(x,"r",stdin)
#define fWrite(x)       freopen (x,"w",stdout)

#define LL              long long
#define ULL             unsigned long long
#define ff              first
#define ss              second
#define pb              push_back
#define PI              acos(-1.0)
#define mk              make_pair
#define pii             pair<int,int>
#define pll             pair<LL,LL>


#define min3(a,b,c)     min(a,min(b,c))
#define max3(a,b,c)     max(a,max(b,c))
#define min4(a,b,c,d)   min(a,min(b,min(c,d)))
#define max4(a,b,c,d)   max(a,max(b,max(c,d)))
#define SQR(a)          ((a)*(a))
#define FOR(i,a,b)      for(int i=a;i<=b;i++)
#define ROF(i,a,b)      for(int i=a;i>=b;i--)
#define REP(i,b)        for(int i=0;i<b;i++)
#define MEM(a,x)        memset(a,x,sizeof(a))
#define ABS(x)          ((x)<0?-(x):(x))

#define SORT(v)         sort(v.begin(),v.end())
#define REV(v)          reverse(v.begin(),v.end())
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
//#pragma comment(linker, "/stack:200000000")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FastRead        ios_base::sync_with_stdio(0);cin.tie(nullptr);
#ifdef VAMP
     #define debug(...) __f(#__VA_ARGS__, __VA_ARGS__)
    template < typename Arg1 >
    void __f(const char* name, Arg1&& arg1){
        cout << name << " = " << arg1 << std::endl;
    }
    template < typename Arg1, typename... Args>
    void __f(const char* names, Arg1&& arg1, Args&&... args){
        const char* comma = strchr(names+1, ',');
        cout.write(names, comma - names) << " = " << arg1 <<" | ";
        __f(comma+1, args...);
    }
#else
    #define debug(...)
#endif

int n;
double prob[3];
double dp[1 << 18][18];
int vis[1 << 18][18],vid;

double call(int mask,int len){
    if(mask == (1 << len) - 1 || len == 0)return 0;
//    debug(mask,len);
    if(vis[mask][len] == vid)return dp[mask][len];
    vis[mask][len] = vid;

    double ret = 1e9;

    for(int i = 0;i < len - 1;i++){
        if(mask & (1 << i) and (mask & (1 << (i + 1)))){
             int mask1 = 0 , mask2 = 0;
             int len1 = 0, len2 = 0;
             for(int j = 0;j <= i;j++){
                mask1 = mask1 | (mask & (1 << j));len1++;
             }
             for(int j = i + 1;j < len;j++){
                mask2 = mask2 | ((mask & (1 << j)) >> (i + 1));len2++;
             }
//             debug(mask,mask1,mask2,len1,len2);
             ret = call(mask1,len1) + call(mask2,len2);
             return dp[mask][len] = ret;
        }
    }
    for(int i = 0;i < len;i++){
        double x = 0;
        double sum = 0;
        for(int j = 0, ptr = i - 1;j < 3;j++,ptr++){
            if(ptr < 0 or ptr >= len)x += prob[j];
            else if(mask & (1 << ptr))x += prob[j];
            else{
                sum += prob[j]/100 * (call(mask | (1 << ptr),len) + 1);
            }
        }
        x/=100;
        if(x == 1)continue;
        double val = (x + sum)/(1 - x);
        ret = min(ret,val);
    }
    return dp[mask][len] = ret;

}
int main()
{

    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    FastRead
    int t;
    cin >> t;
    while(t--){
        cin >> n >> prob[0] >> prob[1] >> prob[2];
        ++vid;
        double ans = call(0,n);
        cout << fixed << setprecision(6) << ans << "\n";
    }

    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}