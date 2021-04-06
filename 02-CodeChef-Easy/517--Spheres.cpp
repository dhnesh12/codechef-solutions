#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
#define endl '\n'
#define ff first
#define ss second
#define ll  long long int
#define vl vector<ll>
#define pll pair<ll,ll>  
#define vll vector<pair<ll,ll>>  
#define all(a) a.begin(), a.end()
#define fastio  ios_base::sync_with_stdio(false);cin.tie(NULL);
ll max(ll a, ll b) { return a >= b ? a : b; }
ll min(ll a, ll b) { return a >= b ? b : a; } 
ll onBits(ll n){return __builtin_popcount(n);} 
ll __lcm(ll a,ll b){return a*b/(__gcd(a,b));}
ll power(ll base, ll exponent,ll modulus){  ll result = 1;  while (exponent > 0){if (exponent % 2 == 1)result = (result * base) % modulus;exponent = exponent >> 1;base = (base * base) % modulus;} return result; }
ll fact[100100];  void factorial(ll mod){ fact[0]=1;  for(ll i=1;i<=100010;i++){ fact[i] = (fact[i-1]*i)%mod;  }}
ll nCr(ll n,ll r ){   if(n<r){  return 0;  }  return fact[n]/(fact[n-r]*fact[r]);  }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &v);
template <typename T> ostream &operator<<(ostream &os, const set<T> &v);
template <typename T> ostream &operator<<(ostream &os, const multiset<T> &v);
template <typename T, typename S> ostream &operator<<(ostream &os, const map<T, S> &v);
template <typename T, typename S> ostream &operator<<(ostream &os, const pair<T, S> &v);
template <typename T> inline istream &operator>>(istream &in, vector<T> &a); 
template <typename T> inline istream &operator>>(istream &in, pair<T,T> &a); 
 
ll dxy4[2][4]={{0,1,0,-1} , {-1,0,1,0}};
ll dxy8[2][8]={{0,1,1,1,0,-1,-1,-1} ,{-1,-1,0,1,1,1,0,-1}};
ll test_case;
ll testArray[10] = {5,2,3,1,8,4,9,7,6,0}; 
struct P{ll x,y;bool operator<(const P& t) const{ return (this->x < t.x);}}; 
const double PI = 22.0/7.0;
const long long int INF = INT_MAX;   
const long long int MOD = 1e9 + 7;   
const ll mxn = 2e5+100; 
ll i,j,k,n,m,x,y; 
vl e[mxn]; 
map<ll,ll> vis;
// ll a[mxn];  
ll c;
vl a, b;
ll dp[1010][1010]={0};
void solve(){  
    cin>>n>>m>>c;
    for(ll i=1;i<=n;i++){
        cin>>x;
        a.push_back(x);
    }
      for(ll i=1;i<=m;i++){
        cin>>x;
        b.push_back(x);
    }
    map<ll,ll> mp1,mp2 ,cnt;
    for(ll i=0;i<n;i++){
        mp1[a[i]]++;
    }
    for(ll i=0;i<m;i++){
        mp2[b[i]]++;
    }
    vl s;
    for(auto  x:mp1){
        for(ll i=0;i<min(mp1[x.first] , mp2[x.first]);i++){
            s.push_back(x.first);
        } 
        cnt[x.first] = mp1[x.first]*mp2[x.first];
    }
    sort(all(s));
    vl v;
    v.push_back(s[0]);
    for(ll i=1;i<s.size();i++){
        if(s[i]!=v.back()){
            v.push_back(s[i]);
        }
    }
    s =v;
    

    dp[0][0] =cnt[s[0]];
    n =s.size();
    for(ll i=1;i<n;i++){
        dp[i][0] =cnt[s[i]]+dp[i-1][0];
    } 

    for(ll i=1;i<n;i++){
        for(ll j=1;j<=n;j++){ 
            dp[i][j] = dp[i-1][j-1]*cnt[s[i]]+dp[i-1][j]; 
             
        }
    }

    for(ll i=1;i<=c;i++){
        cout<<dp[n-1][i]<< " ";
    }cout<<endl;

  


} 
//================================================================================================== 
signed main(){
     auto start_time = high_resolution_clock::now(); 

       fastio;   
       test_case=1;
       //cin>>test_case; 
       for(ll test=1;test<=test_case;test++){
         solve();
        }

    auto stop_time = high_resolution_clock::now();  
    auto duration = duration_cast<microseconds>(stop_time - start_time); 
     //cout <<endl<< "time : " << duration.count() << " ms" << endl;  
 }
//==================================================================================================


// Functions 
template <typename T> ostream &operator<<(ostream &os, const vector<T> &v)
{
    os << "[";
    for (int i = 0; i < (int)v.size(); ++i)
    {
        if (i)
            os << ", ";
        os << v[i];
    }
    os << "]\n";
    return os;
}
template <typename T> ostream &operator<<(ostream &os, const set<T> &v)
{
    
     os << "{";
    for (auto it : v)
    {
        os << it;
        if (it != *v.rbegin())
            os << ", ";
    }
    os << "}\n";
    return os;
}
template <typename T> ostream &operator<<(ostream &os, const multiset<T> &v)
{
    if((int)v.size()==0){
        os << "{}";
        return os;
    }
    os << "{";
    auto  last = v.end();
    last--;
    for (auto it = v.begin() ; it != v.end() ; it++)
    {
        os << *it;
        if (it != last)
            os << ", ";
    }
    os << "}\n";
    return os;
} 
template <typename T, typename S> ostream &operator<<(ostream &os, const map<T, S> &v)
{
    os << "{";
    for (auto it : v)
    {
        os << "(" << it.first << " : " << it.second << ")";
        if (it != *v.rbegin())
            os << ", ";
    }
    os << "}\n";
    return os;
}
template <typename T, typename S> ostream &operator<<(ostream &os, const pair<T, S> &v)
{
    os << "( ";
    os << v.first << " , " << v.second << " )";
    return os;
}
template <typename T> inline istream &operator>>(istream &in, vector<T> &a)
{
    for (auto &x : a)
        in >> x;
    return in;
}
template <typename T> inline istream &operator>>(istream &in, pair<T,T> &a)
{
    in >> a.first >> a.second ;
    return in;
}