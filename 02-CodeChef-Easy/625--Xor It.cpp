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
   #define countbit(x) __builtin_popcount(x)
 
const ll inf=100000000000000001;
 const ll mod=1000000007  ;
 


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

 
//template end
//mod operations
void sub(ll &a, ll b){
    b%=mod;
    a=(a+mod-b);
    a%=mod;
}
ll lcm(ll a,ll b)
{
    return a*b/__gcd(a,b);
}

//

//seg tree
vll seg;

void build(ll l,ll r,ll i,ll arr[])
{   //cout<<l<<" "<<r<<"\n";
    if(l==r)
    {
        seg[i]=arr[l];
        return;
    }
  
    ll mid=(l+r)/2;
    build(l,mid,2*i+1,arr);
     build(mid+1,r,2*i+2,arr);
     seg[i]=min(seg[2*i+1],seg[2*i+2]);

}
ll query(ll l,ll r,ll tl,ll tr,ll i)
{   
    if(tl>=l&&tr<=r) return seg[i];
    if(tr<l||tl>r) return 1e9+1;


     ll mid=(tl+tr)/2;
ll left=query(l,r,tl,mid,2*i+1);
ll right=query(l,r,mid+1,tr,2*i+2);
return min(left,right);
    
    
}

void update(ll tl,ll tr,ll pos,ll new_val,ll i) {
    if (tl == tr) {
        seg[i] =new_val;
    } else {
        ll mid=(tl + tr) / 2;
        if (pos <= mid)
            update(tl,mid, pos, new_val,2*i+1);
        else
            update(mid+1, tr, pos, new_val,2*i+2);
        seg[i] = min(seg[i*2+1],seg[i*2+2]);
    }
}


//end


vll fact;
void factorial()
{
    fact.resize(2e5+1);
      fact[0] = 1;
    for (int i = 1; i <=2e5; i++)
        fact[i] = (fact[i - 1] * i) % mod;

}
 ll ncrmod( ll n,ll r, ll p)
{   if (n < r)   return 0;
     if (r == 0)  return 1;
 return (fact[n]*invmod(fact[r],p)%p*invmod(fact[n-r],p)%p)%p;
}

///////////////////////////////////////////////////
vll se;

void call()
{  se.resize((ll)1e6+1,1);
    se[1]=0;
    for(ll i=2;i<=1e6;i++)
    {
        if(se[i]==1)
        { //p.pb(i);
          se[i]=i;
            for(ll j=i*i;j<=1e6;j+=i)
             se[j]=i;
        }
    }
    
}
/////////////////////////////////////////////////////
ll gen(ll n)
{   ll tot = n * (n + 1) / 2;
	for (ll b = 1; n; n >>= 1, b <<= 1)
		tot -= (n + 1) / 2 * b, tot --;
	return (tot);
}
void solve()
{    ll l,r;
cin>>l>>r;
cout<<gen(r)-gen(l-1);
}


  
   



 
        
 
     
      
 
 
    
    
 
 
int main()
{

  boost
#ifndef ONLINE_JUDGE 
        freopen("input.txt", "r", stdin); 
        freopen("output.txt", "w", stdout); 
    #endif
//factorial();
   // call();

 ll t=1;
cin>>t;
 

  while (t--)
  {
   
 solve();
 cout<<endl;
}
}