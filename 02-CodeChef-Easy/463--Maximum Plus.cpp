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
ll t;
cin >>t;
while(t--)
{
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> v(n, vector<ll>(m, 0)),sm(n,vector<ll>(m,0));
    for (ll i = 0; i < n;i++)
    {
        ll s = 0;
        for (ll j = 0; j < m;j++)
        {
            cin >> v[i][j];
            sm[i][j] = v[i][j];
        }
    }
    for (ll i = 1; i < n;i++)
    {
        ll prev=v[i][0];
        for (ll j = 1;j<m;j++)
        {
            sm[i][j]+= prev;
            if(prev<0)
                prev = 0;
            prev += v[i][j];
        }
        prev = v[i][m - 1];
        for (ll j = m - 2; j >= 0;j--)
        {
            sm[i][j] += prev;
            if(prev<0)
                prev = 0;
            prev += v[i][j];
        }
    }
    for (ll j = 1; j < m; j++)
    {
        ll prev = v[0][j];
        for (ll i = 1; i < n; i++)
        {
            sm[i][j] += prev;
            if (prev < 0)
                prev = 0;
            prev += v[i][j];
        }
        prev = v[n-1][j];
        for (ll i = n - 2; i >= 0; i--)
        {
            sm[i][j] += prev;
            if (prev < 0)
                prev = 0;
            prev += v[i][j];
        }
    }
    ll ans = -1*M;
    for (ll i = 1; i < n-1;i++)
    {
        for (ll j = 1; j < m - 1;j++)
            ans = max(ans,sm[i][j]);
    }
    cout << ans << "\n";
}
}