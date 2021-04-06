#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<bits/stdc++.h>
#include<stack>
#include<queue>
#include<list>
#include<vector>
#include<bitset>
#include<unordered_map> 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// #include "boost/algorithm/string.hpp"
#define fio ios_base::sync_with_stdio(false)
#define mod 1000000007
#define mod1 mod
#define mod2 1000000007
#define li long long int
#define ll li
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define readi(x) scanf("%d",&x)
#define  reads(x)  scanf("%s", x)
#define readl(x) scanf("%I64d",&x)
#define rep(i,n) for(i=0;i<n;i++)
#define revp(i,n) for(i=(n-1);i>=0;i--)
#define myrep1(i,a,b) for(i=a;i<=b;i++)
#define myrep2(i,a,b) for(i=b;i>=a;i--)
#define pb push_back
#define mp make_pair
#define fi first
#define sec second
#define MAXN 1000000000000000005
#define MINN -1000000000000000000
#define INTMAX 1000001000
#define pii pair<ll,ll> 
#define pdd pair<double,double>
#define pic pair<int,char>
#define N 400000
#define lgn 20
#define ddouble long double
#define minus minu
#define PI 3.1415926535
#define lgn 20
 
 
// #define INTMAX 200000000 
 
// using namespace boost;
// #define si short int
 
using namespace std;
using namespace __gnu_pbds;             
typedef priority_queue<ll, vector<ll > > max_pq;
typedef priority_queue<ll, vector<ll> , greater<ll >  > min_pq;
ll toint(const string &s) {stringstream ss; ss << s; ll x; ss >> x; return x;}
string tostring ( ll number ){stringstream ss; ss<< number; return ss.str();}
 
// using namespace __gnu_pbds;         
// typedef priority_queue<pair<ll,char> , vector<pair<ll , char> > > max_pq;
// typedef priority_queue<pii , vector<pii > ,greater<pii > > min_pq;
typedef tree<pii , null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> OST;
// typedef priority_queue<pair < ll , pair < pii , ll > >  , vector<pair < ll , pair < pii , ll > >  > ,greater<pair < ll , pair < pii , ll > >  > > min_pq;
#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
    template <typename Arg1>
    void __f(const char* name, Arg1&& arg1){
        cout << name << " : " << arg1 << std::endl;
        //use cerr if u want to display at the bottom
    }
    template <typename Arg1, typename... Args>
    void __f(const char* names, Arg1&& arg1, Args&&... args){
        const char* comma = strchr(names + 1, ','); cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
    }
#else
#define trace(...)
#endif
#define nn 2000005
ll t;
vector < list < ll > > adjlist ( 300 );
ll n,m;
ll r,c;
ll scc = 0;
bool visited[ 200 ];
ll deg[ 200 ];
pii di[ 200 ];

ll ar[ 105 ][ 105*105 ];
void dfs ( ll i )
{
    scc++;
    for ( auto it : adjlist[i] )
    {
        if ( !visited[it] )
        {
            visited[it]=1;
            dfs(it);
        }
    }
}
pii dfsrc ( ll i , ll par )
{
    ll r = 0,c = 0;
    ll ch = 0;
    for ( auto it : adjlist[i] )
    {
        if ( it != par )
        {
            ch ++;
            pii val = dfsrc(it,i);
            r = max(r,val.fi);
            c += val.sec;

        }
    }
    if ( ch == 0 )
    {
        di[i] = mp(1,1);
        return mp(1,1);
    }
    else
    {
        di[i] = mp(r+1,c+ch+1);
        return mp(r+1,c+ch+1);
    }
}
void fill ( ll i , ll par, ll col , ll x1, ll y1, ll y2 )
{
    ll r1 = x1 + 1, c1 = y1 + 1;
    for ( auto it : adjlist[i] )
    {
        if ( it != par )
        {
            fill(it,i,1-col,r1,c1,c1+di[it].sec-1);
            c1 += di[it].sec + 1;
        }
    }
    for ( ll p = x1; p <= r; p ++)
    {
        for ( ll q = y1; q <= y2; q ++)
        {
            if ( ar[p][q] == -1 )
            {
                ar[p][q]=col;
            }
        }
    }


}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    t = 1;
    while( t-- )
    {
        cin >> n >> m;
        for ( ll i = 1; i <= m; i ++)
        {
            ll a,b;
            cin >> a >> b;
            deg[a]++;
            deg[b]++;
            adjlist[a].pb(b);
            adjlist[b].pb(a);
        }
        if ( m != n-1 )
        {
            cout <<"-1";
            return 0;
        }
        visited[1]=1;
        dfs(1);
        if ( scc == n )
        {
            pii dim = dfsrc(1,0);
            r = dim.fi;
            c = dim.sec;
            for ( ll i = 0; i <= r; i ++)
                for ( ll j = 0; j <= c; j ++)
                    ar[i][j] = -1;
            fill ( 1, 0 , 1 ,1, 1,c);
            cout << r <<" " << c << endl;
            for ( ll i = 1; i <= r; i ++)
            {
                for ( ll j = 1; j <= c; j ++)
                {
                    cout <<ar[i][j];
                }
                cout << endl;
            }
        }
        else
        {
            cout <<"-1";
            return 0;
        }
    }

}