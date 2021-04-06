#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
 
#define ff              first
#define ss              second
#define sq(a)           (a*a)
#define lc(x)           (x<<1)
#define rc(x)           (x<<1)|1
#define fr(a,b,c)       for(int i=a;i<b;i+=c)
#define frj(a,b,c)      for(int j=a;j<b;j+=c)
#define fl(a,b,c)       for(int i=a;i>=b;i-=c)
#define int             long long
#define ld              long double
#define ip(x)           int x;cin>>x
#define pb              push_back
#define mp              make_pair
#define mt              make_tuple
#define ub              upper_bound
#define lb              lower_bound
#define pii             pair<int,int>
#define vi              vector<int>
#define mii             map<int,int>
#define pos(pqrs,x)     pqrs.order_of_key(x)
#define idx(pqrs,x)     *pqrs.find_by_order(x)
#define pqb             priority_queue<int>
#define pqs             priority_queue<int,vi,greater<int> >
#define setbits(x)      __builtin_popcountll(x)
#define N               1000005
#define mod             1000000007
#define inf             (int)9e18
#define ps(x,y)         fixed<<setprecision(y)<<x
#define mk(arr,n,type)  type *arr=new type[n];
#define range(a,b)		substr(a,b-a+1)
#define w(x)            int x; cin>>x; while(x--)
#define trace(x) 		cerr<<#x<<": "<<x<<" "<<endl;
#define FIO             ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
mt19937                 rng(chrono::steady_clock::now().time_since_epoch().count());

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

vi v(100005);

int power(int x, int y)
{
    if (y == 0) return 1;
    int p=power(x,y/2)%mod;
    p = (p*p)%mod;
 
    return (!(y%2))?p:(x*p)%mod;
}

int modInverse(int a)
{
    return power(a, mod-2);
}

int32_t main()
{
    FIO; v[0]=1;
    fr(1,v.size(),1)v[i]=(v[i-1]*i)%mod;
    w(t)
    {    
        ip(n);ip(k);
        if(n<k)cout<<1<<endl;
        else
        {
            int ans = 1;
            fr(1,n/k+1,1)
            {
                //cout<<v[n-i*k+i]<<' '<<modInverse(v[i])<<' '<<modInverse(v[n-i*k])<<endl;
                (ans+=((v[n-i*k+i]*modInverse(v[i]))%mod)*modInverse(v[n-i*k]))%=mod;
            }
            cout<<ans<<endl;
        }
    }    
    return 0;
}