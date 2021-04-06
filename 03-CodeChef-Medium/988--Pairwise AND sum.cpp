// Hail god Yato
 
#include <bits/stdc++.h> 
using namespace std;
 
#define hs ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
typedef long long ll;
const ll MOD = 1000000007;
const ll INF = 1e18;
const ll MAX = 100001;
//
//
#define int ll
void solve(){
    int n;
    cin>>n;
    vector<ll> vec(n);
    for(int i = 0; i < n; i++)
        cin>>vec[i];

    int bits[50] = {0};
    for(int num : vec){
        int idx = 0;
        while(num){
            bits[idx] += (num&1);
            ++idx;
            num >>= 1;
        }
    }
    ll ans = 0;
    for(int i = 0; i < 50; i++){
        ans += (bits[i]*(bits[i] - 1))/2*(1<<i);
    }
    cout<<ans;
}
signed main(){ 
        hs;
        ll t;
        t=1;
        // cin>>t;
        for (int i=1; i<=t; i++){
                //cout<<"Case #"<<i<<": ";
                solve();
         }
        return 0; 
}