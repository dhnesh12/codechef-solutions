#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include<cstdio>
#include <cstdlib>
#include<queue>
#include<cmath>
#include<algorithm>
#include<set>
#include <vector>
#include <map>
#include <set>
#include <bitset>
#include <queue>
#include <stack>
#include <sstream>
#include <cstring>
#include <numeric>
#include <ctime>
#include <cassert>
#define sqrt(x) sqrt(abs(x))
#define unq(x) (x.resize(unique(all(x)) - x.begin()))
#define spc(i,n) " \n"[i == n - 1]
#define next next239
#define prev prev239
#define BIT(x, i) ((x >> i) & 1)
#define ff first
#define re return
#define se second
#define pb push_back
#define all (x).begin(), (x).end()
#define f4(x) ((int) (x).size())
#define rep1(i, n) for (int i = 0; i < (n); i++)
#define rrep(i, n) for (int i = (n) - 1; i >= 0; i--)
#define y0 y32479
#define y1 y95874
#define fill(x, y) memset(x, y, sizeof(x))
#define sqr(x) ((x) * (x))
#define sqrt(x) sqrt(abs(x))
#define unq(x) (x.resize(unique(all(x)) - x.begin()))
#define spc(i,n) " \n"[i == n - 1]
#define next next239
#define prev prev239
#define BIT(x, i) ((x >> i) & 1)
#define nn 100100
#define mt make_tuple
#define mp make_pair
#define ll long long int
#define db double
#define ldb long double
#define inf 200000ll
#define logn 20
#define mod1 mod
#define mod2 100000009ll
#define nullp mp(-1,-1)
#define set0(a) memset(a,0,sizeof a)
#define init(a) memset(a,-1,sizeof a)
#define cmp 1e-16
#define input1(a) long long int a;cin>>a;
#define input2(p,q,r) long p,q,r;cin>>p>>q>>r;
#define input3(i,a) for(long long int i=a;i<=1e18;i++)
#define input4(i,p)for(int i=0;i<p.length();i++)
#define vll vector<ll>
#define aLL(x) (x).begin(), (x).end()
#define sZ(x) ((int)(x).size())
#define getx 
#define putx putchar_unlocked
#define in(n) scanf("%d",&n)
#define inl(n) scanf("%lld",&n)
#define outl(n) printf("%lld",n);
#define el putchar('\n')
#define sp putchar(' ')
#define fin  cin.ignore(numeric_limits<streamsize>::max(),'\n')
#define fout cout.flush()
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
#define ldb long double
#define db double
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
#define mldb map<ldb,ldb>
#define umll unordered_map<ll,ll>
#define sll set<ll>
#define usll unordered_set<ll>
#define sfor(i,azz,bzz) for (ll i = (azz); i <= (bzz); ++i)
#define rfor(i,bzz,azz) for (ll i = (bzz); i >= (azz); --i)
#define sim template < class c
#define ris return * this
#define mod 998244353
#define M2 998244353
#define ld long double
#define pll pair<ll,ll>
#define inf 200000ll
#define nn 100100
#define fl(i,a,b) for(ll i=a;i<b;i++)
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define vll vector<ll>
#define ldb long double
#define y0 y32479
#define y1 y95874
#define next next239
#define prev prev239
#define BIT(x, i) ((x >> i) & 1)
#define spc(i,n) " \n"[i == n - 1]
using namespace std;
using namespace __gnu_pbds;
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
  *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
 
#define shandom_ruffle random_shuffle
#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
    template <typename Arg1>
    void __f(const char* name, Arg1&& arg1){
        cout << name << " : " << arg1 << endl;
    }
    template <typename Arg1, typename... Args>
    void __f(const char* names, Arg1&& arg1, Args&&... args){
        const char* comma = strchr(names + 1, ','); cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
    }
#else
#define trace(...)
#endif
typedef pair<int,int> pii;
typedef pair<long long ,int> pli;
typedef pair<int,long long > pil;
typedef pair<long double,long double> pdd;
typedef double D;
typedef long double LD;
template<class T> T abs(T x) { return x > 0 ? x : -x;}
map<pair<long long,long long>,long long > mapp;
map<pair<long long,long long>,long long > np;
map<pair<long long,long long>,bool > con;
map<pair<long long,long long>,bool> ne;
template<class T>
using max_pq = priority_queue<T>;
template<class T>
using min_pq = priority_queue<T,vector<T>,greater<T>>;
template<class T> T gcd(T a,T b){return (b==0)?a:gcd(b,a%b);}


