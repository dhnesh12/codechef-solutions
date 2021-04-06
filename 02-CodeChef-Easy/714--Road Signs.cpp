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

ll bin(ll a,ll b)
{
    if(b==0)
    return 1;

    ll temp=bin(a,b/2)%mod;
    temp=temp*temp;
    temp%=mod;
    if(b%2==1)
    {
        temp*=a;
        temp%=mod;
    }

    return temp;
}
int main()
{
clock_t begin=clock();
    file_i_o();
    ll t;
    cin >> t;
    while(t--){
        ll k;
        cin>>k;

        cout<<(10*bin(2,k-1))%mod<<"\n";
    }
#ifndef ONLINE_JUDGE
clock_t end=clock();
 cout<<"\n\n Executed In: "<<double(end-begin)/CLOCKS_PER_SEC<<"\n";
 #endif
    return 0;
}