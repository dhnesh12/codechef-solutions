#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;
#define P 1000000007
#define rep(i,n) for(i=0;i<n;++i)
#define re(i,a,n) for(i=a;i<=n;++i)
#define repr(i,a,n) for(i=a;i>=n;--i)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ub(v,val) upper_bound(v.begin(),v.end(),val)
#define np(str) next_permutation(str.begin(),str.end())
#define lb(v,val) lower_bound(v.begin(),v.end(),val)
#define sortv(vec) sort(vec.begin(),vec.end())
#define rev(p) reverse(p.begin(),p.end());
#define mset(a,val) memset(a,val,sizeof(a));
#define at(s,pos) *(s.find_by_order(pos))
#define set_ind(s,val) s.order_of_key(val)
#define PI 3.14159265
/*#include <ext/pb_ds/assoc_container.hpp> // Common file  
#include <ext/pb_ds/tree_policy.hpp>  
#include <functional> // for less  
#include <iostream>  
// Important header files   
using namespace __gnu_pbds;  
using namespace std;  
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;*/

ll binpow(ll x, ll y, ll p)
{
    ll res = 1;
    x = x % p;
   while (y > 0)
    {
        if (y & 1)
            res = (res*x) % p;
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}
ll modInverse(ll n, ll p)
{
    return binpow(n, p-2, p);
}
 
const ll INF = 1000000000000;


vector<ll> pr;

/*int calc_hash(string const& s) {
    ll n = s.size();

    const int p = 31;
    const int m = 1e9 + 9;
    vector<long long> p_pow(n);
    p_pow[0] = 1;
    for (int i = 1; i < n; i++)
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(n + 1, 0);
    for (int i = 0; i < n; i++)
        h[i+1] = (h[i] + (s[i] - 'a' + 1) * p_pow[i]) % m;

    int cnt = 0;
    for (int l = 1; l <= n; l++) {
        set<long long> hs;
        for (int i = 0; i <= n - l; i++) {
            long long cur_h = (h[i + l] + m - h[i]) % m;
            cur_h = (cur_h * p_pow[n-i-1]) % m;
            hs.insert(cur_h);
        }
        cnt += hs.size();
    }
    return cnt;
}*/

/*const ll MAXN=1e5+1;
ll spf[MAXN];
void sieve() 
{ 
    spf[1] = 1; 
    ll i,j;
    for (i=2; i<MAXN; i++) 
          spf[i] = i; 
  
    for (i=4; i<MAXN; i+=2) 
        spf[i] = 2; 
  
    for (i=3; i*i<MAXN; i++) 
    { 
        
        if (spf[i] == i) 
        { 
            
            for (j=i*i; j<MAXN; j+=i) 
  
                if (spf[j]==j) 
                    spf[j] = i; 
        } 
    } 
    for(i=2;i<MAXN;++i) if(spf[i]==i) pr.pb(i);
 } */

/*void SieveOfEratosthenes(int n)
{
    
    bool prime[n + 1];
    memset(prime, true, sizeof(prime));
 
    for (int p = 2; p * p <= n; p++)
    {
        
        if (prime[p] == true) 
        {
           
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
 
    
    for (int p = 2; p <= n; p++)
        if (prime[p])
            pr.pb(p);
}*/

 



ll can[101][5051];

string find(ll n,ll k)
{
  if(k==0&&n==0) return "" ;
  string s;
  ll x=can[n][k];
  string s1=find(n-x,k-(x*(x+1))/2);
  s='('+s1+')';
  ll i;
  rep(i,x-1) s+="()";
  return s;
}


int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   ll t,n,m,k,i,j,x,l,r,h,f,a,b,e,c,y;
   ll t1,t2,t3,ans,temp ;
   cin >> t;
   can[0][0]=1;
   for(i=0;i<=100;++i)
   {
    for(j=i;j<=(i*(i+1))/2;++j)
    {
        //if(i==j) {can[i][j]=i;continue;}
        for(k=1;k<=i;++k)
        {
          if(j<(k*(k+1))/2) continue ;
          if(can[i-k][j-(k*(k+1))/2])
          {
            can[i][j]=k;
            break;
          }
        }
    }
   }


   while(t--)
   {
      cin >> n >> k ;
      x=n/2;
      y=(x*(x+1))/2;
      if(n%2||k<x||k>y) cout << "impossible"<< endl ;
      else
      {
         n/=2;
         if(can[n][k])
         cout << find(n,k)<< endl;
          else cout << "impossible" << endl;
      }


      
   }
    
  return 0;
        
}