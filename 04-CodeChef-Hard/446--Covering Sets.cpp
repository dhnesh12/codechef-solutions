#include <bits/stdc++.h>
 
using namespace std ;
 
#define i64 int64_t // typecast using i64(x)
#define int int64_t 
#define ld long double
#define f(i,a,b) for(int i=(a); i<(b); ++i)
#define endl '\n'
 
#define PQ priority_queue
#define LB lower_bound  
#define UB upper_bound
#define fr first
#define sc second
 
#define all(a) (a).begin(),(a).end()
#define allr(a) (a).rbegin(),(a).rend()
#define sz(x) ((int)(x).size())
 
//#ifndef ONLINE_JUDGE
template<typename T>
void __p(T a) {
  cout<<a; 
}
template<typename T, typename F>
void __p(pair<T, F> a) {
  cout<<"{";
  __p(a.first);
  cout<<",";
  __p(a.second);
  cout<<"}\n"; 
}
template<typename T>
void __p(std::vector<T> a) {
  cout<<"{";
  for(auto it=a.begin(); it<a.end(); it++)
    __p(*it),cout<<",}\n"[it+1==a.end()]; 
}
template<typename T, typename ...Arg>
void __p(T a1, Arg ...a) {
  __p(a1);
  __p(a...);
}
template<typename Arg1>
void __f(const char *name, Arg1 &&arg1) {
  cout<<name<<" : ";
  __p(arg1);
  cout<<endl;
}
template<typename Arg1, typename ... Args>
void __f(const char *names, Arg1 &&arg1, Args &&... args) {
  int bracket=0,i=0;
  for(;; i++)
    if(names[i]==','&&bracket==0)
      break;
    else if(names[i]=='(')
      bracket++;
    else if(names[i]==')')
      bracket--;
  const char *comma=names+i;
  cout.write(names,comma-names)<<" : ";
  __p(arg1);
  cout<<" | ";
  __f(comma+1,args...);
}
//#endif
 
void setIO(string s = "") {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); 
  cin.exceptions(cin.failbit); 
  if(sz(s)){
    freopen((s+".in").c_str(),"r",stdin);
    freopen((s+".out").c_str(),"w",stdout);
  }
}
/**
 * Description: modular arithmetic operations
 * take care of input/output use .v in that else for any other operation its not required
 * dont use #define int long long when using this
 * when using power typecast the int to mi using mi(x) else you will get wrong answer
 * when (bitshift) type cast to mi to multiply numbers else you will get overflow
 * when using nCr make sure you are passing integer/long long/int64_t(all of them works) type
 * opertion between int and modint can be done
 * be careful when multiplying no modint type into a modint this can give overflow and wrong answer
 * Source: 
  * KACTL, BENQ with own modifications 
  * https://codeforces.com/blog/entry/63903
  * https://codeforces.com/contest/1261/submission/65632855 (tourist)
  * https://codeforces.com/contest/1264/submission/66344993 (ksun)
  * also see https://github.com/ecnerwala/cp-book/blob/master/src/modnum.hpp (ecnerwal)
 * Verification: 
  * https://open.kattis.com/problems/modulararithmetic
        * for nCr need to be done

 */
 
template<int MOD> struct mint {
  static const int mod = MOD ;
  int v; explicit operator int() const { return v; } // explicit -> don't silently convert to int
  mint() { v = 0; }
  mint(long long _v) { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
    if (v < 0) v += MOD; }
  friend bool operator==(const mint& a, const mint& b) { 
    return a.v == b.v; }
  friend bool operator!=(const mint& a, const mint& b) { 
    return !(a == b); }
  friend bool operator<(const mint& a, const mint& b) { 
    return a.v < b.v; }
   
  mint& operator+=(const mint& m) { 
    if ((v += m.v) >= MOD) v -= MOD; 
    return *this; }
  mint& operator-=(const mint& m) { 
    if ((v -= m.v) < 0) v += MOD; 
    return *this; }
  mint& operator*=(const mint& m) { 
    v = int((long long)v*m.v%MOD); return *this; }
  mint& operator/=(const mint& m) { return (*this) *= inv(m); }
  friend mint power(mint a, long long p) {
    mint ans = 1; assert(p >= 0);
    for (; p; p /= 2, a *= a) if (p&1) ans *= a;
    return ans; }
  friend mint inv(const mint& a) { assert(a.v != 0); 
    return power(a,MOD-2); }
    
  mint operator-() const { return mint(-v); }
  mint& operator++() { return *this += 1; }
  mint& operator--() { return *this -= 1; }
  friend mint operator+(mint a, const mint& b) { return a += b; }
  friend mint operator-(mint a, const mint& b) { return a -= b; }
  friend mint operator*(mint a, const mint& b) { return a *= b; }
  friend mint operator/(mint a, const mint& b) { return a /= b; }
};
const int MOD = 1e9 + 7, MAX_N = 3e5 ;
typedef mint<MOD> mi; // 5 is primitive root for both common mods

/*
  Description :- sum over subsets
  source :- https://codeforces.com/contest/449/submission/50928731 
  verification :-
*/
//this is sum over superset
void sos (vector<mi>& dp, int x = 1) { // x = -1 reverses
    int SZ = 31 - __builtin_clz(sz(dp)) ;
    f(i,0,SZ){
      f(j,0,1<<SZ){
        if(j & (1<<i)){
          if (x == 1) dp[j^(1<<i)] += dp[j] ;
          else        dp[j^(1<<i)] -= dp[j] ;
        }
      }
    }   
}
 
vector<mi> andConv(vector<mi> a, vector<mi> b) { // a[i]*b[j] contributes to result[i&j]
    sos(a), sos(b);
    f(i,0,sz(a)) a[i] *= b[i];
    sos(a,-1) ;
    return a ;
}

signed main(){
  setIO() ;
  int N ; cin >> N ;
  auto neg = [&](int x){
    x ^= ((1<<N) - 1) ;
    return x ;
  };
  vector<mi> a[3] ;
  f(i,0,3) a[i].resize(1<<N) ;
  f(i,0,3){
    f(j,0,1<<N){
      cin >> a[i][neg(j)].v ;
    }
  }
  auto c = andConv(a[1],a[2]) ;
  c = andConv(c,a[0]) ;
  mi ans = 0 ;
  f(i,0,1<<N){
    int res = N - __builtin_popcount(i) ;
    ans += power(mi(2),res) * c[i] ;
  }
  cout << ans.v ;
}