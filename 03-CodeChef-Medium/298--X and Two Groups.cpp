//#include <ext/pb_ds/assoc_container.hpp> 
 //#include <ext/pb_ds/tree_policy.hpp>
 //#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <valarray>
#include <iterator>
#include <functional>
#include <limits>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <stack>
using namespace std;
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define trace(x) cerr << #x << ": " << x << " " << endl;
 
typedef int64_t ll;
 
#define endl '\n'
#define int ll
ll mod=1e9+7;
ll mod1=998244353;
ll power(ll a,ll b)
{
    if(b==0) return 1;
    else if(b%2==0)
        return power(((((a)%mod)*((a)%mod))%mod),b/2)%mod;
    else return (((a)%mod)*(power(((((a)%mod)*((a)%mod))%mod),b/2)%mod))%mod;
}
inline ll inverse(ll a,ll md) {
  a %= md;
  if (a < 0) a += md;
  ll b = md, u = 0, v = 1;
  while (a) {
    ll t = b / a;
    b -= t * a; swap(a, b);
    u -= t * v; swap(u, v);
  }
  assert(b == 1);
  if (u < 0) u += md;
  return u;
}
  
  
 //using namespace __gnu_pbds;
 //#define ordered_set tree<pair<int,int>, null_type,less<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update>
//find_by_order(k)  returns iterator to kth element starting from 0;
//order_of_key(k) returns count of elements strictly smaller than k;
//erase,insert same as normal set
 //mt19937 mrand(chrono::high_resolution_clock::now().time_since_epoch().count()); //for randomized solution
const int ce=998244353;
ll fast_mod(ll input)
{
    return input < ce ? input : input%ce;
}
int32_t main()
{
    IOS
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif 
    
    int n,m,x;
    cin>>n>>m>>x;
    int a[n+1];
    for(int i=1;i<=n;i++)
        cin>>a[i];
    int b[m+1];
    for(int i=1;i<=m;i++)
        cin>>b[i];
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    int c=0,c1=0;
    for(int i=1;i<=n;i++)
    {
        c+=(a[i]-a[1])/x;
    }
    for(int i=1;i<=m;i++)
    {
        c1+=(b[i]-b[1])/x;
    }
    if(c>=c1)
    {
        for(int i=1;i<=n;i++)
        {
            int sub=((a[i]-a[1])/x)*x;
            a[i]-=sub;
        }
        sort(a+1,a+n+1);
        for(int j=1;j<=m;j++)
        {
            int sub=((b[j]-b[1])/x)*x;
            b[j]-=sub;
        }
        sort(b+1,b+m+1);
        int k=(c-c1)%m;
        int it=0;
        for(int i=m;i>=1;--i)
        {
            if(it==k)
                break;
            b[i]-=x;
            it++;
        }
        sort(b+1,b+m+1);
    }
    else
    {
        for(int i=1;i<=n;i++)
        {
            int sub=((a[i]-a[1])/x)*x;
            a[i]-=sub;
        }
        sort(a+1,a+n+1);
        for(int j=1;j<=m;j++)
        {
            int sub=((b[j]-b[1])/x)*x;
            b[j]-=sub;
        }
        sort(b+1,b+m+1);
        int k=(c1-c)%n;
        int it=0;
        for(int i=n;i>=1;--i)
        {
            if(it==k)
                break;
            a[i]-=x;
            it++;
        }
        sort(a+1,a+n+1);
    }
    int ans=a[n]-a[1]+b[m]-b[1];
    deque<int> m2,m3;
    for(int i=1;i<=n;i++)
        m2.push_back(a[i]);
    for(int i=1;i<=m;i++)
        m3.push_back(b[i]);
    vector<int> v,v1;
    int d=n;
    while(d--)
    {
        int t=m2.back();
        int t3=m2.front();
        v.push_back(abs(t-t3));
        m2.pop_back();
        t-=x;
        m2.push_front(t);
    }
    d=m;
    while(d--)
    {
        int t=m3.back();
        int t3=m3.front();
        v1.push_back(abs(t-t3));
        m3.pop_back();
        t-=x;
        m3.push_front(t);
    }
    int k=__gcd(n,m);
    for(int i=1;i<=k;i++)
    {
        int mini=1e15,mini1=1e15;
        for(int j=i-1;j<n;j+=k)
            mini=min(mini,v[j]);
        for(int j=i-1;j<m;j+=k)
            mini1=min(mini1,v1[j]);
        ans=min(ans,mini1+mini);
    }

    cout<<ans<<endl;
}       
