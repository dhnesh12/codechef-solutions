#include <bits/stdc++.h>
#define ll long long
#define rep(i, n) for (ll i = 0; i < n; i++)
#define repr(i, a, b) for (ll i = a; i < b; i++)
#define all(a) a.begin(), a.end()
#define w(tc)  \
    ll tc;     \
    cin >> tc; \
    while (tc--)
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);
#define PI 3.14159265359
static const int INF = 1e9 + 7;
using namespace std;
int main(){
    ll t;
    cin>>t;
    while(t--){
        ll n,m;
        cin>>n>>m;
        ll a[n][m], b[n][m];
        rep(i,n){
            rep(j,m){
                char ch;
                cin>>ch;
                a[i][j]=ch-'0';
                }}
        rep(i,n){
            rep(j,m){
                char ch;
                cin>>ch;
                b[i][j]=ch-'0';
                }}
        ll ans=INT_MAX;
        ll cost=0;
        for(ll dr=-(n-1);dr<n;dr++){
            for(ll dc=-(m-1);dc<m;dc++){
                for(ll i=0;i<n;i++){
                    for(ll j=0;j<m;j++){
                        if(i+dr<0||j+dc<0||i+dr>=n||j+dc>=m){
                            if(a[i][j]==1){
                                cost++;
                                continue;
                            }}
                        else{
                            if(a[i][j]!=b[i+dr][j+dc]){
                                cost++;
                            }}}}
                ans=min(ans,cost);
                cost=0;
            }}
        cout<<ans<<endl;
    }}