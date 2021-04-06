#include <bits/stdc++.h>
using namespace std;
//#include "testlib.h"
#define ff first
#define ss second
#define all(v) v.begin(),v.end()
#define int long long
#define ll long long
#define M 1000000007
#define MM 998244353
#define inputarr(a,n) for(int i=0;i<n;++i) cin>>a[i]
#define GCD(m,n) __gcd(m,n)
#define LCM(m,n) m*(n/GCD(m,n))
#define mii  map<ll ,ll >
#define msi  map<string,ll >
#define rep(a,b)    for(ll i=a;i<b;i++)
#define rep0(n)    for(ll i=0;i<n;i++)
#define repi(i,a,b) for(ll i=a;i<b;i++)
#define pb push_back
#define vi vector<ll>
#define vs vector<string>
#define ppb pop_back
#define endl '\n'
#define asdf ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define r0 return 0;
#define FORD(i, a, b) for (int i = (int) (a); i >= (int) (b); --i)
#define inputoutput freopen("input.txt", "r", stdin);freopen("output.txt", "w", stdout);
#define Set(a, s) (a, s, sizeof (a))
#define FOR repi
#define vii vector<pii>
#define pii pair<int,int>
#define REVERSE(v) reverse(all(v))
#define trav(a, x) for(auto& a : x)
#define display(x) trav(a,x) cout<<a<<" ";cout<<endl
#define debug cerr<<"bhau"<<endl
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
    std::cerr << name << " : " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
    const char* comma = strchr(names + 1, ',');std::cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
template<typename T, typename U> static inline void amin(T &x, U y) 
{ 
    if (y < x) 
        x = y; 
}
template<typename T, typename U> static inline void amax(T &x, U y) 
{ 
    if (x < y) 
        x = y; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll max(ll a, ll b) { return (a > b)? a : b;}
int min(int a, int b) { return (a < b)? a : b;} 


int solve(){

     string a,b;
    cin>>a>>b;
    int n = a.size();
    assert(n==b.size());

    int dp[n+1][3][3];
    memset(dp,0,sizeof(dp));
    dp[0][0][0] = 1;

    for(int i=1;i<n;i++){
        if(a[i-1] == '1' && b[i-1]=='1'){

            for(int j=0;j<3;j++){
                for(int k=0;k<3;k++){
                    if(j==1 || k==1) continue;
                    dp[i][0][0] = (dp[i][0][0] + dp[i-1][j][k]);

                }
            }                

            dp[i][0][0] *= 2;
            dp[i][0][0] %= M;
            // trace(dp[i][0][0]);


        }
        else if(a[i-1]=='2' && b[i-1]=='2'){
            dp[i][1][1] = 2 * (dp[i-1][0][0]) %M;
            dp[i][1][2] = 2 * (dp[i-1][0][1]) %M;
            dp[i][2][1] = 2 * (dp[i-1][1][0]) %M;
            dp[i][2][2] = 2 * (dp[i-1][1][1]) %M;
        }
        else{
            for(int j=1;j<=2;j++){
                for(int k=0;k<=2;k++){
                    if(k==1) continue;
                    dp[i][0][j] += dp[i-1][k][j-1];
                }
                dp[i][0][j] %= M;
                // trace(1,i,j,dp[i][0][j]);
            }

            for(int j=1;j<=2;j++){

                for(int k=0;k<=2;k++){

                    if(k==1) continue;
                    
                    dp[i][j][0] += dp[i-1][j-1][k];
                }
                dp[i][j][0] %= M;
                // trace(2,i,j,dp[i][j][0]);

            }
        }
    }

    cout<<(2 * dp[n-1][0][0]) %M <<endl;



    return 0;
}
signed main(){
    asdf
    int t=1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
