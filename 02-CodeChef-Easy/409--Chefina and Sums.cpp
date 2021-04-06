#include <bits/stdc++.h>
#include <math.h>
    using namespace std; 
 
    #define ll long long 
    #define ld long double
    #define pb push_back
    #define boost ios_base::sync_with_stdio(false),cin.tie(NULL);
    #define fi0n for(ll i=0;i<n;i++)
    #define fin0 for(ll i=n-1;i>-1;i--)
    #define all(v) v.begin(),v.end()
    #define set(arr,x) memset(arr,x,sizeof(arr));
    #define pb push_back
     #define eb emplace_back
    #define max3(a,b,c) max(max((a),(b)),(c))
    #define max4(a,b,c,d) max(max((a),(b)),max((c),(d)))
    #define min3(a,b,c) min(min((a),(b)),(c))
    #define min4(a,b,c,d) min(min((a),(b)),min((c),(d)))
    
    #define pll pair<ll,ll>
    #define mp make_pair
    #define ft first
    #define sd second
    
    #define vll vector<ll>
    #define prec(x) cout << fixed << setprecision(10) << x
 
 
const ll inf=100000000000000001;
 const ll mod=1000000007;
 


//power under mod
ll pow(ll x, unsigned ll y, ll p){
    ll res=1;
    x=x%p;
    if (x==0) return 0;
    while (y > 0)
    {
        if (y & 1)
            res = (res*x) % p;
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}
ll _pow(ll a, ll b){
    if(!b)
        return 1;
    ll temp = _pow(a, b / 2);
    temp = (temp * temp);
    if(b % 2)
        return (a * temp);
    return temp;
}
// inverse under mod
ll invmod(ll a,ll m){
	return pow(a,m-2,m);
}
 
 ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b); 
     
}
 bool isprime(ll n) 
{   if (n<=1)  return false; 
    if (n<=3)  return true; 
    if (n%2==0||n%3==0) return false; 
   for (ll i=5;i*i<=n; i=i+6) 
        if (n%i==0||n%(i+2)==0) 
           return false; 
  
    return true; 
} 
 
      bool coprime(ll a, ll b) { 
      
    if ( __gcd(a,b)==1) 
       return true;  
    else return false;
                 
}
 ll cl(ll x,ll y)
 {
     return (x+y-1)/y;
 }
 
//template end
//mod operations
void ad(ll &a, ll b){
    a+=b;
    a%=mod;
}
void sub(ll &a, ll b){
    b%=mod;
    a=(a+mod-b);
    a%=mod;
}
ll mu(ll a, ll b){
    return (a*b)%mod;
}
//
//1 based FT, 0 based g(i)=i&i+1
ll fen[(ll)1e5];
void ufen(ll i,ll val)
{ i++;
 for(;i<=1e5;i+=i&-i)
      fen[i]+=val;  
}
ll psfen(ll i)
{  ll ans=0;
     for(;i>0;i-=i&-i)
      ans+=fen[i];
     return ans;
}
//fenwick end

    void solve()
{ll n;
cin>>n;
vll arr(n);

ll sum=0;
fi0n {cin>>arr[i];
sum+=arr[i];
}
ll p[n];


unordered_map<ll,ll> m;
ll ct=0;
ll ts=0;
fi0n{
  
  if((sum-arr[i])%2==0)
  { 
    ct+=m[(sum-arr[i])/2];
  }
  
ts+=arr[i];
 m[ts]++;

}
m.clear();
ts=0;
for(ll i=n-1;i>-1;i--)
{  if((sum-arr[i])%2==0)
    { ct+=m[(sum-arr[i])/2];
       
    }
    
ts+=arr[i];
m[ts]++;
}

 cout<<ct;
  } 


  
 
 
        
 
     
      
 
 
    
    
 
 
int main()
{ 
  boost
#ifndef ONLINE_JUDGE 
        freopen("input1.txt", "r", stdin); 
        freopen("output1.txt", "w", stdout); 
    #endif
 ll t=1;
cin>>t;

  while (t--)
  {
    
 
 solve();
cout<<endl;
}
}