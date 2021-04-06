#include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define mp(a,b) make_pair(a,b)
#define ms(v,x) memset(v,x,sizeof(v))
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define Unique(v) sort(all(v));v.erase(unique(all(v)),v.end());
#define sz(v) ((int)v.size())
#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; g(...) 0
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
    if (e & 1) ans = ans * b % m;
  return ans;
}

struct SuffixArray {
  vi sa, lcp;
  SuffixArray(string& s, int lim=256) { // or basic_string<int>
    int n = sz(s) + 1, k = 0, a, b;
    vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
    sa = lcp = y, iota(all(sa), 0);
    for (int j = 0, p = 0; p < n; j = max(1ll, j * 2), lim = p) {
      p = j, iota(all(y), n - j);
      rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
      fill(all(ws), 0);
      rep(i,0,n) ws[x[i]]++;
      rep(i,1,lim) ws[i] += ws[i - 1];
      for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[sa[0]] = 0;
      rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
        (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
    }
    rep(i,1,n) rank[sa[i]] = i;
    for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
      for (k && k--, j = sa[rank[i] - 1];
          s[i + k] == s[j + k]; k++);
  }
};

const int N = 200100;
int sz[N],p[N];
const int K = 506;
const int M = 998244353;
int k;
ll dp[K+10];
void add(int x){
  if(!x)return;
  for(int i=k;i>=1;i--){
    dp[i] = (dp[i] + x*(ll)dp[i-1])%M;
    if(dp[i]<0)dp[i]+=M;
  }
}
void dec(int x){
  if(!x)return;
  for(int i=1;i<=k;i++){
    dp[i] = (dp[i] - x*(ll)dp[i-1])%M;
    if(dp[i]<0)dp[i]+=M;
  }
}


int f(int x){return p[x]=(p[x]==x?x:f(p[x]));}
void join(int a,int b){
  a=f(a),b=f(b);
  if(a==b)return;
  if(sz[a] > sz[b])swap(a,b);
  dec(sz[a]);
  dec(sz[b]);
  add(sz[a] + sz[b]);
  sz[b]+=sz[a];

  p[a] = b;
}

int rev[N];
vi pos[N];
int res[N];
int32_t main(){
  fastio;
  int t;
  cin >> t;
  while(t--){
    string s;
    cin>>s>>k;
    rep(i,0,K)dp[i]=0;
    dp[0]=1;
    int n = sz(s);
    
    if(n == 1){
      if(k==1)cout<<1<<endl;
      else cout << 0 << endl;
      continue;
    }
    SuffixArray sa(s);
    rep(i,0,n+1)pos[i].clear();
    for(int i=0;i<=n;i++){
      sz[i]=0,p[i]=i;
      rev[sa.sa[i]] = i;
      if(sa.lcp[i]){
        pos[sa.lcp[i]].pb(i);
      }
      
    }

    for(int i=n-1;i>=0;i--){
      int a = rev[n-1-i];
      
      dec(sz[f(a)]);
      sz[f(a)]++;
      add(sz[f(a)]);
      
      for(int p : pos[i+1]){
        join(p,p-1);
      }
      pos[i+1].clear();
      res[i+1] = dp[k];
    }
    int f=1;
    for(int i=1;i<=k;i++)
      f=1ll*f*i%M;
    for(int i=1;i<=n;i++){

      ll r = res[i] * f%M;
      ll D = exp(n-i+1,k,M);
      D = exp(D,M-2,M);
      r = r * D%M;
      r = mod(r,M);
      cout << r<<" \n"[i==n];
    }

  }
  
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}