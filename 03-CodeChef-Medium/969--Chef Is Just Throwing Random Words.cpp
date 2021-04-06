#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define S second
#define F first
#define FAST ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define vll vector<long long int>
#define vld vector<long double>
#define pll pair<long long int,long long int>
/* unordered_map<int,int>mp; mp.reserve(1024); mp.max_load_factor(0.25); */
#define mod 1000000007
#define mod2 998244353
#define ll long long int
#define ld long double
#define pi 3.141592653589793238
#define Endl endl
#define endl "\n"
const int N = 1e5 + 5;
const ll inf = 1e9;

void solve()
{   
        ll n;
        cin >> n;
        vll a(n);
        for(auto &x:a)
                cin >> x;
        vll dp(64);
        for(auto x:a)
        {
                for(ll j=0;j<64;j++)
                {
                        dp[j] += x%2;
                        x/=2;
                }
        }
        ll ans = 0;
        ll p = 1;
        for(ll i=0;i<60;i++)
        {
                if(i)
                        dp[i] += dp[i-1]/2;
                if(dp[i])
                        ans += p;
                p *= 2;
        }
        cout << ans << endl;
}

void debug(ll tt) {}
 
signed main()
{
        FAST;
        int t = 1;
        cin >> t;
        while(t--)
        {
                solve();
        }
}
