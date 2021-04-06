#include <bits/stdc++.h>
using namespace std;
#define N 200005
#define pb push_back
#define all(f) f.begin(),f.end()
#define nl "\n"
#define debug(g) cout<<#g<<" : "<<g<<nl
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> pii;
const ll mod=(1e9)+7;
const double pi=acos(-1);
ll gcd(ll a,ll b){return (b==0)?a:gcd(b,a%b);}
ll lcm(ll a,ll b){return (a*b)/gcd(a,b);}
void solve(){
    int n,i,j,x=0,y=0,a[1001][2],ans;
    string s;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>s;
        a[i][0]=a[i][1]=0;
        for(j=0;j<n;j++){
            if((j+1)<=(n/2)){
                if(s[j]=='1')
                a[i][0]++;
            }
            else{
                if(s[j]=='1')
                a[i][1]++;
            }
        }
        x+=a[i][0];
        y+=a[i][1];
    }
    ans=abs(x-y);
    for(i=1;i<=n;i++){
        ans=min(ans,abs((x-a[i][0]+a[i][1])-(y-a[i][1]+a[i][0])));
    }
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
    while(t--){
        solve();
    }
    return 0;
}