#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll = long long int;
const ll mod = 1000000007;
const ll M = 1000000000000000000ll;
#define fi first
#define se second
#define pb push_back
#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>
inline ll add(ll a, ll b) {return ((a % mod + b % mod) % mod);}
inline ll sub(ll a, ll b) {return ((a % mod - b % mod + mod) % mod);}
inline ll mult(ll a, ll b) {return (((a % mod) * (b % mod)) % mod);}
inline ll power(ll n, ll x) {ll p = 1; while (x != 0) {if (x % 2 == 0) {n = mult(n, n); x = x / 2;} p = mult(p, n); x--;} return p;}
inline ll recurmult(ll a, ll b) {ll r = 0; while (b) {if (b & 1)r = add(r, a); a = mult(2, a); b >>= 1;} return r % mod;}
int main()
{
ios::sync_with_stdio(0);
cin.tie(0);
#ifndef ONLINE_JUDGE
freopen("input.txt","r",stdin);
freopen("output.txt", "w", stdout);
#endif 
ll n;
cin >> n;
vector<pair<ll, ll>> v;
set<pair<ll, ll>> ss;

for(ll i=0;i<n;i++)
{
    ll x,y;
    cin>>x>>y;
    v.pb({x, y});
    ss.insert({x, y});
}
if (n <= 2)
{
    cout << (4 - n) << "\n";
    return 0;
}
int ans = 0;
for(auto pt1:v)
{
    for(auto pt2:v)
    {
        if(pt1!=pt2)
        {
            pair<ll, ll> x1 = {pt1.first+-1*(pt2.second-pt1.second),pt1.second+1*(pt2.first-pt1.first)};
            pair<ll, ll> x2 = {pt2.first + -1 * (pt2.second - pt1.second), pt2.second + 1 * (pt2.first - pt1.first)};
            pair<ll, ll> y1 = {pt1.first +1 * (pt2.second - pt1.second), pt1.second -1 * (pt2.first - pt1.first)};
            pair<ll, ll> y2 = {pt2.first +1 * (pt2.second - pt1.second), pt2.second -1 * (pt2.first - pt1.first)};
            int k = 0;
            if (ss.find(x1) != ss.end())
            {
                if (ss.find(x2) != ss.end())
                    k = max(k, 2);
                else
                    k = max(k, 1);
        }
        if (ss.find(y1) != ss.end())
        {
            if (ss.find(y2) != ss.end())
                k = max(k,2);
            else
                k = max(k,1);
        }

        ans = max(ans, k);
        }
    }
}
cout << (2 - ans) << "\n";
}