const ldb pi=3.141592653589793238462643383;

const int MAXN = (int)((1e5) + 10);
const int Maxm = 100005;
long long t;
long long x[600000];
long long y[600000];
long double s[600000];
long long cl[600000];
long long cs[600000];
long long c,d;
long long orient(long long i,long long j,long long k) {
    return (y[j]-y[i])*(x[k]-x[i])-(x[j]-x[i])*(y[k]-y[i]);
}
bool cmap(long long g,long long h) {
    //cout<<c<<" "<<d<<" "<<g<<" "<<" "<<h<<" "<<orient(d,c,g)<<" "<<orient(d,c,h)<<endl;
    return (orient(c,g,h)<0);
}
vector<long long> nei[600000];
vector<long long> top;
vector<long long> triangle[600000];
vector<long long> tree[600000];
vector<long long> ctree[600000];
vector<pair<int,pair<int,int> > > planes;
vector<pair<double,int > > planes2;
vector<vector<int> > save(400000); 
vector<int> memo(400000);
vector<int> last(400000);
vector<int> used(400000);
bool vis[600000];
long long cf[3][200000];
bool cen[600000];
vector<long long> mem[600000];
long long ch[600000];
stack<int> st;
stack<int> dt;
int par[200000];
bool check_triangles() {
  for(int i=0;i<c;i++) {
    cerr<<i<<" "<<c<<endl;
    for(int j=0;j<i;j++) {
      if(orient(triangle[j][0],triangle[i][0],triangle[i][1])<0 && orient(triangle[j][1],triangle[i][0],triangle[i][1])>0) return false;
      if(orient(triangle[j][0],triangle[i][0],triangle[i][1])>0 && orient(triangle[j][1],triangle[i][0],triangle[i][1])<0) return false;
      if(orient(triangle[j][1],triangle[i][0],triangle[i][1])<0 && orient(triangle[j][2],triangle[i][0],triangle[i][1])>0) return false;
      if(orient(triangle[j][1],triangle[i][0],triangle[i][1])>0 && orient(triangle[j][2],triangle[i][0],triangle[i][1])<0) return false;
      if(orient(triangle[j][2],triangle[i][0],triangle[i][1])<0 && orient(triangle[j][0],triangle[i][0],triangle[i][1])>0) return false;
      if(orient(triangle[j][2],triangle[i][0],triangle[i][1])>0 && orient(triangle[j][0],triangle[i][0],triangle[i][1])<0) return false;
      if(orient(triangle[j][0],triangle[i][1],triangle[i][2])<0 && orient(triangle[j][1],triangle[i][1],triangle[i][2])>0) return false;
      if(orient(triangle[j][0],triangle[i][1],triangle[i][2])>0 && orient(triangle[j][1],triangle[i][1],triangle[i][2])<0) return false;
      if(orient(triangle[j][1],triangle[i][1],triangle[i][2])<0 && orient(triangle[j][2],triangle[i][1],triangle[i][2])>0) return false;
      if(orient(triangle[j][1],triangle[i][1],triangle[i][2])>0 && orient(triangle[j][2],triangle[i][1],triangle[i][2])<0) return false;
      if(orient(triangle[j][2],triangle[i][1],triangle[i][2])<0 && orient(triangle[j][0],triangle[i][1],triangle[i][2])>0) return false;
      if(orient(triangle[j][2],triangle[i][1],triangle[i][2])>0 && orient(triangle[j][0],triangle[i][1],triangle[i][2])<0) return false;
      if(orient(triangle[j][0],triangle[i][2],triangle[i][0])<0 && orient(triangle[j][1],triangle[i][2],triangle[i][0])>0) return false;
      if(orient(triangle[j][0],triangle[i][2],triangle[i][0])>0 && orient(triangle[j][1],triangle[i][2],triangle[i][0])<0) return false;
      if(orient(triangle[j][1],triangle[i][2],triangle[i][0])<0 && orient(triangle[j][2],triangle[i][2],triangle[i][0])>0) return false;
      if(orient(triangle[j][1],triangle[i][2],triangle[i][0])>0 && orient(triangle[j][2],triangle[i][2],triangle[i][0])<0) return false;
      if(orient(triangle[j][2],triangle[i][2],triangle[i][0])<0 && orient(triangle[j][0],triangle[i][2],triangle[i][0])>0) return false;
      if(orient(triangle[j][2],triangle[i][2],triangle[i][0])>0 && orient(triangle[j][0],triangle[i][2],triangle[i][0])<0) return false;
    }
  }
  return true;
}
int gcd(int a,int b)
 { 
  if (a == 0) 
    return b; 
  return gcd(b%a, a);
}

