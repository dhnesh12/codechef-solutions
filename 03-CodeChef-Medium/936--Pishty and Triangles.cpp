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
const ll mxn = 1e5+100; 
ll i,j,k,n,m,x,y; 
vl e[mxn]; 
map<ll,ll> vis;
ll a[mxn] ;
map<ll,ll> isLeaf;
multiset<ll> st[mxn];
multiset<ll> merger(multiset<ll>a, multiset<ll> b, ll limit){
    multiset<ll> ans;
    for(auto  x:a){
        ans.insert(x);
    }
    for(auto x:b){
        ans.insert(x);
    }
    while(ans.size()>limit){
        ans.erase(ans.begin());
    }
    a.clear();
    b.clear();
    return ans;
}


void upd(ll node, ll l , ll r , ll index , ll val){
    if(l>index||r<index){return;}
    if(index==l && r==l){
        st[node].clear(); 
        st[node].insert(val);
        return;
    }
    ll m = (r-l)/2+l;
    upd(2*node,  l,m,index ,val);    
    upd(2*node+1,  m+1,r,index ,val);
    st[node]  = merger(st[2*node] , st[2*node+1] , min(50,r-l+1));
  
}

multiset<ll> query(ll node , ll l ,ll r ,ll ql,ll qr ){
    if(l>qr||r<ql){
        multiset<ll> ans;
        return ans;
    }
    if(l>=ql && r<=qr){
        return st[node];
    }
    ll m = (r-l)/2+l;
    return merger(query(2*node,l,m,ql,qr) ,query(2*node+1,m+1,r,ql,qr) ,min(50,r-l+1) );
 
}

ll maxFinder(vl v){
    ll n = v.size();
    ll ans =-1;
    for(ll i=n-3;i>=0;i--){
        if(v[i]+v[i+1]>v[i+2]){
            return v[i]+v[i+1]+v[i+2];
        }
    }
    return 0;
}

  
 void solve(){  
     ll q;
    cin>>n>>q;
     for(ll i=1;i<=n;i++){
        cin>>a[i];
    }
    
    for(ll i=1;i<=n;i++){
        upd(1,1,n,i, a[i]);
    }
 
while(q--){
    ll r;
    cin>>r>>x>>y;
    if(r==1){
        upd(1,1,n,x,y);
    }else{
        multiset<ll> mm = query(1,1,n,x,y);
        vl v(all(mm));
        cout<<maxFinder(v)<<"\n";
     }
}
 
    

     


    
    
    

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