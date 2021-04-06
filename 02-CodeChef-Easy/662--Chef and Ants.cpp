//Yash Patel
//SEAS,AU 
//DSA 


#include<bits/stdc++.h>
using namespace std;
#define fin  cin.ignore(numeric_limits<streamsize>::max(),'\n')
#define fout cout.flush()
#define fill(w,t) memset(w,t,sizeof(w))
#define google cout<<"Case #"<<countu<<": "
#define S(t) (ll)t.size()
#define bl '\n'
#define nl cout<<bl
#define cout1(a) cout<<a<<bl
#define cout2(a,b) cout<<a<<" "<<b<<bl
#define cout3(a,b,c) cout<<a<<" "<<b<<" "<<c<<bl
#define cout4(a,b,c,d) cout<<a<<" "<<b<<" "<<c<<" "<<d<<bl
#define print(azz,szz,ezz) for(ll i=szz;i<=ezz;i++){ cout<<azz[i]<<" "; }
#define rprint(azz,szz,ezz) for(ll i=szz;i>=ezz;i--){ cout<<azz[i]<<" "; }
#define input(azz,szz,ezz) sfor(pzz,szz,ezz) cin>>azz[pzz]
#define all(v) v.begin(),v.end()
#define ll long long
#define ldb long double
#define db double
#define ull unsigned long long
#define lb lower_bound
#define ub upper_bound
#define pb push_back
#define mk make_pair
#define pll pair<ll,ll>
#define pldb pair<ldb,ldb>
#define fi first
#define se second
#define vull vector<ull>
#define vll vector<ll>
#define vb vector<bool>
#define vldb vector<ldb>
#define vpll vector< pll >
#define vpldb vector< pldb >
#define pqmin priority_queue<ll,vector<ll>,greater<ll> >     //minheap
#define pq priority_queue<ll>                                //maxheap ll
#define pqpll priority_queue<pll>                            //maxheap pll
#define pqpllmin priority_queue<pll, vector<pll>, greater<pll> >   //minheap pll
#define mll map<ll,ll>
#define mldb map<ldb,ldb>
#define umll unordered_map<ll,ll>
#define sll set<ll>
#define usll unordered_set<ll>
#define sfor(i,azz,bzz) for (ll i = (azz); i <= (bzz); ++i)
#define rfor(i,bzz,azz) for (ll i = (bzz); i >= (azz); --i)
const ll mod = 1e9+7;
// const ll mod=998244353 ;
const ll maxn = 1e6+1;
const ll llmax = (1ll<<60);
const int intmax = (1<<30);
const ldb PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899863;
vll fact , ifact;
vll primes;
vll spf;
void sieve()
{
    spf.resize(maxn+1,0);
  spf[0]=0; spf[1]=1;
    for(ll i =2; i<=maxn; i++)
    {
        if(spf[i])
         continue;
        spf[i]=i;
        for(ll j = i*i; j<=maxn; j+=i)
        {
          if(spf[j]==0)
               spf[j]=i;
      }
    }
    for (ll p=2; p<=maxn; p++)
      if (spf[p]==p)
          primes.pb(p);
}
vll primes1;
void sieve2(ll l,ll r)
{
  vb isprime(r-l+1,1);

  if(l==1)
      isprime[0]=false;
  ll base;
  for(ll i=0;primes[i]*primes[i]<=r;i++)
  {
    base = (l/primes[i])*primes[i];
    if(base<l)
    {
      base += primes[i];
    }
    for(long long j=base;j<=r;j+=primes[i])
    {
      isprime[j-l]=false;
    }
    if(base==primes[i]){
      isprime[base-l]=true;
    }
  }
  for(int i=0;i<r-l+1;i++)
  {
    if(isprime[i])
        primes1.pb(i+l);
  }
}
void primefactorll(ll x,mll &mp)
{
     for(ll i=0;primes[i]*primes[i]<=x;i++)
    {
        while(x%primes[i]==0)
        {
            mp[primes[i]]++;
            x/=primes[i];
        }
    }
    if(x!=1)
    {
        mp[x]++;
    }
}
void primefactor(ll n,mll &mp)
{
    while(n!=1)
    {
        mp[spf[n]]++;
        n/=spf[n];
    }
}

bool primeornot(ll n)
{
    for(ll i=0;primes[i]*primes[i]<=n;i++)
    {
        if(n%primes[i]==0)
        {
            return false;
        }
    }
    return true;
}

// #include<bits/stdc++.h>
// #include<iostream>
// #include<string.h>
// #include<math.h>

// #define ll long long int 
#define vec vector<int>
#define all(v) v.begin(),v.end()

// using namespace std;
void solve(){
   ll n;
   cin >> n;
   
   vector<ll>chef[n];
   unordered_map<ll,ll> mapp;
   
//   int answer=0;
//       int foo=1;
//       for(int j=0; j<a; j++){
//         final1 = final1 - m[j]+n[b-j-1]
   for(ll i=0; i<n; i++){
    
    ll m;
    cin >> m;
    //
    for(ll j=0; j<m; j++){
       //
       ll a;
       cin >> a;
    //   int ans = 0;
    //         for(int j = 0; j < no; j++){
    //             arr[j] = sc.nextInt();
    //         }
       mapp[abs(a)]++;
       
       chef[i].push_back(a);
    }
    //
    sort(all(chef[i]));
  }
  //
  ll temp = 0;
  ll answer = 0;
  //
  for (auto &a: mapp){
    if (a.second > 1) answer++;
  }
  for(ll i=0; i<n; i++){
      //
    for(ll j=0;j<(ll)chef[i].size();j++){
      ll var = 0;
    //   answer++;
    //     if(final1 > final2){
    //       cout << answer << endl;
    //       foo=0;
      if (mapp[abs(chef[i][j])] > 1){
          //
        if (chef[i][j]>0) var = (chef[i].size())-(j + 1);
        else var = j;
      }
      //
      else{
        if (chef[i][j] > 0) var = lower_bound(all(chef[i]), -1 * chef[i][j]) - chef[i].begin();
    //     sort(m,m+a); 
    //   sort(n,n+b);
    //   if(temp1 > temp2){
    //     cout << "0" << endl;
        else var = (chef[i].size()) - (upper_bound(all(chef[i]), -1 * chef[i][j]) - chef[i].begin());
        }
        temp+=var;
      }
      //
     }
    cout << temp + answer << endl;
}
   int main(){
       
    //   ans=arr[no - 1];
    //         int flagoff = -1;
       ios_base::sync_with_stdio(false);cin.tie(NULL);

       ll testcase=1;
       cin >> testcase; 
       while(testcase--) { 
           solve();
       } 
   return 0;
}