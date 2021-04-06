#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ul ;
typedef long long ll ;
typedef pair<ll, ll>  p ;
typedef pair< p , ll > edge ;
//#define Euc_D(x1,y1,x2,y2) (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)
#define vi vector< ll >
#define vl vector< ll >
#define sci(x) ll x; scanf("%d",&x)
#define scu(x) ul x ; scanf("%llu", &x)
#define scl(x) ll x ; scanf("%lld", &x)
#define pr(x) prllf("%llu", x)
#define rep(i , a , b , n) for(ll i = a; i < b ; i += n )
#define f first
// #define s second
#define pb push_back
#define mp make_pair
#define tc(t) scu(t); while ( t-- )
#define nl '\n'
#define MOD 1000000007
// just type fast; at the beginning to do both these
#define fast ios::sync_with_stdio(false); cin.tie(0)
#define inf 0x3f3f
ll n,k;
ll B[200000];
ll ans(ll l, ll r){
    if(l>=r)
        return 0;
    ll m = (l+r)/2;
    for(int i=m+1;i<=r;i++){
        if(B[i]<B[m]){
            m = i;
        }
    }
    for(int i=m-1;i>=l;i--){
        if(B[i]<B[m]){
            m = i;
        }
    }
    ll val = ans(l,m-1)+ans(m+1,r);
    map<ll,ll>M;
    ll s = 0;
    for(int i=m-1;i>=l;i--){
        s = (s+B[i])%k;
        if(s==0)
            val++;
        M[s]++;
    }
    s = 0;
    for(int i=m+1;i<=r;i++){
        s = (s+B[i])%k;
        if(s==0)
            val++;
        val += M[(k-s)%k];
    }
    return val;
}
int main()
{
   // fast;
    ll T;
    //cin>>T;
    T = 1;
    for(ll t=1;t<=T;t++){
            //ll n,k;
            cin>>n>>k;
            //ll B[n];
            for(int i=0;i<n;i++)
                cin>>B[i];

            cout<<ans(0,n-1)<<"\n";

    }
    return 0;
}
