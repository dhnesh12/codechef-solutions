#include <bits/stdc++.h>
using namespace std;
#define N 100001
#define pb push_back
#define all(x) x.begin(),x.end()
#define nl "\n"
#define debug(v) cout<<#v<<" : "<<v<<nl
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
const ll mod=(1e9)+7;
const double pi=acos(-1);
ll gcd(ll a,ll b){return (b==0)?a:gcd(b,a%b);}
ll lcm(ll a,ll b){return (a*b)/gcd(a,b);}
ll fib[N];
void fibo(){
    ll i,n=100000;
    fib[1]=0;
    fib[2]=1;
    for(i=3;i<=n;i++){
        fib[i]=((fib[i-1]%mod)+(fib[i-2]%mod))%mod;
    }
}
void solve(){
    ll i,n,m,num,sa=0,sb=0,ans,ans1,ans2;
    cin>>m>>n;
    for(i=0;i<m;i++){
        cin>>num;
        sa=((sa%mod)+(num%mod))%mod;
    }
    for(i=0;i<m;i++){
        cin>>num;
        sb=((sb%mod)+(num%mod))%mod;
    }
    if(n==1){
        ans1=((m%mod)*(sa%mod))%mod;
        ans=ans1;
    }
    else{
        ans1=((m%mod)*(fib[n-1]%mod))%mod;
        ans1=((ans1%mod)*(sa%mod))%mod;
        ans2=((m%mod)*(fib[n]%mod))%mod;
        ans2=((ans2%mod)*(sb%mod))%mod;
        ans=ans1+ans2;
    }
    ans=ans%mod;
    // debug(ans1);
    // debug(ans2);
    cout<<ans<<nl;
}
int main(){
    //fast io
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    #ifndef ONLINE_JUDGE 
        freopen("input.txt", "r", stdin); 
        freopen("output.txt", "w", stdout); 
    #endif
    ll t=1;
    cin>>t;
    fibo();
    while(t--){
        solve();
    }
    return 0;
}