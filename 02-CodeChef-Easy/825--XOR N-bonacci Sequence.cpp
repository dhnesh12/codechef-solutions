//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma,sse,sse2,sse3,sse4")
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define int           long long
#define pb            push_back
#define ppb           pop_back
#define si            set <int>
#define endl          '\n'
#define fr            first
#define sc            second
#define mii           map<int,int>
#define msi           map<string,int>
#define mis           map<int,string>
#define rep(i,a,b)    for(int  i=a;i<b;i++)
#define all(v)        v.begin(),v.end()
#define pii           pair<int,int>
#define vi            vector<int>
#define vii           vector<pair<int,int>>
#define vs            vector<string>
#define sz(x)         (int)x.size()
#define rt            return
#define M             1000000007
#define bs            binary_search
#define rev(a)        reverse(aint(a));
#define sp(n)         setprecision(n)
#define spl           " "
#define arr(a,n)      rep(i,0,n) cin>>a[i]
#define mod           998244353
#define time          cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
#define INF           1ll<<31
#define fio           freopen("input.txt","r",stdin) ; freopen("output.txt","w",stdout); 
#define rt            return
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif
/*---------------------------------------------*/
//const int fx[]={+1,-1,+0,+0};
//const int fy[]={+0,+0,+1,-1};
//const int fx[]={+0,+0,+1,-1,-1,+1,-1,+1};
//const int fy[]={-1,+1,+0,+0,+1,+1,-1,-1};
//const int fx[]={-2, -2, -1, -1,  1,  1,  2,  2};
//const int fy[]={-1,  1, -2,  2, -2,  2, -1,  1};
/*------------------------------------------------*/

/*
int f[1000000];
void calc_fac()
{
    f[0]=1;
    f[1]=1;
    for(int i=2;i<1000000;i++) {
        f[i]=(f[i-1]*i)%M;
    }
}
int bpow(int a, int b, int mm = M)
{
    int res = 1;

    while(b)
    {
        if(b & 1)
            res = (res * a) % mm;
        a = (a * a) % mm;

        b >>= 1;
    }

    return res;
}
int modInverse(int A,int mm)
{
    return bpow(A,mm-2,mm);
}

int nCrModPFermat(int n, int r, int p)
{
    if (r==0)
        return 1;
    if(n<r) return 0;
    return (f[n]*modInverse(f[r],p)%p*modInverse(f[n-r], p)%p)%p;
}
*/


void solve()
{
   int n,q;
   cin>>n>>q;
   vector<int> a;
   int xr=0;
   for(int i=0;i<n;i++){
    int x;
    cin>>x;
    xr^=x;
    a.pb(x);
   }
   a.pb(xr);
   //debug(a);
   rep(i,1,sz(a))
   a[i]^=a[i-1];
   //debug(a);
   while(q--){
    int k;
    cin>>k;
    int x=(k-1)%sz(a);
    cout<<a[x]<<"\n";
   }

}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t=1;
     //cin>>t;
    while(t--) solve();

}
