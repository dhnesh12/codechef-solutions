#include <bits/stdc++.h>
using namespace std;
// #define mod 1000000007
#define pb push_back
#define mp make_pair
#define fi first
#define sec second
typedef long long int  ll;
typedef long double  ld;
#define pii pair<ll,ll> 
#define pic pair<ll,char>
#define vi vector< ll > 
#define vvi vector< vi > 
#define vpi vector< pii > 
#define vvpi vector< vpi > 
#define st  set <ll, greater <ll> >
#define mst  multiset <ll, greater <ll> >
#define fast ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define mapp  unordered_map <ll, ll>
#define ppii pair< pii, pii > 
#define test(t) ll t;cin>>t;while(t--)
#define inarr(n) ll arr[n];for(ll i=0;i<n;i++)cin>>arr[i];
#define ingra(m) vvi arr(100005);for(ll i=0;i<m;i++){ll u,v;cin>>u>>v;arr[u].pb(v);arr[v].pb(u);}
#define mem(a,b) memset(a,b,sizeof(a))
#define inn freopen("input.txt", "r", stdin)
#define outt freopen("output.txt", "w", stdout)
#define all(arr) arr.begin(),arr.end()
ll n,m,k,mod;
ll power(ll x,ll y){ll res = 1;while(y){if(y&1) res = (res*x)%mod;y=y/2,x=(x*x)%mod;}return res%mod;}
ll dp[56][56][56][56];
ll fact[201];
ll inv[201];
void factorial()
{
  ll i;
  fact[0] = 1;
  inv[0] = power(fact[0],mod-2);
  for(i=1;i<=200;i++)
  {
    fact[i] = (i*fact[i-1])%mod;
    inv[i] = power(fact[i],mod-2);
  }
}
ll ncr(ll x,ll y)
{
  if(x<y)
    return 0;
  ll temp = fact[x];
  temp = (temp*inv[y])%mod;
  temp = (temp*inv[x-y])%mod;
  return temp;
}
ll func(ll pos,ll done,ll activity,ll last)
{
    if(done<0 or activity<0 or activity>done)
        return 0;
    if(pos==n+1)
    {
        if(done==0 and activity==0)
            return 1;
        return 0;
    }
    ll &ret = dp[pos][done][activity][last];
    if(ret!=-1)
        return ret;
    ret = func(pos+1,done,activity,last);
    for(ll i=1;i<=done;i++)
    {
        
        ret = ret + ncr(last,i)*func(pos+1,done-i,activity,last)%mod+(ncr(pos,i)-ncr(last,i)+mod)%mod*func(pos+1,done-i,activity-1,pos)%mod;
        ret%=mod;
    }  
    return ret;
}
signed main()
{
    fast;
    mem(dp,-1);
    cin>>n>>m>>k>>mod;
    factorial();
    cout<<func(1,m,k,0);
}