int min(int a,int b)
{
  if(a<b) 
    return a; 
  else return b;}  
bool isPrime(int N)
{ 
  for(int i=2;i*i<=N;++i)
    {
      if(N%i==0) 
        return false;
    }
    return true;
  }
int cbrt(int x)
{ 
  int lo=1,hi=min(2000000ll,x);
  while(hi-lo>1)
    {
      int mid=(lo+hi)/2;
      if(mid*mid*mid<x){lo=mid;
      }
      else hi=mid;
    }
    if(hi*hi*hi<=x) 
      return hi;
    else return lo;
  } 
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
const int nax =  (int)(5*1e5);

vector<int>adj[nn];
ll dp[nn][2][2];

int dfs(int node,int par)
{
    if(adj[node].size()==1 && node!=par)
    {
        dp[node][0][1]=dp[node][0][0]=dp[node][1][1]=inf;
        dp[node][1][0]=1;
        return 1;
    }
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
            dp[node][i][j]=0;
    }
    ll t1=inf,t2=inf,t3=inf,t4=inf;
    int h=inf;
    for(auto& u:adj[node])
    {
        if(u==par)
            continue;
        h=min(h,dfs(u,node));
        ll tmp=min(dp[u][1][0],dp[u][1][1]);
        ll tmp2=min(tmp,min(dp[u][0][1],dp[u][0][0]));
        dp[node][0][0]+=min(tmp,dp[u][0][0]);
        dp[node][0][1]+=min(tmp,dp[u][0][0]);
        dp[node][1][0]+=tmp2;
        dp[node][1][1]+=tmp2;
        if(tmp-min(tmp,dp[u][0][0])<t2)
        {
            t2=tmp-min(tmp,dp[u][0][0]);
        }
        if(t2<t1)
            swap(t1,t2);
        t3=min(t3,min(dp[u][0][1],dp[u][0][0])-tmp2);
        t4=min(t4,tmp-tmp2);
    }
    assert(t2>=t1);
    dp[node][0][1]+=t1;
    dp[node][0][0]+=(t1+t2);
    dp[node][1][0]+=t3+1;
    dp[node][1][1]+=t4+1;
    if(h==1)
        dp[node][0][0]=inf;
    return h+1;
}

int slide(string s, int size,int no,int nz,vector<int> l,int so,int se,int n)
{
  set<pair<pair<int,int>,pair<int,int>>> sew;
  sew.insert(make_pair(make_pair(no,nz),make_pair(so,se)));
  for(int i=size;i<n;i++)
  {
    if(s[i-size]=='1')
    {
      l.erase(l.begin());
      int t=se;
      se=so;
      so=t;
      no-=1;
    }
    else
    {
      nz-=1;
      l[0]-=1;
      se-=1;
    }
    if(s[i]=='1')
    {
      no+=1;
      l.push_back(0);
    }
    else
    {
      nz+=1;
      l[l.size()-1]+=1;
      if(l.size()%2==1)
      {
        se+=1;
      }
      else
      {
        so+=1;
      }
    }
    sew.insert(make_pair(make_pair(no,nz),make_pair(so,se)));
  }
  return sew.size();
}
int substring(string s,int n,int len)
{
  vector<int> l;
  int rt=0,no=0,nz=0,so=0,se=0,cur=0;
  for(int i=0;i<n;i++)
  {
    if (s[i]=='0')
    {
      if (cur%2==0)
        se+=1;
      else
        so+=1;
      rt+=1;
      nz+=1;
    }
    else
    {
      l.push_back(rt);
      rt=0;
            cur+=1;
            no+=1;
        }
    }
    l.push_back(rt);
    return slide(s,n,no,nz,l,so,se,len);
}

int main() {
    int i, k, u, ncase;
    scanf("%*d");
    for(scanf("%d", &u); u; u--) scanf("%*d");
    for(scanf("%d", &u); u; u--) scanf("%*d");
    scanf("%d", &ncase);
    while(ncase--) {
        for(scanf("%d%*d", &k), u=k*3; u; u--) scanf("%*d");
        printf("-1\n");
        for(i=0; i<k; i++) printf(i==k-1? "0\n":"0 ");
        fflush(stdout);
    }
    return 0;
}

 
 
