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

const int N = 100005;
int n , q;
LL ara[N];
LL ans[N];
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
        cin >> n >> q;
        FOR(i,1,n){
            cin >> ara[i];
        }
        sort(ara + 1,ara + n + 1);

        deque<pair<int,int>>queries;
        FOR(i,1,q){
            int x;cin >> x;
            queries.push_back(mk(x , i));
        }
        SORT(queries);

        int indx = 0;
        long long lft = queries[0].first;

        long long sub = 0;
        long long pw = 1;

        for(int days = 1;days <= n;days++){

            while(lft <= ara[days] and indx < q){
                LL d = queries[indx + 1].first - queries[indx].first;
                lft = lft + d * pw;
                lft = min(lft,2000000000LL);
                ans[queries[indx].second] = days - 1;
                indx++;
            }
//            cout << days << " " << lft << " " << indx << "\n";
            lft = 2 * (lft - ara[days]);
            lft = min(lft,2000000000LL);

            pw = min(pw * 2,2000000000LL);
        }
        while(indx < q){
            ans[queries[indx].second] = n;
            indx++;
        }
        FOR(i,1,q)cout << ans[i] << "\n";
    }

    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}