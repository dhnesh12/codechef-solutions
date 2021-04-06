#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef pair<int,int> p32;
typedef pair<ll,ll> p64;
typedef pair<double,double> pdd;
typedef vector<ll> v64;
typedef vector<int> v32;
typedef vector<vector<int> > vv32;
typedef vector<vector<ll> > vv64;
typedef vector<vector<p64> > vvp64;
typedef vector<p64> vp64;
typedef vector<p32> vp32;
double eps = 1e-12;
#define mod 1000000007
#define loop(i,s,e) for(ll i = (s); i <=(e); i++)
#define looprev(i,s,e) for(ll i = s; i >=e; i--)
#define logarr(arr,a,b) for(ll i=a;i<=b;i++) cout<<arr[i]<<" ";cout<<"\n"
#define ln "\n"
#define dbg(x) cout<<#x<<" = "<<x<<ln
#define mp make_pair
#define pb push_back
#define ump unordered_map
#define fi first
#define se second
#define INF 2e18
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())
 

void file_i_o()
{
ios_base::sync_with_stdio(false);
cin.tie(NULL);
cout.tie(NULL);
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
#endif
}

ll exp(ll a,ll b)
{
    if(b==0)
    return 1;

    ll temp=exp(a,b/2)%mod;

    if(b%2==1)
    return (((temp*temp)%mod)*a)%mod;

    return (temp*temp)%mod;
}
int main()
{
clock_t begin=clock();
    file_i_o();
    v64 fac(100005);
    fac[0]=1;
    fac[1]=1;

    loop(i,2,100004)
    {
        fac[i]=(i*fac[i-1])%mod;
    }

    v64 facmod(100005);
    facmod[0]=1;
    facmod[1]=1;

    loop(i,2,100004)
    {
        facmod[i]=(facmod[i-1]*(exp(i,mod-2))%mod);
    }
    ll t;
    cin >> t;
    while(t--){
        ll n,k;
        cin>>n>>k;
        v64 a(n);
       ll zero=0;
        loop(i,0,n-1)
        {
            cin>>a[i];
            if(a[i]==0)
            zero++;
        }
      ll sum=0;
      n-=zero;
        // if(zero==0)
        // {
               
        // }
       // else
        {
             for(ll i=0;i<min(n+1,k+1);i++)
             {
                 if(zero || (k+i)%2==0)
                 {
                     ll temp=fac[n];
                    //  cout<<i<<" "<<temp<<"\n";
                     temp*=exp(fac[i],mod-2);
                    //  cout<<"inverse"<<" "<<exp(fac[i],mod-2)<<'\n';
                     temp%=mod;
                     temp*=exp(fac[n-i],mod-2);
                                        //   cout<<"inverse2"<<" "<<exp(fac[n-i],mod-2)<<'\n';

                     temp%=mod;
                     sum+=temp;;
                    //  cout<<sum<<endl;
                    //  sum=sum+(fac[n])*(facmod[n-i]*facmod[i])%mod;
                     sum%=mod;
                 }
             }
             cout<<sum<<"\n";
        }
        


    }
#ifndef ONLINE_JUDGE
clock_t end=clock();
 cout<<"\n\n Executed In: "<<double(end-begin)/CLOCKS_PER_SEC<<"\n";
 #endif
    return 0;
}