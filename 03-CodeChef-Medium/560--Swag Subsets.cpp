
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
//#define int long long int
typedef complex<long double> cd;
const long double pi=acos(-1);
typedef double db;
typedef long double ldb;
typedef pair <int, int> pii;
typedef pair <db, db> pdd;
typedef vector<int> vi;
typedef vector<vector<int> > matrix;

#define m1 make_pair
#define pb push_back
#define flush fflush(stdout)
#define IOS std::ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define reset(x,v) memset(x,v,sizeof(x))

#define fi first
#define se second
#define endl "\n"
#define debug(x) (cerr << #x << ": " << x << "\n")
#define setbits(x) __builtin_popcount(x)
#define setbitsll(x) __builtin_popcountll(x)
#define all(x) x.begin(),x.end()
#define pii pair<int,int>

inline ll gcd(ll a,ll b){if(a==0) return b;return gcd(b%a,a);}
inline ll power(ll a,ll n,ll m){if(n==0)return 1;ll p=power(a,n/2,m);p=(p%m*p%m)%m;if(n%2) return (p%m*a%m)%m;else return p;}
const double EPS = 1e-9;
const ll MOD =998244353;
const ll hell=1000000007;
const int INF = 1e8;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
template<typename T>
using ordered_set=tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 rng(seed);

double startTime;
double getCurrentTime() {
    return ((double)clock() - startTime) / CLOCKS_PER_SEC;
}


const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };

const int N=200005;
ll st[4*N];int lazy[4*N];
int bit[N+1];ll pr[N+1];

void update(int i,int l,int r,int qs,int qe)
{
    if(lazy[i])
    {
        st[i]=(st[i]*pr[lazy[i]])%hell;
        if(l!=r)
        {
            lazy[2*i+1]=(lazy[2*i+1]+lazy[i]);
            lazy[2*i+2]=(lazy[2*i+2]+lazy[i]);
        }
        lazy[i]=0;
    }
    if(qs>r||qe<l)
        return;
    if(qs<=l&&qe>=r)
    {
        st[i]=(st[i]*2)%hell;
        if(l!=r)
        {
            lazy[2*i+1]=(lazy[2*i+1]+1);
            lazy[2*i+2]=(lazy[2*i+2]+1);
        }
        return;
    }
    int m=(l+r)/2;
    update(2*i+1,l,m,qs,qe);
    update(2*i+2,m+1,r,qs,qe);
    st[i]=(st[2*i+1]+st[2*i+2])%hell;
}
void pointupdate(int i,int l,int r,int in,int x)
{
    if(lazy[i] )
    {
        st[i]=(st[i]*pr[lazy[i]])%hell;
        if(l!=r)
        {
            lazy[2*i+1]=(lazy[2*i+1]+lazy[i]);
            lazy[2*i+2]=(lazy[2*i+2]+lazy[i]);
        }
        lazy[i]=0;
    }
    if(in>r||in<l)
        return;
    if(l==r)
    {
        st[i]=(st[i]+x)%hell;
        return;
    }
    int m=(l+r)/2;
    pointupdate(2*i+1,l,m,in,x);
    pointupdate(2*i+2,m+1,r,in,x);
    st[i]=(st[2*i+1]+st[2*i+2])%hell;
}
int query(int i,int l,int r,int qs,int qe)
{
    if(lazy[i])
    {
        st[i]=(st[i]*pr[lazy[i]])%hell;
        if(l!=r)
        {
            lazy[2*i+1]=(lazy[2*i+1]+lazy[i]);
            lazy[2*i+2]=(lazy[2*i+2]+lazy[i]);
        }
        lazy[i]=0;
    }
    if(qs>r||qe<l)
        return 0;
    if(qs<=l&&qe>=r)
        return st[i];
    int m=(l+r)/2;
    return (query(2*i+1,l,m,qs,qe)+query(2*i+2,m+1,r,qs,qe))%hell;
}
int getparent(int i)
{
    return i-(i& -i);
}
int getnext(int i)
{
    return i+(i& -i);
}
void Update(int i,int x)
{
    while(i<=N)
    {
        bit[i]+=x;
        i=getnext(i);
    }
}
int getsum(int r)
{
    int ans=0;
      while(r>0)
      {
          ans+=bit[r];
          r=getparent(r);
      }
    return ans;
}

void solve()
{
    int n;
    cin>>n;
    pair<int,int> a[n];
    for(int i=0;i<=4*n;i++)
    {
        st[i]=0;
        lazy[i]=0;
    }
    for(int i=0;i<n;i++)
        cin>>a[i].fi;
    for(int i=0;i<n;i++)
        cin>>a[i].se;
    map<int,int>mp1;
    for(int i=0;i<n;i++)
    {
        mp1[a[i].se]=1;
    }
    int k=1;
    for(auto it=mp1.begin();it!=mp1.end();it++)
    { it->second= k++;
        
    }
    
    sort(a,a+n);
    int tl=0;
    for(int i=0;i<n;i++)
    {
        
        int z=mp1[a[i].se];
        int x=getsum(z);
        ll S=(pr[x]*a[i].se)%hell;
        Update(z,1);
        pointupdate(0,0,n+1,z,S);
        
        ll Z=query(0,0,n+1,z+1,n+1);
        update(0,0,n+1,z+1,n+1);
        
        Z=(Z+S)%hell;
        Z=(Z*a[i].fi)%hell;
        tl=(tl+Z)%hell;
       
    }
    for(int i=0;i<n;i++)
        Update(mp1[a[i].se],-1);
    cout<<tl<<endl;
    
    
    
}




int32_t main()
{
    IOS;
    pr[0]=1;
    for(int i=1;i<=N;i++)
        pr[i]=(pr[i-1]*2)%hell;
    int t;
    t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}
