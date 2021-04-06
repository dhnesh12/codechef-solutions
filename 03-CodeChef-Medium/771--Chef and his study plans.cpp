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
const int M = 1000006;

vector<pii>in[M] , out[M];
int P[N][20];
int who[M];

int L[N] , R[N];

int main()
{
    #ifdef VAMP
        clock_t tStart = clock();
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    FastRead
    int n , q;
    cin >> n >> q;

    FOR(i,1,n){
        int l , r;
        cin >> l >> r;
        L[i] = l;
        R[i] = r;

        in[l].push_back(mk(i,r));
        out[r].push_back(mk(i,l));
    }
    R[n + 1] = L[n + 1] = 1e9;
    for(int j = 0;j < 20;j++)for(int i = 0;i <= n + 1;i++)P[i][j] = n + 1;

    int indx = n + 1, lowestR = 1e9;
    for(int i = M - 1;i >= 0;i--){

        for(pii x : out[i]){
            P[x.first][0] = indx;
        }

        for(pii x : in[i]){
            if(x.second < lowestR){
                lowestR = x.second;
                indx = x.first;
            }
        }
        who[i] = indx;
    }
    for(int j = 1;j < 20;j++){
        for(int i = 1;i <= n + 1;i++){
            P[i][j] = P[P[i][j - 1]][j - 1];
        }
    }
    for(int Q = 1;Q <= q;Q++){
        int l , r;
        cin >> l >> r;

        int me = who[l];

        if(r < R[me]){
            cout << 0 << "\n";
            continue;
        }
        int ans = 1;
        for(int i = 19;i >= 0;i--){
            int she = P[me][i];

            if(r >= R[she]){
                me = P[me][i];
                ans += (1 << i);
            }
        }
        cout << ans << "\n";
    }

    #ifdef VAMP
        fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);
    #endif
}