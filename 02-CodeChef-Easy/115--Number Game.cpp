#include<bits/stdc++.h>
// #pragma optimize("-O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,avx,mmx,tune=native")
using namespace std;
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define INF 1e9
//#define BIG_INF 1e18
#define vi vector<ll>
#define sz(a) ll((a).size())
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1)
// #include <ext/pb_ds/assoc_container.hpp> // Common file
// #include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
// typedef tree<
// ll,
// null_type,
// less<ll>,
// rb_tree_tag,
// tree_order_statistics_node_update>
// ordered_set;
typedef long long ll;
 const ll BIG_INF = 9e18;
ll mod = 998244353;
 ll fast_exp(ll a, ll b)
{
    if(b <= 0)
       return 1;
    else
    {
       ll res = 1;
       res = fast_exp(a,b/2);
       res = (res*res)%mod;
       if(b%2 == 1)
          res = (res*a)%mod;
       return res;
 
    }
}

typedef long double ld;
const long long N = 1e6+1000;
const long double pi = acos(-1.0);
using cd = complex<double>;
const double PI = acos(-1);
vector <int> edge[1005];
bool vis[1005] = {};

int pref[N] = {};
int p10[N] = {};
int can_do[1000] = {};
int rt[N] = {};
int counter = 0;
int chk = 0;
void dfs(int v)
{
    vis[v] = true;
    counter += can_do[v];
    
    for(auto e: edge[v])
    {
        if(vis[e] == false)
            dfs(e);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    //freopen("c.txt","r",stdin);
    int t;
    cin >> t;
    while(t--)
    {
        string a;
        cin >> a;
        int m;
        cin >> m;
        vector <int> d;
        int n = a.size();
        pref[0] = ((int)a[0] - (int)'0');
        for(int i = 1; i<n; i++)
            pref[i] = (((int)a[i] - (int)'0') + 10 * pref[i-1]) % m;
        int p10[n] = {};
        p10[n-1] = 1;
        rt[n-1] = (int)a[n-1] - (int)'0';
        int val; 
        for(int i = n-2; i>=0 ; i--)
        {
            p10[i] = (10 * p10[i+1]) % m;
            val = (p10[i] * ((int)a[i] - (int)'0')) % m ;
            rt[i] = (rt[i+1] + val) % m;
        }
        for(int i = 0; i<1000; i++)
            can_do[i] = 0;
        for(int i = 0; i<= m; i++)
        {    
            edge[i].clear();
            vis[i] = 0;
        }
        for(int i = 0; i<n; i++)
        {
            val = 0;
            if(i > 0)
                val = pref[i-1];
            val = (val * p10[i]) % m;
            if(i+1 < n)
                val = (val + rt[i+1]) % m;
            can_do[val]++;

        }
        for(int i = 0; i<m; i++)
            if(can_do[i] > 0)
                d.pb(i);


        for(int i = 0; i<m; i++)
        {
            for(auto e: d)
            {
                int other = (p10[0] * i + e) % m;
                edge[other].pb(i);
            }
        }
        counter = 0;
        dfs(0);
        

        cout << counter << '\n';

    }
    
     
    
    // cerr<< '\n' << "Time elapsed :" << clock() * 1000.0 / CLOCKS_PER_SEC << " ms\n" ;
    return 0;
    
    
}










 