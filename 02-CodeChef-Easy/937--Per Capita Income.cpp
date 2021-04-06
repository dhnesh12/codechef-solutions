/*
 *This code was made by -
 *                       __
 *    /\                /
 *   /__\               \_
 *  /    \                 \
 * /      \JITESH        __/AXENA
 *
 */

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define MOD 1000000007
#define DEBUG(x) cout << '>' << #x << " : " << x << '\n';
#define mp make_pair
#define pb push_back
#define fastIO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define POB pop_back
#define F first
#define S second
#define max(a, b) ((a < b)? b : a)
#define min(a, b) ((a > b)?b : a)
#define FOR(a,c)   for (auto (a) = 0; (a)<(c); (a)++)
#define FORL(a,b,c)  for (auto (a) = (b); (a)<=(c); (a)++)
#define FORR(a,b,c)  for (auto (a) = (b); (a)>=(c); (a)--)
#define FORB(a,c)   for (auto (a) = (c); (a)>=0; (a)--)

typedef long long int ll;
typedef map<ll, ll> MLL;
typedef set<ll> SL;
typedef vector<ll> VL;
typedef pair<ll,ll> PLL;
typedef vector<pair<ll,ll>> VPLL;
typedef map<int, int> MII;
typedef set<int> SI;
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector<pair<int,int>> VPII;

#define ordered_set_int tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_multiset_int tree<int, null_type, less_equal<>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_set_ll tree<ll, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_multiset_ll tree<ll, null_type, less_equal<>, rb_tree_tag, tree_order_statistics_node_update>
// oset.order_of_key(x) -> number of elements which are STRICTLY smaller than x
// oset.find_by_order(x) -> returns an iterator corresponding to the xth position in the set. (0-based indexing)

template<typename T>
T ceil(T a,T b)
{
    return (a+b-1)/b;
}
template<typename T>

T floor(T a,T b)
{
    return a/b;
}
// use as - ceil<ll>(1221,2323);
ll power(ll x, ll y, ll p = LLONG_MAX)
{
    ll res = 1;

    x = x % p;

    if (x == 0)
        return 0;

    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;

        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
ll modInverse(ll n, ll p)
{
    return power(n, p - 2, p);
}
/*-------------------------------------------------------------------------------------------------------*/

void solve();
int main()
{
#ifndef ONLINE_JUDGE
#ifndef CPH
    auto t1 = std::chrono::high_resolution_clock::now();
#endif
#endif
    fastIO;
    int t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
#ifndef ONLINE_JUDGE
#ifndef CPH
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    cout << "time taken: " << static_cast<double>(duration)/1000000;
#endif
#endif
    return 0;
}

typedef struct disjointset {
    VI parent,rank;
    int n;

    disjointset(int s) {
        parent.resize(s);
        rank.resize(s);
        n = s;
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int a) {
        if (parent[a] == a)
        {
            return a;
        }

        int rep = find(parent[a]);
        parent[a] = rep;
        return rep;
    }

    void unionByRank(int a,int b)
    {
        int sa = find(a);
        int sb = find(b);

        if(sa == sb)
        {
            return;
        }

        if(rank[sa] > rank[sb])
        {
            parent[sb] = sa;
        }
        else if(rank[sa] < rank[sb])
        {
            parent[sa] = sb;
        }
        else
        {
            parent[sa] = sb;
            rank[sa]++;
        }
    }
} disjointset;

void solve()
{
    int n,e;
    cin>>n>>e;

    VL a(n),b(n);
    map<PII,VI> m;
    vector<PII> c(n);
    int t;
    for(auto& x:a) cin>>x;
    for(auto& x:b) cin>>x;
    t=__gcd(a[0],b[0]);
    PII maxi={a[0]/t,b[0]/t};
    for (int i = 0; i < n; ++i)
    {
        t = __gcd(a[i],b[i]);
        a[i]/=t;
        b[i]/=t;
        c[i]={a[i],b[i]};
        m[c[i]].push_back(i+1);
        if(maxi.first*b[i] < a[i]*maxi.second)
        {
            maxi={a[i],b[i]};
        }
    }

    vector<int> adj[n+1];
    int u,v;

    for (int i = 0; i < e; ++i)
    {
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    disjointset s(n+1);
    for(auto x:m[maxi])
    {
        for(auto y:adj[x])
        {
            if(c[y-1] == maxi)
                s.unionByRank(y,x);
        }
    }

//    map<int,VI> m1;
//    int ans=0,length=0;
//    for(int i=1;i<s.parent.size();i++)
//    {
//        m1[s.parent[i]].pb(i);
//        if(length < m1[s.parent[i]].size())
//        {
//            length = m1[s.parent[i]].size();
//            ans = s.parent[i];
//        }
//    }
//    cout<<length<<'\n';
//    for(auto x:m1[ans])
//    {
//        cout<<x<<" ";
//    }
//    cout<<'\n';
    
    map<int,VI> m1;
    int size,ans;
    size=0;
    for(auto x:m[maxi])
    {
        m1[s.find(x)].pb(x);
        if(m1[s.find(x)].size()>size)
        {
            size = m1[s.find(x)].size();
            ans = s.find(x);
        }
    }
    
    cout<<size<<'\n';
    for(auto x:m1[ans])
    {
        cout<<x<<" ";
    }
    cout<<'\n';
}